/*************************************************************************
	> File Name: open_read_dir.c
	> Author:YEE 
	> Mail:15509992895@163.com 
	> Created Time: Thu 19 Sep 2024 02:09:00 PM CST
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<errno.h>


char *d_type_string(int t){
    switch(t){
        case DT_BLK: return "block device";
        case DT_CHR: return "charactor device";
        case DT_DIR: return "DIR";
        case DT_FIFO: return "named pipe";
        case DT_LNK: return "link";
        case DT_REG: return "regular file";
        case DT_SOCK: return "socket";
        case DT_UNKNOWN: return "?";
    }

}

int main(int argc, char *argv[]){
    char* dirname = argc > 1? argv[1] : "."; 
    DIR* dir_stream;
    struct dirent * dir_struc;

    dir_stream = opendir(dirname);
    if(dir_stream == NULL){
        perror("opendir");
        return 1;
    }

    while((dir_struc = readdir(dir_stream)) != NULL){
        if(errno) perror("readdir");

        printf("dirName: %s\ndirIno: %lu\nfileType: %s\n", dir_struc->d_name, dir_struc->d_ino, d_type_string(dir_struc->d_type));
        printf("\n");
    }
    return 0;
}
