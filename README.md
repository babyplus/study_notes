# 内核_中断和异常_Interrupts_and_Exceptions  

*20230728*  

## 中断信号的作用 The Role of Interrupt Signals

## 中断和异常 Interrupts and Exceptions

### IRQ和中断 IRQs and Interrupts

#### 高级可编程中断控制器 The Advanced Programmable Interrupt Controller (APIC)

### 异常 Exceptions

### 中断描述符表 Interrupt Descriptor Table (IDT)

### 中断和异常的硬件处理 Hardware Handling of Interrupts and Exceptions

## 中断和异常处理程序的嵌套执行 Nested Execution of Exception and Interrupt Handles

## 初始化中断描述符表 Initiallizing the Interrupt Descriptor Table

### 中断门、陷阱门及系统门 Interrupt,Trap, and System Gates

### IDT的初步初始化 Preliminary Initialization of the IDT

## 异常处理 Exception Handling

### 为异常处理程序保存寄存器的值 Saving the Registers for the Exception Handler

### 进入和离开异常处理程序 Entering and Leaving the Exception Handler

## 中断处理 Interrupt Handling

### I/O中断处理 I/O Interrupte Handling

### 处理器间中断处理 Interprocessor Interrupt Handling

## 软中断及tasklet Softirqs and Tasklets

### 软中断 Softirqs

### Tasklets

## 工作队列 Work Queues

## 从中断和异常返回 Returning from Interrupts and Exceptions