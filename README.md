# 内核_程序的执行_Program_Execution  

*20230816*  

## 可执行文件 Executable Files

An executable file is a regular file that describes how to initialize a new execution context(i.e., how to start a new computation).

可执行文件是一个普通文件，它描述了如何初始化一个新的执行上下文，也就是如何开始一个新的计算。

### 进程的信任状核权能 Process Credentials and Capabilities

Credentials bind the process to a specific user and a specific user group.

信任状把进程与一个特定的用户或用户组捆绑在一起。

Credentials are important on multiuser systems because they determine what each process can or cannot do, 

信任状在多用户系统上尤为重要，因为信任状可以决定每个进程能做什么，不能做什么，这样既保证了每个用户的个人数据的完整性，也保证了系统整体上的稳定性。

#### 进程的权能 Process capabilities

A capability is simply a flag that asserts whether the process is allowed to perform a specific operation or a specific class of operations.

一种权能仅仅是一个标志，它表明是否允许进程执行一个特定的操作或一组特定的操作。

#### Linux安全模块框架 The Linux Security Modules framework

Capabilities are tightly integrated with the Linux Security Modules framework. In short, the LSM framework allows developers to define several alternative models for kernel security.

权能是和Linux安全模块框架紧密结合在一起的。简单地说，LSM框架允许开发人员定义几种可以选择的内核安全模型。

Each security model is implemented by a set of security hooks. A security hook is a function that is invoked by the kernel when it is about to perform an important, security-related operation. The hook function determines whether the operation should be carried on or rejected.

每个安全模型是由一组安全钩实现的。安全钩是由内核调用的一个函数，用于执行与安全有关的重要操作。钩函数决定了一个操作是否可以执行。

### 命令行参数和shell环境 Command-Line Arguments and Shell Enviroment

### 库 Libraris

### 程序段和进程的线性区 Program Segments and Process Memory Regions

#### 灵活线性区布局 Flexible memory region layout

### 执行跟踪 Execution Tracing

## 可执行格式 Executable Formats

## 执行域 Execution Domains

## exec函数 The exec Functions