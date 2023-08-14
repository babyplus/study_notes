# 内核_回收页框_Page_Frame_Reclaiming  

*20230813*  

## 页框回收算法 The Page Frame Reclaiming Algorithm

### 选择目标页 Selecting a Target Page

### PFRA设计 Design of the PFRA

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