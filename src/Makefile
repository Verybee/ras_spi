include ../include/top.mk

CFLAGS:=-I ../include
BUILD_DIR=../build_dir
SOURCE:=$(wildcard *.c)
TARGET:=$(patsubst %.c,%.o,$(SOURCE))

$(TARGET):$(SOURCE)
	$(CC) $(CFLAGS) -c $< -o $(BUILD_DIR)/$@

all:$(TARGET)
clean:
	-$(RM) $(BUILD_DIR)/$(TARGET)
