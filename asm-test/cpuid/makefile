CFLAGS := --gstabs
AS  := as --gstabs


OUT := cpuid
SRC := cpuid.o

.PHONY:clean
clean:	*.o
	rm -rf *.o

.PHONY:build
build: $(SRC)
	ld  $^ -o $(OUT)

s2o:
	$(AS) -o $<
