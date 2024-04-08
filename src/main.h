#define var_m_start 0x8226
#define magic_string_start 0x860E
#define mstack_start 0x8A18

#define MODE_COMP 0xC1
#define MODE_CMPLX 0xC4
#define MODE_EQN 0x45
#define MODE_RATIO 0x4A
#define MODE_INEQ 0x4B

#define TABLE_RANGE 0x06
#define TABLE_STAT_TABLE 0x12
#define TABLE_MATRIX 0x13
#define TABLE_VECTOR 0x14
#define TABLE_EQN 0x15
#define TABLE_RATIO 0x17
#define TABLE_INEQ 0x18
#define TABLE_CALC 0xA0
#define TABLE_SOLVE 0xC0

#define K_MODE 0xE4
#define K_SETUP 0xE5
#define K_AC 0xE6
#define K_CALC 0xFC
#define K_SOLVE 0xFD

#define d_080F2 (*(int*)0x80F2)
#define d_080DC (*(char*)0x80DC)
#define cursor_noflash (*(char*)0x80DD)
#define last_fn_key (*(unsigned char*)0x80F5)
#define mode (*(unsigned char*)0x80F9)
#define screen_state (*(char*)0x80FB)
#define table_mode (*(char*)0x80FC)
#define d_080FE (*(char*)0x80FE)
#define setup_contrast (*(char*)0x810E)
#define use_buffer (*(char*)0x811D)
#define d_08126 (*(char*)0x8126)

#define d_0F00A (*(char*)0xF00A)
#define DSPCNT (*(char*)0xF032)
#define KI (*(int*)0xF040)
#define KI_H (*(int*)0xF041)
#define KO (*(int*)0xF046)
#define d_0F221 (*(char*)0xF221)
#define d_0F222 (*(char*)0xF222)
#define d_0F223 (*(char*)0xF223)

void f_02CFE(int a);
void render_0312C(void);
char pd_value_03486(void);
void f_03518(void);
void f_03558(void);
void memzero_044A8(void *s, size_t n);
void f_044B6(void);
void f_044D2(void);
void f_044D6(void);
void reset_magic_string_04598(void);
char need_reset_045A6(void);
void delay_04640(int a);
void f_046E0(void);
void f_04728(void);
void f_04738(void);
void f_04760(void);
void f_04776(void);
void f_047CA(void);
void f_047DA(void);
void f_047EA(void);
void f_0478E(void);
char diag_init_check_04898(void);
void diagnostic_mode_048C2(void);
void f_04CAA(void);
char f_08CD6(void);
char f_08DBA(void);
void main(void);
char f_09962(char a);
char f_09BDC(char a);
char f_09D54(char a);
char f_09D84(void);
void reset_all_0AFB0(void);
char f_0A050(char a);
void f_0A0BC(void);
char f_0A594(char a);
char f_0A936(char a);
char f_0A93A(char a);
void f_0AFE0(void);
void getkeycode_0B45E(char a);
char f_0B6B6(void);
char f_0B8B8(void);
void f_112EA(void);
char invalid_var_1B4EA(void *var);
