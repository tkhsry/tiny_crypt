
#ifndef SYS_DEF_H
#define SYS_DEF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>



//var max
#define MAX_ALPHA 26
#define MAX_NAME 50
#define MAX_RAND 8

//menu 
#define MIN_MENU 1
#define MAX_MAIN_MENU 4
#define MAX_DECODE_MENU 3


//sys
#define SYS_HELP 0
#define SYS_MODE_MAIN 0
#define SYS_MODE_DECODE 1


//mode exit
#define EXIT_MAIN 0
#define EXIT_DECODE 1


//system message
#define ERR 7
#define SUC 8


//file check
#define EXIST 0
#define NOT_EXIST 1


//file name set mode
#define ENCODE 0
#define DECODE 1
#define ANALYZE 2

//Compile setting
//#define Compile_Windows 1
#define Compile_Linux 1

#ifdef Compile_Windows
#include <direct.h>
#endif



// system global var
int sys_command;
int sys_return;
char file_name[MAX_NAME];
char text_code[MAX_NAME];

// load function
char int_to_char(int);
int char_to_int(char);
void sys_message(int, char[]);
int sys_main(int);
void sys_init(void);


// def struct 
typedef struct text_data {
	FILE *fp;
	char name[MAX_NAME];
}text_data;



/*
	shift シフト数
	key	  鍵情報(シフト数)
	code  平文字
	enc_code 暗号化した平文字
	dec_code 復号化した平文字
	key_code シフト情報を読み込むとき、文字として読み込むから必要
	key_codeはchar型なのでchar to int関数で数値に戻してshiftに代入する

*/

typedef struct enc_info {
	int shift;
	char key;
	char code, enc_code, key_code, dec_code;
}enc_info;


#endif
