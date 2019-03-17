CFLAGS= -Wall -g
ASFLAGS= -gstabs

SRC_BIN=target_bin

SRC_LIB=libmyasm.a

SRC_C=$(wildcard *.c)
SRC_S=$(wildcard *.s)

SRC_COBJ=$(SRC_C:.c=.o)
SRC_SOBJ=$(SRC_S:.s=.o)

SRC_OBJ=$(SRC_COBJ) $(SRC_SOBJ)

all: $(SRC_BIN)

$(SRC_BIN): $(SRC_COBJ) $(SRC_LIB)
	$(CC) -o $@ $(SRC_COBJ) -L./ -lmyasm

$(SRC_LIB) : $(SRC_SOBJ)
	ar rcs $@ $^

clean:
	$(RM) $(SRC_OBJ) $(SRC_BIN) *~
.PHONY:
	all clean