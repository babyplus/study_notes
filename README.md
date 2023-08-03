# 内核_进程调度_Processes_Scheduling  

*20230803*  

## 调度策略 Scheduling Policy

### 进程的抢占 Process Preemption

### 一个时间片必须持续多长？How Long Must a Quantum Last?

## 调度算法 The Scheduling Algorithm

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