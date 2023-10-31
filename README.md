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

The linear address that corresponds to the end of the directly mapped physical memory, and thus to the beginning of the high memory, is stored in the high_memory variable, which is set to 896MB.

高端内存的始端所对应的线性地址存放在high_memory变量中，它被设置为896MB。

Page frames above the 896MB boundary are not generally mapped in the fourth gigagbyte of the kernel linear address spaces, so the kernel is unable to directly access them.

896MB边界以上的页框并不映射在内核线性地址空间的第4个GB，因此，内核不能直接访问它们。

Each page allocator function that returns the linear address of the assigned page frame doesn`t work for high-memory page frames.

返回所分配页框线性地址的页分配器函数不适用于高端内存。

The kernel uses three different mechanisms to map page frames in high-memory:

* permanent kernel mapping
* temporary kernel mapping
* noncontiguous memory allocation

内核可以采用三种不同的机制将页框映射到高端内存：

* 永久内核映射
* 临时内核映射
* 非连续内存分配

#### 永久内核映射 Permanent kernel mappings

Permanent kernel mappings allow the kernel to establish long-lasting mappings of high-memory page frames into the kernel address space.

永久内核映射允许内核建立高端页框到内核地址空间的长期映射。

Permanent kernel mappings use a dedicated Page Table in master kernel page tables, the pkmap_page_table variable stores the address of this Page Table.

使用主内核页表中一个专门的页表，其地址存放在pkmap_page_table变量中。

The dedicated Page Table maps the linear addresses starting from PKMAP_BASE.

该页表映射的线性地址从PKMAP_BASE开始。

The pkmap_count array includes LAST_PKMAP counters, one for each entry of the pkmap_page_table Page Table.

pkmap_count数组包含LAST_PKMAP个计数器，pkmap_page_table页表中的每一项都有一个。

Three cases:

* The counter is 0 The corresponding Page Table entry does not map any high-memory page frame and is usable
* The counter is 1 The corresponding Page Table entry does not map any high-memory page frame, but it cannot be used because the corresponding TLB entry has not been flushed
* The counter is n The corresponding Page Table entry maps a high-memory page frame, which is used by exactly n-1 kernel components

三种情况：

* 计数器为0 对应的页表项没有映射任何高端内存页框，并且是可用的
* 计数器为1 对应的页表项没有映射任何高端内存页框，但是不能使用，因为自从最后一次使用以来，其相应的TLB表项还未被刷新
* 计数器为n 相应的页表项映射一个高端内存页框，有n-1个内核成分在使用这个页框

#### 临时内核映射 Temporary kernel mappings

### 伙伴系统算法 The Buddy System Algorithm

There are essentially two ways to aviod external fragmentation:

* Use the paging circuitry to map groups of noncontiguous free page frames into intervals of contiguous linear addresses
* Develop a suitable technique to keep track of the existing blocks of free contiguous page frames, avoiding as much as possible the need to split up a large free block to satisfy a request for a smaller one

避免外碎片的方法有两种：

* 利用分页单元把一组非连续的空闲页框映射到连续的线性地址空间
* 开发一种适当的技术来记录现存的空闲连续页框的情况，以尽量避免为满足对小块的请求而分割大的空闲块

The second approach is preferred by the kernel for three good reasons:

* In some cases, contiguous page frames are really necessary
* it offers the big advantage of leaving the kernel paging tables unchanged
* Large chunks of contiguous physical memory can be accessed by the kernel through 4MB pages, this reduces the Translation Lookside Buffers misses, thus significantly speeding up the average memory access time

内核首选第二种方法：

* 在某些情况下，连续的页框是必要的
* 起保持内核页表不变的作用
* 内核通过4MB的页可以访问大块连续的物理内存，减少TLB的失效率

#### 数据结构 Data structures

#### 分配块 Allocating a block

#### 释放块 Freeing a block

### 每CPU页框高速缓存 The Per-CPU Page Frame Cache

内核经常请求和释放单个页框，为了提高系统性能，每个内存管理区定义了一个"每CPU"页框高速缓存。

所有"每CPU"高速缓存包含一些预先分配的页框，他们被用于满足本地CPU发出的单一内存请求。

#### 通过每CPU页框高速缓存分配页框 Allocating page frames through the per-CPU page frame caches

#### 释放页框到每CPU页框高速缓存 Releasing page frames to the per-CPU page frame caches

### 管理区分配器 The Zone Allocator

管理区分配器是内核页框分配器的前端。

管理区分配器必须满足几个目标：

* 它应当保护保留的页框池
* 当内存不足且允许阻塞当前进程时，它应当触发页框回收算法；一旦某些页框被释放，管理区分配器将再次尝试分配
* 如果可能，它应当保存小而珍贵的ZONE_DMA内存管理区。

#### 释放一组页框 Releasing a group of page frames

管理区分配器同样负责释放页框。

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
