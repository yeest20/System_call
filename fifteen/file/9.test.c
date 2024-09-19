/*************************************************************************
	> File Name: 6.write.c
	> Author:YEE 
	> Mail:15509992895@163.com 
	> Created Time: Thu 19 Sep 2024 10:10:14 PM CST
 ************************************************************************/

#include"head.h"

void print_err(const int return_value, const char *errInfo){
    if(return_value < 0){
        perror(errInfo);
        exit(1);
    }
}

void copy(int fd_src, int fd_dest){
    int rsize;
    int wsize;
    const size_t BUFFERSIZE = 128;
    char buffer[BUFFERSIZE + 5];
    while(1){
        rsize = read(fd_src, buffer, BUFFERSIZE - 1);
        print_err(rsize, "read");
        if(rsize == 0)  break;
        else{
            wsize = write(fd_dest, buffer, rsize);
            print_err(wsize, "write");
            memset(buffer, 0, BUFFERSIZE);
        }
    }
    return;
}

void deepcopy(int fd_src, int fd_dest){
    struct stat statbuffer_src;
    struct stat statbuffer_dest;
    int stat_return = 0;
    stat_return = fstat(fd_src, &statbuffer_src);
    print_err(stat_return, "stat src");
    
// 复制信息
    int return_value;
    return_value = fchmod(fd_dest, statbuffer_src.st_mode);
    print_err(return_value, "fchmod");

    struct timespec new_times[2];
    new_times[0].tv_sec = statbuffer_src.st_atime;
    new_times[0].tv_nsec = 0;
    new_times[1].tv_sec = statbuffer_src.st_mtime;
    new_times[1].tv_nsec = 0;
    return_value = futimens(fd_dest, new_times);
    print_err(return_value, "futimens");
    return ;
}

int main(int argc, char *argv[]){
// 文件参数
    int fd_src, fd_dest;
    char pathname_src[128] = "./";
    char pathname_dest[128] = "./";
    if(argc < 3) {
        printf("Please input filename....\n");
        exit(1);
    }
    strcat(pathname_src, argv[1]);
    strcat(pathname_dest, argv[2]);
    fd_src = open(pathname_src, O_RDWR, 0644);
    print_err(fd_src, "open src");
    fd_dest = open(pathname_dest, O_RDWR | O_CREAT, 0644);
    print_err(fd_dest, "open dest");

// 文件内容复制
    copy(fd_src, fd_dest);

// 选项参数
    int opt;
    opt = getopt(argc, argv, "a");
// 文件信息复制
    if(opt != 'a')  return 0;
    deepcopy(fd_src, fd_dest); 

    close(fd_src);
    close(fd_dest);
    return  0;
}
