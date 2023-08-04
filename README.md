﻿# 内核_进程_Processes  

*20230727*  

## 进程、轻量级进程和线程 Processes,Lightweight Processes,and Threads

A process is an instance of a program in execution;Each of threads represents an execution flow of the process;Linux uses LWP to offer better support for multithreaded applications.

进程是程序执行时的一个实例；每个线程代表进程的一个执行流；轻量级进程是内核对多线程应用提供的支持。

## 进程描述符 Process Descriptor

### 进程状态 Process State

### 标识一个进程 Identifying a Process

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
