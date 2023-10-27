# 内核_定时测量_Timing_Measurements  

*20230801*  

## 时钟和定时器电路 Clock and Timer Circuits

### 实时时钟 Real Time Clock (RTC)

All PCs include a clock called Real Time Clock (RTC),which is independent of the CPU and all other chips.

所有的PC都包含一个叫实时时钟的时钟，它是独立于CPU和其他芯片的。

The RTC is capable of issuing periodic interrupts on IRQ8 at frequencies ranging between 2 Hz and 8192 Hz. It can also be programmed to activate the IRQ8 line when the RTC reaches a specific value, thus working as an alarm clock.

实时时钟能在IRQ8上发出周期性的中断，频率在2~8192Hz之间。也可以对实时时钟进行编程以使当实时时钟到达某个特定的值时激活IRQ8线，也就是作为一个闹钟来工作。

Linux uses the RTC only to derive the time and date; howeve, it allows processes to program the RTC by acting on the /dev/rtc device file.

Linux只用实时时钟来获取时间和日期，不过，通过对 /dev/rtc 设备文件进行操作，也允许进程对实时时钟编程。

### 时间戳计数器 Time Stamp Counter (TSC)

All 80x86 microprocessors include a CLK input pin, which receives the clock signal of an external oscillator.

所有的80x86微处理器都包含一条CLK输入引线，它接受外部振荡器的时钟信号。

Staring with the Pentium, the 80x86 microprocessors sport a counter that is increased at each clock signal. The counter is accessible through the 64-bit Time Stamp Counter register, which can be read by means of the rdtsc assembly language instruction.

从Pentium开始，80x86微处理器就包含一个64位的时间戳计数器（Time Stamp Counter, TSC）寄存器，在每个时钟信号到来时加1，并可以通过汇编语言指令rdtsc读这个寄存器。

### 可编程间隔定时器 Programmable Interval Timer (PIT)

Besides the Real Time Clock and the Time Stamp Counter, IBM-compatible PCs include another type of time-measuring device called Programmable Interval Timer (PIT).

除了实时时钟和时间戳计数器，IBM兼容PC还包含了第三种类型的时间测量设备，叫做可编程间隔定时器（Programmable Interval Timer, PIT）。

The PIT issues a special interrupt called timer interrupt, which notifies the kernel that one more time interval has elapsed.

可编程间隔定时器通过发出时钟中断（timer interrupt）来通知内核又一个时间间隔过去了。

The PIT goes on issuing interrupts forever at some fixed frequency established by the kernel.

可编程间隔定时器永远以内核确定的固定频率不停地发出中断。

### CPU本地定时器 CPU Local Timer

The local APIC present in recent 80x86 microprocessors provides yet another time-measuing device: CPU local timer.

在80x86微处理器的本地APIC中还提供了另一种定时测量设备：CPU本地定时器。

The CPU local timer is a device similar to the Programmable Interval Timer that can issue one-shot or periodic interrupts.

CPU本地定时器是一种能产生单步中断或周期性中断的设备，类似于可编程间隔定时器。

### 高精度事件定时器 High Precision Event Timer (HPET)

The High Precision Event Timer provides a number of hardware timers that can be exploited by the kernel.

HPET提供了许多可以被内核使用的硬定时器。

Basically, the chip includes up to eight 32-bit or 64-bit independent counters. Each counter is driven by its own clock signal, whose frequency must be at least 10MHz; therefore, the counter is increased at least once in 100 nanoseconds.

这种新定时器芯片主要包含8个32位或64位的独立计数器。每个计数器由它自己的时钟信号所驱动，该时钟信号的频率必须至少为10MHz。

Any counters is associated with at most 32 timers, each of which is composed by a comparator and a match register.

任何计数器最多可以和32个定时器相关联，每个定时器由一个比较器和一个匹配寄存器组成。

The comparator is a circuit that checks the value in the counter against the value in the match register and raises a hardware interrupt if a match is found.

比较器是一组用于检测计数器中的值与匹配寄存器中的值是否匹配的电路，如果找到一组匹配值就产生一个硬件中断。

### ACPI电源管理定时器 ACPI Power Management Timer

The ACPI Power Management Timer is yet another clock device included in almost all ACPI-based motherboards. Its clock signal has a fixed frequency of roughly 3.58MHz.

ACPI电源管理定时器是另一种时钟设备，时钟信号大约为3.58MHz固定频率。

*用途暂时不明*

## Linux计时体系结构 The Linux Timekeeping Architecture

Linux must carry on serveral time-related activities. For instance, the kernel periodically:

* Updates the time elapsed since system startup
* Updates the time and date
* Determines, for every CPU, how long the current process has been running, and preempts it if it has exceeded the time allocated to it.
* Updates resource usage statistics
* Checks whether the interval of time associated with  each software timer has elapsed

内核周期性地执行下列与定时相关的操作：

* 更新系统启动以来所经过的时间
* 更新时间和日期
* 确定当前进程在每个CPU上已运行了多长时间，如果已经超过了分配给它的时间，则抢占它
* 更新资源使用统计数
* 检查每个软定时器的时间间隔是否已到

### 计时体系机构的数据结构 Data Structures of the Timekeeping Architecture

#### 定时器对象 The timer object

In order to handle the possible timer sources in a uniform way, the kernel makes use of a "timer object", which is a descriptor of type timer_opts.

为了使用统一的方法来处理可能存在的定时器资源，内核使用了“定时器对象”，它是timer_opts类型的一个描述符。

The cur_timer variable stores the address of the timer object corresponding to the "best" timer source available in the system.

* Initially, cur_timer points to timer_none
* During the kernel initialization, the select_timer() function sets cur_timer to the address of the appropriate timer object.

变量cur_timer存放了某个定时器对象的地址，该定时器是系统可利用的定时器资源中“最好的”。

* 内核初始化的时候，cur_timer指向timer_none
* 内核初始化期间，select_timer()函数设置cur_timer指向适当定时器对象的地址

#### jiffies变量 The jiffies variable

The jiffies variable is a counter that stores the number of elapsed ticks since the system was started.

jiffies变量是一个计数器，用来记录自系统启动以来产生的节拍总数。

#### xtime变量 The xtime variable

The xtime variable stores the current time and date.

xtime变量存放当前时间和日期，它是一个timespec类型的数据结构。

The xtime variable is usually updated once in a tick, that is, roughly 1000 times persecond.

xtime变量通常是每个节拍更新一次，也就是说，大约每秒更新1000次。

### 单处理器系统上的计时体系结构 Timekeeping Architecture in Uniprocessor Systems

在单处理器系统上，所有与定时有关的活动都是由IRQ线0上的可编程间隔定时器产生的中断触发的。

#### 初始化阶段 Initialization phase

在内核初始化期间，time_init()函数被用来建立计时体系结构，通常执行以下操作：

* 初始化xtime变量
* 初始化wall_to_monotonic变量
* 如果内核支持HPET，它将调用hpet_enable()函数来确认ACPI固件是否探测到了该芯片并将它的寄存器映射到了内存地址中。如果结果是肯定的，那么hpet_enable()将对HPET芯片的第一个定时器编程，使其以每秒1000次的频率引发IRQ 0处中断；否则，内核将使用PIT(该芯片已经被init_IRQ()函数编程，使得它以每秒1000次的频率引发IRQ 0处的中断。
* 调用select_timer()来挑选系统中可利用的最好的定时器，并设置cur_timer变量
* 调用setup_irq(0, &irq0)来创建与IRQ 0相应的中断门，IRQ 0引脚线连接着系统时钟中断源(PIT或者HPET)

#### 时钟中断处理程序 The timer interrupt handler

timer_interrupt()函数是PIT或者HPET的中断服务例程(ISR)：

* 在xtime_lock顺序锁上产生一个write_seqlock()来保护与定时相关的内核变量
* 执行cur_timer定时器对象的mark_offset方法
* 调用do_timer_interrupt()函数
* 调用write_sequnlock()释放xtime_lock顺序锁
* 返回值1，报告中断已经被有效处理

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



