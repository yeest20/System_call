/*************************************************************************
	> File Name: 2.weather_cli.c
	> Author:YEE 
	> Mail:15509992895@163.com 
	> Created Time: Thu 19 Sep 2024 10:22:51 AM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>



#define VERSION "weather 1.0"

typedef struct {
    char city[50];
    char condition[50];
    double temp;
}WeatherInfo;


WeatherInfo weather_data[] = {
    {"BeiJing", "Sunny", 15.2},
    {"ShangHai", "Cloudy", 18.2},
    {"NewYork", "Rainy", 10.6},
    {"Lundon", "Snowy", 7.8},
    {"", "", 0}
};

const char *get_weather_emoji(const char* condition){
    if(strcmp(condition, "Sunny") == 0) {
        return "☀";
    }else if(strcmp(condition, "Cloudy") == 0) {
        return "☁";
    }else if(strcmp(condition, "Rainy") == 0) {
        return "🌧";
    }else if(strcmp(condition, "Snowy") == 0) {
        return "❄";
    }else{
        return "❓";
    }
}

void print_usage(const char *cmdname){
    printf("Usage: %s [OPTIONS] !\n", cmdname);
    printf("Options:\n");
    printf("-h: Show help message\n");
    printf("-v: Show vesion information\n");
    printf("-t: Only show temperature\n");
    printf("-C: Only show weather condition\n");
    printf("-a: Show all weather information of the DB\n");
    printf("-c City: Specify the city of weather query\n");
    
    return;
}

void print_all_weather(){
    for(int i = 0; weather_data[i].city[0] != '\0'; i++){
        printf("%s : %s  %.1lf℃\n", weather_data[i].city, get_weather_emoji(weather_data[i].condition), weather_data[i].temp);
    }
    return;
}

void print_weather(const char *city, int t_flag, int C_flag){
    double temp = 0;
    char *Condition;
    int city_in_flag = 0;
    for(int i = 0; weather_data[i].city[0] != '\0'; i++){
        if(strcmp(city, weather_data[i].city) != 0) continue;
        Condition = weather_data[i].condition;
        temp = weather_data[i].temp;
        city_in_flag = 1;
        break;
    }

    if(!city_in_flag){
        printf("No such city....\n");
        return;
    }

    printf("%s : ", city);
    if(!t_flag && !C_flag){
        printf("%s  %.1lf℃ \n", get_weather_emoji(Condition), temp);
    }
    if(C_flag){
        printf("%s  ", get_weather_emoji(Condition));
        if(!t_flag) printf("\n");

    } 
    if(t_flag){
        printf("%.1lf℃ \n", temp);
    }
    return;
}

int main(int argc, char* argv[]){
    int opt;
    int t_flag = 0, C_flag = 0, a_flag = 0;
    char *city = NULL;
    while((opt = getopt(argc, argv, "vhtc:Ca")) != -1 ){
        switch(opt){
            case 'h':
                print_usage(argv[0]);
                return 0;
            case 'v':
                printf(VERSION"\n");
            case 'c':
                city = optarg;
                break;
            case 't':
                t_flag = 1;
                break;
            case 'C':
                C_flag = 1;
                break;
            case 'a':
                a_flag = 1;
                break;
            default:
                print_usage(argv[0]);
                return 1;
        }
    }
    if(a_flag){
        print_all_weather();
    }else if(city != NULL){
        print_weather(city, t_flag, C_flag);
    }else{
        printf("Error...Please input again...\n");
        print_usage(argv[0]);
    } 
    return 0;
}
