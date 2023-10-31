# 内核_系统调用_System_Calls  

*20230806*  

## POSIX API 和系统调用 POSIX APIS and System Calls

POSIX API is a function definition that specifies how to obtain a given service.

POSIX API是一个函数定义，说明了如何获得一个给定的服务。

The system call is an explicit request to the kernel made via a software interrupt.

系统调用是通过软中断向内核态发出一个明确而请求。

The POSIX standard refers to APIs and not to system calls.

POSIX标准针对API而不针对系统调用。

## 系统调用处理程序及服务例程 System Call Handler and Service Routines

When a User Mode process invokes a system call, the CPU switches to Kernel Mode and starts the execution of a kernel function.

当用户态的进程调用一个系统调用时，CPU切换到内核态并开始执行一个内核函数。

Because the kernel implements many different system calls, the User Mode process must pass a parameter called the system call number to identify the required system call, the eax register is used by Linux for this purpose.

因为内核实现了很多不同的系统调用，因此进程必须传递一个名为系统调用号的参数来识别所需的系统调用，eax寄存器就用作此目的。

The system calls performs the following operations:

* Saves the contents of most registers in the Kernel Mode stack
* Handles the system call by invoking a corresponding C function called the system call service routine
* Exits from the handler: the regitsters are loaded with the values saved in the Kernel Mode stack, and the CPU is switched back from Kernel Mode to User Mode.

系统调用处理程序执行下列操作：

* 在内核态栈保存大多数寄存器的内容
* 调用名为系统调用服务例程的相应的C函数处理系统调用
* 退出系统调用处理程序：用保存在内核栈中的值加载寄存器，CPU从内核态切换回到用户态

## 进入和退出系统调用 Entering and Exiting a System Call

本地应用可以通过两个不同的方式调用系统调用：

* 执行int $0x80汇编指令
* 执行sysenter汇编指令

内核可以通过两种方式从系统调用退出：

* 执行iret指令
* 执行sysexit指令

### 通过 int $0x80 指令发出系统调用 Issuing a System Call via the int $0x80 Instruction

向量128（0x80）对应于内核入口点。

在内核初始化期间调用的函数trap_init()，建立对应于向量128的中断描述符表表项。

当用户态进程发出int $0x80指令时，CPU切换到内核态并开始从地址system_call处开始执行指令。

#### The system_call() function

* system_call()函数首先把系统调用号和这个异常处理程序可以用到的所有CPU寄存器保存到相应的栈中
* 在ebx中存放当前进程的thread_info数据结构的地址
* 检查是否有某一调试程序正在跟踪执行程序对系统调用的调用
* 对用户态进程传递来的系统调用号进行有效性检查
* 如果无效，则恢复在用户态的执行时并在eax中发现一个负的返回值
* 如果有效，则调用与eax中所包含的系统调用号对应的特定服务例程

分派表中的每个表项占4个字节，因此首先把系统调用号乘以4，再加上sys_call_table分派表的起始地址，然后从这个地址获取指向服务例程的指针，内核就能找到要调用的服务例程。

#### 从系统调用退出 Exiting from the system call

* system_call()函数从eax获得它的返回值，并把这个返回值存放在曾保存用户态eax寄存器值的那个栈单元的位置上
* 关闭本地中断并检查当前进程的thread_info结构中的标志，若有任何一种标志被置1，那么就要在返回用户态之前完成一些工作
* 最终跳转到restore_all标记处以恢复用户态进程的执行

### 通过sysenter指令发出系统调用 Issuing a System Call via the sysenter Instruction

#### sysenter指令 The sysenter instruction

#### vsyscall页 The vsyscall page

#### 进入系统调用 Entering the system call

#### 退出系统调用 Exiting from the system call

#### sysexit指令 The sysexit instruction

### The SYSENTER_RETURN code

## 参数传递 Parameter Passing

### 验证参数 Verifying the Parameters

### 访问进程地址空间 Accessing the Process Address Space

### 动态地址检查：修正代码 Dynamic Address Checking: The Fix-up Code

### 异常表 The Exception Tables

### 生成异常表和修正代码 Generating the Exception Tables and the Fixup Code

## 内核封装例程 Kernel Warpper Routines
