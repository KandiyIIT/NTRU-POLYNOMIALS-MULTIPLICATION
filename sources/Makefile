GСС = gcc
AS =nasm
LD = gcc

INCLUDE := /usr/include/
CFLAGS := -O3  -D_TACTS -D_KUPYNA -march=native -mtune=native -g  -Wall -mavx  -mavx2 -mfma -maes -fopenmp -I$(INCLUDE)


AFLAGS := -f elf64  -g -w+all
LFLAGS := 
LIBS := -lcrypto -lgomp
C_SOURCES := main.c \
	ForTest.c \
	mul_f1_f2_f3.c \
	mul16.c \
	mult_bershtein.c

OBJECTS := main.o \
	mul_f1_f2_f3.o \
	ForTest.o \
	mul16.o \
	F1_h_plus_F2.o \
	F3.o \
	ThreadFunMulAsm.o \
	mult_bershtein.o



A_SOURCES := F1_h_plus_F2.asm \
	F3.asm \
	ThreadFunMulAsm.asm


PROG := np
  
default: $(PROG) 


%.o : %.c
	$(GCC) gcc -c  $(CFLAGS) $(LIBS) $< -o $@

%.o : %.asm
	$(AS) $(AFLAGS) $< -o $@


$(PROG): $(OBJECTS)
	$(LD) $(LFLAGS) $(OBJECTS)  -o $(PROG) $(LIBS)

clean:
	rm -rf *.o *~ np 
