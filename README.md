# 内核_进程_Processes  

*20230727*  

## 进程、轻量级进程和线程 Processes,Lightweight Processes,and Threads

A process is an instance of a program in execution; Each thread represents an execution flow of the process; Linux uses LWP to offer better support for multithreaded applications.

进程是程序执行时的一个实例；每个线程代表进程的一个执行流；轻量级进程是内核对多线程应用提供的支持。

## 进程描述符 Process Descriptor

### 进程状态 Process State

As its name implies, the state field of the process descriptor describes what is currently happening to the process. In the current Linux version, these states are mutually exclusive, and hence exactly one flag of state always is set; the remaining flags are cleared.

* TASK_RUNNING
* TASK_INTERRUPTIBLE
* TASK_UNINTERRUPTIBLE
* TASK_STOP
* TASK_TRACED
* EXIT_ZOMBIE
* EXIT_DEAD

进程描述符中的state字段描述了进程当前所处的状态（互斥）。

* 可运行状态
* 可中断的等待状态
* 不可中断的等待状态
* 暂停状态
* 跟踪状态
* 僵死状态
* 僵死撤销状态

### 标识一个进程 Identifying a Process

As a general rule, each execution context that can be independently scheduled must have its own process descriptor; therefore, even lightweight processes, which share a large portion of their kernel data structures, have their own task_struct structures.

能被独立调度的每个执行上下文都必循拥有它自己的进程描述符（包括共享内核大部分数据结构的轻量级进程）。

The strict one-to-one correspondence between the process and process descriptor makes the 32-bit address of the task_struct structure a useful means for the kernel to identify processes.

进程和进程描述符之间有非常严格的一一对应关系，这使得用32位进程描述符地址来标识进程成为一种方便的方式。

Unix-like operating systems allow users to identify processes by means of a number called the Process ID(PID), which is stored in the pid field of the process descriptor. When recycling PID numbers, the Kernel must manage a pidmap_array bitmap that denotes which are the PIDs currently assigned and which are the free ones.

类Unix操作系统允许用户使用一个叫做进程标识符process ID（PID）的数来标识进程，PID存放在进程描述符的pid字段中。由于循环使用PID编号，内核必须通过管理一个pidmap_array位图来表示当前已分配的PID号和闲置的PID号。

To comply with the POSIX 1003.1c standard that all threads of a multithreaded application must have the same PID, Linux makes use of thread groups. The identifier shared by the threads is the PID of the thread group leader, which refers to the PID of the first lightweight process in the group; it is stored in the tgid field of the process descriptors. The getpid() system call returns the value of tgid relative to the current process instead of the value of pid, so all the threads of a multithreaded application share the same identifier.

一个线程组中的所有线程使用和该线程组的领头线程相同的PID，也就是该组中第一个轻量级进程的PID，它被存入进程描述符的tgid字段中。getpid()系统调用返回当前进程的tgid值而不是pid值。

#### 进程描述符处理 Process descriptors handling

For each process, Linux packs two different data structures in a single per-process memory area:

* The thread_info structure
* The Kernel Mode process stack

对于每个进程来说，Linux都把两个不同的数据结构紧凑地存放在一个单独为进程分配的存储区域内：

* 一个是线程描述符
* 另一个是内核态的进程堆栈

The length of this memory area is usually 8192 bytes (two page frames).

这块存储区域的大小通常为8192个字节（2个页框）。

The esp register is the CPU statck pointer, which is used to address the stack`s top location.

esp寄存器用来存放栈顶单元的地址。

C language allows the thread_info structure and the kernel statck of a process to be conveniently represented by means of the thread_union union construct.

C语言用thread_union联合结构表示一个进程的线程描述符和内核栈。

#### 标识当前进程 Identifying the current process

The close association between the thread_info structure and the Kernel Mode stack just described offers a key benefit in terms of efficiency: the kernel can easily obtain the address of the thread_info structure of the process currently running on a CPU from the value of the esp register.

thread_info结构与内核态堆栈之间紧密结合提供的主要好处是：内核很容易从esp寄存器的值获取当前CPU上正在运行进程的thread_info结构的地址。

The first page frame of thread_union aligned to a multiple of 2^13. The kernel masks out the 13 least significant bits of esp to obain the base address of the thread_info structure. 

通常情况下，thread_union结构的起始地址是2^13的倍数。内核屏蔽掉esp寄存器的低13位有效位就可以获得thread_info结构的基地址。

#### 双向链表 Doubly linked lists

Linux defines the list_head data structure, whose only fields next and prev represent the forward and back pointers of a generic doubly linked list element.

Linux内核定义了list_head数据结构，字段next和prev分别表示通用双向链表向前和向后的指针元素。

#### 进程链表 The process list

The process list links together all existing process descriptors.

进程链表把所有进程的描述符链接起来。

The head of the process list is the init_task task_struct descriptor, it is the process descriptor of the so-called process 0 or swapper.

进程链表的头是init_task task_struct描述符，它是所谓的0进程或swapper进程的进程描述符。

The tasks->prev field of init_task points to the tasks field of the process descriptor inserted last in the list.

init_task的tasks.prev字段指向链表中最后插入的进程描述符的tasks字段。

#### TASK_RUNNING状态的进程链表 The lists of TASK_RUNNING Processes

When looking for a new process to run on a CPU, the kernel has to consider only the runnable processes (the processes in the TASK_RUNNING state).

当内核寻找一个新进程在CPU上运行时，必须只考虑可运行进程（即处在TASK_RUNNING状态的进程）

The trick used to achieve the scheduler speedup consists of splitting the runqueue in many list of runnable processes, one list per process priority.

建立多个可运行进程链表，每种进程优先权对应一个不同的链表。

All the lists of process descriptors are implemented by a single prio_array_t data structure.

所有进程描述符链表都在一个单独的prio_array_t数据结构里实现。

### 进程间的关系 Relationships Among Processes

程序创建的进程具有父子关系。一个进程创建多个子进程时，则子进程之间具有兄弟关系。

进程描述符中表示进程亲属关系的字段：

* real_parent
* parent
* children
* sibling

进程之间还存在其他关系：一个进程可能是一个进程组或登录会话的领头进程，也可能是一个线程组的领头进程，还可能跟踪其他进程的执行。

建立非亲属关系的进程描述符字段：

* group_leader
* signal->pgrp
* tgid
* signal->session
* ptrace_children
* ptrace_list

#### pidhash表及链表 The pidhash table and chained lists

内核需要能从进程的PID导出对应的进程描述符指针，顺序扫描进程链表并检查进程描述符的pid字段可行但是相当低效，为了加速查找引入四个散列表：

* PIDTYPE_PID
* PIDTYPE_TGID
* PIDTYPE_PGID
* PIDTYPE_SID

### 如何组织进程 How Processes Are Organized

#### 等待队列 Wait queues

#### 等待队列的操作 Handling wait queues

### 进程资源限制 Process Resource Limits

## 进程切换 Process Switch

### 硬件上下文 Hardware Context

### 任务状态栏 Task State Segment

#### thread字段 The thread field

### 执行进程切换 Performing the Process Switch

#### switch_to宏 The switch_to macro

#### __switch_to()函数 The __switch_to() function

### 保存和加载FPU、MMX及XMM寄存器 Saving and Loading the FPU,MMX,and XMM Registers

#### 保存FPU寄存器 Saving the FPU registers

#### 装载FPU寄存器 Loading the FPU registers

#### 在内核态使用FPU、MMX和SSE/SSE2单元 Using the FPU,MMX,and SSE/SSE2 units in Kernel Mode

## 创建进程 Creating Processes

### clone()、fork()及vfork()系统调用 The clone(),fork(),and vfork() System Calls

#### do_fork()函数 The do_fork() function

#### copy_process()函数 The copy_process() function

### 内核线程 Kernel Threads

#### 创建一个内核线程 Creating a kernel thread

#### 进程0 Process 0

#### 进程1 Process 1

#### 其他内核线程 Other kernel threads

## 撤销进程 Destroying Processes

### 进程终止 Process Termination

#### do_group_exit()函数 The do_group_exit() function

#### do_exit()函数 The do_exit() function

### 进程删除 Process Removal
