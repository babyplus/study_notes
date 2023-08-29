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

### 向管道中写入数据 Writing into a Pipe

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