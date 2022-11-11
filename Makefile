BUILD:=./build
BIN:=./bin
FILES = ${BIN}/boot.bin ${BIN}/setup.bin
INCLUDES = -I./oskernel
#FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc

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
	dd if=${BIN}/boot.bin of=$(BUILD)/$(HD_IMG_NAME) bs=512 seek=0 count=1 conv=notrunc
	dd if=${BIN}/setup.bin of=$(BUILD)/$(HD_IMG_NAME) bs=512 seek=1 count=4 conv=notrunc

${BIN}/setup.bin: ${BUILD}/boot/setup.o
	objcopy -O binary $< $@
#	nm ${BUILD}/kernel.bin | sort > ${BUILD}/system.map

${BUILD}/boot/setup.o:${BUILD}/boot/setup_asm.o ${BUILD}/boot/setup_c.o ${BUILD}/idt/idt_asm.o ${BUILD}/idt/idt_c.o ${BUILD}/memory/mem.o ${BUILD}/lib/string.o
	ld -m elf_i386 $^ -o $@ -Ttext 0x500

${BUILD}/boot/setup_c.o: ./src/boot/setup.c
	$(shell mkdir -p ${BUILD}/boot)
	gcc ${CFLAGS} ${DEBUG} -c $< -o $@

${BUILD}/boot/setup_asm.o: ./src/boot/setup.asm
	nasm -f elf32 -g $< -o $@

${BUILD}/lib/string.o: ./src/lib/string.c
	$(shell mkdir -p ${BUILD}/lib)
	gcc ${CFLAGS} ${DEBUG} -c $< -o $@


${BUILD}/idt/idt_c.o: ./src/idt/idt.c
	gcc ${CFLAGS} ${DEBUG} -c $< -o $@

${BUILD}/idt/idt_asm.o: ./src/idt/idt.asm
	$(shell mkdir -p ${BUILD}/idt)
	nasm -f elf32 -g $< -o $@

${BUILD}/memory/mem.o: ./src/memory/mem.c
	$(shell mkdir -p ${BUILD}/memory)
	gcc ${CFLAGS} ${DEBUG} -c $< -o $@

#${BUILD}/main.o: ./src/main.c
#	$(shell mkdir -p ${BUILD}/init)
#	gcc ${CFLAGS} ${DEBUG} -c $< -o $@

#${BUILD}/setup.o: src/boot/setup.asm
#	nasm -f elf32 -g $< -o $@

${BIN}/boot.bin: ./src/boot/boot.asm
	$(shell mkdir -p ${BUILD}/boot)
	nasm $< -o $@

${BUILD}/boot/%.o: ./src/boot/%.asm
	nasm $< -o $@

clean:
	$(shell rm -rf ${BUILD})
	$(shell rm -rf ${BIN})
	$(shell mkdir ${BIN})
	$(shell mkdir ${BUILD})

bochs:
	bochs -q -f bochsrc

qemug: all
	qemu-system-x86_64 -m 32M -hda $(BUILD)/$(HD_IMG_NAME) -S -s

qemu: all
	qemu-system-x86_64 -m 32M -hda $(BUILD)/$(HD_IMG_NAME)