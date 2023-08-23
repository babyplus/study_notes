# 内核_块设备驱动程序_Block_Device_Drivers  

*20230810*  

## 块设备的处理 Block Devices Handling

What the kernel typically does to service the process request:

* The service routine of the read() system call activates a suitable VFS function, passing to it a file descriptor and an offset inside the file
* The VFS function determines if the requested data is already available and how to perform the read operation if necessary
* If the kernel read the data from the block device, thus it must determine the physical location of that data
* The kernel makes use of the generic block layer, which starts the I/O operations that transfer the requested data
* The I/O scheduler sorts the pending I/O data transfer requests according to predefined kernel policies, the purpose is to group requests of data that lie near each other on the physical medium
* The block device drivers take care of the actual data transfer by sending suitable commands to the hardware interfaces of the disk controllers

内核对进程请求给与回应的一般步骤：

* read() 系统调用的服务例程调用一个适当的VFS函数，将文件描述符和文件内的偏移量传递给他
* VFS函数确定所请求数据是否已经存在
* 若从硬盘读取数据，那么就必须确定数据的物理位置
* 内核利用通用块层启动I/O操作来传送所请求的数据
* I/O调度程序把物理介质上相邻的数据请求聚集在一起
* 块设备驱动程序向磁盘控制器的硬件接口发送适当的命令

### 扇区 Sectors

The controllers of the hardware block devices transfer data in chunks of fixed length called "sectors".

硬件块设备控制器采用称为“扇区”的固定长度的块来传送数据。

The I/O scheduler and the block device drivers must manage sectors data.

I/O调度程序和块设备驱动程序必须管理数据扇区。

### 块 Blocks

The Virtual Filesystem, the mapping layer and the filesystems group the disk data in logical units called "blocks".

虚拟文件系统、映射层和文件系统将磁盘数据存放在称为“块”的逻辑单元中。

A block corresponds to the minimal disk storage unit inside a filesystem.

一个块对应的文件系统中一个最小的磁盘存储单元。

### 段 Segments

The block device drivers should be able to copy with "segments" of data: each segment is a memory page or a portion of a memory page, including chunks of data that are physically adjacent on the disk.

块设备驱动程序能够处理数据的“段”， 一个段就是一个内存页或内存页的一部分，它们包含磁盘上物理相邻的数据块。

## 通用块层 The Generic Block Layer

The generic block layer is a kernel component that handles the requests for all block devices in the system:

* Put data buffers in high memory, the page frame(s) will be mapped in the kernel linear address space only when the CPU access the data, and will be unmapped right after.
* The disk data is directly put in the User Mode address space without being copied to the kernel memory first
* Manage logical volumes
* Exploit the advance features of the most recent disk controllers

通用块层处理来自系统中的所有块设备发出的请求：

* 将数据缓冲区放在高端内存，仅当CPU访问其数据时，才将页框映射为内核中的线性地址空间，并在数据访问完后取消映射
* 通过一些附加的手段，将磁盘数据直接存放在用户态地址空间而不是复制到内核内存区。
* 管理逻辑卷
* 发挥大部分新磁盘控制器的高级特性

### The Bio Structure

The core data structure of the generic block layer is a descriptor of an ongoing I/O block device operation called bio.

通用块层的核心数据结构时一个称为bio的描述符，它描述了块设备的I/O操作。

Each I/O essentially includes an identifier for a disk storage area (the initial sector number and the number of sectors included in the storage area),

每个bio结构都包含一个磁盘存储区标识符（存储区中的起始扇区号和扇区数目）和一个或多个描述与I/O操作相关的内存区的段。

### 磁盘和磁盘分区的表示 Representing Disks and Disk Partitions

A disk is a logical block device that is handled by the generic block layer.

磁盘是一个由通用块层处理的逻辑块设备。

A disk is represented by the gendisk object.

磁盘是由gendisk对象描述的。

Hard disks are commonly split into logical partitions.Each block device file may represent either a whole disk or a partition inside the disk.

每个块设备文件要么代表整个磁盘，要么代表磁盘中的某个分区。

If a disk is split in partitions, their layout is kept in an array of hd_struct structures whose address is stored in the part field of the gendisk object.

将一个硬盘分成几个分区，那么其分区表保存在hd_struct结构的数组中，该数组的地址存放在gendisk对象的part字段中。

When the kernel discovers a new disk in the system, it invokes the alloc_disk() function, which allocates and initializes a new gendisk object and, if the new disk is split into several partitions, a suitable array of hd_struct descriptors. Then, it invokes the add_disk() function go insert the new gendisk descriptor into the data structures of the generic block layer.

当内核发现系统中一个新的磁盘时，就调用alloc_disk()函数，该函数分配并初始化一个新的gendisk对象，如果新磁盘被分成了几个分区，那么alloc_disk()还会分配并初始化一个适当的hd_struct类型的数组。然后，内核调用add_disk()函数将新的gendisk对象插入到通用块层的数据结构中。

### 提交请求 Submitting a Request

## I/O调度程序 The I/O Scheduler

### 请求队列描述符 Request Queue Descriptors

### 请求描述符 Request Descriptors

#### 对请求描述符的分配进行管理 Managing the allocation of request descriptors

#### 避免请求队列拥塞 Avoiding request queue congestion

### 激活块设备驱动程序 Activating the Block Device Driver

### I/O调度算法 I/O Scheduling Algorithms

#### Noop 算法 The "Noop" elevator

#### CFQ 算法 The "CFQ" elevator

#### 最后期限 算法 The "Deadline" elevator

#### 预期 算法 The "Anticipatory" elevator

### 向 I/O 调度程序发出请求 Issuing a Request to the I/O Scheduler

#### The blk_queue_bounce() function

## 块设备驱动程序 Block Device Drivers

### 块设备 Block Devices

#### 访问块设备 Accessing a block device

### 注册和初始化设备驱动程序 Device Driver Registration and Initialization

#### 自定义驱动程序描述符 Defining a custom driver descriptor

#### 预定主设备号 Reserving the major number

#### 初始化自定义描述符 Initializing the custom descriptor

#### 初始化gendisk描述符 Initializing the gendisk descriptor

#### 初始化块设备操作表 Initializing the table of block device methods

#### 分配和初始化请求队列 Allocating and initializing a  request queue

#### 设置中断处理程序 Setting up the interrupt handler

#### 注册磁盘 Registering the disk

### 策略例程 The Strategy Routine

### 中断处理程序 The Interrupt Handler

## 打开块设备文件 Opening a Block Device File

