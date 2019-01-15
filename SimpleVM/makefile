CXXFLAGS = -O0 -Wall
CCFLAGS = -O0 -Wall


OUTPUT = vmtest
OBJECTS = vm.o vmtest.o

all: executable

CC = cc $(CCFLAGS)
CXX = g++ $(CXXFLAGS)

executable: $(OBJECTS)
	$(CC) -o $(OUTPUT) $^

#编译所有的.c 文件为 .o
.c.o: 
	$(CC) -c $<

clean:
	rm -rf *.o