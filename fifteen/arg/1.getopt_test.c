/*************************************************************************
	> File Name: 1.getopt_test.c
	> Author:YEE 
	> Mail:15509992895@163.com 
	> Created Time: Thu 19 Sep 2024 12:41:25 AM CST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

char *name = NULL;
int age = 18;
char *gender = "male";

int main(int argc, char *argv[]){
    int opt;
    while((opt = getopt(argc, argv, "nag")) != -1 ){
        switch(opt){
            case 'n':
                name = "YEE";
                break;
            case 'a':
                age = 18;
                break;
            case 'g':
                gender = "male";
                break;
            default:
                fprintf(stderr, "Usage : %s -n  -a  -g \n", argv[0]);
                return 1;
        }
    }
    printf("optind : %d\n", optind);
    printf("argv : %s\n", argv[optind]);
    printf("name: %s\n", name);
    printf("age : %d\n", age);
    printf("gender: %s\n", gender);
    return 0;
}
