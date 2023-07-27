# 内核_进程_Processes  

*20230727*  

## 进程、轻量级进程和线程 Processes,Lightweight Processes,and Threads

A process is an instance of a program in execution;Each of which represents an execution flow of the process;Linux uses LWP to offer better support for multithreaded applications.

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

## 创建进程 Creating Processes

## 撤销进程 Destroying Processes