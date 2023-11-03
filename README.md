# 内核_页高速缓存_The_Page_Cache  

*20230811*  

## 页高速缓存 The Page Cache

The page cache is the main disk cache used by the Linux kernel.

页高速缓存是Linux内核所使用的主要磁盘高速缓存。

New pages are added to the page cache to satisfy User Mode processes` read requests.

新页被追加到页高速缓存以满足用户态进程的读请求。

If the page is not already in the cache, a new entry is added to the cache and filled with the data read from the disk.

如果页不在高速缓存中，新页就被加到高速缓存中，然后用从磁盘读出的数据填充他。

If there is enough free memory, the page is kept in the cache for an indefinite period of time and can then be reused by other processes without accessing the disk.

如果内存有足够的空闲空间，就让该页在高速缓存中长期保留，使其他进程再使用该页时不再访问磁盘。

Similarly, before writing a page of data to a block device, the kernel verifies whether the corresponding page is already included in the cache, if not, a new entry is add to the cache and filled with the data to be written on disk.

把一页数据写到块设备之前，内核首先检查对应的页是否已经在高速缓存中，如果不在，就要先在其中增加一个新项，并用要写到磁盘的数据填充该项。

The pages included in the page cache can be of  the following types:

* Pages containing data of regular files
* Pages containing directories
* Pages containing data directly read from block device files(skipping the filesystem layer)
* Pages containing data of User Mode processes that have been swapped out on disk
* Pages belonging to files of special filesystems

页高速缓存中的页有可能是下面的类型：

* 含有普通文件数据的页
* 含有目录的页
* 含有直接从块设备文件（跳过文件系统层）读出的数据的页
* 含有用户态进程数据的页，但页中的数据已经被交换到磁盘
* 属于特殊文件系统文件的页

Kernel designers have implemented the page cache to fulfill two main requirements:

* Quickly locate a specific page containing data relative to a given owner
* Keep track of how every page in the cache should be handled when reading or writing its content

页高速缓存主要为了满足下面两种需求：

* 快速定位含有给定所有者相关数据的特定页
* 记录在读或写页中的数据时应当如何处理高速缓存中的每个页

### address_space对象 The address_space Object

页高速缓存的核心结构是address_space对象，他是一个嵌入在页所有者的索引节点对象中的数据结构。

高速缓存中的许多页可能属于同一个所有者，从而可能被链接到同一个address_space对象。

每个页描述符都包括把页链接到页高速缓存的两个字段mapping和index。

### 基树 The Radix Tree

### 页高速缓存的处理函数 Page Cache Handling Functions

#### 查找页 Finding a page

#### 增加页 Adding a page

#### 删除页 Removing a page

#### 更新页 Updating a page

### 基树的标记 The Tags of the Radix Tree

## 把块存放在页高速缓存中 Storing Blocks in the Page Cache

### 块缓冲区和缓冲区首部 Block Buffers and Buffer Heads

### 管理缓冲区首部 Managing the Buffer Heads

### 缓冲区页 Buffer Pages

### 分配块设备缓冲区页 Allocating Block Device Buffer Pages

### 释放块设备缓冲区页 Releasing Block Device BUffer Pages

### 在页高速缓存中搜索块 Searching Blocks in the Page Cache

#### The __find_get_block() function

#### The __getblk() function

#### The __bread() function

### 向通用块层提交缓冲区首部 Submitting Buffer Heads to the Generic Block Layer

#### The submit_bh() function

#### The ll_rw_block() function

## 把脏页写进磁盘 Writing Dirty Pages to Disk

### pdflush 内核线程 The pdflush Kernel Threads

### 搜索要刷新的脏页 Looking for Dirty Pages To Be Flushed

### 回写陈旧的脏页 Retrieving Old Dirty Pages

## sync(), fsync() and fdatasync()

### The sync() System Call

### The fsync() and fdatasync() System Calls
