#### Tools
TOOL=arm-linux-gnueabihf-
CC=$(TOOL)gcc
LD=$(TOOL)ld
OBJCOPY=$(TOOL)objcopy
TARGET=hello
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
####

all: $(TARGET)

$(TARGET): $(OBJ) 
	$(CC) -o $@ $^
	$(OBJCOPY) -O binary $@ $@.bin

%.o: %.c
	$(CC) -g -c $< -I. -marm

clean:
	rm -f *.o *.bin $(TARGET)

