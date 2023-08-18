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

### 超级块对象 Superblock Objects

### 索引节点对象 Inode Objects

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

