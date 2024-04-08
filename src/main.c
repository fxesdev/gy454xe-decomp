#include <string.h>
#include "main.h"

void memzero_044A8(void *s, size_t n) {
	memset(s, 0, n);
	return;
}

void reset_magic_string_04598(void) {
	char *ptr = magic_string_start;
	char i;
	for (i = 0xf; i >= -1; i--) {
		*ptr = i;
		++ptr;
	}
	return;
}

char need_reset_045A6(void) {
	char i;
	char *ptr = magic_string_start;

	for (i = 0xf; i >= -1; i--) {
		if (*ptr != i) return 1;
		++ptr;
	}
	if (setup_contrast > 0x1d || setup_contrast < 4) return 1;
	
	ptr = var_m_start;
	for (i = 10; i >= -1; i--) {
		if (invalid_var_1B4EA(ptr)) return 1;
		ptr += 10;
	}
	return (d_080DC & 0xf8) == 0 ? 0 : 1;
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
	char i;
	int j = ki_adr;
	KO = 1;

	i = 5;
	loop: if ((*(char*)j) != 0x7b) goto exit;
	else if (--i) goto loop;
	d_080F2 = 0x0180;
	
	exit: f_047EA();
	return i;
}

void diagnostic_mode_048C2(void) {
	fill_screen_02CFE(0x100);
	line_print_small_049F2(1, 0x1f03);
	line_print_small_049F2(0x16, 0x1ee8);
	render_0312C();
	if (f_0B804()) diagnostic_048F6();
	return;
}

void diagnostic_048F6(void) {
	int *ptr = magic_string_start;
	char temp;

	*ptr = 0; ptr += 2; *ptr = 0;
	cursor_noflash = 1;
	diag_scr_fill_ws_04A02(0xff);
	diag_scr_fill_ws_04A02(0);
	diag_scr_box_ws_04A58();
	diag_scr_ckb1_ws_04A10();
	diag_scr_ckb2_ws_04A30();
	diag_checksum_04A9E();
	f_0B5C6(0);
	set_contrast_08FA2(1);
	diag_check_key_04986();
	line_print_small_049F2(0, 0x1ef1);
	line_print_small_049F2(0xf, 0x1ef9);
	line_print_small_049F2(0x16, 0x1ee8);
	render_0312C();
	// getscancode takes in an argument from ER14/FP! may need updating in the future
	getscancode_0B0C6(1);
	temp = setup_contrast;
	reset_all_0AFB0();
	setup_contrast = temp;
	f_04776();
	f_03558();
	return;
}

// 09712
void main(void) {
	char i, j;

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
		fill_screen_02CFE(0x200);
	}

	if (mode == MODE_EQN) table_mode = TABLE_EQN;
	else if (mode == MODE_INEQ) table_mode = TABLE_INEQ;
	else if (mode == MODE_RATIO) table_mode = TABLE_RATIO;
	f_112EA();

	j = 0;
	while (1) {
		if (j) {
			f_0478E();
			// odd MOV R0, #1 in compiled code here
			getkeycode_0B45E(1);
			f_044D6();
			if (last_fn_key == K_MODE) screen_state = 1;
			else if (last_fn_key == K_SETUP) screen_state = 2;
			else if (last_fn_key > 0 && last_fn_key < 12) screen_state = 3;
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
		j = 1;
		if (screen_state) {
			switch (screen_state) {
				case 1:
					d_08126 = 0;
					i = f_08CD6();
				case 2:
					d_08126 = 0;
					if (i = f_08DBA()) {
						f_044D2();
						if (!(table_mode & (1 << 4))) f_044B6();
					}
			}
			if (!i) render_0312C();
			else j = 0;
			screen_state = 0;
		}
		if (f_0B6B6()) j = f_09962(0);
		else {
			if (table_mode != TABLE_EQN && table_mode != TABLE_INEQ && TABLE_RATIO && last_fn_key == K_AC) {
				table_mode = 1;
				f_0B8B8();
				j = 0;
			}
			else if (table_mode == TABLE_STAT_TABLE) {
				f_0A0BC();
				j = 1;
			}
			else if (table_mode == TABLE_MATRIX) j = f_0A93A(i);
			else if (table_mode == TABLE_VECTOR) j = f_0A936(i);
			else if (table_mode == TABLE_EQN) j = f_0A594(i);
			else if (table_mode == TABLE_RANGE) j = f_0A050(i);
			else if (table_mode == TABLE_CALC) j = f_09BDC(i);
			else if (table_mode == TABLE_SOLVE) j = f_09BDC(i);
		}
	}
}


void reset_all_0AFB0(void) {
	memzero_044A8(0x8000, 0xa17);
	setup_contrast = 0x11;
	f_04776();
	use_buffer = 1;
	d_080DC = pd_value_03486();
	f_0AFE0();
	reset_magic_string_04598();
	return;
}
