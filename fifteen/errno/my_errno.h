/*************************************************************************
	> File Name: my_errno.h
	> Author:YEE 
	> Mail:15509992895@163.com 
	> Created Time: Wed 18 Sep 2024 08:44:13 PM CST
 ************************************************************************/

#ifndef _MY_ERRNO_H
#define _MY_ERRNO_H

#define MY_SUCCESS 0
#define MY_NO_ACCESS 1
#define MY_HEART_LOCKED 2

extern int my_errno;

const char* my_strerror(int my_errno);
void my_perror(const char *prefix);
int open_heart(const char *name);
#endif
//避免头文件重复引用
