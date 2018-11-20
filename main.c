#include "sys/sys_def.h"


//encode and decode file name
char cfile_name[MAX_NAME] = "./encrypted/u_";
char kfile_name[MAX_NAME] = "./key/k_";
int sys_mode = SYS_MODE_MAIN;



int main(void) {
	int exit_result;
	sys_init();

	for (;;) {
		exit_result = sys_main(sys_mode);
		if (exit_result == EXIT_MAIN)
			break;
	}

	return 0;
}
