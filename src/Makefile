include ../include/top.mk

CFLAGS:= $(SELF_INCLUDE) $(EXT_INCLUDE) $(USER_CONFIG)
BUILD_DIR=../build_dir
SOURCE:=$(wildcard *.c)
TARGET:=$(patsubst %.c,%.o,$(SOURCE))

all:$(TARGET)

$(TARGET):%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $(BUILD_DIR)/$@

clean:
	-cd $(BUILD_DIR) && $(RM) $(TARGET)
