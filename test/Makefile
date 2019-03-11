include ../include/top.mk

CFLAGS:= -I ../include
BUILD_DIR:=../build_dir
SOURCE:=$(wildcard *.c)
TARGET:=$(notdir $(SOURCE))
TARGET:=$(patsubst %.c,%.o,$(TARGET))

all:$(TARGET)

$(TARGET):$(SOURCE)
	$(CC) $(CFLAGS) -c $< -o $(BUILD_DIR)/$@

clean:
	-$(RM) $(BUILD_DIR)/$(TARGET)
