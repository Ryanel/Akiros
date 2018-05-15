#==========================================================
# Build Data
ARCH	:= x86
BOARD	:= i686
KERNEL_OUTPUT 	:= kernel
OUTPUT_DIRECTORY := ../../build/
#----------------------------------------------------------
# Tools
.PHONY: clean clean-sysroot

DEBUGFG := -g -Og -ggdb -g3
AS		:= nasm -felf32# NASM or YASM is required for x86
GAS		:= as
CC		:= i686-elf-gcc
CPP		:= i686-elf-g++
CPP_EXTRA := 
CPFLAGS := -ffreestanding -std=gnu++14 -nostartfiles -fno-rtti -fno-exceptions -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -Wall -Wextra -DARCH${ARCH} -O2 ${DEBUGFG} -lgcc
LD		:= ${CPP}
LD_FLAGS:= -ffreestanding -mcmodel=large -z max-page-size=0x1000 -nostdlib ${CPFLAGS}
GENISO 	:= genisoimage
GENISOF	:= -R -b boot/grub/stage2_eltorito -quiet -no-emul-boot -boot-load-size 4 -boot-info-table
#----------------------------------------------------------
# Precalculated variables
LD_LINKER_SCRIPT := ${ARCH}/${BOARD}/link.ld
#----------------------------------------------------------
# All Source Files
FILES_KERNEL	:= $(patsubst %.cpp,%.o,$(wildcard *.cpp))
FILES_LIB   	:= $(patsubst %.cpp,%.o,$(wildcard lib/*.cpp))
FILES_ARCH  	:= $(patsubst %.cpp,%.o,$(wildcard ${ARCH}/*.cpp)) $(patsubst %.asm,%.o,$(wildcard ${ARCH}/*.asm))
FILES_BOARD 	:= $(patsubst %.cpp,%.o,$(wildcard ${ARCH}/${BOARD}/*.cpp)) $(patsubst %.asm,%.o,$(wildcard ${ARCH}/${BOARD}/*.asm))

FILES_ARCH_DEVICES := $(patsubst %.cpp,%.o,$(wildcard ${ARCH}/devices/*.cpp)) $(patsubst %.asm,%.o,$(wildcard ${ARCH}/devices/*.asm))
FILES_BOARD_DEVICES := $(patsubst %.cpp,%.o,$(wildcard ${ARCH}/${BOARD}/devices/*.cpp)) $(patsubst %.asm,%.o,$(wildcard $${ARCH}/${BOARD}/devices/*.asm))

CRTBEGIN_OBJ:=$(shell $(CPP) $(CPFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CPP) $(CPFLAGS) -print-file-name=crtend.o)
CRTI_OBJ=${ARCH}/${BOARD}/crt/crti.o
CRTN_OBJ=${ARCH}/${BOARD}/crt/crtn.o

FILES_ALL		:= ${FILES_INIT} ${FILES_DRIVERS} ${FILES_KERNEL} ${FILES_LIB} ${FILES_LOG} ${FILES_ARCH} ${FILES_ARCH_DEVICES} ${FILES_BOARD} ${FILES_BOARD_DEVICES} 
FILES_COMPILE	:= ${FILES_ALL}

FINAL_LINK:=$(CRTI_OBJ) $(CRTBEGIN_OBJ) $(FILES_COMPILE) $(CRTEND_OBJ) $(CRTN_OBJ)
#==========================================================

all: kernel

%.o: %.asm
	@echo " [AS]" $@
	@${AS} -o $@ $<

%.o: %.cpp
	@echo "[CPP]" $@
	@${CPP} ${CPP_EXTRA} -c ${CPFLAGS} -I includes -DBOARD_NAME=\"${BOARD}\" -o $@ $<

kernel: ${FINAL_LINK} 
	@echo " [LD] Kernel"
	@${LD} -T ${LD_LINKER_SCRIPT} -Iincludes/ -o ${OUTPUT_DIRECTORY}${KERNEL_OUTPUT} ${LD_FLAGS} ${FINAL_LINK} -lgcc

clean:
	-@find . -name "*.o" -type f -delete
	-@find . -name "*.iso" -type f -delete

run: 
	@echo "[RUN] ${OUTPUT_DIRECTORY}${KERNEL_OUTPUT}"
	@qemu-system-i386 -m 32M -kernel ${OUTPUT_DIRECTORY}/${KERNEL_OUTPUT}
