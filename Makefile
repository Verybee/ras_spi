include include/top.mk

TOPDIR := ${CURDIR}
SUBDIRS := src \
           test
TARGET := test.bin
BUILD_DIR := build_dir
BIN_DIR := $(BUILD_DIR)
CFLAGS := $(USER_CONFIG)

all:$(TARGET)

$(TARGET):$(SUBDIRS)
	$(CC) $(CFLAGS) $(BUILD_DIR)/*.o -o $(BIN_DIR)/$@

$(SUBDIRS):CHECKDIR
	@$(MAKE) -C $@ all || exit 1;

CHECKDIR:ECHO
	@mkdir -p build_dir

ECHO:
	@echo [INFO] Find Dirs : $(SUBDIRS)
	@echo [INFO] Now start compile!

clean:
	@for dir in $(SUBDIRS);\
	do $(MAKE) -C $$dir clean || exit 1;\
	done
