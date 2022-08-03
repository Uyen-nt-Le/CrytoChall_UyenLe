#ifndef CHALL_UTILITIES
#define CHALL_UTILITIES

// Created for Challenge 1
int hex_to_dec(char hbuf[], int dbuf[], const size_t bs);
int * dec_to_bin4(int dbuf[], int bbuf[], const size_t bs);
char * bin_to_base64(char b64buf[], int bbuf[], const size_t n, const size_t bs);

// Created for Challenge 2
int * b_XOR_b(int bbuf1[], int bbuf2[], int bbuf3[], const size_t H);
int * bin4_to_dec(int bbuf[], int dbuf[], const size_t bs);
char * dec_to_hex(int dbuf[], char hbuf[], const size_t bs);

// Created for Challenge 3
int * dec_to_bin8(int dbuf[], int bbuf[], const size_t bs);
int * fill_binbuf(int buf[], int bits[], const size_t bs, int bi);
int * get_bin(int dec, int bits[], const size_t n);
void testkeys(int a, int b, const size_t bs, int msgbuf[]);
char * dec_to_char(char st[], int dbuf[], const size_t bs);
int * bin8_to_dec(int bbuf[], int dbuf[], const size_t bs);

// Created for Challenge 4
char * str_to_char(std::string s, char c[]);
void testkeys2(int a, int b, const size_t bs, int msgbuf[], std::ofstream& f);
bool char_only(char s[], const size_t len);
bool best_sentence(char st[], size_t len);

// Created for Challenge 5
int * char_to_dec(char st[], int dbuf[], const size_t bs);

// Helpers
void printbuf(int buf[], int s);
void printbuf_space(int buf[], int s);
void printbuf_space_set(int buf[], int s, int bb);
void print_matrix(std::string (*mtrx)[4]);
void print_wordint(int (*w)[8]);
void print_matrix3(int mtrx[4][4][8]);


// Created for Challenge 6
int hamming(int bbuf1[], int bbuf2[], const size_t s);
int * base64_to_dec(char b64[], int dbuf[], const size_t s);
int * dec_to_bin6(int dbuf[], int bbuf[], const size_t bs);
int * binchar_to_int(char cbuf[], int bbuf[], const size_t s);
int min_el_in(double buf[], const size_t s);
double * get_ham_dist(const size_t K, int keysize[], const size_t bi_temp, int tempbinbuf[], double ham[]);
void get_keysiz_matrix(std::ifstream& bin_file2, std::ofstream& bin_keysiz_block, std::string bin_line, int &max_col, int &max_row, char (*block_matrix)[1000][8]);
void transpose_matrix(int &max_col, int &max_row, char (*block_transpose_matrix)[100][8], char (*block_matrix)[1000][8], std::ofstream& bin_block);
char * testkeys3(int a, int b, const size_t bs, int msgbuf[], std::ofstream& f, char keys[], size_t& k_i);

// Created for Challenge 7
void create_4x4(char hbuf[], std::string (*mtrx)[4]);
int hex_to_dec_single(char h);
std::string * sub_word(std::string w[4], std::string sw[4]);
void key_expansion(std::string (*keymtrx)[4], std::string (*subkeymtrx)[4], int round);
void get_word_bin(std::string w[4], int (*wordbin)[8]);
std::string * rot_word(std::string w[4], std::string rw[4], int shift);
std::string * get_round_constant(int r, std::string rc[]);
void g(std::string w[], int (*xorword)[8], int round);
void xor_word(int w1[4][8], int w2[4][8], int (*w3)[8]);
std::string * get_word_hex(int w[4][8], std::string h[4]);
std::string convert_toString(char cbuf[], const size_t len);
void fill_subkey(std::string (*subkeymtrx)[4], std::string w1[], std::string w2[], std::string w3[], std::string w4[]);
void fill_keys(std::string (*allkeys)[4][4], std::string (*key)[4], size_t n);
void get_matrix_bin(std::string m[4][4], int (*mbin)[4][8]);
void get_curkey(std::string (*allkeys)[4][4], std::string (*curkeymtrx)[4], const size_t n);
void xor_matrix(int pmb[4][4][8], int cmb[4][4][8], int (*xm)[4][8]);
void bin_to_hex_matrix(std::string (*mhex)[4], int mbin[4][4][8]);
void sub_bytes(std::string m[4][4], std::string (*sm)[4]);
void shift_rows(std::string m[4][4], std::string (*shm)[4]);
void mix_cols(std::string m[4][4], std::string (*mc)[4]);
int * bin_addition(int bbuf1[8], int bbuf2[8], int bbuf3[8], int &overflow);
std::string row_col_multiplication(int mtrxrow[4], int mtrxcol[4][8]);
int * xor4(int mr[4][8], int x[]);
void matrix_multiplication(int bmtrx1[4][4], int bmtrx2[4][4][8], std::string (*bmtrx3)[4]);
void get_matrix_col_bin(int m[8][4][8], int (*cm)[8], int col);
std::string get_ciphertext(std::string m[4][4]);
std::string aes_128_encrypt(char pthex[], std::string all_keys[11][4][4]);
char dec_to_hex_single(int d);
std::string get_inverse_sbox(int row, int col);
std::string aes_128_decrypt(char ciphhex[], std::string all_keys[11][4][4]);
std::string constant_9(int row, int col);
std::string constant_11(int row, int col);
std::string constant_13(int row, int col);
std::string constant_14(int row, int col);
std::string rev_row_col_multiplication(int mtrxrow[4], std::string mtrxcol[4]);
void rev_matrix_multiplication(int bmtrx1[4], std::string bmtrx2[4][4][8], std::string (*bmtrx3)[4]);
std::string * get_matrix_col(std::string bmtrx2[4][4], std::string colword[4], int col);
std::string get_plaintext(std::string m[4][4]);

// Created for Challenge 8
bool is_block_equal(std::string block1, std::string block2);
std::string * get_blocks(std::string blocks[], std::string cipher_line, int &num);

#endif