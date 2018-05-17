# Configuration settings
ARCH := x86
BOARD := i686
KERNEL_OUTPUT 	:= kernel
OUTPUT_DIRECTORY := ../../build/

# Tools
ifndef COMPILE_PREFIX
CXX := i686-elf-g++
else
CXX := ${COMPILE_PREFIX}-g++
endif
ASM := nasm -felf32

# Flags
CXXFLAGS := -g -ffreestanding -nostartfiles -fstack-protector-strong -std=gnu++14 -fno-rtti -fno-exceptions -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -Wall -Wextra -O2 -I includes ${CXXFLAGS}
LDFLAGS := ${CXXFLAGS} -mcmodel=large -z max-page-size=0x1000 -nostdlib 
LDAFTERFLAGS := -lgcc

# Cached variables
LD_LINKER_SCRIPT := ${ARCH}/${BOARD}/link.ld

# Files
FILES_KERNEL 	 := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
FILES_LIB    	 := $(patsubst %.cpp,%.o,$(wildcard lib/*.cpp))
FILES_ARCH   	 := $(patsubst %.cpp,%.o,$(wildcard ${ARCH}/*.cpp)) $(patsubst %.asm,%.o,$(wildcard ${ARCH}/*.asm))
FILES_BOARD  	 := $(patsubst %.cpp,%.o,$(wildcard ${ARCH}/${BOARD}/*.cpp)) $(patsubst %.asm,%.o,$(wildcard ${ARCH}/${BOARD}/*.asm))

CRTBEGIN_OBJ     :=$(shell $(CXX) $(CXXFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ       :=$(shell $(CXX) $(CXXFLAGS) -print-file-name=crtend.o)
CRTI_OBJ         :=${ARCH}/${BOARD}/crt/crti.o
CRTN_OBJ         :=${ARCH}/${BOARD}/crt/crtn.o

FILES_ALL_KERNEL := ${FILES_BOARD} ${FILES_ARCH} ${FILES_KERNEL} ${FILES_LIB}
FINAL_LINK   	 := $(CRTI_OBJ) $(CRTBEGIN_OBJ) $(FILES_ALL_KERNEL) $(CRTEND_OBJ) $(CRTN_OBJ)

# Rules
.PHONY: clean distclean kernel all

all: kernel

kernel:	${FINAL_LINK}
	@${CXX} -T ${LD_LINKER_SCRIPT} ${LDFLAGS} -o ${OUTPUT_DIRECTORY}/${KERNEL_OUTPUT} ${FINAL_LINK} ${LDAFTERFLAGS}

clean:
	-@find . -name "*.o" -type f -delete

distclean: clean

run: 
	@echo "[RUN] ${OUTPUT_DIRECTORY}${KERNEL_OUTPUT}"
	@qemu-system-i386 -m 32M -s -kernel ${OUTPUT_DIRECTORY}/${KERNEL_OUTPUT}

# Build rules
%.o: %.asm	
	@echo "[ AS]:" $@
	@${ASM} -o $@ $<

%.o: %.cpp
	@echo "[CXX]:" $@
	@${CXX} -c ${CXXFLAGS} -o $@ $<
	
#%.o: %.cpp
#	@echo "[CXX]:" $@
#	@${CXX} -c ${CXXFLAGS} -fno-stack-protector -o $@ $<