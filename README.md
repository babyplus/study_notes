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
* 拷贝第一个扇区的内容到物理地址0x00007c00开始的位置
* 执行代码把包含内核镜像的其他所有扇区拷贝到RAM中

## 引导装入程序  The Boot Loader

引导装入程序是由BIOS用来把操作系统内核镜像装载到RAM中所调用的一个程序。

## 从磁盘启动 Linux Booting Linux from a disk

## setup()

## startup_32()

## start_kernel()