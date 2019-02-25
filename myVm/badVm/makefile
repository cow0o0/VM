CC := cc
CFLAGS := -g -w
OUT := test
SRC := vmopcode.o test.o

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


