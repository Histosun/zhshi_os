#define VIDEO_MEM 0xB8000

void kernel_main(){
    char * video_mem = (char *) VIDEO_MEM;

    video_mem[0] = 'A';
    video_mem[1] = 15;
}