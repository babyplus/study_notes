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

Every conventional process has its own static priority, which is a value used by the scheduler to rate the process with respect to the other conventional processes in the system.

每个普通的进程都有他自己的静态优先级，调度程序使用静态优先级来估价系统中这个进程与其他进程之间的调度的程度。

The kernel represents the static priority of a conventional process with a number ranging from 100(highest priority) to 139(lowest priority).

内核用从100（最高优先级）到139（最低优先级）的数来表示普通进程的静态优先级。

#### 基本时间片 Base time quantum

The static priority essentially determines the base time quantum of a process, the higher the static priority, the longer the base time quantum.

静态优先级本质上决定了进程的基本时间片，静态优先级越高，基本时间片就越长。

if static priority < 120, base time quantum=(140-static priority)*20
if static priority >= 120, base time quantum=(140-static priority)*5

若静态优先级<120，则基本时间片=(140-静态优先级)*20
若静态优先级>=120，则基本时间片=(140-静态优先级)*5

#### 动态优先级和平均睡眠时间 Dynamic priority and average sleep time

Beside a static priority, a conventional process also has a dynamic priority, which is  a value ranging from 100(highest priority) to 139(lowest priority).

普通进程除了静态优先级，还有动态优先级，其值得范围是100（最高优先级）到139（最低优先级）。

The dynamic priority is the number actually looked up by the scheduler when selecting the new process to run.

动态优先级是调度程序在选择新进程来运行的时候使用的数。

dynamic priority=max(100, min(static priority-bonus+5, 139))

动态优先级=max(100, min(静态优先级-奖励值+5， 139))

The bonus is a value ranging from 0 to 10; it depends on the past history of the process, more precisely, it is related to the average sleep time of the process.

奖励值依赖于进程过去的情况，与进程的平均睡眠时间相关，范围是0到10。

#### 活动和过期进程 Active and expired processes

To avoid process starvation, the scheduler keeps two disjoint sets of runnable processes.

* Active processes: these runnable processes have not yet exhausted their time quantum and are thus allowed to run
* Expired processes: these runnable processes have exhausted their time quantum and are thus forbidden to run until all active processes expire

为了避免进程饥饿，调度程序维持两个不相交的可运行进程的集合。

* 活动进程：这些进程还没用完时间，因此允许他们运行
* 过期进程：这些可运行进程已经用完他们的时间片并因此被禁止运行直到所有活动进程都过期

### 实时进程的调度 Scheduling of Real-Time Processes

Every real-time process is associated with a real-time priority, which is a value ranging from 1 (highest priority) to 99 (lowest priority).

每个实时进程都与一个实时优先级相关，实时优先级是一个范围从1到99的值。

A real-time process inhibits the execution of every lower-priority process while it remains runnable.

实时进程运行的过程中，禁止低优先级进程的执行。

Real-time processes are always considered active.

实时进程总是被当成活动进程。

If several real-time runnable processes have the same highest priority, the scheduler chooses the process that occurs first in the corresponding list of the local CPU`s run-queue.

如果几个可运行的实时进程具有相同的最高优先级，那么调度程序选择第一个出现在本地CPU的运行队列相应链表中的进程。

A real-time process is replaced by another process only when one of the following event occurs:

* The process is preempted by another process having higher real-time priority
* The process performs a blocking operation, and it is put to sleep
* The process is stopped
* The process voluntarily relinquishes the CPU by invoking the sched_yield() system call
* The process is a Round Robin real-time process (SCHED_RR), and it has exhausted its time quantum

只有在下述事件之一发生时，实时进程才会被另一个进程取代：

* 进程被另一个具有更高实时优先级的实时进程抢占
* 进程执行了阻塞操作并进入睡眠
* 进程停止或者被杀死
* 进程通过调用系统调用sched_yield()资源放弃CPU
* 进程是基于时间片轮转的实时进程并用完了它的时间片

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
