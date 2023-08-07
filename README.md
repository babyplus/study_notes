# 内核_进程_Processes  

*20230727*  

## 进程、轻量级进程和线程 Processes,Lightweight Processes,and Threads

A process is an instance of a program in execution;Each of threads represents an execution flow of the process;Linux uses LWP to offer better support for multithreaded applications.

进程是程序执行时的一个实例；每个线程代表进程的一个执行流；轻量级进程是内核对多线程应用提供的支持。

## 进程描述符 Process Descriptor

### 进程状态 Process State

As its name implies, the state field of the process descriptor describes what is currently happening to the process.In the cerrent Linux version, these states are mutually exclusive, and hence exactly one flag of state always is set; the remaining flags are cleared.

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

As general rule, each execution context that can be independently scheduled must have its own process descriptor; therefore, even lightweight processes, which share a large portion of their kernel data structures, have their own task_struct structures.

能被独立调度的每个执行上下文都必循拥有它自己的进程描述符（包括共享内核大部分数据结构的轻量级进程）。

The strict ont-to-one correspondence between the process and process decriptor makes the 32-bit address of the task_struct structure a useful means for the kernel to identify processes.

进程和进程描述符之间有非常严格的一一对应关系，这使得用32位进程描述符地址来标识进程成为一种方便的方式。

Unix-like operating systems allow users to identify processes by means of a number called the Process ID(PID), which is stored in the pid field of the process descriptor. When recycling PID numbers, the Kernel must manage a pidmap_array bitmap that denotes which are the PIDs currently assigned and which are the free ones.

类Unix操作系统允许用户使用一个叫做进程标识符process ID（PID）的数来标识进程，PID存放在进程描述符的pid字段中。由于循环使用PID编号，内核必须通过管理一个pidmap_array位图来表示当前已分配的PID号和闲置的PID号。

To comply with the POSIX 1003.1c standard that all threads of a multithreaded application must have the same PID, Linux makes use of thread groups. The identifier shared by the threads is the PID of the thread group leader, that is, the PID of the first lightweight process in the group; it is stored in the tgid field of the process descriptors. The getpid() system call returns the value of tgid relative to the current process instead of the value of pid, so all the threads of a multithreaded application share the same identifier.

一个线程组中的所有线程使用和该线程组的领头线程相同的PID，也就是该组中第一个轻量级进程的PID，它被存入进程描述符的tgid字段中。getpid()系统调用返回当前进程的tgid值而不是pid值。

#### 进程描述符处理 Process descriptors handling

#### 标识当前进程 Identifying the current process

#### 双向链表 Doubly linked lists

#### 进程链表 The process list

#### TASK_RUNNING状态的进程链表 The lists of TASK_RUNNING Processes

### 进程间的关系 Relationships Among Processes

#### pidhash表及链表 The pidhash table and chained lists

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
