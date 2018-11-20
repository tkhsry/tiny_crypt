#include "sys/sys_def.h"
#include "sys/sys_file.h"
#include "sys/sys_io.h"
 
extern int sys_mode;


/*
	sys_mode システムの状態 通常モード(か復号化モード
	sys_main関数にsys_modeを与えてシステムを切り替える
	モードを復号化モードにしたいなら、sys_mode = SYS_MODE_DECODE とする
	通常モードに戻す場合はsys_mode = SYS_MODE_MAIN として
	sys_main関数に渡すとモードが切り替わる
*/



int sys_main(int system_mode) {
	
	//system mode によって異なるmenuを表示
	sys_menu(system_mode);


	switch (system_mode) {
	
		//MAIN MENU
		case SYS_MODE_MAIN:
			for (;;) {
			
				/*
					sys_command : main menu に表示された数値1~4などが格納される
					sys_input_commnad(a,b,c) aがmenuの最小数 bがメニューの最大数
					ここでは1~4のメニューを作りたいので 1,4を代入している
					(MIN_MENU = 1 MAX_MENU = 4)
					system_mode にはMAIN or DECODE モードの情報が入っているから
					sys_commandはそれに応じて menuのtitleを変えてくれる
				*/
				sys_command = sys_input_command(MIN_MENU, MAX_MAIN_MENU, system_mode);

				switch (sys_command) {
					case 1:
						//暗号化
						sys_input_str(file_name, "TEXT FILE NAME");
						sys_return = text_encode(file_name);
						if(sys_return == SUC)
							sys_message(SUC, "encrypted!");
						break;


					case 2:
						sys_mode = SYS_MODE_DECODE;
						return sys_exit(EXIT_DECODE);
						break;

					case 3:
						sys_input_str(text_code, "ENCRYPTED CODE");
						text_analyze(text_code);
						return sys_exit(EXIT_MAIN);
						break;

					case 4:
						return sys_exit(EXIT_MAIN);
						break;
				}
			}
			break;


		//DECODE MODE MENU
		case SYS_MODE_DECODE:
			for (;;) {
				
				
				sys_command = sys_input_command(MIN_MENU, MAX_DECODE_MENU, system_mode);

				switch (sys_command) {
					case 1:
						// LIST DISPLAY
						text_cat_dir();
						break;

					case 2:
						// SYS_MODE_DECODE
						sys_input_str(file_name, "ENCRYPTED FILE NAME");
						/*
							text_decode(filename) は与えられたfile名に対応する
							暗号化済みファイルを検索して復号化してくれる
							成功ならば SUCを返し,エラーであればERRを返すint型の関数
							sys_return :: int に実行結果を代入して、
							成功していればメッセージを表示させる
						*/
						sys_return = text_decode(file_name);
						if(sys_return == SUC)
							sys_message(SUC, "uncrypted!\n");
							
							
						/*
							復号化モジュールが終了したら sys_modeをメインに戻して
							復号化を終了する　このsys_main関数は main.c において
							無限ループしている。
							ループを抜け出すにはsys_exitの引数にEXIT_MAINを代入する
							sys_exitにEXIT_DECODEを入れたらDECODE MODEが終了して
							メインメニューへ戻る
						*/
						sys_mode = SYS_MODE_MAIN;
						return sys_exit(EXIT_DECODE);
						break;

					case 3:
						// EXIT
						
						sys_mode = SYS_MODE_MAIN;
						return sys_exit(EXIT_DECODE);
						break;
				}


			}
			break;
	}
}
