# miniVm

代码实现主要来自一道简单的Vm题目，简单到我不认为这是一道VM题。基本上就是IDA扣下来的代码。

op+index+data
code{
    2,0,1,
    2,1,1,
    2,2,1,
    2,3,1,
    2,4,1,
    2,5,1,
    2,6,1
}

主要是几个全局变量。

正常的VM应该有 push pop mov jcc jae jbe ja jb jne je jna jle jnl jnle jg

code 里没有终止条件。需要手动设置。