# 内核_进程调度_Processes_Scheduling  

*20230803*  

## 调度策略 Scheduling Policy

The set of rules used to determine when and how to select a new process to run is called scheduling policy.

决定什么时候以怎样的方式选择一个新进程运行的这组规则就是所谓的调度策略（scheduling policy）。

Linux scheduling is based on the time sharing technique; several processes run in "time multiplexing" because the CPU time is devided into slices, one for each runnable process.

Linux的调度基于分时（time sharing）技术：多个进程以“时间多路复用”方式运行，因为CPU的时间被分成“片（slice）”，给每个可运行的程序分配一片。

If a currently running process is not terminated when its time slice or quantum expires, a process switch may take place.

如果当前运行进程的时间片或时限（quantum）到期时，该进程还没有运行完毕，进程切换就可以发生。

Time sharing relies on timer interrupts and is thus transparent to processes. No additional code needs to be inserted in the programs to ensure CPU time sharing.

分时依赖于定时中断，因此对进程是透明的，不需要在程序中插入额外的代码来保证CPU分时。

The traditional classification of processes:

* I/O-bound
* CPU-bound

传统上对进程的分类：

* I/O受限
* CPU受限

An alternative classification distinguishes tree clases of processes:

* Interactive processes
* Batch processes
* Real-time processes

对进程的另一种分类：

* 交互式进程
* 批处理进程
* 实时进程

### 进程的抢占 Process Preemption

### 一个时间片必须持续多长？How Long Must a Quantum Last?

If the average quantum duration is too short, the system overhead caused by process switches becomes excessively high; If the average quantum duration is too long, processes no longer appear to be executed concurrently.

如果平均时间片太短，由进程切换引起的系统额外开销就变得非常高；如果平均时间片太长，进程看起来就不再是并发执行。

## 调度算法 The Scheduling Algorithm

Every Linux process is always scheduled according to one of the following scheduling classes:

* SCHED_FIFO: A First-In, First-Out real-time process
* SCHED_RR: A Round Robin Real-time process
* SCHED_NORMAL: A conventional, time-shared process 

每个Linux进程总是按照下面的调度类型被调度：

* SCHED_FIFO：先进先出的实时进程
* SCHED_RR：时间片轮转的实时进程
* SCHED_NORMAL：普通的分时进程

### 普通进程的调度 Scheduling of Conventional Processes

#### 基本时间片 Base time quantum

#### 动态优先级和平均睡眠时间 Dynamic priority and average sleep time

#### 活动和过期进程 Active and expired processes

### 实时进程的调度 Scheduling of Real-Time Processes

## 调度程序所使用的数据结构 Data Structures Used by the Scheduler

### 数据结构runqueue The runqueue Data Structure

### 进程描述符 Process Descriptor

## 调度程序所使用的函数 Functions Used by the Scheduler

### scheduler_tick()

#### 更新实时进程的时间片 Updating the time slice of a real-time process

#### 更新普通进程的时间片 Updating the time slice of a conventional process

### try_to_wake_up()

### recale_task_prio()

### schedule()

#### 直接调用 Direct invocation

#### 延迟调用 Lazy invocation

#### 进程切换之前schedule()所执行的操作 Actions performed by schedule() before a process switch

#### schedule()完成进程切换时所执行的操作 Actions performed by schedule() to make the process switch

#### 进程切换后schedule()所执行的操作 Actions performed by schedule() after a process switch

## 多处理器系统中运行队列的平衡 Runqueue Balancing in Multiprocessor Systems

### 调度域 Scheduling Domains

### rebalance_tick()

### load_balance()

### move_tasks()

## 与调度相关的系统调用 System Calls Related to Scheduling

### nice()系统调用

### getpriority()和setpriority()系统调用

### sched_getaffinity()和sched_setaffinity()系统调用

### 与实时进程相关的系统调用 System Calls Related to Real-Time Processes

#### sched_getscheduler()和sched_setschduler()系统调用

#### sched_getparam()和shced_setparam()系统调用

#### sched_yield()系统调用

#### sched_get_priority_min()和sched_get_priority_max()系统调用

#### sched_rr_get_interval()系统调用