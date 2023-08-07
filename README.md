# 内存管理_Memory_Management

*20230804*  

## 页框管理 Page Frame Management

### 页描述符 Page Descriptors

### 非一致内存访问 Non-Uniform Memory Access (NUMA)

### 内存管理区 Memory Zones

### 保留的页框池 The Pool of Reserved Page Frames

### 分区页框分配器 The Zoned Page Frame Allocator

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