/*************************************************************************
	> File Name: 6.write.c
	> Author:YEE 
	> Mail:15509992895@163.com 
	> Created Time: Thu 19 Sep 2024 10:10:14 PM CST
 ************************************************************************/

#include"head.h"

int main(){
    int fd, fd_out;
    char pathname[128] = "./x.c";
    fd = open(pathname, O_RDWR | O_CREAT, 0644);
    if(fd < 0){
        perror("open x.c");
        return 1;
    }
    fd_out = open("./x.x", O_RDWR | O_CREAT, 0644);
    if(fd_out < 0){
        perror("open x.x");
        return 2;
    }
    int rsize;
    int wsize;
    char buffer[10];
    int len = sizeof(buffer);
    while(1){
        rsize = read(fd, buffer, len - 1);
        if(rsize < 0){
            perror("read");
            return 3;
        }else if(rsize == 0){
            break;
        }else{
            printf("%s", buffer);
            wsize = write(fd_out, buffer, rsize);
            if(wsize < 0){
                perror("write");
                return 4;
            }
            memset(buffer, 0, len);
        }
    }

    close(fd);
    close(fd_out);
    return  0;
}
