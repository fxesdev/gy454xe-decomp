#include <string.h>
#include "main.h"

void memzero_044A8(void s, size_t n) {
	memset(s, 0, n);
	return;
}

void reset_magic_string_04598(void) {
	int ptr = magic_string_start;
	for (i = 0xf; i >= -1; i--) (char*)ptr = i;
	return;
}

char need_reset_045A6(void) {
	char i;
	int ptr = magic_string_start;

	for (i = 0xf; i >= -1; i--) {
		if ((char*)ptr != i) return 1;
	}
	if (setup_contrast > 0x1d || setup_contrast < 4) return 1;
	
	ptr = var_m_start;
	for (i = 10; i >= -1; i--) {
		if (invalid_var_1B4EA(ptr)) return 1;
		ptr += 10;
	}
	return (d_080DC & 0b11111000) == 0 ? 0 : 1
}

void f_046E0(void) {
	char i = 53;
	int j = 501;

	d_0F00A = 0;
	while (--i) {}
	while (--j) {}
	d_0F221 = 5;
	d_0F222 = 4;
	d_0F223 = 1;
	f_04760();
	f_04728();
	f_04738();
	KI_H = 0;
	f_03518();
	f_047DA();
	f_047EA();
	return;
}

char diag_init_check_04898(void) {
	KO = 1;
	char i;

	while (i--)
	{
		if (KI != 0b01111011) {
			f_047EA();
			return i;
		}
	}
	d_080F2 = 0x0180;
	f_047EA();
	return i;
}

void main_09712(void) {
	char j;

	memset((char*)mstack_start, 90, 800);
	f_046E0();
	delay_04640(952);
	cursor_noflash = 0;
	if (need_reset_045A6()) {
		reset_all_0AFB0();
	}
	f_03558();
	f_047CA();
	f_0478E();
	f_04CAA();
	if (!diag_init_check_04898()) {
		diagnostic_mode_048C2();
	}
	if (mode == MODE_EQN || mode == MODE_INEQ || mode == MODE_RATIO) {
		d_080FE = 0;
		last_fn_key = 0;
		f_02CFE(0x200);
	}

	switch (mode) {
		case MODE_EQN: table_mode = TABLE_EQN; break;
		case MODE_INEQ: table_mode = TABLE_INEQ; break;
		case MODE_RATIO: table_mode = TABLE_RATIO; break;
	}
	f_112EA();

	j = 0;
	while (1) {
		if (j) {
			f_0478E();
			// odd MOV R0, #1 in compiled code here
			getkeycode_0B45E();
			f_044D6();
			if (last_fn_key == K_MODE) screen_state = 1;
			else if (last_fn_key == K_SETUP) screen_state = 2;
			if (last_fn_key > 0 && last_fn_key < 12) screen_state = 3;
			else {
				if (last_fn_key == K_CALC) {
					if (f_09D84()) continue;
					if (mode == MODE_COMP || mode == MODE_CMPLX) f_09D54(0xa0);
					else continue;
				}
				else if (last_fn_key == K_SOLVE) {
					if (f_09D84()) continue;
					if (mode == MODE_COMP) f_09D54(0xc0);
					else continue;
				}
				else screen_state = 0;
			}
		}
		// TODO
	}

	return;
}

void reset_all_0AFB0(void) {
	memzero_044A8(0x8000, 0xa17)
	setup_contrast = 0x11;
	f_04776();
	use_buffer = 1;
	d_080DC = pd_value_03486();
	f_0AFE0();
	reset_magic_string_04598();
	return;
}

void main(void) {
	main_09712();
	return;
}
