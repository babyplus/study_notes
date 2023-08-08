# 内核_虚拟文件系统_The_Virtual_Filesystem  

*20230808*  

## 虚拟文件系统的作用 The Role of the Virtual Filesystem(VFS)

### 通用文件模型 The Common File Model

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

