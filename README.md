# 内核_I/O体系结构和设备驱动程序_I/O_Architecture_and_Device_Drivers  

*20230809*  

## I/O体系结构 I/O Architecture

### I/O端口 I/O Ports

#### 访问I/O端口 Accessing I/O ports

### I/O接口 I/O Interfaces

#### 专用I/O接口 Custom I/O interfaces

#### 通用I/O接口 General-purpose I/O interfaces

### 设备控制器 Device Controllers

## 设备驱动程序模型 The Device Driver Model

### sysfs文件系统 The sysfs Filesystem

### kobjects

#### kobjects, ksets, and subsystems

#### 注册kobject、kset和subsystem Registering kobjects, ksets, and subsystems

### 设备驱动程序模型的组件 Components of the Device Driver Model

#### 设备 Devices

#### 驱动程序 Drivers

#### 总线 Buses

#### 类 Classes

## 设备文件 Device Files

### 设备文件的用户态处理 User Mode Handling of Device Files

#### 动态分配设备号 Dynamic device number assignment

#### 动态创建设备文件 Dynamic device file creation

### 设备文件的VFS处理 VFS Handling of Device Files

## 设备驱动文件 Device Drivers

### 注册设备驱动程序 Device Driver Registration

### 初始化设备驱动程序 Device Driver Initialization

### 监控I/O操作 Monitoring I/O Operations

#### 轮询模式 Polling mode

#### 中断模式 Interrupt mode

### 访问I/O共享存储器 Accessing the I/O Shared Memory

### 直接内存访问 Direct Memory Access (DMA)

#### 同步DMA和异步DMA Synchronous and asynchronous DMA

#### DMA传送的辅助函数 Helper functions for DMA transfers

#### 总线地址 Bus addresses

#### 高速缓存的一致性 Cache coherency

#### 一致性DMA映射的辅助函数 Helper functions for coherent DMA mappings

#### 流式DMA映射的辅助函数 Helper functions for streaming DMA mappings

### 内核支持的级别 Levels of Kernel Support

## 字符设备驱动程序 Character Device Drivers

### 分配设备号 Assigning Device Numbers

#### The register_chrdev_region() and alloc_chrdev_region() functions

#### The register_chrdev() function

### 访问字符设备驱动程序 Accessing a Character Device Driver

### 字符设备的缓冲策略 Buffering Strategies for Character Devices