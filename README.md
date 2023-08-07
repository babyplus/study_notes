# 内核_信号_Signals  

*20230807*  

## 信号的作用 The Role of Signals

### 传递信号前所执行的操作 Action Performed upon Delivering Signal

### POSIX信号和多线程应用 POSIX Signals and Multithreaded Applications

### 与信号相关的数据结构 Data Structures Associated with Signals

#### 信号描述符和信号处理程序描述符 The signal descriptor and the signal handler descriptor

#### The sigaction data structure
 
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