# 内核_Ext2和Ext3文件系统_The_Ext2_and_Ext3_Filesystems  

*20230814*  

## Ext2的一般特征 General Characteristics of Ext2

The following features contribute to the efficiency of Ext2:

* The system administrator may choose the optimal block size depending on the expected average file length
* The system administrator may choose how many inodes to allow for a partition of a given size, depending on the expected number of files to be stored on it
* The filesystem partitions disk blocks into groups
* The filesystem preallocates disk data blocks to regular files before they are actually used.
* Fast symbolic links are supported

有助于效率的特点：

* 系统管理员可以根据预期的文件平均长度来选择最佳块的大小
* 系统管理员可以根据在给定大小的分区上预计存放的文件数来选择给该分区分配多少索引节点
* 文件系统把磁盘块分为组，每组包含存放在相邻磁道上的数据块和索引节点
* 在磁盘数据块被实际使用前，文件系统就把这些块预分配给普通文件
* 支持快速符号链接

The Second Extended Filesystem includes other features that make it both robust and flexible:

* A careful implementation of file-updating that minimizes the impact of system crashes
* Support for automatic consistency checks on the filesystem status at boot time
* Support for immutable files and for append-only files
* Compatible with both the SVR4 and the BSD

健壮又灵活的特点：

* 文件更新策略的谨慎实现将系统奔溃的影响减到最少
* 在启动时支持对文件系统的状态进行自动的一致性检查
* 支持不可变的文件和仅追加的文件
* 同时兼容SVR4以及BSD

Other features that are needed but not included:

* Block fragmentation
* Handling of transparently compressed and encrypted files
* Logical deletion
* Journaling

其他需要但是却不包含的特点：

* 块片
* 透明地处理压缩和加密文件
* 逻辑删除
* 日志

## Ext2磁盘数据结构 Ext2 Disk Data Structures

### 超级块 Superblock

### 组描述符和位图 Group Descriptor and Bitmap

### 索引节点表 Inode Table

### 索引节点的增强属性 Extended Attributes of an Inode

### 访问控制列表 Access Control Lists

### 各种文件类型如何使用磁盘块 How Various File Types Use Disk Blocks

#### 普通文件 Regular file

#### 目录 Directory

#### 符号链接 Symbolic link

#### 设备文件、管道和套接字 Device file, pipe and socket

## Ext2的内存数据结构 Ext2 Memory Data Structures

### Ext2的超级块对象 Ext2 Superblock Object

### Ext2的索引节点对象 Ext2 Inode Object

## 创建Ext2文件系统 Creating the Ext2 Filesystem

## Ext2的方法 Ext2 Methods

### Ext2超级块的操作 Ext2 Superblock Operations

### Ext2索引节点的操作 Ext2 Inode Operations

### Ext2的文件操作 Ext2 File Operations

## 管理Ext2磁盘空间 Managing Ext2 Disk Space

### 创建索引节点 Creating inodes

### 删除索引节点 Deleting inodes

### 数据块寻址 Data Blocks Addressing

### 文件的洞 File Holes

### 分配数据块 Allocating a Data Block

### 释放数据块 Releasing a Data Block

## Ext3文件系统 The Ext3 Filesystem

### 日志文件系统 Journaling Filesystems

### Ext3日志文件系统 The Ext3 Journaling Filesystem

### 日志块设备层 The Journaling Block Device Layer

#### 日志记录 Log records

#### 原子操作处理 Atomic operation handles

#### 事务 Transactions

### 日志如何工作 How Journaling Works