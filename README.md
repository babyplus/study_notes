# 内核_回收页框_Page_Frame_Reclaiming  

*20230813*  

## 页框回收算法 The Page Frame Reclaiming Algorithm

When the system load is low, the RAM is filled mostly by the disk caches and the few runnig processes can benefit from the information stored in them. However, when the system load increases, the RAM is filled mostly by pages of the processes and the caches are shrunken to make room for additional processes.

当系统负载较低时，RAM的大部分由磁盘高速缓存占用，很少正在运行的进程可以从中受益；当系统负载增加时，RAM的大部分则由进程页占用，高速缓存就会缩小从而给后来的进程让出空间。

The cache system doesn`t know if and when processes will reuse some of the cached data and is therefore unable to identify the portions of the cache that should be released.

高速缓存系统并不知道进程是否会重新使用某些缓存数据，因此不能确定高速缓存的哪些部分应该被释放。

Because the demand paging mechanism, User Mode processes get page frames as long as they proceed with their execution, however, demand paging has no way to force the processes to release the page frames whenever they are no longer used.

请求调页机制，只要用户态进程继续执行，他们就能获得页框；然而，请求调页没有办法强制进程释放不再使用的页框。

The page frame reclaiming algorithm of Linux kernel refilles the lists of free blocks of the buddy system by "stealing" page frames from both User Mode processes and kernel caches.

Linux内核的页框回收算法采取从用户态进程和内核高速缓存“窃取”页框的方法补充伙伴系统的空闲块列表。

One of the goals of the page frame reclaiming is thus to conserve a minimal pool of free page frames so that the kernel may safely recover from "low on momery" conditions.

页框回收算法的目标之一就是保存最少的空闲页框池以便内核可以安全地从“内存紧缺”的情形中恢复过来。

### 选择目标页 Selecting a Target Page

Clearly the page frames selected by the PFRA must be non-free, that is, they must not be already included in one of the free_area arrays used by the buddy system.

页框回收算法选取的页框肯定不是空闲的，即这些页框原本不在伙伴系统的任何一个free_area数组中。

The PFRA handles the page frames in different ways, according to their contents:

* Unreclaimable: No reclaiming allowed or needed

1. Free pages (included in buddy system lists)
2. Reserved pages (with PG_reserved flag set)
3. Pages dynamically allocated by the kernel
4. Pages in the Kernel Mode stacks of the processes
5. Temporarily locked pages (with PG_locked flag set)
6. Memeory locked pages (in memory regions with VM_LOCKED flag set)

* Swappable: Save the page contents in a swap area

1. Anonymous pages in User Mode address spaces
2. Mapped pages of tmpfs filesystem (e.g., pages of IPC shared memory)

* Syncable: Synchronize the page with its image on disk, if necessary

1. Mapped pages in User Mode address spaces
2. Pages included in the page cache and containing data of disk files
3. Block device buffer pages
4. Pages of some disk cache (e.g., the inode cache)

* Discardable: Nothing to be done

1. Unused pages included in memory caches (e.g., slab allocator caches)
2. Unused pages of the dentry cache

页框回收算法按照页框所含内容，以不同方式处理页框：

* 不可回收页：不允许也无需回收

1. 空闲页（包含在伙伴系统列表中）
2. 保留页（PG_reserved标志置位）
3. 内核动态分配页
4. 进程内核态堆栈页
5. 临时锁定页（PG_locked标志置位）
6. 内存锁定页（在线性区中且VM_LOCKED标志置位）

* 可交换页：将页的内容保存在交换区

1. 用户态地址空间的匿名页
2. tmpfs文件系统的映射页（如IPC共享内存的页）

* 可同步页：必要时，与磁盘映像同步这些页

1. 用户态地址空间的映射页
2. 存有磁盘文件数据且在页高速缓存中的页
3. 块设备缓冲区页
4. 某些磁盘高速缓存的页（如索引点高速缓存）

* 可丢弃页：无需操作

1. 内存高速缓存中的未使用页（如slab分配器高速缓存）
2. 目录项高速缓存的未使用页

### PFRA设计 Design of the PFRA

Selecting the proper target pages is perhaps the most sensitive issue in kernel design.

选择合适的目标页是内核设计中最精巧的问题。

A few general rules adopted by the PFRA:

* Free the "harmless" pages first
* Make all pages of a User Mode process reclaimable
* Reclaim a shared page frame by unmapping at once all page table entries that reference it
* Reclaim "unused" pages only

页框回收算法采用几个原则：

* 首先释放无害页
* 将用户态进程的所有页定为可回收页
* 同时取消引用一个共享页框的所有页表项的映射，就可以回收该共享页框
* 只回收“未用”页

## 反向映射 Reverse Mapping

### 匿名页的反向映射 Reverse Mapping for Anonymous Pages

#### The try_to_unmap_anon() function

#### The try_to_unmap_one() function

### 映射页的反向映射 Reverse Mapping for Mapped Pages

#### 优先搜索树 The priority search tree

#### The try_to_unmap_file() function

## PFRA实现 Implementing the PFRA

### 最近最少使用（LRU）链表 The Least Recently Used(LRU) Lists

#### 在LRU链表之间移动页  Moving pages across the LRU lists

#### The mark_page_accessed() function

#### The page_referenced() function

#### The refill_inactive_zone() function

### 内存紧缺回收 Low On Memory Reclaiming

#### The free_more_memory() function

#### The try_to_free_pages() function

#### The shrink_caches() function

#### The shrink_zone() function

#### The shrink_cache() function

#### The shrink_list() function

#### The pageout() function

### 回收可压缩磁盘高速缓存的页 Reclaiming Pages of Shrinkable Disk Caches

#### 从目录项高速缓存回收页框 Reclaiming page frames from the dentry cache

#### 从索引点高速缓存回收页框 Reclaiming page frames from the inode cache

### 周期回收 Periodic Reclaiming

#### kswapd内核线程 The kswapd kernel threads

#### The cache_reap() function

### 内存不足删除程序 The Out of Memory Killer

### 交换标记 The Swap Token

## 交换 Swapping

### 交换区 Swap Area

#### 创建和激活交换区 Creating and activating a swap area

#### 如何在交换区中分布页 How to distribute pages in the swap areas

### 交换区描述符 Swap Area Descriptor

### 换出页标识符 Swapped-Out Page Identifier

### 激活和禁用交换区 Activating and Deactivating a Swap Area

#### sys_swapon()服务例程 The sys_swapon() service routine

#### sys_swapoff()服务例程 The sys_swapoff() service routine

#### The try_to_unuse() function

### 分配和释放页槽 Allocating and Releasing a Page Slot

#### The scan_swap_map() function

#### The get_swap_page() function

#### The swap_free() function

### 交换高速缓存 The Swap Cache

#### 交换高速缓存的实现 Swap cache implementation

#### 交换高速缓存的辅助函数 Swap cache helper functions

### 换出页 Swapping Out Pages

#### 向交换高速缓存插入页框 Inserting the page frame in the swap cache

#### 更新页表项  Updating the Page Table entries

#### 将页写入交换区 Writing the page into the  swap area

#### 从交换高速缓存中删除页框 Removing the page frame from the swap cache

### 换入页 Swapping in Pages

#### The do_swap_page() function

#### The read_swap_cache_async() function