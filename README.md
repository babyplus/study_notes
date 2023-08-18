# 内核_I/O体系结构和设备驱动程序_I/O_Architecture_and_Device_Drivers  

*20230809*  

## I/O体系结构 I/O Architecture

CPU和I/O设备之间的数据通路通常称为I/O总线。

任何I/O设备有且仅能连接一条总线。

总线的类型影响I/O设备的内部设计，也影响着内核如何处理设备。

### I/O端口 I/O Ports

Each device connected to the I/O bus has its own set of I/O addresses, which are usually called I/O ports.

每个连接到I/O总线上的设备都有自己的I/O地址集，通常称为I/O端口。

Four special assembly language instructions called in, ins, out and outs allow the CPU to read from and write into an I/O port.

有四条专用的汇编指令可以允许CPU对I/O端口进行读写。（in、ins、out、outs）

I/O ports may also be mapped into addresses of the physical address space. The process is then able to communicate with an I/O device by issuing assembly language instructions that operate directly on memory. 

I/O端口可以被映射到物理地址空间。因此，处理器和I/O设备之间的通信可以使用对内存直接进行操作的汇编语言指令。

The I/O ports of each device are structured into a set of specialized registers:

* device control register
* device status register
* device input register
* device output register

每个设备的I/O端口都被组织成一组专用寄存器：

* 设备控制寄存器
* 设备状态寄存器
* 设备输入寄存器
* 设备输出寄存器

#### 访问I/O端口 Accessing I/O ports

### I/O接口 I/O Interfaces

An I/O interface is a hardware circuit inserted between a group of I/O ports and the corresponding device controller.

I/O接口是处于一组I/O端口和对应的设备控制器之间的一种硬件电路。

An I/O interface acts as an interpreter that translates the values in the I/O ports into commands and data for the device. In the opposite direction, it detects changes in the device state and corresponding updates the I/O port that plays the role of status register.

I/O接口起翻译器的作用，即把I/O端口中的值转换成设备所需要的命令和数据，在相反方向上检测设备状态的变化，更新状态寄存器。

The circuit can alse be connected through an IRQ line to a Programmable Interrupt Controller, so that it issues interrupt requests on behalf of the device.

I/O接口可以通过一条IRQ线把电路连接到可编程中断控制器，以使它代表相应的设备发出中断请求。

#### 专用I/O接口 Custom I/O interfaces

Devoted to one specific hardware device.

专门用于一个特定的硬件设备。

#### 通用I/O接口 General-purpose I/O interfaces

Used to connect several different hardware devices.

用来连接多个不同的硬件设备。

### 设备控制器 Device Controllers

Essentially, the controler plays two important roles:

* It interprets the high-level commands received from the I/O interface and forces the device to execute specific actions by sending proper sequences of electrical signals to it
* It converts and properly interprets the electrical signals received from the device and modifies (through the I/O interface) the value of the status register.

设备控制器起俩个重要作用：

* 对从I/O接口接收到的高级命令进行解释，并通过向设备发送适当的电信号序列强制设备执行特定的操作
* 对从设备接收到的电信号进行转换和适当地解释，并通过I/O接口修改状态寄存器的值。

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