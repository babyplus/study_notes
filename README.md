# 进程地址空间_Process_Address_Space

*20230805*  

The kernel succeeds in deferring the allocation of dynamic memory to processes by using a new kind of resource.

内核使用一种新的资源实现了对进程动态内存的推迟分配。

When a User Mode process asks for dynamic memory, it doesn`t get additional page frames; instead, it gets the right to use a new range of linear addresses, which become part of its address space. This interval is called a "memory region".

当用户态进程请求动态内存时，并没有获得请求的页框，而仅仅获得对一个新的线性地址区间的使用权，而这一线性地址区间就成为进程地址空间的一部分。这一区间叫做“线性区”。

## 进程的地址空间 The Process`s Address Space

The address space of a process consist of all linear addresses that the process is allowed to use.

进程的地址空间由允许进程使用的全部线性地址组成。

Each process sees a different set of linear addresses.

每个进程所看到的线性地址集合是不同的。

## 内存描述符 The Memory Descriptor

All information related to the process address space is included in an object called the memory descriptor of type mm_struct.

与进程地址空间有关的全部信息都包含在一个叫做内存描述符的数据结构中，这个结构的类型为mm_struct。

### 内核线程的内存描述符 Memory Descriptor of Kernel Threads

Kernel threads run only in Kernel Mode. so they never access linear addresses below TASK_SIZE.

内核线程仅运行在内核态，因此，它们永远不会访问低于TASK_SIZE的地址。

Contrary to regular processes, kernel threads do not use memory regions.

与普通线程相反，内核线程不用线性区。

## 线性区 Memory Regions

Linux implements a memory region by means of an object of type vm_area_struct. Each memory region descriptor identifies a linear address interval.

Linux通过类型为vm_area_struct的对象实现线性区，每个线性区描述符表示一个线性地址区间。

### 线性区数据结构 Memory Region Data Structures

All the regions owned by a process are linked in a simple list. The kernel finds the memory regions through the mmap field of the process memory descriptor.

进程所拥有的所有线性区是通过一个简单的链表链接在一起的。内核通过内存描述符中的mmap字段来查找线性区。

### 线性区访问权限 Memory Region Access Rights

Each memory region consists of a set of pages that have consecutive page numbers.

每个线性区都由一组号码连续的页所构成。

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