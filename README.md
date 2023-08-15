# 内核_进程通信_Process_Communication  

*20230815*  

## 管道 Pipes

### 使用管道 Using a Pipe

### 管道数据结构 Pipe Data Structures

#### pipefs特殊文件系统 The pipefs special filesystem

### 创建和撤销管道 Creating and Destroying a Pipe

### 从管道中读取数据 Reading from Pipe

### 向管道中写入数据 Writing into a Pipe

## FIFOs

### 创建并打开FIFO Creating and Opening a FIFO

## System V IPC

### 使用IPC资源 Using an IPC Resource

### ipc()系统调用 The ipc() System Call

### IPC信号量 IPC Semaphores

#### 可取消的信号量操作 Undoable semaphore operations

#### 挂起请求的队列 The queue of pending requests

### IPC消息 IPC Messages

### IPC共享内存 IPC Shared Memory

#### 换出IPC共享内存区的页 Swapping out pages of IPC shared memory regions

#### IPC共享内存区的请求调页 Demand paging for IPC shared memory regions

## POSIX消息队列 POSIX Message Queues