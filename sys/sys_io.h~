
/*
	system standard input and output functions.
*/



#ifndef SYS_IO_H
#define SYS_IO_H

#include <math.h>


//初期化 フォルダ作成、乱数設定
void sys_init(void) {

#ifdef Compile_Windows
	mkdir("encrypted");
	mkdir("key");
#endif

#ifdef Compile_Linux
	mkdir("encrypted",0755);
	mkdir("key",0755);
#endif

	//乱数初期化
	srand((unsigned)time(NULL));
}

int sys_exit(int res) {
	if (res == 0)
		sys_message(0, "SEE YOU... ");
	return res;
}



// system message
void sys_menu(int mode) {
	printf("\n\n#======================================#\n");
	switch (mode) {
		case SYS_MODE_MAIN:
			printf("\tTINY  CRYPT\t\n");
			printf("\t  1.Encryption\n");
			printf("\t  2.Decryption\n");
			printf("\t  3.Analyze\n");
			printf("\t  4.Exit\n");
			break;

		case SYS_MODE_DECODE:
			printf("\tDECODE MODE\t\n");
			printf("\t  1.List Display\n");
			printf("\t  2.Decryption\n");
			printf("\t  3.Exit\n");
			break;
	}
	printf("#======================================#\n\n\n");
}


void sys_message(int mode, char message[MAX_NAME]) {
	switch (mode) {
	case ERR:
		printf("\n\nERROR: ");
		break;
	case SUC:
		printf("\n\nSUCCESS: ");
		break;
	default:
		printf("\n");
		break;
	}
	printf("%s\n", message);
}



// file name または mode の入力

int sys_input_int(char message[MAX_NAME]) {
	int num;
	printf("%s", message);
	printf(" >>");
	scanf("%d", &num);
	return num;
}


void sys_input_str(char *name, char message[MAX_NAME]) {
	printf("%s", message);
	printf(" >>");
	scanf("%s", name);
}




// menu の入力機構 menuの数に応じて入力待ちさせられる

int sys_input_command(int menu_min, int menu_max, int sys_mode) {
	int sys_command;
	do {
		sys_command = sys_input_int("COMMAND");
		if (sys_command == SYS_HELP) {
			sys_menu(sys_mode);
		}
		else if (sys_command > menu_max || sys_command < menu_min) {
			sys_message(ERR, "this is not command \n");
			printf("Please check command -- help: 0\n\n");
		}
	} while (sys_command > menu_max || sys_command < menu_min);
	return sys_command;
}









/* 
	encode, decode関係
*/

int text_encode(char name[MAX_NAME]) {
	if( check_file_name(name) == NOT_EXIST){
		sys_message(ERR,"This file is not exist.\n");
		return ERR;
	}
	
	set_file_name(ENCODE,name);
	if (check_file_name(cfile_name) == EXIST) {
		sys_message(ERR, "This file has been encrypted.\n");
		reset_file_name();
		return ERR;
	}
	
	text_data heibun = init_text_data(name);
	enc_info enc;

	while ((enc.code = fgetc(heibun.fp)) != EOF) {

		/*
		安全性を大きくするためにシフト数は毎回変動
		そのために情報は毎回更新しなくてはいけない
		シフト数や暗号化後の文字情報などを更新する
		*/
		enc = update_enc_data(enc);



		if (islower(enc.code)) {
			//暗号化後の情報を表示(TEST用)
			putchar(enc.enc_code);

			//write_enc_data(暗号化情報,鍵情報) を書き込む
			write_enc_data(enc.enc_code, enc.key);
		}
		else {
			putchar(enc.code);
			write_enc_data(enc.code, int_to_char(0));
		}
	}
	//ファイル名の初期化をする必要がある
	reset_file_name();
	fclose(heibun.fp);
	return SUC;
}


// decode function
// key file name を受け取る
int text_decode(char name[MAX_NAME]) {
	
	// set decode file name
	char decode_file_name[MAX_NAME] = "dec_";
	strcat(decode_file_name,name);
	
	
	
	//decode fileの名前を格納する
	//存在しないfileの入力があればreject
	if (set_file_name(DECODE,name) == ERR) {
		sys_message(ERR, "This file is not exist.\n");
		reset_file_name();
		return ERR;
	}


	// file open and information initialize
	printf("%s\n%s\n", kfile_name, cfile_name);
	text_data cfile = init_text_data(cfile_name);
	text_data kfile = init_text_data(kfile_name);
	enc_info dec;


	// decode
	while (((dec.code = fgetc(cfile.fp)) != EOF) && ((dec.key = fgetc(kfile.fp)) != EOF)) {
		if (islower(dec.code)) {
			dec.dec_code = dec.code - char_to_int(dec.key);
			if (dec.dec_code < 97)
				dec.dec_code += MAX_ALPHA;
			
			
			// file 復元
			write_data(decode_file_name,dec.dec_code);
			putchar(dec.dec_code);
		}
		else {
			write_data(decode_file_name,dec.code);
			putchar(dec.code);

		}
	}
	reset_file_name();
	fclose(cfile.fp);
	fclose(kfile.fp);
	return SUC;
}


void text_cat_dir(void) {
	printf("\n+---CRYPTED FILES---+\n");
	#ifdef Compile_Windows
		system("dir /b encrypted");
	#endif

	#ifdef Compile_Linux
		system("ls ./encrypted/");
	#endif
	printf("\n");
}



//analys 
char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
double alpha_freq[] = { 8.2,1.5,2.8,4.3,12.7,2.2,2.0,6.1,7.0,0.2,0.8,4.0,2.4,
6.7,7.5,1.9,0.1,6.0,6.3,9.1,2.8,1.0,2.4,0.2,2.0,0.1 };



// analys var
double alpha_str_freq[MAX_ALPHA];
double alpha_chisqr[MAX_ALPHA];



//文字列中にあるアルファベットが何文字あったか返す
int alpha_count(char alpha, char str[MAX_NAME]) {
	int count = 0, i;
	for (i = 0; i < strlen(str); i++) {
		if (str[i] == alpha)
			count++;
	}
	return count;
}


double array_min(double *list) {
	int i;
	double min = list[0];
	for (i = 1; i < MAX_ALPHA; i++) {
		if (list[i] < min)
			min = list[i];
	}
	return min;
}


int search_list(double num, double *list) {
	int i;
	for (i = 0; i < MAX_ALPHA; i++) {
		if (list[i] == num)
			return i;
	}
}



void freqs(char str[MAX_NAME]) {
	int len = strlen(str), i;
	for (i = 0; i < len; i++) {
		alpha_str_freq[i] = (alpha_count(alphabet[i], str)/(double)len)*100;
	}
}


//カイ二乗検定
double chisqr(double alp_freq[]) {
	int i;
	double numerator,result=0;

	for (i = 0; i < MAX_ALPHA; i++) {
		numerator = (alp_freq[i] - alpha_freq[i]);
		alpha_chisqr[i] = (pow(numerator, 2) / alpha_freq[i]);
		result += alpha_chisqr[i];
	}
	return result;
}


void text_shift(char text[MAX_NAME],int shift) {
	enc_info crypt;

	// file name にする 入力は空白の処理とかあるからだめ
	//text_data textdata = init_text_data(text);
	//enc_info enc_data;

	int i,enc[MAX_NAME],dec[MAX_NAME];

	for (i = 0; i < strlen(text); i++) {
		crypt.code = text[i];
		if (islower(crypt.code)) {
			crypt.dec_code = crypt.code - shift;
			if (crypt.dec_code < 97)
				crypt.dec_code += MAX_ALPHA;
			text[i] = crypt.dec_code;
		}
	}
}


void copy_text(char copy_text[MAX_NAME], char text[MAX_NAME]) {
	int i;
	for (i = 0; i < MAX_NAME; i++) {
		copy_text[i] = text[i];
	}
}



//
void text_analyze(char text[MAX_NAME]) {
	int shift,key,i;
	char exp_text[MAX_NAME];
	double exp_list[MAX_ALPHA],exp_min;

	copy_text(exp_text, text);

	for (shift = 0; shift < MAX_ALPHA; shift++) {
		text_shift(text,shift);

		// 文字の出現頻度を alpha_str_freq に代入する
		freqs(text);

		/*
		出現頻度に基づいてカイ二乗検定を行い
		その結果をalpha_chisqrの結果が小さいほど英文の頻出率に似ている
		*/

		exp_list[shift] = chisqr(alpha_str_freq);
	}

	// 予想される検定の中で最小のものを代入
	exp_min = array_min(exp_list);

	key = search_list(exp_min,exp_list);
	printf("key: %d\n", key);

	printf("text: %s\n", exp_text);
	text_shift(exp_text, key+1);
	printf("exp : %s\n", exp_text);
}


#endif
