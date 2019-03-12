include include/top.mk

TOPDIR := ${CURDIR}
SUBDIRS := src \
           test
TARGET := spi_test.exe
BUILD_DIR := build_dir
BIN_DIR := bin

all:$(TARGET)

$(TARGET):$(SUBDIRS)
	$(CC) $(BUILD_DIR)/*.o -o $(BIN_DIR)/$@

$(SUBDIRS):CHECKDIR
	@$(MAKE) -C $@ all || exit 1;

CHECKDIR:ECHO
	@mkdir -p build_dir
	@mkdir -p bin

ECHO:
	@echo [INFO] Find Dirs : $(SUBDIRS)
	@echo [INFO] Now start compile!

clean:
	@for dir in $(SUBDIRS);\
	do $(MAKE) -C $$dir clean || exit 1;\
	done
