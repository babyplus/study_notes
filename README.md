# 内核_系统调用_System_Calls  

*20230806*  

## POSIX API 和系统调用 POSIX APIS and System Calls

## 系统调用处理程序及服务例程 System Call Handler and Service Routines

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