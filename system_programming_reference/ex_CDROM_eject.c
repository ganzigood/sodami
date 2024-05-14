#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<unistd.h>
#include<linux/cdrom.h>
#include<stdio.h>

int main(int argc, char** argv) {

    int fd, ret;

    if(argc <2 ){
       fprintf(stderr,"usage : %s <device to eject>\n", argv[0]);
       return 1;
    }

    /*
    cd-rom 드바이스를 읽기 전용으로 연다.
    O_NONBLOCK은 드라이브에 미디어가 없더라도 트레이를 열겠다는 의미다.
    */
    fd =open(argv[1], O_RDONLY | O_NONBLOCK);
    if(fd<0) {
        perror("open");
        return 1;
    }

    ret=ioctl(fd, CDROMEJECT,0);
    if(ret) {
        perror("ioctl");
        return 1;
    }

    ret = close(fd);
    if (ret) {
        perror("close");
        return 1;
    }

    return 0;
}