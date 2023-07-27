# 内核_系统启动_System_Startup  

*20230725*  

## BIOS

* RAM芯片中包含的是随机数据
* CPU的一个引脚上产生一个RESET逻辑值
* 处理器的一些寄存器设置成固定值
* 把物理地址0xfffffff0映射到某个存储芯片(ROM)中
* ROM中存放着基本输入输出系统(BOIS)
* 执行物理地址0xfffffff0的代码
* 上电自检，对计算机硬件执行一系列的测试
* 初始化硬件设备
* 搜索一个操作系统启动
* 拷贝第一个扇区的内容（主引导记录MBR）到物理地址0x00007c00开始的位置
* 执行代码把包含内核镜像的其他所有扇区拷贝到RAM中

## 引导装入程序  The Boot Loader

引导装入程序是由BIOS用来把操作系统内核镜像装载到RAM中所调用的一个程序。

* 读取分区表中的分区的起止扇区和处理分区的操作系统类型
* 用引导装入程序装载被启动的操作系统所在分区的第一个扇区或者体积较大的引导装入程序（LILO或者GRUB等）被分为两部分，第一部分程序把自己移到地址0x00096a00，建立实模式栈（0x00098000~0x000969ff），再将第二部分程序装入地址由0x00096c00开始的RAM中

## 从磁盘启动 Linux Booting Linux from a disk

* 第二部分的引导装入程序依次从磁盘读取可用操作系统的映射表，用户从中选择一个
* 调用一个BIOS过程把相应分区的引导扇区（第一个512字节）拷贝到地址从0x00090000开始的RAM中
* 调用一个BIOS例程将setup()函数的代码拷贝到地址从0x00090200开始的RAM中
* 调用一个BIOS例程装载其余内核映像
* 跳转到setup()

## setup()

setup()汇编语言函数的代码由链接程序放在内核映像文件的偏移量0x200处。重新初始化计算机中的硬件设备以增强可移植性和健壮性，为内核程序的执行建立环境。

* 在ACPI兼容的系统中调用一个BIOS例程，在RAM中建立系统物理内存布局表（关键字"BIOS-e820"）
* 设置键盘重复延时和速率
* 初始化显卡
* 初始化磁盘控制器并检测磁盘参数
* 检查IBM微通道总线
* 检查PS/2指针设备
* 检查对高级电源管理（APM）BIOS的支持
* 若支持增强磁盘驱动服务，则调用相应的BIOS过程在RAM中建立系统可用硬盘表
* 若系统内核是被低装载到RAM（0x00010000）中，就把它移动到0x00001000
* 置位8042键盘控制器的A20引脚
* 建立一个临时的中断描述符表（IDT）和一个临时的全局描述符表（GDT）
* 按需重置浮点单元（FPU）
* 重新编写可编程中断控制器（Programmable Interrupt Controller, PIC）以屏蔽除两个PIC之间的级联中断IRQ2外的其他所有中断
* 设置cr0状态寄存器，把cpu从实模式切换到保护模式
* 跳转到startup_32()

```
[root@localhost ~]# dmesg | grep e820
[    0.000000] BIOS-e820: [mem 0x0000000000000000-0x000000000009fbff] usable
[    0.000000] BIOS-e820: [mem 0x000000000009fc00-0x000000000009ffff] reserved
[    0.000000] BIOS-e820: [mem 0x00000000000f0000-0x00000000000fffff] reserved
[    0.000000] BIOS-e820: [mem 0x0000000000100000-0x00000000dffeffff] usable
[    0.000000] BIOS-e820: [mem 0x00000000dfff0000-0x00000000dfffffff] ACPI data
[    0.000000] BIOS-e820: [mem 0x00000000fec00000-0x00000000fec00fff] reserved
[    0.000000] BIOS-e820: [mem 0x00000000fee00000-0x00000000fee00fff] reserved
[    0.000000] BIOS-e820: [mem 0x00000000fffc0000-0x00000000ffffffff] reserved
[    0.000000] BIOS-e820: [mem 0x0000000100000000-0x000000011fffffff] usable
[    0.007762] e820: update [mem 0x00000000-0x00000fff] usable ==> reserved
[    0.007764] e820: remove [mem 0x000a0000-0x000fffff] usable
[    1.084024] e820: reserve RAM buffer [mem 0x0009fc00-0x0009ffff]
[    1.084026] e820: reserve RAM buffer [mem 0xdfff0000-0xdfffffff]

```

## startup_32()

## start_kernel()