
#ifndef SYS_FILE_H
#define SYS_FILE_H


#include <sys/stat.h>


extern char cfile_name[MAX_NAME];
extern char kfile_name[MAX_NAME];


//text_data function
text_data init_text_data(char name[MAX_NAME]) {
	text_data text;
	text.fp = fopen(name, "r");
	return text;
}


enc_info update_enc_data(enc_info enc) {
	enc.shift = (rand() % MAX_RAND) + 1;
	enc.enc_code = (enc.code + enc.shift) % 123;
	enc.key = int_to_char(enc.shift);
	if (enc.enc_code < 97)
		enc.enc_code += 97;
	return enc;
}



//コード操作
char int_to_char(int num) {
	return num + '0';
}

int char_to_int(char c) {
	return c - '0';
}

//ファイル操作
void reset_file_name() {
	strcpy(cfile_name, "./encrypted/u_");
	strcpy(kfile_name, "./key/k_");
}


// check_file_name(file)
// file が存在すればEXIST を返す。なければNOT_EXIST
int check_file_name(char file_name[MAX_NAME]) {
	struct stat statBuf;
	if (stat(file_name, &statBuf) == 0)
		return EXIST;
	else
		return NOT_EXIST;

}

int set_file_name(int mode,char name[MAX_NAME]) {	
	/*
		基本的にcfile_nameなどはディレクトリの位置が代入されている
		そこにファイル名を挿入することで、暗号化対象のパスをcfile_name に代入できる
		復号化の場合は暗号化済みのファイル名を入力してもらうこととする

		そのため、鍵ファイルのパスは若干処理を加えなくてはいけない
		そのため DECODE と ENCODEとしてモードを分けることにした。
	*/
	switch (mode) {
		case ENCODE:
			
			
			//key file name
			strcat(kfile_name, name);

			//crypt file name
			strcat(cfile_name, name);
			break;


		case DECODE:
			strcpy(cfile_name, "./encrypted/");
			strcat(cfile_name, name);


			// u_text.txt から text.txtを抽出
			int str_length = strlen(name), i;
			for (i = 0; i <= str_length; i++) {
				name[i] = name[i + 2];
			}

			// ./key/k_ + test.txt
			strcat(kfile_name, name);
			break;
	}

	if (check_file_name(cfile_name) == NOT_EXIST)
		return ERR;
	return SUC;

}



// write
void write_data(char fileName[MAX_NAME], char code) {
	FILE *fp;
	fp = fopen(fileName, "a");
	fprintf(fp, "%c", code);
	fclose(fp);
}


void write_enc_data(char code, char key) {
	write_data(cfile_name, code);
	write_data(kfile_name, key);
}


#endif
