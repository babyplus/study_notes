# 内核_虚拟文件系统_The_Virtual_Filesystem  

*20230808*  

## 虚拟文件系统的作用 The Role of the Virtual Filesystem(VFS)

The virtual Filesystem is a kernel software layer that handles all system calls related to a standard Unix filesystem.

虚拟文件系统也可以称之为虚拟文件系统转换（VFS），是一个内核软件层，用来处理与Unix标准文件系统相关的所有系统调用。

Filesystems supported by the VFS may be grouped into three main classes:

* Disk-based filesystems
* Network filesystems
* Special filesystems

VFS支持的文件系统可以分为三种主要类型：

* 磁盘文件系统
* 网络文件系统
* 特殊文件系统

### 通用文件模型 The Common File Model

The key idea behind the VFS consist of introducing a common file model captable of representing all supported filesystems.

VFS所隐含的主要思想在于引入了一个通用的文件模型，这个模型能够表示所有支持的文件系统。

more essentially, the Linux kernel cannot hardcode a particular function, it must use a pointer for each operation, the pointer is made to point to the proper function for the particular filesystem being accessed.

Linux内核不能对一个特定的函数进行硬编码，而是对每个操作都必须使用一个指针，指向要访问的具体文件系统的适当函数。

The common file model consists of the following object types:

* The superblock object
* The inode object
* The file object
* The dentry object

通用文件模型由下列对象类型组成：

* 超级块对象
* 索引节点对象
* 文件对象
* 目录项对象

Besides providing a common interface to all filesystem implementations, the VFS has another important fole related to system performance. The most recently used dentry objects are contained in a disk cache named the dentry cache, which speed up the translation from a file pathname to the inode of the last pathname component.

VFS除了能为所有文件系统的实现提供一个通用接口外，还具有另一个与系统性能相关的重要作用。最近最常使用的目录项对象被放在目录项高速缓存的磁盘高速缓存中，以加速从文件路径名到最后一个路径分量的索引节点的转换过程。

A disk cache is a software mechanism. 

磁盘高速缓存属于软件机制。

### VFS所处理的系统调用 System Calls Handle by the VFS

## VFS的数据结构 VFS Data Structures

每个VFS对象都存放在一个适当的数据结构中，其中包括对象的属性和指向对象方法表的指针。

内核可以动态地修改对象的方法，因此可以为对象建立专用的行为。

### 超级块对象 Superblock Objects

超级块对象由super_block结构组成。

所有的超级块对象都以双向循环链表的形式链接在一起。链表中的第一个元素用super_blocks变量来表示，而超级块对象的s_list字段存放指向链表相邻元素的指针。

sb_lock自旋锁保护链表免受多处理器系统上的同时访问。

s_fs_info字段指向属于具体文件系统的超级块信息。

s_dirt标志表示超级块是否脏，磁盘上的数据是否必须要更新。

与超级块关联的方法就是所谓的超级块操作，由数据结构super_operations来描述，该结构的起始地址存放在超级块的s_op字段中。

每个具体的文件系统都可以定义自己的超级块操作。

### 索引节点对象 Inode Objects

文件系统处理文件所需要的所有信息都放在一个名为索引节点的数据结构中。

文件名可以随时更改，但是索引节点对文件是唯一的，并且随着文件的存在而存在。

每个索引节点会复制磁盘索引节点包含的一些数据，如果i_state字段的值等于I_DIRTY_SYNC I_DIRTY_DATASYNC I_DIRTY_PAGES，该索引节点就是"脏"，也就是说，对应的磁盘索引节点必须被更新。

每个索引节点总是出现在下列双向循环链表的某个链表中：

* 有效未使用的索引节点链表
* 正在使用的索引节点链表
* 脏索引节点链表

这些链表通过适当的索引节点对象的i_list字段链接在一起。

每个索引节点对象也包含在每文件系统的双向循环链表中。

索引节点对象还存放在一个称为inode_hashtable的散列表中。散列表加速了对索引节点对象的搜索，前提是系统内核要知道索引节点号及文件所在文件系统对应的超级块对象的地址。

与索引节点对象关联的方法叫索引节点操作，由inode_operations结构来描述，该结构的地址存放在i_op字段中。

### 文件对象 File Objects

### 目录项对象 dentry Objects

### 目录项高速缓存 The dentry Cache

### 与进程相关的文件 Files associated with a Process

## 文件系统类型 Filesystem Types

### 特殊文件系统 Special Filesystems

### 文件系统类型注册 Filesystem Type Registration

## 文件系统处理 Filesystem Handling

### 命名空间 Namespaces

### 文件系统安装 Filesystem Mounting

### 安装普通文件系统 Mounting a Generic Filesystem

#### The do_kern_mount() function

#### 分配超级块对象 Allocating a superblock object

### 安装根文件系统 Mounting the Root Filesystem

#### 安装rootfs文件系统 Mounting the rootfs filesystem

#### 安装实际根文件系统 Mounting the real root filesystem

### 卸载文件系统 Unmounting a Filesystem

## 路径名查找 Pathname Lookup

### 标准路径名查找 Standard Pathname Lookup

### 父路径名查找 Parent Pathname Lookup

### 符号链接的查找 Lookup of Symbolic Links

## VFS系统调用的实现 Implementations of VFS System Calls

### The open() System Call

### The read() and write() System Calls

### The close() System Call

## 文件加锁 File Locking

### Linux文件加锁 Linux File Locking

### 文件锁的数据结构 File-Locking Data Structures

### FL_FLOCK Locks

### FL_POSIX Locks

