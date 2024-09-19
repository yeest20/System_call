/*************************************************************************
	> File Name: 2.my_errornum_test.c
	> Author:YEE 
	> Mail:15509992895@163.com 
	> Created Time: Wed 18 Sep 2024 09:03:30 PM CST
 ************************************************************************/

#include<stdio.h>
#include"my_errno.h"

int main(){
    if(open_heart(NULL) < 0){
        my_perror("open_heart NULL");
    } 

    if(open_heart("/Lily") < 0){
        fprintf(stderr, "open_heart / Lily : %s\n", my_strerror(my_errno));
    }
    
    if(open_heart("Lucy") < 0){
        my_perror("open_heart Lucy");
    }
    return 0;
}
