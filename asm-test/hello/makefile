CFLAGS := --gstabs
OUT := make-test
SRC := hello.o
AS  := as --gstabs
.PHONY:clean
clean:	*.o
	rm -rf *.o

.PHONY:build
build: $(SRC)
	ld  $^ -o $(OUT)

s2o:
	$(AS) -o $<
