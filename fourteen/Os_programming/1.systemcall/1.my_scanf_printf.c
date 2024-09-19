/*************************************************************************
	> File Name: 1.my_scanf_printf.c
	> Author:YEE 
	> Mail:15509992895@163.com 
	> Created Time: Wed 18 Sep 2024 02:34:49 PM CST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdarg.h>

#define BUFFER_SIZE 1024

void my_scanf(const char *format, ...){
    char buffer[BUFFER_SIZE];
    va_list args;
    va_start(args, format);
    ssize_t len = read(STDIN_FILENO, buffer, BUFFER_SIZE);
    vsscanf(buffer, format, args);
    va_end(args);
}
void my_printf(const char *format, ...){
    char buffer[BUFFER_SIZE];
    va_list args;
    va_start(args, format);
    ssize_t len = vsnprintf(buffer, BUFFER_SIZE, format, args);
    va_end(args);
    // write
    write(STDOUT_FILENO, buffer, len);
}

int main(){
    int num;
    char str[10];
    my_printf("Please input a number : \n");
    my_scanf("%d", &num);
    my_printf("The numer input is : %d\n", num);

    my_printf("Please input a string : \n");
    my_scanf("%s", str);
    my_printf("The string input is : %s\n", str);
    return 0;
}


