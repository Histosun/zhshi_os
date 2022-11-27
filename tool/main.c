#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>


#define ALIGN(x, a) (((x) + (a) - 1) & ~((a) - 1))
#define P4K_ALIGN(x) ALIGN(x,0x1000)
#define ZHOS_MAGIC (u_int64_t)((((u_int64_t)'Z')<<56)|(((u_int64_t)'H')<<48)|(((u_int64_t)'O')<<40)|(((u_int64_t)'S')<<32)|(((u_int64_t)'M')<<24)|(((u_int64_t)'A')<<16)|(((u_int64_t)'C')<<8)|((u_int64_t)'H'))


typedef struct kernel_desc{
    u_int64_t kernel_magic;
    u_int64_t kernel_start;
    u_int64_t offset;
    u_int64_t kernel_size;
    u_int64_t next_pg;
}__attribute__((packed)) kernel_desc_t;

int main (int argc,char *argv[]) {
    if(argc != 3){
        printf("Only support 2 parameters\n");
        return -1;
    }
    char* filename = argv[1];
    int ifd;
    if((ifd = open(filename, O_RDONLY)) < 0){
        printf("Open file error!\n");
        return -1;
    }
    int kernel_size=0;
    kernel_size = lseek(ifd, 0 ,SEEK_END);
    printf("Kernel size is %d.\n", kernel_size);
    if(kernel_size<0){
        printf("Lseek error.\n");
        return -1;
    }

    char buf[4096];
    memset(buf, 0, sizeof(buf));
    kernel_desc_t desc;
    desc.kernel_magic = ZHOS_MAGIC;
    desc.kernel_size = kernel_size;
    desc.offset = 4096;

    int ofd;

    if((ofd = open(argv[2], O_RDWR|O_TRUNC|O_CREAT)) < 0){
        printf("Open file error!\n");
        return -1;
    }
    write(ofd, &desc, sizeof(desc));
    write(ofd, buf, 4096 - sizeof (desc));

    lseek(ifd, 0 , SEEK_SET);
    int offset = 0;
    int read_size = 0;
    do{
        read_size = read(ifd, buf, sizeof (buf));
        write(ofd, buf, read_size);
    } while (read_size!=0);

    printf("package finished!\n");
    close(ifd);
    close(ofd);

    return 0;
}