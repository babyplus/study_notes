# 内核_页高速缓存_The_Page_Cache  

*20230811*  

## 页高速缓存 The Page Cache

### address_space对象 The address_space Object

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