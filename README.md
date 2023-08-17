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

### 通过 ini $0x80 指令发出系统调用 Issuing a System Call via the int $0x80 Instruction

#### The system_call() function

#### 从系统调用退出 Exiting from the system call

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