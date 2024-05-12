# Change this as needed
export ZCCCFG := $(HOME)/z88dk/lib/config

# Compiler
CC = zcc

# Assembler
AS = z88dk-z80asm

# Compiler flags
CFLAGS = +cpm -vn -I$(HOME)/z88dk/include -I./include

# Source directory
SRC_DIR = src
# Object directory
BUILD_DIR = build

# Find all subdirectories of src excluding src/app and its subdirectories
SUBDIRS := $(shell find $(SRC_DIR) -mindepth 1 -maxdepth 1 -type d ! -name app)

# Generate object file names for both C and assembly files
OBJS := $(patsubst $(SRC_DIR)/%, $(BUILD_DIR)/%, \
         $(patsubst %.c, %.o, $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))) \
         $(patsubst %.asm, %.o, $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.asm))))

# Targets
all: $(OBJS)

# Rule to compile C source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile assembly source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.asm
	@mkdir -p $(dir $@)
	$(AS) $< -o$@

# Target to create lib files
lib: c3l.lst
	@mkdir -p $(BUILD_DIR)/lib
	$(AS) -d -x./build/lib/c3l @$<
	
# Target to create lib files
demo: demo.lst
	@mkdir -p $(BUILD_DIR)/lib
	$(AS) -d -x./build/lib/demo @$<
	

# Clean rule
clean:
	@rm -rf $(BUILD_DIR)

.PHONY: all lib demo clean
