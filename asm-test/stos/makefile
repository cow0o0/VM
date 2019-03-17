CFLAGS := --gstabs
AS  := as --gstabs


OUT := main
SRC := main.o



.PHONY:build
build: $(SRC)
	ld  $^ -o $(OUT)

s2o:
	$(AS) -o $<

.PHONY:clean
clean:	*.o
	rm -rf *.o
