BUILD:=./build
TOOL:=./tool
BIN:=./bin
HAL:=hal/x86_64
FILES = ${BIN}/boot.bin ${BIN}/setup.bin ${BIN}/kernel.pkg
INCLUDES = -I./oskernel
#FLAGS = -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc

CFLAGS:= -m32 # 32 bit program
CFLAGS+= -masm=intel
CFLAGS+= -fno-builtin			# no gcc built-in function
CFLAGS+= -nostdinc				# no std head file
CFLAGS+= -fno-pic				# position independent code
CFLAGS+= -fno-pie				# position independent executable
CFLAGS+= -nostdlib				# no std lib
CFLAGS+= -fno-stack-protector	# no stack protector
CFLAGS:= $(strip ${CFLAGS})

CFLAGS_64:= -m64 # 64 bit program
#CFLAGS_64+= -masm=intel
CFLAGS_64+= -fno-builtin			# no gcc built-in function
CFLAGS_64+= -nostdinc				# no std head file
CFLAGS_64+= -fno-pic				# position independent code
CFLAGS_64+= -fno-pie				# position independent executable
CFLAGS_64+= -nostdlib				# no std lib
CFLAGS_64+= -fno-stack-protector	# no stack protector
CFLAGS_64+= -ffreestanding
CFLAGS_64:= $(strip ${CFLAGS_64})

DEBUG:= -g

HD_IMG_NAME:= "hd.img"

all: clean ${FILES}
	$(shell rm -rf $(BUILD)/$(HD_IMG_NAME))
	bximage -q -hd=16 -func=create -sectsize=512 -imgmode=flat $(BUILD)/$(HD_IMG_NAME)
	dd if=${BIN}/boot.bin of=$(BUILD)/$(HD_IMG_NAME) bs=512 seek=0 count=1 conv=notrunc
	dd if=${BIN}/setup.bin of=$(BUILD)/$(HD_IMG_NAME) bs=512 seek=1 count=4 conv=notrunc
	dd if=${BIN}/kernel.pkg of=$(BUILD)/$(HD_IMG_NAME) bs=512 seek=5 count=60 conv=notrunc

#boot.bin
${BIN}/boot.bin: ./src/boot/boot.asm
	$(shell mkdir -p ${BUILD}/boot)
	nasm $< -o $@

# setup.bin
${BIN}/setup.bin: ${BUILD}/boot/setup.o
	objcopy -O binary $< $@
	nm ${BUILD}/boot/setup.o | sort > ${BUILD}/system.map

${BUILD}/boot/setup.o:${BUILD}/boot/setup_asm.o ${BUILD}/boot/setup_c.o ${BUILD}/boot/ldr.o
	ld -m elf_i386 $^ -o $@ -Ttext 0x500

${BUILD}/boot/setup_asm.o: ./src/boot/setup.asm
	nasm -f elf32 -g $< -o $@

${BUILD}/boot/setup_c.o: ./src/boot/setup.c
	$(shell mkdir -p ${BUILD}/boot)
	gcc ${CFLAGS} ${DEBUG} -c $< -o $@

${BUILD}/boot/ldr.o: ./src/ldr/ldr.c
	$(shell mkdir -p ${BUILD}/boot)
	gcc ${CFLAGS} ${DEBUG} -c $< -o $@

# kernel.pkg
${BIN}/kernel.pkg: ${BIN}/kernel.bin ${BUILD}/OStool
	${BUILD}/OStool ${BIN}/kernel.bin $@
	chmod 777 $@

${BUILD}/OStool: ${TOOL}/main.c
	gcc $< -o $@
	chmod 777 $<

# kernel.bin
${BIN}/kernel.bin:${BUILD}/kernel/kernel_entry.o ${BUILD}/kernel/kernel_c.o \
 						${BUILD}/${HAL}/halinit.o ${BUILD}/${HAL}/halconsole.o ${BUILD}/${HAL}/halmm.o ${BUILD}/${HAL}/halmm_t.o\
 						${BUILD}/${HAL}/interrupt/halidt.o ${BUILD}/${HAL}/interrupt/halidt.o ${BUILD}/${HAL}/interrupt/halisr.asm.o ${BUILD}/${HAL}/interrupt/interrupt_handler.o\
 						${BUILD}/lib/kprintf.o
	ld -m elf_x86_64 $^ -o $@ -s -static -T ./linker.ld -n -Map kernel.map
	#nm ${BUILD}/kernel/kernel.o | sort > ${BUILD}/kernel.map

#${BIN}/kernel.bin: ${BUILD}/kernel/kernel.o
#	objcopy -S -O binary $< $@
#	nm ${BUILD}/kernel/kernel.o | sort > ${BUILD}/kernel.map
#
#${BUILD}/kernel/kernel.o:${BUILD}/kernel/kernel_entry.o ${BUILD}/kernel/kernel_c.o \
# 						${BUILD}/${HAL}/halinit.o ${BUILD}/${HAL}/halconsole.o ${BUILD}/${HAL}/halmm.o ${BUILD}/${HAL}/halmm_t.o\
# 						${BUILD}/${HAL}/interrupt/halidt.o ${BUILD}/${HAL}/interrupt/halidt.o ${BUILD}/${HAL}/interrupt/halisr.asm.o ${BUILD}/${HAL}/interrupt/interrupt_handler.o\
# 						${BUILD}/lib/kprintf.o
#	ld -m elf_x86_64 $^ -o $@ -s -static -Text 0x2000000

${BUILD}/kernel/kernel_entry.o: ./src/kernel/kernel_entry.asm
	$(shell mkdir -p ${BUILD}/kernel)
	nasm -f elf64 -g $< -o $@

${BUILD}/kernel/kernel_c.o: ./src/kernel/kernel.c
	gcc ${CFLAGS_64} ${DEBUG} -c $< -o $@

${BUILD}/${HAL}/%.o: ./src/${HAL}/%.c
	$(shell mkdir -p ${BUILD}/${HAL})
	gcc ${CFLAGS_64} ${DEBUG} -c $< -o $@

${BUILD}/${HAL}/%.asm.o: ./src/${HAL}/%.asm
	$(shell mkdir -p ${BUILD}/${HAL})
	nasm -f elf64 -g $< -o $@

${BUILD}/${HAL}/interrupt/%.o: ./src/${HAL}/interrupt/%.c
	$(shell mkdir -p ${BUILD}/${HAL}/interrupt)
	gcc ${CFLAGS_64} ${DEBUG} -c $< -o $@

${BUILD}/${HAL}/interrupt/%.asm.o: ./src/${HAL}/interrupt/%.asm
	$(shell mkdir -p ${BUILD}/${HAL})
	nasm -f elf64 -g -I ./src/${HAL}/interrupt $< -o $@

${BUILD}/lib/%.o: ./src/lib/%.c
	$(shell mkdir -p ${BUILD}/lib)
	gcc ${CFLAGS_64} ${DEBUG} -c $< -o $@

clean:
	$(shell rm -rf ${BUILD})
	$(shell rm -rf ${BIN})
	$(shell mkdir ${BIN})
	$(shell mkdir ${BUILD})

bochs:
	bochs -q -f bochsrc

qemug: all
	qemu-system-x86_64 -m 2048 -hda $(BUILD)/$(HD_IMG_NAME) -S -s

qemu: all
	qemu-system-x86_64 -m 2048 -hda $(BUILD)/$(HD_IMG_NAME)