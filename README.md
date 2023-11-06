# 内核_进程通信_Process_Communication  

*20230815*  

Here are the basic mechanisms that Unix systems offer to allow interprocess communication:

* Pipes and FIFOs (named pipes)
* Semaphores
* Messages
* Shared memory regions
* Sockets

Unix系统提供的进程间通信的基本机制：

* 管道和FIFO（命名管道）
* 信号量
* 消息
* 共享内存区
* 套接字

## 管道 Pipes

A pipe is a one-way flow of data between processes; all data written by a process to the pipe is routed by the kernel to another process, which can thus read it.

管道是进程之间的一个单向数据流；一个进程写入管道的所有数据都由内核定向到另一个进程，另一个进程由此就可以从管道中读取数据。

### 使用管道 Using a Pipe

A process creates a new pipe by means of the pipe() system call, which returns a pair of file descriptors; the process may then pass these descriptors to its descendants through fork(), thus sharing the pipe with them.

使用pipe()系统调用来创建一个新管道，这个系统调用返回一对文件描述符；然后进程通过fork()把这两个文件描述符传递给它的子进程，由此与子进程共享管道。

Many Unix systems provide, besides the pipe() system call, two wrapper functions named popen() and pclose() that handle all the dirty work usually done when using pipes.

除了pipe()外，很多Unix系统还提供popen()和pclose()的封装函数用于处理在使用管道的过程中产生的脏工作。

### 管道数据结构 Pipe Data Structures

Once a pipe is created, a process uses the read() and write() VFS system calls to access it. Therefore, for each pipe, the kernel creates an inode object plus two file objects.

只要管道一被创建，进程就可以使用read()和write()这两个VFS系统调用来访问管道，因此，对于每个管道来说，内核都要创建一个索引节点对象和两个文件对象，一个用于读一个用于写。

Besides one inode and two file objects, each pipe has its own set of pipe buffers.

除了索引节点对象和文件对象之外，每个管道还有自己的管道缓冲区。

A pipe buffer is a page frame that contains data written into the pipe and yet to be read.

管道缓冲区是一个单独的页，其中包含了已经写入和等待读出的数据。

#### pipefs特殊文件系统 The pipefs special filesystem

A pipe is implemented as a set of VFS objects, which have no corresponding disk images.

管道是作为一组VFS对象来实现的，因此没有对应的磁盘映像。

### 创建和撤销管道 Creating and Destroying a Pipe

The pipe() system call is serviced by the sys_pipe() function, which in turn invokes the do_pipe() function.

pipe() 系统调用由sys_pipe() 函数处理，后者又会调用 do_pipe() 函数。

do_pipe() performs the following operations:

* Invokes the get_pipe_inode() function, which allocates and initializes an inode object for the pipe in the pipefs filesystem
* Allocates a file object and a file descriptor for the read channel of the pipe, sets the f_flag field of the file object to O_RDONLY, and initializes the f_op field with the address of the read_pipe_fops table 
* Allocates a file object and a file descriptor for the write channel of the pipe, sets the f_flag field of the file object to O_WRONLY, and initializes the f_op field with the address of the write_pipe_fops table 
* Allocates a dentry object and uses it to link the two file objects and the inode object; then inserts the new inode in the pipefs special filesystem
* Returns the two file descriptors to the User Mode process

do_pipe() 函数执行以下操作：

* 调用 get_pipe_inode() 为pipefs 文件系统中的管道分配一个索引节点对象并对其进行初始化
* 为管道的读通道分配一个文件对象和一个文件描述符，并把这个文件对象的 f_flag 字段设置为 O_RDONLY，把 f_op 字段初始化为 read_pipe_fops 表的地址
* 为管道的写通道分配一个文件对象和一个文件描述符，并把这个文件对象的 f_flag 字段设置为 O_WRONLY，把 f_op 字段初始化为 write_pipe_fops 表的地址
* 分配一个目录项对象，并使用它把两个文件对象和索引节点对象连接在一起；然后把新的节点插入pipefs特殊文件系统中
* 把两个文件描述符返回给用户态进程

### 从管道中读取数据 Reading from Pipe

希望从管道中读取数据的进程发出一个read()系统调用，为管道的读端指定一个文件描述符。

内核最终调用与这个文件描述符相关的文件操作表中所找到的read方法。

read方法在read_pipe_fops表中的表项指向pipe_read()函数。

pipe_read()函数执行以下操作：

* 获取索引节点的i_sem信号量
* 确定存放在pipe_inode_info结构nrbufs字段中的管道大小是否为0并确定函数必须返回还是进程在等待时必须被阻塞，直到其他进程向管道中写入一些数据
* 从pipe_inode_info数据结构的curbuf字段得到当前管道缓冲区索引
* 执行管道缓冲区的map方法
* 从管道缓冲区拷贝请求的字节数到用户地址空间
* 执行管道缓冲区的unmap方法
* 更新相应pipe_buffer对象的offset和len字段
* 如果管道缓冲区已空，调用管道缓冲区的release方法释放对应的页框，把pipe_buffer对象的ops字段设置为NULL，增加在pipe_inode_info数据结构的curbuf字段中存放的当前管道缓冲区索引，并减小nrbufs字段中非空管道缓冲区计数器的值
* 如果所有请求字节拷贝完毕，则释放索引节点的i_sem信号量
* 如果还没有把所有请求字节拷贝到用户地址空间，则重新从第三步开始执行
* 管道缓冲区没有剩余字节，但是至少有一个写进程正在休眠且读操作是阻塞的，那么调用wake_up_interruptible_sync()唤醒在管道等待队列中所有睡眠的进程，然后从第二步开始执行

### 向管道中写入数据 Writing into a Pipe

希望向管道中写入数据的进程发出一个write()系统调用，为管道的写端指定一个文件描述符。

内核通过调用适当文件对象的write方法来满足这个请求。

write_pipe_fops表中相应的项指向了pipe_write()函数。

* 获取索引节点的i_sem信号量
* 检查管道是否至少有一个读进程，如果不是，就向当前进程发送一个SIGPIPE信号，释放索引节点信号量并返回-EPIPE值
* 将pipe_inode_info数据结构curbuf和nrbufs字段相加并减一得到最后写入的管道缓冲区索引，如果管道缓冲区有足够空间存放待写字节，就拷入这些数据
* 如果pipe_inode_info数据结构的nrbufs字段等于16，就表明没有空闲管道缓冲区来存放字节，这种情况下如果写操作是非阻塞的，释放索引节点信号量后结束并返回错误码-EAGAIN；如果写操作是阻塞的，调用prepare_to_wait()将当前操作加入管道等待队列，释放索引节点信号量，调用schedule()。一旦唤醒，则调用finish_wait()从等待队列中移出当前操作，重新获得索引节点信号量，递减waiting_writes字段，然后跳回第四步
* 得到第一个空缓冲区的索引
* 除非pipe_inode_info数据结构的tmp_page字段不是NULL，否则从伙伴系统中分配一个页框
* 从用户态地址空间拷贝多大4096个字节到页框
* 更新与管道缓冲区关联的pipe_buffer对象的字段：将page字段设为页框描述符的地址，ops字段设为anon_pipe_buf_ops表的地址，offset字段设为0，len字段设为写入的字节数
* 增加非空管道缓冲区计数器的值
* 如果所有请求的字节还没有写完，跳至第四步

## FIFOs

### 创建并打开FIFO Creating and Opening a FIFO

## System V IPC

### 使用IPC资源 Using an IPC Resource

### ipc()系统调用 The ipc() System Call

### IPC信号量 IPC Semaphores

#### 可取消的信号量操作 Undoable semaphore operations

#### 挂起请求的队列 The queue of pending requests

### IPC消息 IPC Messages

### IPC共享内存 IPC Shared Memory

#### 换出IPC共享内存区的页 Swapping out pages of IPC shared memory regions

#### IPC共享内存区的请求调页 Demand paging for IPC shared memory regions

## POSIX消息队列 POSIX Message Queues
