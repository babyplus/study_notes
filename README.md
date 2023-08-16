# 内核_内存管理_Memory_Management

*20230804*  

Some portion of RAM is permanently assigned to the kernel and used to store both the kernel code and the static kernel data structures.

RAM的某些部分永久地分配给内核，并用来存放内核代码以及静态内核数据结构。

The remaining part of the RAM is called dynamic memory, the performance of the entire system depends on how efficiently dynamic memory is managed.

RAM的其余部分称为动态内存，整个系统的性能取决于如何有效地管理动态内存。

## 页框管理 Page Frame Management

The Intel Pentium processor canuse two different page frame size: 4KB and 4MB.

Intel的Pentium处理器可以采用两种不同的页框大小：4KB和4MB。

Linux adopts the smaller 4KB page frame size as the standard memory allocation unit.

Linux采用4KB页框大小作为标准的内存分配单元。

### 页描述符 Page Descriptors

The kernel must keep track of the current status of each page frame.

内核必须记录每个页框当前的状态。

State information of a page frame is kept in a page descriptor of type page, all page descriptors are stored in the mem_map array.

页框的状态信息保存在一个类型为page的页描述符中，所有的页描述符存放在mem_map数组中。

### 非一致内存访问 Non-Uniform Memory Access (NUMA)

Linux 2.6 supports the Non-Uniform Memory Access model, in which the access times for different memory locations from a given CPU may vary.

Linux 2.6 支持非一致内存访问模型，在这种模型中，给定CPU对不同内存单元的访问时间可能不一样。

The physical memory of the system is partitioned in several nodes.

系统的物理内存被划分为几个节点。

The physical memory inside each node can be split into several zones.

每个节点中的物理内存又可以分为几个管理区。

Each node has a descriptor of type pg_data_t.

每个节点都有一个类型为pg_data_t的描述符。

All node descriptors are stored in a single linked list.

所有节点的描述符存放在一个单向链表中。

### 内存管理区 Memory Zones

Linux 2.6 partitions the physical memory of every memory node into three zones:

* ZONE_DMA：Contains page frames of memory below 16MB
* ZONE_NORMAL：Contains page frames of memory at and above 16MB and below 896MB
* ZONE_HIGHMEM：Contains page frames of memory at and above 896MB

Linux 2.6 把每个内存节点的物理内存划分为3个管理区：

* ZONE_DMA：包含低于16MB的内存页框
* ZONE_NORMAL：包含高于16MB且低于896MB的内存页框
* ZONE_HIGHMEM：包含高于896MB的内存页框

### 保留的页框池 The Pool of Reserved Page Frames

Some kernel control paths cannot be blocked while requesting memory , should issue atomic memory allocation requests.  

在一些内核路径不能被阻塞的情况下应当产生原子内存分配请求。

The kernel reserves a pool of page frames for atomic memory allocation requests to be used only on low-on-memory conditions.

内核为原子内存分配请求保留了一个页框池，只有在内存不足时才使用。

### 分区页框分配器 The Zoned Page Frame Allocator

The kernel subsystem that handles the memory allocation requests for groups of contiguous page frames is called the zoned page frame allocator.

分区页框分配器（内核子系统）用于处理对连续页框组的内存分配请求。

#### 请求和释放页框 Requesting and releasing page frames

### 高端内存页框的内核映射 Kernel Mappings of High-Memory Page Frames

#### 永久内核映射 Permanent kernel mappings

#### 临时内核映射 Temporary kernel mappings

### 伙伴系统算法 The Buddy System Algorithm

#### 数据结构 Data structures

#### 分配块 Allocating a block

#### 释放块 Freeing a block

### 每CPU页框高速缓存 The Per-CPU Page Frame Cache

#### 通过每CPU页框高速缓存分配页框 Allocating page frames through the per-CPU page frame caches

#### 释放页框到每CPU页框高速缓存 Releasing page frames to the per-CPU page frame caches

### 管理区分配器 The Zone Allocator

#### 释放一组页框 Releasing a group of page frames

## 内存区管理 Memory Area Management

### slab分配器 The Slab Allocator

### 高速缓存描述符 Cache Descriptor

### slab描述符 Slab Descriptor

### 普通和专用高速缓存 General and Specific Caches

### slab分配器与分区页框分配器的接口 Interfacing the Slab Allocator with the Zoned Page Frame Allocator

### 给高速缓存分配slab Allocator a Slab to a Cache

### 从高速缓存中释放slab Releasing a Slab from a Cache

### 对象描述符 Object Descriptor

### 对齐内存中的对象 Aligning Objects in Memory

### slab着色 Slab coloring

### 空闲slab对象的本地高速缓存 Local Caches of Free Slab Objects

### 分配slab对象 Allocating a Slab Object

### 释放slab对象 Freeing a Slab Object

### 通用对象 General Purpose Objects

### 内存池 Memory Pools

## 非连续内存区管理 Noncontiguous Memory Area Management

### 非连续内存区的线性地址 Linear Addresses of Noncontiguous Memory Areas

### 非连续内存区的描述符 Descriptors of Noncontiguous Memory Areas

### 分配非连续内存区 Allocating a Noncontiguous Memory Area

### 释放非连续内存区 Releasing a Noncontiguous Memory Area
