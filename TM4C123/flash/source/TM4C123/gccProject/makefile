#-------------------------------------------------------------------------------
#
#    CooCox Cortex M3 Flash Programmer(CoFlash) -- Flash Algorithm makefile
# 
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
#    User-modifiable options
#-------------------------------------------------------------------------------

# Set the Target output(LM3S_FlashSize)
# LM3S_8   (LM3S 8kB Flash)
# LM3S_16  (LM3S 16kB Flash)
# LM3S_32  (LM3S 32kB Flash)
# LM3S_64  (LM3S 64kB Flash)
# LM3S_128 (LM3S 128kB Flash)
# LM3S_256 (LM3S 256kB Flash)

FLASH_CHIP = TM4C123_256




# Optimization level, put in comment for debugging
OPTIMIZATION = -O0


#flash algorithm path
FLASH_ALGO_DIR := ../../..


# flash algorithm framework path
FRAMEWORK_DIR := ../../framework


# flash algorithm path
ALGO_DIR := ..


LDS := $(FRAMEWORK_DIR)/target.ld


# Output file basename
OUTPUT := $(FLASH_CHIP)


# Output directories
BIN_DIR := bin
OBJ_DIR := obj

#-------------------------------------------------------------------------------
#    Tools
#-------------------------------------------------------------------------------

# Tool suffix when cross-compiling
CROSS_COMPILE := arm-none-eabi-

# Compilation tools
CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump
READELF := $(CROSS_COMPILE)readelf
RM    := rm -rf   
MKDIR := C:\cygwin\bin\mkdir
COPY  := cp 

# includes
INCLUDES  = -I$(FRAMEWORK_DIR)/

# defines
DEFINES = -D$(FLASH_CHIP) -Dgcc

TARGET_OPTS = -mcpu=cortex-m3 -mthumb
#position-independent options
PI_OPTS = -fPIC -fPIE -msingle-pic-base -mpic-register=9


CFLAGS = $(TARGET_OPTS)
#CFLAGS += -g -Wall -mlong-calls
CFLAGS += -g -Wall 
CFLAGS += $(OPTIMIZATION) $(INCLUDES) $(DEFINES) $(PI_OPTS)
LDFLAGS = $(OPTIMIZATION)  -nostartfiles $(TARGET_OPTS) -Wl,-Map=$(OUTPUT).map,--cref


#-------------------------------------------------------------------------------
#    Files
#-------------------------------------------------------------------------------

# Directories where source files can be found

VPATH  = $(FRAMEWORK_DIR)/
VPATH += $(ALGO_DIR)/


# Objects built from C source files

FRAMEWORK_SRCS := FlashExecFnc.c
      
ALGO_SRCS := $(wildcard $(ALGO_DIR)/*.c)
ALGO_SRCS := $(subst $(ALGO_DIR)/,, $(ALGO_SRCS)) 


SRCS := $(FRAMEWORK_SRCS) $(ALGO_SRCS)

C_OBJECTS := $(patsubst %.c,%.o,$(SRCS)) 

# Append OBJ and BIN directories to output filename
OUTPUT := $(BIN_DIR)/$(OUTPUT)

#-------------------------------------------------------------------------------
#    Rules
#-------------------------------------------------------------------------------

TARGET_ELF :=  $(OUTPUT).elf
C_OBJECTS_EXT := $(addprefix $(OBJ_DIR)/, $(C_OBJECTS))
C_DEPS_EXT := $(patsubst %.o, %.d, $(C_OBJECTS_EXT))


all:  $(OBJ_DIR) $(BIN_DIR)  $(TARGET_ELF)
$(BIN_DIR):
	@echo
	mkdir -p $@
$(OBJ_DIR):
	mkdir -p $@


$(TARGET_ELF) : $(C_OBJECTS_EXT)
	$(CC) $(LDFLAGS) -T$(LDS) -o $@ $^
	$(OBJDUMP) -D $@ >  $(@:.elf=.dis)
	$(OBJDUMP) -S $@ >  $(@:.elf=.src)
	$(READELF) -a $@ >  $(@:.elf=.info)
	$(OBJCOPY) -O binary $@ $(@:.elf=.bin)
	$(COPY) $@ $(FLASH_ALGO_DIR)

$(C_OBJECTS_EXT) : $(SRCS) 
$(OBJ_DIR)/%.d : %.c 
	$(CC) -MM -MT $(@:.d=.o) $(CFLAGS) $< > $@
	
$(OBJ_DIR)/%.o :%.c
	$(CC) $(CFLAGS) -c $< -o $@

-include $(C_DEPS_EXT)


.PHONY : clean
clean:
	-$(RM) $(OBJ_DIR)/*.o $(OBJ_DIR)/*.d $(BIN_DIR)/*.bin $(BIN_DIR)/*.elf  $(BIN_DIR)/*.map $(BIN_DIR)/*.dis $(BIN_DIR)/*.src $(BIN_DIR)/*.info
	
show:
	@echo SRCS = $(SRCS)
	@echo C_OBJECTS = $(C_OBJECTS)
	@echo C_OBJECTS_EXT = $(C_OBJECTS_EXT)
	@echo TARGET_ELF = $(TARGET_ELF)
