# 内核_信号_Signals  

*20230807*  

## 信号的作用 The Role of Signals

A Signal is a very short message that may be sent to a process or a group of processes.

信号是很短的消息，可以被发送到一个进程或一组进程。

The only information given to the process is usually a number identifying the signal.

发送给进程的唯一信息通常是一个数，以此来标识信号。

A set of macros whose names start with the prefix SIG is used to identify signals.

名字前缀为SIG的一组宏来标识信号。

Signals serve two main purposes:

* To make a process aware that a specific event has occurred
* To cause a process to execute a signal handle function include in its code

使用信号的两个主要目的：

* 让进程知道已经发生了一个特定事件
* 强迫进程执行他自己代码中的信号处理程序

An important characteristic of signals is that they may be sent at any time to a process whose state is usually unpredictable. Signals sent to a process that is not currently executing must be saved by the kernel until that process resumes execution.

信号的一个重要特点是它们可以随时被发送给状态经常不可预知的进程。发送给非运行进程的信号必须由内核保存，直到进程恢复执行。

The kernel distinguishes two different phases related to signal transmission:

* Signal generation: The kernel updates a data structure of the destination process to represent that a new signal has been sent
* Signal delivery: The kernel forces the destination process to react to the signal by changing its execution state, by starting the execution of a specified signal handler, or both

内核区分信号传递的两个不同阶段：

* 信号产生：内核更新目标进程的数据结构以表示一个新的信号已被发送
* 信号传递：内核强迫目标进程通过以下方式对信号作出反应，改变目标进程的执行状态或者开始执行一个特定的信号处理程序

Signals that have been generated but not yet delivered are called pending signals.

已经产生但还没有传递的信号称为挂起信号。

### 传递信号前所执行的操作 Action Performed upon Delivering Signal

There are three ways in which a process can respond to a signal:

* Explicitly ignore the signal
* Execute the defautl action associated with the signal
* Catch the signal by invoking a corresponding singal-handle function

进程以三种方式对一个信号做出应答：

* 显式地忽略信号
* 执行与信号相关的缺省操作
* 通过调用相应的信号处理函数捕获信号

### POSIX信号和多线程应用 POSIX Signals and Multithreaded Applications

### 与信号相关的数据结构 Data Structures Associated with Signals

#### 信号描述符和信号处理程序描述符 The signal descriptor and the signal handler descriptor

#### sigaction 数据结构 The sigaction data structure
 
#### 挂起信号队列 The pending signal queues

### 在信号数据结构上的操作 Operations on Signal Data Structures

## 产生信号 Generating a Signal

### The specific_send_sig_info() Function

### The send_signal() Function

### The group_send_sig_info() Function

## 传递信号 Delivering a Signal

### 执行信号的缺省操作 Executing the Default Action for the Signal

### 捕获信号 Catching the Signal

#### 建立帧 Setting up the frame

#### 检查信号标志 Evaluating the signal flags

#### 开始执行信号处理程序 Staring the signal handler

#### 终止信号处理程序 Terminating the signal handler

### 系统调用的重新执行 Reexecution of System Calls

#### 重新执行被未捕获信号中断的系统调用 Restarting a system call interrupted by a non-caught signal

#### 为所捕获的信号重新执行系统调用 Restarting a system call for a caught signal

## 与信号处理相关的系统调用 System Calls Related to Signal Handling

### The kill() System Call

### The tkill() and tgkill() System Calls

### 改变信号的操作 Changing a Signal Action

### 检查挂起的阻塞信号 Examining the Pending Blocked Signals

### 修改阻塞信号的集合 Modifying the Set of Blocked Signals

### 挂起进程 Suspending the Process

### 实时信号的系统调用 System Calls for Real-Time Signals