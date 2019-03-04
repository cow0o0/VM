# badVm-2.0

这版较1.0版本肯定会有十分巨大的改动。

一个虚拟机的设计主要考虑三块内容：

1. 指令系统
2. 编译器
3. 解释器

## 指令系统

这是基于堆栈的虚拟机

那什么是基于寄存器的虚拟机呢？？？？

表达式：
　　Add eax,ecx
　　可以翻译为：
　　Push ecx
　　Push eax
　　Add
　　Pop eax

设计原则，将操作分解为原子指令，在此基础上进行封装。

vAdd
vPush

之前写的第一个版本主要是借鉴的x86指令集的设计方法。
第二版我觉得有必要了解一下mips指令集的设计方法。

今晚就是了解的时候，其实就是理解它是如何进行mov，jmp，immmov，addrmov，cmp，push，pop



## 编译器
这里的编译器指的是将mips指令转换为可读结构的工具，通常需要使用到反汇编引擎，自己实现一个反汇编引擎明显是不太现实的一件事情

利用python的cstpyon。。。模块

针对核心代码进行反汇编。得到可读的结构，然后根据目标指令和自定义指令的一一对应的关系，进行映射

这部分放在最后进行完善，如果没有时间可以考虑略写。

## 解释器
这里的解释器指的是翻译并执行虚拟机指令的功能模块。

解释器和指令系统结合的比较紧密，这是指令系统的具体编程实现

主要是大小的问题，内存分配，各个结构的大小：































# badVm-1.0

Editor by BadRer

---

主体框架结构参考自 https://xz.aliyun.com/t/3851 

结合《加密与解密》关于虚拟机的设计一章进行编写。

目前实现了`35`条指令

```
enum regs {
    EAX = 0,
    EBX = 1,
    ECX = 2,
    EDX = 3,
    ESI = 4,
    EDI = 5,
    EBP = 6,
    ESP = 7,
    EFL = 8,
};
enum opcodes{

    //4
    PushReg32 = 0xe1,
    PushImm32 = 0xe3,
    PushMem32 = 0xe4,
    PopReg32 = 0xe5,

    //4
    MovImm2Reg = 0xa1,
    MovReg2Reg = 0xa2,
    MovMem2Reg = 0xa3,
    MovReg2Mem = 0xa4,

    //6
    AddReg2Reg = 0xa5,
    AddImm2Reg = 0xa6,
    AddMem2Reg = 0xa7,
    AddImm2Mem = 0xa8,
    AddReg2Mem = 0xa9,
    AddMem2Mem = 0xa0,

    //6
    MulReg2Reg = 0xe6,
    MulImm2Reg = 0xe7,
    MulMem2Reg = 0xe8,
    MulImm2Mem = 0xe9,
    MulReg2Mem = 0xea,
    MulMem2Mem = 0xeb,

    //6
    XorReg2Reg = 0xc0,
    XorImm2Reg = 0xc1,
    XorMem2Reg = 0xc2,
    XorImm2Mem = 0xc3,
    XorReg2Mem = 0xc4,
    XorMem2Mem = 0xc5,

    //5
    Jmp = 0xb0,
    Ja = 0xb1,
    Jb = 0xb2,
    Je = 0xb3,
    Jz = 0xb4,
    
    //2
    Sal = 0x99,
    Sar = 0x88,
    
    //1
    CmpReg2Reg = 0x77,

    //2
    Nop = 0x66,
    RET = 0xff,
};

```

### 基本功能

1. 基本的线性伪指令执行
2. 实现简单的循环结构
3. 设置了EFL寄存器的ZF和CF标志位
4. 维护了一个栈和VM的内存


### 不足和改进

不足的地方太多了。

1. 只维护了一个堆栈，因此在循环时只能有一个动态变化的量（不知道如何进行描述了）
2. 指令太乱，没有规划
3. 对计算机CPU的运行了解不够
4. 无法动态取址

### 一个简单demo

```

uint8_t vm_code[] = {
    MovMem2Reg,0x0,EAX,
    MovReg2Reg,EAX,EBX,
    Sal,0x18,
    Sar,0x18,
    PushReg32,EAX,
    MovReg2Reg,EBX,EAX,
    Sal,0x10,
    Sar,0x18,
    PushReg32,EAX,
    MovReg2Reg,EBX,EAX,
    Sal,0x8,
    Sar,0x18,
    PushReg32,EAX,
    MovReg2Reg,EBX,EAX,
    Sar,0x18,
    PushReg32,EAX,
    
    MovImm2Reg,0x4,0x0,0x0,0x0,ECX,
    MovImm2Reg,0x0,0x0,0x0,0x0,EBX,
    XorReg2Reg,EDX,EDX,

    Jmp,77,
    MovReg2Reg,EBX,EDI,
    AddImm2Reg,0x30,0x0,0x0,0x0,EDI,
    PopReg32,EAX,
    XorReg2Reg,EDI,EAX,
    AddReg2Reg,EAX,EDX,
    AddImm2Reg,0x1,0x0,0x0,0x0,EBX,
    CmpReg2Reg,EBX,ECX,
    
    Jb,54,
    MovReg2Mem,EDX,1,

    Nop,
    RET

};

```

获取用户输入的4字节，取出每个字节并压栈，循环进行如下操作

```
sum = 0;
for(i=0;i<4;i++){
	sum += input^(i+0x30);
}
flag = sum

最后将flag在VM外面进行判断正确与否
```

我把`(i+0x30)`称作动态取址，整个VM只能有一个动态取址的操作，因此循环的功能就显得很鸡肋，局限性很大。

