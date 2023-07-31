# 内核_内核同步_Kernel_Synchronization  

*20230731*  

## 内核如何为不同的请求提供服务 How the Kernel Services Requests

### 内核抢占 Kernel Preemption

### 什么时候同步是必需的 When Synchronization Is Necessary

### 什么时候同步是不必要的 When Synchronization Is Not Necessary

## 同步原语 Synchronization Primitives

### 每CPU变量 Per-CPU Variables

### 原子操作 Atomic Operations

### 优化和内存屏障 Optimization and Memory Barriers

### 自旋锁 Spin Locks

#### 具有内核抢占的spin_lock宏 The spin_lock macro with Kernel Preemption

#### 非抢占式内核中的spin_lock宏 The spin_lock macro without Kernel Preemption

#### spin_unlock宏 The spin_unlock macro

### 读/写自旋锁 Read/White Spin Locks

#### 为读获取和释放一个锁 Getting and releasing a lock for reading

#### 为写获取和释放一个锁 Getting and releasing a lock for writing

### 顺序锁 Seqlocks

### 读-拷贝-更新（RCU）Read-Copy Update

### 信号量 Semaphores

#### 获取和释放信号量 Getting and releasing semaphores

### 读/写信号量 Read/Write Semaphores

### 补充原语 Completions

### 禁止本地中断 Local Interrupt Disabling

### 禁止和激活可延迟函数 Disabling and Enabling Deferrable Functions

## 对内核数据结构的同步访问 Synchronizing Accesses to Kernel Data Structures

### 在自旋锁、信号量及中断禁止之间选择 Choosing Among Spin Locks,Semaphores,and Interrupt Disabling

#### 保护异常所访问的数据结构 Protecting a data structure accessed by exceptions

#### 保护中断所访问的数据结构 Protecting a data structure accessed by interrupts

#### 保护可延迟函数所访问的数据结构 Protecting a data structure accessed by deferrable functions

#### 保护由异常和中断访问的数据结构  Protecting a data structure accessed by exceptions and interrupts

#### 保护由异常和可延迟函数访问的数据结构  Protecting a data structure accessed by exceptions and deferrable functions

#### 保护由中断和可延迟函数访问的数据结构  Protecting a data structure accessed by interrupts and deferrable functions

#### 保护由异常、中断和可延迟函数访问的数据结构  Protecting a data structure accessed by exceptions, interrupts, and deferrable functions

## 避免竞争条件的实例 Examples of Race Condition Prevention

### 引用计数器 Reference Counters

### 大内核锁 The Big Kernel Lock

### 内存描述符读/写信号量 Memory Descriptor Read/Write Semaphore

### slab高速缓存链表的信号量 Slab Cache List Semaphore

### 索引节点的信号量 Inode Semaphore