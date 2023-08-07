# 进程地址空间_Process_Address_Space

*20230805*  

## 进程的地址空间 The Process`s Address Space

## 内存描述符 The Memory Descriptor

### 内核线程的内存描述符 Memory Descriptor of Kernel Threads

## 线性区 Memory Regions

### 线性区数据结构 Memory Region Data Structures

### 线性区访问权限 Memory Region Access Rights

### 线性区的处理 Memory Region Handling

#### 查找给定地址的最邻近区 Finding the closed region to a given address: find_vma()

#### 查找一个与给定的地址区间相重叠的线性区 Finding a region that overlaps a given interval: find_vma_intersection()

#### 查找一个空闲的地址空间 Finding a free interval: get_unmapped_area()

#### 向内存描述符链表中插入一个线性区 Inserting a region in the memory descriptor list: insert_vm_struct()

### 分配线性地址区间 Allocating a Linear Address Interval

### 释放线性地址区间 Releasing a Linear Address Interval

#### The do_munmap() function

#### The split_vma() function

#### The unmap_region() function

## 缺页异常处理程序 Page Fault Exception Handler

### 处理地址空间外的错误地址 Handling a Faulty Address Outside the Address Space

### 处理地址空间内的错误地址 Handling a Faulty Address Inside the Address Space

### 请求调页 Demand Paging

### 写时复制 Copy On Write

### 处理非连续内存区访问 Handling Noncontiguous Memory Area Accesses

## 创建和删除进程的地址空间 Creating and Deleting a Process Address Space

### 创建进程的地址空间 Creating a Process Address Space

### 删除进程的地址空间 Deleting a Process Address Space

## 堆的管理 Managing the Heap