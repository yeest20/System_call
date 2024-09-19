/*************************************************************************
	> File Name: open_read_dir.c
	> Author:YEE 
	> Mail:15509992895@163.com 
	> Created Time: Thu 19 Sep 2024 02:09:00 PM CST
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>

const char* time2string(time_t timestamp){
    static char time_str[64];
    struct tm *time_info;
    time_info = localtime(&timestamp);
    if(time_info != NULL) {
        strftime(time_str, sizeof(time_str), "%Y-%m-%d  %H:%M", time_info);
        return time_str;
    }
    perror("localtime");
}



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

const char *mode2string(mode_t mode){
    static char str_mode[20];
    switch(mode & S_IFMT){
        case S_IFSOCK:
            str_mode[0] = 's';
            break;
        case S_IFLNK: 
            str_mode[0] = 'l';
            break;
        case S_IFREG: 
            str_mode[0] = 'r';
            break;
        case S_IFBLK: 
            str_mode[0] = 'b';
            break;
        case S_IFDIR: 
            str_mode[0] = 'd';
            break;
        case S_IFCHR: 
            str_mode[0] = 'c';
            break;
        case S_IFIFO: 
            str_mode[0] = 'f';
            break;
    }
    str_mode[1] = (mode & S_IRUSR)? 'r' : '-';
    str_mode[2] = (mode & S_IWUSR)? 'w' : '-';
    str_mode[3] = (mode & S_IXUSR)? 'x' : '-';
    str_mode[4] = (mode & S_IRGRP)? 'r' : '-';
    str_mode[5] = (mode & S_IWGRP)? 'w' : '-';
    str_mode[6] = (mode & S_IXGRP)? 'x' : '-';
    str_mode[7] = (mode & S_IROTH)? 'r' : '-';
    str_mode[8] = (mode & S_IWOTH)? 'w' : '-';
    str_mode[9] = (mode & S_IXOTH)? 'x' : '-';
    
    str_mode[10] = '\0';
    return str_mode;
}

const char *uid2string(uid_t uid){
    struct passwd *pwd = getpwuid(uid);
    if(pwd != NULL) return pwd->pw_name;
    perror("getpwuid");
}

const char *gid2string(gid_t gid){
    struct group *grd = getgrgid(gid);
    if(grd != NULL) return grd->gr_name;
    perror("getgrgid");
}

void print_info(const char* filename, const struct stat * statbuffer){
    printf("name: %s\n", filename);
    printf("Ino : %lu\n", statbuffer->st_ino);
    printf("mode : %s\n", mode2string(statbuffer->st_mode));
    printf("lnknum: %lu\n", statbuffer->st_nlink);
    printf("userid: %s\n", uid2string(statbuffer->st_uid));
    printf("grpid : %s\n", gid2string(statbuffer->st_gid));
    printf("size : %lu\n", statbuffer->st_size);
    printf("time : %s\n", time2string(statbuffer->st_mtime));
    printf("\n");
    return;
}


int main(int argc, char *argv[]){
    char* dirname = argc > 1? argv[1] : "."; 
    DIR* dir_stream;
    struct dirent * dir_struc;
    struct stat * statbuffer;

// 获取文件流
    dir_stream = opendir(dirname);
    if(dir_stream == NULL){
        perror("opendir");
        return 1;
    }
// 读取文件流
    while((dir_struc = readdir(dir_stream)) != NULL){
        if(errno) {
            perror("readdir");
            return 2;
        };
        char pathname[1024] = {0};
        strcat(pathname, dirname);
        strcat(strcat(pathname, "/"), dir_struc->d_name);
        printf("pathname = %s\n", pathname);
        if(stat(pathname, statbuffer)) {
            perror("stat");
            return 3;
        }
        print_info(dir_struc->d_name, statbuffer);
    }

    return 0;
}
