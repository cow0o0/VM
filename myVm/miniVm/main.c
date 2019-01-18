#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

char flag[8];
uint8_t code[] = {
    2,0,1,
    2,1,1,
    2,2,1,
    2,3,1,
    2,4,1,
    2,5,1,
    2,6,1
};
int getStr(char *buffer,int maxLen){
    char c;  // 读取到的一个字符
    int len = 0;  // 当前输入的字符串的长度
    // 一次读取一个字符，保存到buffer
    // 直到遇到换行符(\n)，或者长度超过maxLen时，停止读取
    while( (c=getchar()) != '\n' ){
        buffer[len++]=c;  // 将读取到的字符保存到buffer
        if(len>=maxLen){
            break;
        }
    }
    buffer[len]='\0';  // 读取结束，在末尾手动添加字符串结束标志
    fflush(stdin);  // 刷新输入缓冲区
    return len;
}

uint8_t vm_start(){
    uint8_t i = 0;
    uint8_t v0,v3,result = 0;
    for(i=0;i<=21;i+=3){
        v0 = code[i];
        v3 = code[i+2];
        result = v0;
        switch( v0 ){
            case 1:
                result = code[i+1];
                flag[result] += v3;
                break;
            case 2:
                result = code[i+1];
                flag[result] -= v3;
                break;
            case 3:
                result = code[i+1];
                flag[result] ^= v3;
                break;
            case 4:
                result = code[i+1];
                flag[result] *= v3;
                break;
            case 5:
                result = code[i+1];
                flag[result] ^= flag[v3];
                break;
            default:
                continue;

        }

    }
    return result;
}
/*
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

*/
uint8_t result_cmp[] = {49,50,51,52,53,54,55};//2345678
int main(int argc,char ** argv){

    bool succeed = true;
    uint8_t i = 0;
    getStr(flag,7);
    uint8_t len = 0;

    len = strlen(flag);
    printf("%d\n",len);
    vm_start();

    if ( strlen(flag) != 7 )
        succeed = 0;

    for ( i = 0; i <= 6; ++i )
    {
        if ( flag[i] != result_cmp[i] )
        succeed = 0;
    }
    if ( succeed ){
        puts("correct");
    } else{
        puts("wrong");
    }    

    return 0;
}
    