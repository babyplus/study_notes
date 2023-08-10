# 内核_块设备驱动程序_Block_Device_Drivers  

*20230810*  

## 块设备的处理 Block Devices Handling

### 扇区 Sectors

### 块 Blocks

### 段 Segments

## 通用块层 The Generic Block Layer

### The Bio Structure

### 磁盘和磁盘分区的表示 Representing Disks and Disk Partitions

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

