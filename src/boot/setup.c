#define VIDEO_MEM 0xB8000

void setup_main(){
    char * video_mem = (char *) VIDEO_MEM;

    video_mem[0] = 'B';
    video_mem[1] = 15;
}