# VM
vm -- code interpreter

# myVM

自己瞎写的一个VM，指令集还不完善，基本实现，但是整个指令系统比较的混乱，没有合理规划好。

主要包含三个内容：

1. miniVm
2. babyVm
3. badVm

## miniVm

代码来自于一道简单的`VM`逆向题

## babyVm

来自于这位师傅 https://xz.aliyun.com/t/3851 

提供了很好的框架

## badVm

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


# other vm

包含了别人的VM实现代码

1. 一个是基于`https://github.com/codyebberson/vm`
进行了简单改写
2. 另一个是别人针对`https://github.com/codyebberson/vm`进行的改写。

两者实现起来简单，功能有十分有限，但是对于VM的初学者来说可以参考借鉴。


# PDF

主要是一些VM相关的电子书籍，不过我并没有阅读。

# vm-packer

来自于《加密与解密（第四版）》

整个项目采用C++实现，代码量稍大，对于初学者难度很大，项目本身不能直接运行，通过代码可以加深我们对VM的理解，之后如果有机会的话，我倒是想将其在linux下实现一遍。

其整个指令集至少比我的调理清楚

# asm-test

学习VM时顺带重温了一遍汇编

主要包含两个内容：

1. 汇编语言程序设计
2. C语言嵌入汇编

其中用汇编实现了`write`,`add`等简短的函数