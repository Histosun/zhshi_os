BUILD:=./build
BIN:=./bin
FILES = ${BUILD}/boot/boot.o ${BUILD}/setup.o ${BUILD}/system.bin
INCLUDES = -I./oskernel
FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc

CFLAGS:= -m32 # 32 bit program
CFLAGS+= -masm=intel
CFLAGS+= -fno-builtin	# no gcc built-in function
CFLAGS+= -nostdinc		# no std head file
CFLAGS+= -fno-pic		# position independent code
CFLAGS+= -fno-pie		# position independent executable
CFLAGS+= -nostdlib		# no std lib
CFLAGS+= -fno-stack-protector	# no stack protector
CFLAGS:= $(strip ${CFLAGS})

DEBUG:= -g

HD_IMG_NAME:= "hd.img"

all: ${FILES}
	$(shell rm -rf $(BUILD)/$(HD_IMG_NAME))
	bximage -q -hd=16 -func=create -sectsize=512 -imgmode=flat $(BUILD)/$(HD_IMG_NAME)
	dd if=${BUILD}/boot/boot.o of=$(BUILD)/$(HD_IMG_NAME) bs=512 seek=0 count=1 conv=notrunc
	dd if=${BUILD}/system.bin of=$(BUILD)/$(HD_IMG_NAME) bs=512 seek=1 count=60 conv=notrunc

${BUILD}/system.bin: ${BUILD}/kernel.bin
	objcopy -O binary ${BUILD}/kernel.bin ${BUILD}/system.bin
	nm ${BUILD}/kernel.bin | sort > ${BUILD}/system.map

${BUILD}/kernel.bin: ${BUILD}/setup.o ${BUILD}/main.o
	ld -m elf_i386 $^ -o $@ -Ttext 0x100000

${BUILD}/main.o: ./src/main.c
	$(shell mkdir -p ${BUILD}/init)
	gcc ${CFLAGS} ${DEBUG} -c $< -o $@

${BUILD}/setup.o: ./src/setup.asm
	nasm -f elf32 -g $< -o $@

${BUILD}/boot/boot.o: ./src/boot/boot.asm
	$(shell mkdir -p ${BUILD}/boot)
	nasm $< -o $@

clean:
	$(shell rm -rf ${BUILD})
	$(shell rm -rf ${BIN})
	$(shell mkdir ${BIN})
	$(shell mkdir ${BUILD})

bochs:
	bochs -q -f bochsrc

qemug:
	qemu-system-x86_64 -m 32M -hda $(BUILD)/$(HD_IMG_NAME) -S -s

qemu:
	qemu-system-x86_64 -m 32M -hda $(BUILD)/$(HD_IMG_NAME)