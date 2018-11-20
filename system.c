#include "sys/sys_def.h"
#include "sys/sys_file.h"
#include "sys/sys_io.h"
 
extern int sys_mode;


/*
	sys_mode �V�X�e���̏�� �ʏ탂�[�h(�����������[�h
	sys_main�֐���sys_mode��^���ăV�X�e����؂�ւ���
	���[�h�𕜍������[�h�ɂ������Ȃ�Asys_mode = SYS_MODE_DECODE �Ƃ���
	�ʏ탂�[�h�ɖ߂��ꍇ��sys_mode = SYS_MODE_MAIN �Ƃ���
	sys_main�֐��ɓn���ƃ��[�h���؂�ւ��
*/



int sys_main(int system_mode) {
	
	//system mode �ɂ���ĈقȂ�menu��\��
	sys_menu(system_mode);


	switch (system_mode) {
	
		//MAIN MENU
		case SYS_MODE_MAIN:
			for (;;) {
			
				/*
					sys_command : main menu �ɕ\�����ꂽ���l1~4�Ȃǂ��i�[�����
					sys_input_commnad(a,b,c) a��menu�̍ŏ��� b�����j���[�̍ő吔
					�����ł�1~4�̃��j���[����肽���̂� 1,4�������Ă���
					(MIN_MENU = 1 MAX_MENU = 4)
					system_mode �ɂ�MAIN or DECODE ���[�h�̏�񂪓����Ă��邩��
					sys_command�͂���ɉ����� menu��title��ς��Ă����
				*/
				sys_command = sys_input_command(MIN_MENU, MAX_MAIN_MENU, system_mode);

				switch (sys_command) {
					case 1:
						//�Í���
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
							text_decode(filename) �͗^����ꂽfile���ɑΉ�����
							�Í����ς݃t�@�C�����������ĕ��������Ă����
							�����Ȃ�� SUC��Ԃ�,�G���[�ł����ERR��Ԃ�int�^�̊֐�
							sys_return :: int �Ɏ��s���ʂ������āA
							�������Ă���΃��b�Z�[�W��\��������
						*/
						sys_return = text_decode(file_name);
						if(sys_return == SUC)
							sys_message(SUC, "uncrypted!\n");
							
							
						/*
							���������W���[�����I�������� sys_mode�����C���ɖ߂���
							���������I������@����sys_main�֐��� main.c �ɂ�����
							�������[�v���Ă���B
							���[�v�𔲂��o���ɂ�sys_exit�̈�����EXIT_MAIN��������
							sys_exit��EXIT_DECODE����ꂽ��DECODE MODE���I������
							���C�����j���[�֖߂�
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
