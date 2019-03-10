#CC := mipsel-linux-gnu-gcc
CC := gcc
CFLAGS := -g -w 
#-fno-stack-protector
OUT := badVm-2.0
SRC := vmopcode.o vmhandler.o main.o

all:build

.PHONY:build
build: $(SRC)
	$(CC) $(CFLAGS) $^ -o $(OUT)

#编译所有的.c 文件为 .o
.c.o: 
	$(CC) $(CFLAGS) -c $<

.PHONY:clean
clean:	
	rm -rf *.o


