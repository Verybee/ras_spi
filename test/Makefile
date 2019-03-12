include ../include/top.mk

CFLAGS:=-I ../include
BUILD_DIR=../build_dir
SOURCE:=$(wildcard *.c)
TARGET:=$(patsubst %.c,%.o,$(SOURCE))

all:$(TARGET)

$(TARGET):%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $(BUILD_DIR)/$@

clean:
	-$(RM) $(BUILD_DIR)/$(TARGET)
