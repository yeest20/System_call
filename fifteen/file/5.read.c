/*************************************************************************
	> File Name: 5.read.c
	> Author:YEE 
	> Mail:15509992895@163.com 
	> Created Time: Thu 19 Sep 2024 10:10:14 PM CST
 ************************************************************************/

#include"head.h"

int main(){
    int fd;
    char pathname[128] = "./x.c";
    fd = open(pathname, O_RDWR | O_CREAT, 0644);
    if(fd < 0){
        perror("open");
        return 1;
    }
    int rsize;
    char buffer[10];
    int len = sizeof(buffer);
    while(1){
        rsize = read(fd, buffer, len - 1);
        if(rsize < 0){
            perror("read");
            return 2;
        }else if(rsize == 0){
            break;
        }else{
            printf("%s", buffer);
            memset(buffer, 0, len);
        }
    }
    return  0;
}
