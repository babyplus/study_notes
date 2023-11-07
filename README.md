# 内核_内存寻址_Memory_Addressing  

*20230725*  

## 内存地址 Memory Addresses

In computing, a memory address is a reference to a specific memory location used at various levels by software and hardware.  Memory addresses are fixed-length sequences of digits conventionally displayed and manipulated as unsigned integers.  Such numerical semantic bases themselves upon features of the CPU (such as the instruction pointer and incremental address registers), as well as upon the use of the memory like an array endorsed by various programming languages.

在计算中，内存地址是指软件和硬件在不同级别上使用的特定内存位置的引用。内存地址是固定长度的数字序列，通常作为无符号整数显示和操作。这种数字语义本身基于CPU的特性(如指令指针和增量地址寄存器)，以及像各种编程语言支持的数组一样使用内存。

```
Logical Address --> Segmentation Unit --> Linear Address
Linear Address --> Paging Unit --> Physical Address
```

### 逻辑地址 Logical addresses

Logical addresses is included in the machine language instructions to specify the address of an operand or of an instruction. This type of address embodies the well-known 80 × 86 segmented architecture that forces MS-DOS and Windows programmers to divide their programs into segments. Each logical address consists of a segment and an offset (or displacement) that denotes the distance from the segment`s start to the actual address.

包含在机器语言指令中，用于指定指令的操作数或指令的地址。这种类型的地址体现了众所周知的80x86分段架构，它迫使MS-DOS和Windows程序员将他们的程序划分为段。每个逻辑地址由一个段和一个偏移量(或位移)组成，偏移量表示从段的开始到实际地址的距离。

### 线性地址 Linear addresses

A single 32-bit unsigned integer can be used to address up to 4 GB — that is, up to 4,294,967,296 memory cells. Linear addresses are usually represented in hexadecimal notation; their values range from 0x00000000 to 0xffffffff.

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

为了方便快速检索段选择器，处理器提供了段寄存器，其唯一目的是保存段选择符。

* cs 代码段寄存器
* ss 栈段寄存器
* ds 数据段寄存器
* es fs gs 一般用途

### 段描述符 Segment Descriptors

Each segment is represented by an 8-byte Segment Descriptor that describes the segment characteristics.

每个段由一个8字节的段描述符表示，该段描述符描述了段的特征。

### 快速访问段描述符 Fast Access to Segment Descriptors

#### 非编程寄存器 Nonprogrammable Register

*缓存GDT或LDT中的段描述符细节*

#### 段选择符字段 Segment Selector fields

### 分段单元 Segmentation Unit

Examines the TI field of the Segment Selector; Computes the address of the Segment Descriptor from the index field of the Segment Selector; Adds the offset of the logical address to the Base field of the Segment Descriptor, thus obtaining the linear address.

检查段选择器的Tl字段;从段选择器的索引字段计算段描述符的地址;将逻辑地址的偏移量添加到段描述符的Base字段，从而获得线性地址。

## 系统中的分段 Segmentation in Linux

四个主要的Linux段：

* 用户代码段 __USER_CS
* 用户数据段 __USER_DS
* 内核代码段 __KERNEL_CS
* 内核数据段 __KERNEL_DS

The linear addresses associated with such segments all start at 0 and reach the addressing limit. This means that all processes, either in User Mode or in Kernel Mode, may use the same logical addresses. Another consequence is logical addresses coincide with linear addresses.

所有段都是从0x00000000开始的，意味着在用户态或系统态下的所有进程可以使用相同的逻辑地址并且逻辑地址与线性地址是一致的。

### The Linux GDT

In uniprocessor systems there is only one GDT, while in multiprocessor systems there is one GDT for every CPU in the system. Each GDT includes 18 segment descriptors and 14 null,unused,or reserved entries.

在单处理器系统中只有一个GDT，而在多处理器系统中每个CPU对应一个GDT。每个GDT包含18个段描述符和14个空的、未使用的、或保留的项。

* null 0x0
* reserved
* reserved
* reserved
* not used
* not used
* TLS #1 0x33
* TLS #2 0x3b
* TLS #3 0x43
* reserved
* reserved
* reserved
* kernel code 0x60 __KERNEL_CS
* kernel data 0x68 __KERNEL_DS
* user code 0x73 __USER_CS
* user data 0x7b __USER_DS
* TSS 0x80
* LDT 0x88
* PNPBIOS 32-bit code 0x90
* PNPBIOS 16-bit code 0x98
* PNPBIOS 16-bit code 0xa0
* PNPBIOS 16-bit code 0xa8
* PNPBIOS 16-bit code 0xb0
* APMBIOA 32-bit code 0xb8
* APMBIOA 16-bit code 0xc0
* APMBIOA data 0xc8
* not used
* not used
* not used
* not used
* not used
* double fault TSS 0xf8

All GDTs are stored in the cpu_gdt_table array, while the addresses and sizes of the GDTs (used when initializing the gdtr registers) are stored in the cpu_gdt_descr array.

所有的GDT都存放在cpu_gdt_table数组中，而所有GDT的地址和他们的大小（当初始化gdtr寄存器时使用）被存放在cpu_gdt_descr数组中。

#### 四个用户态和内核态下的代码段和数据段 Four user and kernel code and data segments

#### 一个任务状态段 A Task State Segment

#### 一个包含缺省局部描述符表的段 A segment including the default LDT

#### 三个局部线程存储段 Three Thread-Local Storage segments

#### 三个与高级电源管理（APM）相关的段 Three segments related to Advanced Power Management

#### 五个与即插即用（PnP）功能的BIOS服务程序相关的段 Five segments related to Plug and Play BIOS services.

#### 一个被内核用来处理“双重错误”异常的特殊TSS段 A special TSS segment used by the kernel to handle "Double Fault" exceptions

### The Linux LDTs

Most Linux User Mode applications do not make use of a LDT, thus the kernel defines a default LDT to be shared by most processes.

大多数用户态下的Linux程序不使用局部描述符表，这样内核就定义了一个缺省的LDT供大多数进程共享。

## 硬件中的分页 Paging in Hardware

The paging unit translates linear addresses into physical ones.

分页单元把线性地址转换成物理地址。

Linear addresses are grouped in fixed-length intervals called pages.

线性地址被分成以固定长度为单位的组，称为页。

Contiguous linear addresses within a page are mapped into contiguous physical addresses.

页内部连续的线性地址被映射到连续的物理地址中。

The Paging unit thinks of all RAM as partitioned into fixed-length page frames (sometimes referred to as physical pages).

分页单元把所有的RAM分成固定长度的页框（有时叫做物理页）。

Each page frame contains a page - that is, the length of a page frame coincides with that of a page.

每个页框包含一个页并且长度一致。

Page frame is a consitituent of main memory; A page is a block of data, which may be stored in any page frame or on disk.

页框是主存的一部分；页是一个数据块，可以存放在任何页框或者磁盘。

### 常规分页 Regular Paging

The 32 bits of a linear address are divided into three field:

* Directory: The most significant 10 bits
* Table: The intermediate 10 bits
* Offset: The least significant 12 bits

32位的线性地址被分成3个域：

* 目录：最高10位
* 页表：中间10位
* 偏移量：最低12位（2的12次方是4096，一个页框也是4k大小，相当于从页表中找出页所在的页框的物理地址，然后通过偏移量找到具体位置）

The translation of linear addresses is accomplished in two steps, each based on a type of translation table. 

线性地址的转换分两步完成，每一步都基于一种转换表，第一种转换表称为页目录表，第二种转换表被称为页表。

### 拓展分页 Extended Paging 

Extended paging allows page frames to be 4MB instead of 4KB in size, the kernel can do without intermediate Page Tables and thus save memory and preserve TLB entries.

拓展分页允许页框大小为4MB（2的22次方是4M），内核可以不用中间的页表进行地址转换，从而节省内存并保留TLB项。

### 硬件保护方案 Hardware Protection Scheme

Only two privilege levels are associated with pages and Page Tables, because privileges are controlled by the User/Supervisor flag, When this flag is 0, the page can be addressed only when the CPL is less than 3；when the flag is 1, the page can always be addressed. 

页和页表相关的特权级只有两个，由页目录项和页表项结构体中的User/Supervisor标志控制，若该标志为0，只有当CPL小于3时才能对页寻址，若为1，则总能对页寻址。

### 常规分页举例 An Example of Regular Paging

### 物理地址扩展（PAE）分页机制 The Physical Address Extension (PAE) Paging Machanism

Intel increased the number of pins from 32 to 36, bringing the addressing capacity to 2^26(64GB).

Intel通过把管脚数从32增加到36，寻址能力达到2^26(64GB) 。

With the Pentium Pro processor, Intel introduced a mechanism called Physical Address Extension that translates 32-bit linear addresses into 36-bit physical ones.

从 Pentium Pro 处理器开始，Intel 引入一种叫做物理地址扩展的机制，把32位的线性地址转换为36位物理地址。

Intel has changed the paging mechanism in order to support PAE, the linear addresses are still 32 bits long, this forces kernel programmers to reuse the same linear addresses to map different areas of RAM.

Intel为了支持PAE改变了分页机制，但是线性地址仍然是32位长，迫使内核编程人员用同一线性地址映射不同的RAM区。

PAE does not enlarge the linear address space of a process, because it deals only with physical addresses.

PAE只扩展了物理地址并没有扩大进程的线性地址空间。

A process running in User Mode cannot use a physical address space larger than 4 GB.

用户态下运行的进程不能使用大于4GB的物理地址空间。

### 64位系统中的分页 Paging for 64-bit Architectures

All hardware paging systems for 64-bit processors make use of additional paging levels.

所有的64位处理器的硬件分页系统都使用了额外的分页级别。

### 硬件高速缓存 Hardware Cache

Hardware cache memories are base on the well-known locality principle, which holds both for programs and data structures. This states that because of the cyclic structure of programs and the packing of related data into linear arrays, addresses close to the ones most recently used have a high probability of being used in the near future.

硬件高速缓存基于局部性原理，该原理既适用于程序结构也适用于数据结构。由于程序的循环结构及相关数组可以组织成线性数组，最近最常用的相邻地址在最近的将来又被用到的可能性极大。

A new unit called the line was introduced into the 80x86 architecture, it consists of a few dozen contiguous bytes that are transferred in burst mode between the slow DRAM and the fast on-chip SRAM used to implement caches.

80x86体系结构中引入一个叫行的新单位，行由几十个连续的字节组成，它们以脉冲突发模式在慢速DRAM和快速的用来实现高速缓存的片上静态SRAM之间传送，用来实现高速缓存。

When accessing a RAM memory cell, the CPU extracts the subset index from the physical address and compares the tags of all lines in the subset with the high-order bits of the physical address. If a line with the same tag as the high-order bits of the address is found, the CPU has a cache hit; otherwise, it has a cache miss.

当访问一个RAM存储单元时，CPU从物理地址中提取出子集的索引号并把子集中所有行的标签与物理地址的高几位相比较。如果发现某一行的标签与这个物理地址的高位相同，则CPU命中一个高速缓存；否则，高速缓存没有命中。

When a cache hit occurs, the cache controller behaves differently, depending on the access type:

* Read operation
* Write-through
* Write-back

当命中一个高速缓存时，高速缓存控制器进行不同的操作：

* 读操作
* 通写
* 回写

When a cache miss occurs, the cache line is written to memory, if necessary, and the correct line is fetched from RAM into the cache entry.

当高速缓存没有命中时，高速缓存行被写回到内存中，如果有必要的话，把正确的行从RAM中取出放到高速缓存的表项中。

### 转换后援缓冲器（TLB）Translation Lookaside Buffer

Besides general-purpose hardware caches, 80x86 processors include another cache called Translation Lookaside Buffers (TLB) to speed up linear address translation.

除了通用硬件高速缓存之外，80x86处理器还包含了另一个称为转换后援缓冲器或TLB的高速缓存用于加快线性地址的转换。

Each CPU has its own TLB, called the local TLB of the CPU.

每个CPU都有自己的TLB，这叫做该CPU的本地TLB。

Contrary to the hardware cache, the corresponding entries of the TLB need not be synchronized.

与硬件高速缓存相反，TLB中的对应项不必同步。

## Linux中的分页 Paging in Linux

Linux的进程处理很大程度上依赖于分页，线性地址到物理地址的自动转换使下面的设计目标变得可行：

* 给每一个进程分配一块不同的物理地址空间，确保了可以有效地防止寻址错误
* 区别页和页框

每一个进程有它自己的页全局目录和自己的页表集。当发生进程切换时，Linux把cr3控制寄存器的内容保存在前一个执行进程的描述符中，然后把下一个要执行的描述符的值装入cr3控制寄存器中，当新进程重新开始在cpu上执行时，分页单元指向一组正确的页表。

### 线性地址字段 The Linear Address Fields

* PAGE_SHIFT

指定Offset字段的位数

* PMD_SHIFT

指定Offset字段和Table字段的总位数

* PUD_SHIFT

确定页上级目录能映射的区域大小的对数

* PGDIR_SHIFT

确定页全局目录项能映射的区域大小的对数

* PTRS_PER_PTE,PTRS_PER_PMD,PTRS_PER_PUD,PTRS_PER_PGD

用于计算页表、页中间目录、页上级目录和页全局目录表中表项的个数

### 页表处理 Page Table Handling

pte_t、pmd_t、pud_t、pgd_t分别描述页表项、页中间目录项、页上级目录项和页全局目录项的格式。

pgprot_t是另一个64位（PAE激活）或32位的数据类型，它表示与一个单独表项相关的保护标志。

* 读页标志
* 设置页标志
* 对页表项操作的宏
* 页分配函数

### 物理内存布局 Physical Memory Layout

在初始化阶段，内核必须建立一个物理地址映射来指定哪些物理地址范围对内核可用而哪些不可用。

一般来说，Linux内核安装在RAM中从物理地址0x00100000开始的地方，也就是说从第二个MB开始。

描述内核物理内存布局的变量

* num_physpages
* totalram_pages
* min_low_pfn
* max_pfn
* max_low_pfn
* totalhigh_pages
* highstart_pfn
* highend_pfn

### 进程页表 Process Page Tables

进程的线性地址空间被分成两部分：

* 从0x00000000到0xbfffffff的线性地址，无论用户态还是内核态进程都可以寻址
* 从0xc0000000到0xffffffff的线性地址，只有内核态进程可以寻址

### 内核页表 Kernel Page Tables

内核维持着一组自己使用的页表，驻留在所谓的主内核页全局目录中。

主内核页全局目录的最高目录项部分作为参考模型，为系统中每个普通进程对应的页全局目录项提供参考模型。

初始化内核页表：

* 创建一个有限的空间将内核装入RAM和对其初始化的核心数据结构
* 内核充分利用剩余的RAM并适当地建立分页表

#### 临时内核页表 Provisional kernel Page Tables

#### 当RAM小于896MB时的最终内核页表 Final kernel Page Table when RAM size is less than 896MB

#### 当RAM大小在896MB和4096MB之间时的最终内核页表 Final kernel Page Table when RAM size is between 896MB and 4096MB

#### 当RAM大于4096MB时的最终内核页表 Final kernel Page Tabel when Ram size is more than 4096MB

### 固定映射的线性地址 Fix-Mapped Linear Addresses

### 处理硬件高速缓存和TLB Handling the Hardware Cache and the TLB

#### 处理硬件高速缓存 Handling the hardware cache

#### 处理TLB Handling the TLB
