//
// Created by deadlok on 3/27/23.
//

#ifndef BANKPROJECTWITHC_Z_LIBRARY_H
#define BANKPROJECTWITHC_Z_LIBRARY_H

#include "stdio.h"

//functions declaration
int str_len(char str[100]);//to find length of char array
int int_len(long long int num);
int str_cmp(char str1[100], char str2[100]);
int indexOf_char(char str[100], char toFind); // only can find first index
int index_counter(char str[100], char toFind);
void str_copy(char dest[100], char src[100]);

//global variables
//converting

//code body
int str_len(char str[100]){
    int length = 0;
    while(str[length] != '\0'){
        length++;
    }
    return length;
}

int int_len(long long int num){
    int length = 0;
    while(num != 0){
        length++;
        num /= 10;
    }
    return length;
}

int str_cmp(char str1[100], char str2[100]){
    int str1_counter = str_len(str1);
    int str2_counter = str_len(str2);
    int check_counter = 0;

    if(str1_counter == str2_counter){
        for(int i = 0; i<str1_counter; i++){
            if(str1[i] != str2[i]){
                break;
            }
            check_counter++;
        }
        if(str1_counter == check_counter){
            return 1;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

int indexOf_char(char str[100], char toFind){
    int str_counter = str_len(str);
    for(int i=0; i<str_counter; i++){
        if(str[i] == toFind){
            return i;
        }
    }
    return -1;
}

int index_counter(char str[100], char toFind){
    int str_counter = str_len(str);
    int index = 0;
    for(int i = 0; i<str_counter; i++){
        if(str[i] == toFind){
            index++;
        }
    }

    if(index != 0){
        return index;
    }else{
        return -1;
    }
}

void str_copy(char dest[100], char src[100]){
    int src_counter = str_len(src);
    for(int i = 0; i<src_counter; i++){
        dest[i] = src[i];
    }
}

#endif //BANKPROJECTWITHC_Z_LIBRARY_H
