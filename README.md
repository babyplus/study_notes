# 内核_访问文件_Accessing_Files  

*20230812*  

## 读写文件 Reading and Writing a File

### 从文件中读取数据 Reading from a File

#### 普通文件的readpage方法 The readpage method for regular files

#### 块设备文件的readpage方法 The readpage method for block device files

### 文件的预读 Read-Ahead of Files

#### The page_cache_readahead() function

#### The handle_ra_miss() function

### 写入文件 Writing to a File

#### 普通文件的prepare_write和commit_write方法 The prepare_write and commit_write methods for regular files

#### 块设备文件的prepare_write和commit_write方法 The prepare_write and commit_write methods for block device files

### 将脏页写到磁盘 Writing Dirty Pages to Disk

## 内存映射 Memory Mapping

### 内存映射的数据结构 Memory Mapping Data Structures

### 创建内存映射 Creating a Memory Mapping

### 撤销内存映射 Destroying a Memory Mapping

### 内存映射的请求调页 Demand Paging for Memory Mapping

### 把内存映射的脏页刷新到磁盘 Flushing Dirty Memory Mapping Pages to Disk

### 非线性内存映射 Non-Linear Memory Mappings

## 直接I/O映射 Direct I/O Transfers

## 异步I/O Asynchronous I/O

### Linux 2.6 中的异步I/O Asynchronous I/O in Linux 2.6

#### 异步I/O环境 The asynchronous I/O context

#### 提交异步I/O操作 Submitting the asynchronous I/O operations