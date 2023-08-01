# 内核_定时测量_Timing_Measurements  

*20230801*  

## 时钟和定时器电路 Clock and Timer Circuits

### 实时时钟 Real Time Clock (RTC)

### 时间戳计数器 Time Stamp Counter (TSC)

### 可编程间隔定时器 Programmable Interval Timer (PIT)

### CPU本地定时器 CPU Local Timer

### 高精度事件定时器 High Precision Event Timer (HPET)

### ACPI电源管理定时器 ACPI Power Management Timer

## Linux计时体系结构 The Linux Timekeeping Architecture

### 计时体系机构的数据结构 Data Structures of the Timekeeping Architecture

#### 定时器对象 The timer object

#### jiffies变量 The jiffies variable

#### xtime变量 The xtime variable

### 单处理器系统上的计时体系结构 Timekeeping Architecture in Uniprocessor Systems

#### 初始化阶段 Initialization phase

#### 时钟中断处理程序 The timer interrupt handler

### 多处理器系统上的计时体系结构 Timekeeping Architecture in Multiprocessor Systems

#### 初始化阶段 Initialization phase

#### 全局时钟中断处理程序 The global timer interrupt handler

#### 本地时钟中断处理程序 The local timer interrupt handler

## 更新时间和日期 Updating the Time and Date

## 更新系统统计数 Updating System Statistics

### 更新本地CPU统计数 Updating Local CPU Statistics

### 记录系统负载 Keeping Track of System Load

### 监管内核代码 Profiling the Kernel Code

### 检查非屏蔽中断（NMI）监视器 Checking the NMI Watchdogs

## 软定时器和延迟函数 Software Timers and Delay Functions

### 动态定时器 Dynamic Timers

#### 动态定时器与竞争条件 Dynamic timers and race conditions

#### 动态定时器的数据结构 Data structures for dynamic timers

#### 动态定时器处理 Dynamic timer handling

### 动态定时器应用之一：nanosleep()系统调用 An Application of Dynamic Timers: the nanosleep() System Call

### 延迟函数 Delay Functions

## 与定时测量相关的系统调用 System Calls Related to Timing Measurements

### time()和gettimeofday()系统调用 The time() and gettimeofday() System Calls

### adjtimex()系统调用 The adjtimex() System Call

### setitimer()和alarm()系统调用 The setitimer() and alarm() System Calls

### 与POSIX定时器相关的系统调用 System Calls for POSIX Timers



