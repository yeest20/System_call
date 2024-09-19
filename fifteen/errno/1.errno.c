/*************************************************************************
	> File Name: 1.errno.c
	> Author:YEE 
	> Mail:15509992895@163.com 
	> Created Time: Wed 18 Sep 2024 04:13:02 PM CST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

int main(){
    const char *msg = "hello,errno!\n";
    errno = 13;
    perror("Error ");
    printf("Befor system call errno is %d\n", errno);
    ssize_t wsize = write(3, msg, strlen(msg));
    if(wsize < 0){
        printf("After system call : errno is %d\n", errno);
        perror("write");
    } 
    wsize = write(3, msg, strlen(msg));
    if(wsize < 0){
        printf("write : %s\n", strerror(errno));
    }
    return 0;
}
