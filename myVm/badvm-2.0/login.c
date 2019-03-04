#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>
#include<signal.h>
#include<termios.h>
#include<unistd.h>
#include<stdbool.h>

// 隐藏光标
#define HIDE_CURSOR() printf("\033[?25l")
// 显示光标
#define SHOW_CURSOR() printf("\033[?25h")

void setBufferedInput(bool enable){
    static bool enabled = true;
    static struct termios old;
    struct termios new;

    if(enable && !enabled){
        //restore the terminal
        tcsetattr(STDIN_FILENO,TCSANOW,&old);

        enabled = true;

    }else if(!enable && enabled){
        //get terminal attr
        if(tcgetattr(STDIN_FILENO,&new)==-1){
            printf("tcgetattr Error!\n");
            exit(-1);
        }
        //resotre now terminal attr
        old = new;
        //set c_cflag don't show cursor(光标)  attaction to order
        new.c_lflag &=(~ICANON & ~ECHO);

        tcsetattr(STDIN_FILENO,TCSANOW,&new);

        enabled = false;
    }

}

int main(void){
    printf("Powered by badrer!\n");
    //printf("Please Login.\n");
    printf("---------[LOGIN]---------\n");
    printf("Username:");
    char username[7]; 
    char passwd[7];
    scanf("%s",username);
    printf("Password:");
    HIDE_CURSOR();
    setBufferedInput(false);
    scanf("%s",passwd);
    setBufferedInput(true);
    uint8_t v0 = strncmp(username,"badrer",6);
    uint8_t v1 = strncmp(passwd,"123456",6);
    if(v0 == 0 && v1 == 0){
        printf("\n---------[WELCOME]---------\n");
        system("/bin/sh");
    }else{
        printf("\n----------[EXIT]----------\n");
        system("exit");
    }
    return 0;
}