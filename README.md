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

任何Ext2分区中的第一个块从不受Ext2文件系统的管理，因为这一块是为分区的引导扇区所保留的。

Ext2分区的其余部分分成块组。·

块组中的每个块包含下列信息之一：

* 文件系统的超级块的一个拷贝
* 一组块组描述符的拷贝
* 一个数据块位图 
* 一个索引节点位图
* 一个索引节表
* 属于文件的一大块数据，即数据块

### 超级块 Superblock

Ext2在磁盘上的超级块存放在一个ext2_super_block结构中。

### 组描述符和位图 Group Descriptor and Bitmap

每个组块都有自己的组描述符，它是一个ext2_group_desc结构。

### 索引节点表 Inode Table

索引节点表由一连串连续的块组成，其中每一块包含索引节点的一个预定义号。

索引节点表的第一个块的块号存放在组描述符的bg_inode_table字段中。

所有索引节点的大小相同，即128字节。

VFS模型要求每个文件有不同的索引节点号。在Ext2中，没有必要在磁盘上存放文件的索引节点号与相应块号之间的转换，因为后者的值可以从块组号和它在索引节点表中的相对位置而得出。

### 索引节点的增强属性 Extended Attributes of an Inode

引入增强属性克服的问题：

* 一个Ext2索引节点的128个字符空间中充满了信息，只有少许空间可以增加新的字段
* 将索引节点的长度增加至256不仅相当浪费，而且使用不同索引节点长度的Ext2文件系统之间还会造成兼容问题

### 访问控制列表 Access Control Lists

访问控制列表可以与每个文件关联，用户可以为他的文件限定可以访问的用户（或用户组）名称以及相应的权限。

Linux2.6通过索引节点的增强属性完整实现访问控制列表。

### 各种文件类型如何使用磁盘块 How Various File Types Use Disk Blocks

Ext2所认可的文件类型以不同的方式使用数据块。

Ext2文件类型：

0. 未知
1. 普通文件
2. 目录
3. 字符设备
4. 块设备
5. 命名管道
6. 套接字
7. 符号链接

#### 普通文件 Regular file

普通文件只有在开始有数据时才需要数据块。普通文件在刚开始创建时是空的，并不需要数据块；可以用truncate()或open()系统调用清空它。

#### 目录 Directory

Ext2以一种特殊的文件实现了目录，这种文件的数据块把文件名和相应的索引节点号存放在一起。

Ext2目录项中的字段：

* inode
* rec_len
* name_len
* file_type
* name

删除一个目录项，把inode字段设置为0，并适当地增加前一个有效目录项rec_len字段的值就足够了。

#### 符号链接 Symbolic link

如果符号链接的路径名小于等于60个字符，就把它存放在索引节点的i_blocks字段，如果路径名大于60个字符，就需要一个单独的数据块。

#### 设备文件、管道和套接字 Device file, pipe and socket

这些类型的文件不需要数据块。所有必要信息都存放在索引节点中。

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
