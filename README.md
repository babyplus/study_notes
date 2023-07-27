# 内核_内存访问_Memory_Addressing  

*20230725*  

## 内存地址 Memory Addresses

In computing, a memory address is a reference to a specific memory location used at various levels by software and hardware. Memory addresses are fixed-length sequences of digits conventionally displayed and manipulated as unsigned integers. Such numerical semantic bases itself upon features of CPU (such as the instruction pointer and incremental address registers), as well upon use of the memory like an array endorsed by various programming languages.

在计算中，内存地址是指软件和硬件在不同级别上使用的特定内存位置的引用。内存地址是固定长度的数字序列，通常作为无符号整数显示和操作。这种数字语义本身基于CPU的特性(如指令指针和增量地址寄存器)，以及像各种编程语言支持的数组一样使用内存。

```
Logical Address --> Segmentation Unit --> Linear Address
Linear Address --> Paging Unit --> Physical Address
```

### 逻辑地址 Logical addresses

Included in the machine language instructions to specify the address of an operand or of an instruction. This type of address embodies the well-known 80 × 86 segmented architecture that forces MS-DOS and Windows programmers to divide their programs into segments . Each logical address consists of a segment and an offset (or displacement) that denotes the distance from the start of the segment to the actual address.

包含在机器语言指令中，用于指定指令的操作数或指令的地址。这种类型的地址体现了众所周知的80x86分段架构，它迫使MS-DOS和Windows程序员将他们的程序划分为段。每个逻辑地址由一个段和一个偏移量(或位移)组成，偏移量表示从段的开始到实际地址的距离。

### 线性地址 Linear addresses

A single 32-bit unsigned integer that can be used to address up to 4 GB — that is, up to 4,294,967,296 memory cells. Linear addresses are usually represented in hexadecimal notation; their values range from 0x00000000 to 0xffffffff.

单个32位无符号整数，可用于寻址最多4gb—即最多4,294,967,296个内存单元。线性地址通常用十六进制表示法表示;取值范围为0x00000000到0xffffffff。

### 物理地址 Physical addresses

Used to address memory cells in memory chips. They correspond to the electrical signals sent along the address pins of the microprocessor to the memory bus. Physical addresses are represented as 32-bit or 36-bit unsigned integers.

用于寻址存储芯片中的存储单元。它们与沿着微处理器的地址引脚发送到存储器总线的电信号相对应。物理地址表示为32位或36位无符号整数。

## 硬件中的分段 Segmentation in Hardware

### 段选择器和段寄存器 Segment Selectors and Segmentation Registers

A logical address consists of two parts: a segment identifier and an offset that specifies the relative address within the segment.

逻辑地址由两部分组成:段标识符和指定段内相对地址的偏移量。

*段标识符就是段选择器，是个16位的字段；而偏移量是个32位的字段*

#### 段寄存器 Segmentation Registers

To make it easy to retrieve segment selectors quickly, the processor provides segmentation registers whose only purpose is to hold Segment Selectors.

为了方便快速检索段选择器，处理器提供了段寄存器，其唯一目的是保存段选择器。

* cs 代码段寄存器
* ss 栈段寄存器
* ds 数据段寄存器
* es fs gs 一般用途

### 段描述符 Segment Descriptors

Each segment is represented by an 8-byte Segment Descriptor that describes the segment characteristics.

每个段由一个8字节的段描述符表示，该段描述符描述了段的特征。

#### 全局描述符表 GDT

#### 局部描述符表 LDT

#### 段描述符字段 Segment Descriptor fields

### 快速访问段描述符 Fast Access to Segment Descriptors

#### 非编程寄存器 Nonprogrammable Register

*缓存GDT或LDT中的段描述符细节*

#### 段选择符字段 Segment Selector fields

### 分段单元 Segmentation Unit

* Examines the TI field of the Segment Selector
* Computes the address of the Segment Descriptor from the index field of the Segment Selector
* Adds the offset of the logical address to the Base field of the Segment Descriptor, thus obtaining the linear address.

* 检查段选择器的Tl字段
* 从段选择器的索引字段计算段描述符的地址
* 将逻辑地址的偏移量添加到段描述符的Base字段，从而获得线性地址。

## 系统中的分段 Segmentation in Linux

四个主要的Linux段：

* 用户代码段 __USER_CS
* 用户数据段 __USER_DS
* 内核代码段 __KERNEL_CS
* 内核数据段 __KERNEL_DS

The linear addresses associated with such segments all start at 0 and reach the addressing limit. This means that all processes, either in User Mode or in Kernel Mode, may use the same logical addresses. Another consequence is logical addresses coincide with linear addresses.

所有段都是从0x00000000开始的，意味着在用户态或系统态下的所有进程可以使用相同的逻辑地址并且逻辑地址与线性地址是一致的。

### The Linux GDT

### The Linux LDTs

## 硬件中的分页 Paging in Hardware

## 系统中的分页 Paging in Linux
