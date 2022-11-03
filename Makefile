BUILD:=./build
BIN:=./bin
FILES = ${BUILD}/kernel.o

all: ${BIN}/boot.bin ${BIN}/kernel.bin
	rm -rf ${BIN}/os.bin
	dd if=${BIN}/boot.bin >> ${BIN}/os.bin
	dd if=${BIN}/kernel.bin >> ${BIN}/os.bin
	dd if=/dev/zero bs=512 count=100 >> ${BIN}/os.bin

${BIN}/kernel.bin: ${FILES}
	i686-elf-ld -g -relocatable $(FILES) -o ${BUILD}/kernelfull.o
	i686-elf-gcc -T ./oskernel/linker.ld -o ${BIN}/kernel.bin -ffreestanding -O0 -nostdlib ./build/kernelfull.o

${BIN}/boot.bin: ./oskernel/boot/boot.asm
	nasm -f bin $< -o $@

${BUILD}/%.o: ./oskernel/%.asm
	nasm -f elf -g $< -o $@

clean:
	$(shell rm -rf ${BUILD})
	$(shell rm -rf ${BIN})
	$(shell mkdir ${BIN})
	$(shell mkdir ${BUILD})

bochs:
	bochs -q -f bochsrc

qemug:
	qemu-system-x86_64 -m 32M -fda a.img -S -s

qemu:
	qemu-system-x86_64 -m 32M -fda a.img

qemu_bin:
	qemu-system-x86_64 -hda ${BIN}/os.bin