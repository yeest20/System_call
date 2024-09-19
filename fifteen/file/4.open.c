/*************************************************************************
	> File Name: 4.open.c
	> Author:YEE 
	> Mail:15509992895@163.com 
	> Created Time: Thu 19 Sep 2024 09:48:46 PM CST
 ************************************************************************/

#include"head.h"

int main(){
    int fd;
    close(0);
    char pathname[64] = "./1.test.c";
    fd = open(pathname, O_RDONLY);
    if(fd < 0) {
        perror("open");
        return 1;
    }
    printf("fd = %d\n", fd);
    //sleep(400);
    close(fd);
    close(fd);
    perror("close");
    return 0;
}
