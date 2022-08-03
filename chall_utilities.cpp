#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <fstream>
#include <algorithm>


// Every function after this comment is created for crypto1 part 1

int * reset_buf(int buf[], const size_t bs)
{
    for (size_t i = 0; i < bs; i++)
    {
        buf[i] = 0;
    }
    return buf;
}

int * get_bin(int dec, int bits[], const size_t n)
{
    if (dec%2 == 1) {
        bits[n-1] = 1;
        dec = dec - 1;
    }
    int po2 = n-1;
    for (size_t i = 0; i < n-1; i++)
    {
        if (dec-pow(2,po2) >= 0)
        {
            bits[i] = 1;
            dec = dec-pow(2,po2);
        }
        else
        {
            bits[i] = 0;
        }
        po2--;
    }
    return bits;
}

int * hex_to_dec(char hbuf[], int dbuf[], const size_t bs) 
{
    for (size_t i = 0; i < bs; i++)
    {
        if (isdigit(hbuf[i]))
        {
            dbuf[i] = hbuf[i] - 48;
        } 
        else if (isalpha(hbuf[i])) 
        {
            hbuf[i] = tolower(hbuf[i]);
            dbuf[i] = hbuf[i] - 87;
        }
        if (dbuf[i] < 0 && 15 < dbuf[i]) {std::cout << "HEX to DEC ERROR!\n";}
    }

    return dbuf;
}

int * dec_to_bin4(int dbuf[], int bbuf[], const size_t bs)
{
    const size_t n = 4;
    int bits[n];
    int bin_i = 0;
    for (size_t i = 0; i < bs; i++)
    {
        for (size_t b = 0; b < n; b++)
        {
            bits[b] = 0;
        }
        
        get_bin(dbuf[i], bits, n);
        for (size_t j = 0; j < n; j++)
        {
            bbuf[bin_i] = bits[j];
            bin_i++;
        }
    }
    return bbuf;
}

char * bin_to_base64(char b64buf[], int bbuf[], const size_t n, const size_t bs)
{
    const size_t m = 6;
    int bits2[m];
    int sum64 = 0;
    char temp64 = 0;
    int b64_i = 0;
    int bin_i = 0;
    int po2 = 0;

    for (size_t i = 0; i < bs*4; i= i+6)
    {
        sum64 = 0;
        bin_i = i;
        for (size_t k = 0; k < m; k++)
        {
            bits2[k] = bbuf[bin_i + k];
        }
        
        po2 = m-1;
        for (size_t h = 0; h < m; h++)
        {
            if (bits2[h] == 1)
            {
                sum64 = sum64 + pow(2,po2);
            }
            po2--;
        }
        if (sum64 < 26)
        {
            temp64 = sum64 + 65;
        }
        else if (sum64 < 52)
        {
            temp64 = sum64 + 71;
        }
        else if (sum64 < 62)
        {
            temp64 = sum64 - 4;
        }
        else if (sum64 == 62)
        {
            temp64 = 43;
        }
        else if (sum64 == 63)
        {
            temp64 = 47;
        }
        else
        {
            std::cout << "BIN to BASE64 ERROR!\n";
        }
        b64buf[b64_i] = temp64;
        b64_i++;
    }
    return b64buf;
}

int * b_XOR_b(int bbuf1[], int bbuf2[], int bbuf3[], const size_t H)
{
    for (size_t i = 0; i < H*4; i++)
    {
        if (bbuf1[i] == 0 && bbuf2[i] == 0)
        {
            bbuf3[i] = 0;
        }
        else if (bbuf1[i] == 0 && bbuf2[i] == 1)
        {
            bbuf3[i] = 1;
        }
        else if (bbuf1[i] == 1 && bbuf2[i] == 0)
        {
            bbuf3[i] = 1;
        }
        else if (bbuf1[i] == 1 && bbuf2[i] == 1)
        {
            bbuf3[i] = 0;
        }
    }
    return bbuf3;
}

int * bin4_to_dec(int bbuf[], int dbuf[], const size_t bs)
{
    const size_t bb = 4;
    int sum = 0;
    int po2 = bb-1;
    int bin_i = 0;
    int d_i = 0;
    int bits[bb];
    for (size_t i = 0; i < bs; i = i+bb)
    {
        po2 = bb-1;
        sum = 0;
        bin_i = i;
        for (size_t k = 0; k < bb; k++)
        {
            bits[k] = bbuf[bin_i + k];
        }
        for (size_t h = 0; h < bb; h++)
        {
            if (bits[h] == 1)
            {
                sum = sum + pow(2,po2);
            }
            po2--;
        }
        dbuf[d_i] = sum;
        d_i++;
    }
    return dbuf;
}

int * bin8_to_dec(int bbuf[], int dbuf[], const size_t bs)
{
    const size_t bb = 8;
    int sum = 0;
    int po2 = bb-1;
    int bin_i = 0;
    int d_i = 0;
    int bits[bb];
    for (size_t i = 0; i < bs; i = i+bb)
    {
        po2 = bb-1;
        sum = 0;
        bin_i = i;
        for (size_t k = 0; k < bb; k++)
        {
            bits[k] = bbuf[bin_i + k];
        }
        for (size_t h = 0; h < bb; h++)
        {
            if (bits[h] == 1)
            {
                sum = sum + pow(2,po2);
            }
            po2--;
        }
        dbuf[d_i] = sum;
        d_i++;
    }
    return dbuf;
}

char * dec_to_hex(int dbuf[], char hbuf[], const size_t bs)
{
    for (size_t i = 0; i < bs; i++)
    {
        if (dbuf[i] < 10)
        {
            hbuf[i] = dbuf[i] + 48;
        }
        else if (dbuf[i] < 16)
        {
            hbuf[i] = dbuf[i] + 87;
        }
        else
        {
            std::cout << "DEC to HEX ERROR!\n";
        }
    }
    return hbuf;
}

int * dec_to_bin8(int dbuf[], int bbuf[], const size_t bs)
{
    const size_t n = 8;
    int bits[n];
    int bin_i = 0;
    for (size_t i = 0; i < bs; i++)
    {
        for (size_t b = 0; b < n; b++)
        {
            bits[b] = 0;
        }
        
        get_bin(dbuf[i], bits, n);
        for (size_t j = 0; j < n; j++)
        {
            bbuf[bin_i] = bits[j];
            bin_i++;
        }
    }
    return bbuf;
}

int * fill_binbuf(int buf[], int bits[], size_t bs, int bi)
{
    size_t temp = 0;
    int tempbuf[BUFSIZ];
    if((bs+1)%bi != 0)
    {
        temp = bs + (bs+1)%bi;
    }
    for (size_t i = 0; i < temp; i = i + bi)
    {
        for (size_t j = 0; j < bi; j++)
        {
            tempbuf[i+j] = bits[j];
        }
    }
    for (size_t i = 0; i < bs; i++)
    {
        buf[i] = tempbuf[i];
    }
    
    return buf;
}

void printbuf(int buf[], int s)
{
    for (size_t i = 0; i < s; i++)
    {
        std::cout << buf[i];
    }
    std::cout<<'\n';
}

void printbuf_space(int buf[], int s)
{
    for (size_t i = 0; i < s; i++)
    {
        std::cout << buf[i] << " ";
    }
    std::cout<<'\n';
}

void printbuf_space_set(int buf[], int s, int bb)
{
    for (size_t i = 0; i < s; i++)
    {
        std::cout << buf[i];
        if ((i+1)%bb==0) {std::cout<<" ";}
    }
    std::cout<<'\n';
}

char * dec_to_char(char st[], int dbuf[], const size_t bs)
{
    for (size_t i = 0; i < bs; i++)
    {
        st[i] = dbuf[i];
    }
    return st;
}

int * char_to_dec(char st[], int dbuf[], const size_t bs)
{
    for (size_t i = 0; i < bs; i++)
    {
        dbuf[i] = st[i];
    }
    return dbuf;
}

bool char_only(char s[], const size_t len)
{
    bool c_o = true;
    char exclud [] = {0, 7, 8, 9, 10, 13, 17, 27};
    for (size_t i = 0; i < len; i++)
    {
        if((s[i] < 32 || s[i] > 126) && (s[i] != 0 /*&& s[i] != 7 && s[i] != 8*/ && 
            s[i] != 9 && s[i] != 10 && s[i] != 13 /*&& s[i] != 17 && s[i] != 27*/ )) 
        { 
            c_o = false; 
        }
    }
    return c_o;
}

bool best_sentence(char st[], size_t len)
{
    int total_al = 0;
    int total_sp = 0;
    int total_sym = 0;
    int total_digit = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (isalpha(st[i]))
        {
            total_al += 1;
        }
        else if (st[i] == ' ')
        {
            total_sp += 1;
        }
        else if(isdigit(st[i]))
        {
            total_digit += 1;
        }
        else
        {
            total_sym += 1;
        }
    }
    return total_al > total_sp && total_sp > total_sym && total_al > total_digit;
}

void testkeys(int a, int b, const size_t bs, int msgbuf[])
{
    const size_t n = 8;
    int bits[n];
    int testbbuf[BUFSIZ];
    int resultbbuf[BUFSIZ];
    int resultdbuf[BUFSIZ];
    char st[BUFSIZ];
    memset(st, 0, BUFSIZ);
    int best_i = 0;

    for (int i = a; i <= b; i++)
    {
        for (size_t x = 0; x < n; x++)
        {
            bits[x] = 0;
        }
        for (size_t y = 0; y < bs; y++)
        {
            testbbuf[y] = 0;
        }
        get_bin(i, bits, n);
        fill_binbuf(testbbuf, bits, bs, 8);
        b_XOR_b(msgbuf, testbbuf, resultbbuf, bs);
        bin8_to_dec(resultbbuf, resultdbuf, bs);
        dec_to_char(st, resultdbuf, bs/8);
        if(char_only(st, bs/8))
        {
            if(best_sentence(st, bs/8))
            {
                best_i = i;
            }
        }
    }

    get_bin(best_i, bits, n);
    fill_binbuf(testbbuf, bits, bs, 8);
    b_XOR_b(msgbuf, testbbuf, resultbbuf, bs);
    bin8_to_dec(resultbbuf, resultdbuf, bs);
    dec_to_char(st, resultdbuf, bs/8);
    std::cout << st << '\n';
}

char * str_to_char(std::string s, char c[])
{
    for (size_t i = 0; i < s.length(); i++)
    {
        c[i] = s[i];
    }
    return c;
}

void testkeys2(int a, int b, const size_t bs, int msgbuf[], std::ofstream& f)
{
    const size_t n = 8;
    int bits[n];
    int testbbuf[BUFSIZ];
    int resultbbuf[BUFSIZ];
    int resultdbuf[BUFSIZ];
    char st[BUFSIZ];
    memset(st, 0, BUFSIZ);
    int best_i = 0;

    for (int i = a; i <= b; i++)
    {
        for (size_t x = 0; x < n; x++)
        {
            bits[x] = 0;
        }
        for (size_t y = 0; y < bs; y++)
        {
            testbbuf[y] = 0;
        }
        get_bin(i, bits, n);
        fill_binbuf(testbbuf, bits, bs, 8);
        b_XOR_b(msgbuf, testbbuf, resultbbuf, bs);
        bin8_to_dec(resultbbuf, resultdbuf, bs);
        dec_to_char(st, resultdbuf, bs/8);
        if(f.is_open() && char_only(st, bs/8) && best_sentence(st, bs/8))
        {
            f << i << " -> " << st << '\n';
            std::cout << st << '\n';
        }
    }
}

// Every function after this comment is created for crypto1 part 2

int hamming(int bbuf1[], int bbuf2[], const size_t s)
{
    int count = 0;
    for (size_t i = 0; i < s; i++)
    {
        if(bbuf1[i] != bbuf2[i]) {count++;}
    }
    return count;
}

int * base64_to_dec(char b64[], int dbuf[], const size_t s)
{
    int temp = 0;
    for (size_t i = 0; i < s; i++)
    {
        if(b64[i] >= 'A' && b64[i] <= 'Z')
        {
            temp = b64[i] - 'A';
        }
        else if(b64[i] >= 'a' && b64[i] <= 'z')
        {
            temp = b64[i] - 'a' + 26;
        }
        else if(b64[i] >= '0' && b64[i] <= '9')
        {
            temp = b64[i] - '0' + 52;
        }
        else if(b64[i] == '+')
        {
            temp = 62;
        }
        else if(b64[i] == '/')
        {
            temp = 63;
        }
        dbuf[i] = temp;
    }
    return dbuf;
}

int * dec_to_bin6(int dbuf[], int bbuf[], const size_t bs)
{
    const size_t n = 6;
    int bits[n];
    int bin_i = 0;
    for (size_t i = 0; i < bs; i++)
    {
        for (size_t b = 0; b < n; b++)
        {
            bits[b] = 0;
        }
        
        get_bin(dbuf[i], bits, n);
        for (size_t j = 0; j < n; j++)
        {
            bbuf[bin_i] = bits[j];
            bin_i++;
        }
    }
    return bbuf;
}

int * binchar_to_int(char cbuf[], int bbuf[], const size_t s)
{
    for (size_t i = 0; i < s; i++)
    {
        if(cbuf[i] == '0') {bbuf[i] = 0;}
        else if(cbuf[i] == '1') {bbuf[i] = 1;}
        // else {std::cout << "BIN CHAR TO INT ERROR!!!";}
    }
    return bbuf;
}

int min_el_in(double buf[], const size_t s) // return max element index
{
    double min_value = buf[0];
    int min_index = 0;
    for (size_t i = 0; i < s; i++)
    {
        if(buf[i] < min_value)
        {
            min_value = buf[i];
            min_index = i;
        }
    }
    return min_index;
}

double * get_ham_dist(const size_t K, int keysize[], const size_t bi_temp, int tempbinbuf[], double ham[])
{
    double ham_temp = 0;
    int ham_count = 0;
    int hambin1[BUFSIZ];
    int hambin2[BUFSIZ];
    int temp_i = 0;

    for (size_t i = 0; i < K; i++)
    {
        for (size_t a = 0; a < bi_temp-keysize[i]*8*2; a+=keysize[i]*8*2)
        {
            temp_i = 0;
            for (size_t b = a; b < keysize[i]*8; b++)
            {
                hambin1[temp_i] = tempbinbuf[b];
                temp_i++;
            }
            temp_i = 0;
            for (size_t c = a+keysize[i]*8; c < a+keysize[i]*8*2; c++)
            {
                hambin2[temp_i] = tempbinbuf[c];
                temp_i++;
            }
            ham_temp =+ hamming(hambin1, hambin2, keysize[i]*8)/(double)keysize[i];
            ham_count++;

        }
        ham[i] = ham_temp/ham_count;
    }
    return ham;
}

void get_keysiz_matrix(std::ifstream& bin_file2, std::ofstream& bin_keysiz_block, std::string bin_line, int &max_col, int &max_row, char (*block_matrix)[1000][8])
{
    // char block_matrix[1000][1000][8];

    int row = 0;
    int col = 0;
    int block_i = 0;
    // int max_col = keysiz;
    // int max_row = 0;
    if(bin_file2.is_open())
    {
        while(getline(bin_file2, bin_line))
        {
            for (size_t i = 0; i < bin_line.length(); i++)
            {
                if(block_i>=8)
                {
                    block_i=0;
                    col++;
                }
                if (col >= max_col)
                {
                    col = 0;
                    row++;
                }
                block_matrix[row][col][block_i] = bin_line[i];
                block_i++;
            }
        }
    }
    max_row = row+1;

    // Store to ofstream
    for (size_t r = 0; r < max_row; r++)
    {
        for (size_t c = 0; c < max_col; c++)
        {
            for (size_t b = 0; b < 8; b++)
            {
                bin_keysiz_block << block_matrix[r][c][b];
            }
        }
        bin_keysiz_block << '\n';
    }
}

void transpose_matrix(int &max_col, int &max_row, char (*block_transpose_matrix)[100][8], char (*block_matrix)[1000][8], std::ofstream& bin_block)
{
    for (size_t c = 0; c < max_col; c++)
    {
        for (size_t r = 0; r < max_row; r++)
        {
            for (size_t b = 0; b < 8; b++)
            {
                block_transpose_matrix[c][r][b] = block_matrix[r][c][b];
            }
            
        }
        
    }
    std::swap(max_row, max_col);
    
    for (size_t r = 0; r < max_row; r++)
    {
        for (size_t c = 0; c < max_col; c++)
        {
            for (size_t b = 0; b < 8; b++)
            {
                if (isdigit(block_transpose_matrix[r][c][b]))
                {
                    bin_block << block_transpose_matrix[r][c][b];
                }
                
            }
        }
        bin_block << '\n';
    }
}

char * testkeys3(int a, int b, const size_t bs, int msgbuf[], std::ofstream& f, char keys[], size_t& k_i)
{
    const size_t n = 8;
    int bits[n];
    int testbbuf[1000];
    int resultbbuf[1000];
    int resultdbuf[1000];
    char st[1000];
    memset(st, 0, 1000);
    int best_i = 0;
    // int k_i = k_i;

    for (int i = a; i <= b; i++)
    {
        for (size_t x = 0; x < n; x++)
        {
            bits[x] = 0;
        }
        for (size_t y = 0; y < bs; y++)
        {
            testbbuf[y] = 0;
        }
        get_bin(i, bits, n);
        fill_binbuf(testbbuf, bits, bs, 8);
        b_XOR_b(msgbuf, testbbuf, resultbbuf, bs/4);
        bin8_to_dec(resultbbuf, resultdbuf, bs);
        dec_to_char(st, resultdbuf, bs/8);
        if(f.is_open() && char_only(st, bs/8) && best_sentence(st, bs/8))
        {
            f << (char)i << " -> " << st << '\n';
            // std::cout << st << '\n';
            keys[k_i] = i;
            k_i ++;
        }
    }
    return keys;
}

int hex_to_dec_single(char h)
{
    int temp = 0;
    if(isdigit(h))
    {
        temp = h - '0';
    } else if(isalpha(h))
    {
        temp = tolower(h) - 'a' + 10;
        if(temp > 'g') {temp = -1;}
    }
    return temp;
}

char dec_to_hex_single(int d)
{
    char h;
    if (d < 10)
    {
        h = d + 48;
    }
    else if (d < 16)
    {
        h = d + 87;
    }
    else
    {
        std::cout << "DEC to HEX ERROR!\n";
    }
    
    return h;
}

std::string get_sbox_val(int row, int col)
{
    //subsitution lookup table
    std::string sbox[16][16] =
    // 00    01    02    03    04    05    06    07    08    09    0a    0b    0c    0d    0e    0f
    {{"63", "7c", "77", "7b", "f2", "6b", "6f", "c5", "30", "01", "67", "2b", "fe", "d7", "ab", "76"}, // 00
     {"ca", "82", "c9", "7d", "fa", "59", "47", "f0", "ad", "d4", "a2", "af", "9c", "a4", "72", "c0"}, // 10
     {"b7", "fd", "93", "26", "36", "3f", "f7", "cc", "34", "a5", "e5", "f1", "71", "d8", "31", "15"}, // 20
     {"04", "c7", "23", "c3", "18", "96", "05", "9a", "07", "12", "80", "e2", "eb", "27", "b2", "75"}, // 30
     {"09", "83", "2c", "1a", "1b", "6e", "5a", "a0", "52", "3b", "d6", "b3", "29", "e3", "2f", "84"}, // 40
     {"53", "d1", "00", "ed", "20", "fc", "b1", "5b", "6a", "cb", "be", "39", "4a", "4c", "58", "cf"}, // 50
     {"d0", "ef", "aa", "fb", "43", "4d", "33", "85", "45", "f9", "02", "7f", "50", "3c", "9f", "a8"}, // 60
     {"51", "a3", "40", "8f", "92", "9d", "38", "f5", "bc", "b6", "da", "21", "10", "ff", "f3", "d2"}, // 70
     {"cd", "0c", "13", "ec", "5f", "97", "44", "17", "c4", "a7", "7e", "3d", "64", "5d", "19", "73"}, // 80
     {"60", "81", "4f", "dc", "22", "2a", "90", "88", "46", "ee", "b8", "14", "de", "5e", "0b", "db"}, // 90
     {"e0", "32", "3a", "0a", "49", "06", "24", "5c", "c2", "d3", "ac", "62", "91", "95", "e4", "79"}, // a0
     {"e7", "c8", "37", "6d", "8d", "d5", "4e", "a9", "6c", "56", "f4", "ea", "65", "7a", "ae", "08"}, // b0
     {"ba", "78", "25", "2e", "1c", "a6", "b4", "c6", "e8", "dd", "74", "1f", "4b", "bd", "8b", "8a"}, // c0
     {"70", "3e", "b5", "66", "48", "03", "f6", "0e", "61", "35", "57", "b9", "86", "c1", "1d", "9e"}, // d0
     {"e1", "f8", "98", "11", "69", "d9", "8e", "94", "9b", "1e", "87", "e9", "ce", "55", "28", "df"}, // e0
     {"8c", "a1", "89", "0d", "bf", "e6", "42", "68", "41", "99", "2d", "0f", "b0", "54", "bb", "16"}}; // f0

    return sbox[row][col];
}

std::string get_inverse_sbox(int row, int col)
{
    // // GENERATE INVERSE SBOX FROM SBOX
    // // --------------------------------
    // std::string sbox[16][16] =
    // // 00    01    02    03    04    05    06    07    08    09    0a    0b    0c    0d    0e    0f
    // {{"63", "7c", "77", "7b", "f2", "6b", "6f", "c5", "30", "01", "67", "2b", "fe", "d7", "ab", "76"}, // 00
    //  {"ca", "82", "c9", "7d", "fa", "59", "47", "f0", "ad", "d4", "a2", "af", "9c", "a4", "72", "c0"}, // 10
    //  {"b7", "fd", "93", "26", "36", "3f", "f7", "cc", "34", "a5", "e5", "f1", "71", "d8", "31", "15"}, // 20
    //  {"04", "c7", "23", "c3", "18", "96", "05", "9a", "07", "12", "80", "e2", "eb", "27", "b2", "75"}, // 30
    //  {"09", "83", "2c", "1a", "1b", "6e", "5a", "a0", "52", "3b", "d6", "b3", "29", "e3", "2f", "84"}, // 40
    //  {"53", "d1", "00", "ed", "20", "fc", "b1", "5b", "6a", "cb", "be", "39", "4a", "4c", "58", "cf"}, // 50
    //  {"d0", "ef", "aa", "fb", "43", "4d", "33", "85", "45", "f9", "02", "7f", "50", "3c", "9f", "a8"}, // 60
    //  {"51", "a3", "40", "8f", "92", "9d", "38", "f5", "bc", "b6", "da", "21", "10", "ff", "f3", "d2"}, // 70
    //  {"cd", "0c", "13", "ec", "5f", "97", "44", "17", "c4", "a7", "7e", "3d", "64", "5d", "19", "73"}, // 80
    //  {"60", "81", "4f", "dc", "22", "2a", "90", "88", "46", "ee", "b8", "14", "de", "5e", "0b", "db"}, // 90
    //  {"e0", "32", "3a", "0a", "49", "06", "24", "5c", "c2", "d3", "ac", "62", "91", "95", "e4", "79"}, // a0
    //  {"e7", "c8", "37", "6d", "8d", "d5", "4e", "a9", "6c", "56", "f4", "ea", "65", "7a", "ae", "08"}, // b0
    //  {"ba", "78", "25", "2e", "1c", "a6", "b4", "c6", "e8", "dd", "74", "1f", "4b", "bd", "8b", "8a"}, // c0
    //  {"70", "3e", "b5", "66", "48", "03", "f6", "0e", "61", "35", "57", "b9", "86", "c1", "1d", "9e"}, // d0
    //  {"e1", "f8", "98", "11", "69", "d9", "8e", "94", "9b", "1e", "87", "e9", "ce", "55", "28", "df"}, // e0
    //  {"8c", "a1", "89", "0d", "bf", "e6", "42", "68", "41", "99", "2d", "0f", "b0", "54", "bb", "16"}}; // f0

    // std::string inv_sbox[16][16] = {};
    // int row = 0;
    // int col = 0;
    // std::string temp = "";
    // for (size_t i = 0; i < 16; i++)
    // {
    //     for (size_t j = 0; j < 16; j++)
    //     {
    //         row = hex_to_dec_single(sbox[i][j][0]);
    //         col = hex_to_dec_single(sbox[i][j][1]);
    //         temp = "";
    //         temp = temp + dec_to_hex_single(i);
    //         temp = temp + dec_to_hex_single(j);
    //         inv_sbox[row][col] = temp;
    //     }
    //     std::cout << '\n';
    // }
    // for (size_t i = 0; i < 16; i++)
    // {
    //     std::cout << "{";
    //     for (size_t j = 0; j < 16; j++)
    //     {
    //         std::cout << "\"" << inv_sbox[i][j] << "\", ";
    //     }
    //     std::cout << "}," << '\n';
    // }

    std::string inv_sbox[16][16] =
    // 00    01    02    03    04    05    06    07    08    09    0a    0b    0c    0d    0e    0f
    {{"52", "09", "6a", "d5", "30", "36", "a5", "38", "bf", "40", "a3", "9e", "81", "f3", "d7", "fb"}, // 00
     {"7c", "e3", "39", "82", "9b", "2f", "ff", "87", "34", "8e", "43", "44", "c4", "de", "e9", "cb"}, // 10
     {"54", "7b", "94", "32", "a6", "c2", "23", "3d", "ee", "4c", "95", "0b", "42", "fa", "c3", "4e"}, // 20
     {"08", "2e", "a1", "66", "28", "d9", "24", "b2", "76", "5b", "a2", "49", "6d", "8b", "d1", "25"}, // 30
     {"72", "f8", "f6", "64", "86", "68", "98", "16", "d4", "a4", "5c", "cc", "5d", "65", "b6", "92"}, // 40
     {"6c", "70", "48", "50", "fd", "ed", "b9", "da", "5e", "15", "46", "57", "a7", "8d", "9d", "84"}, // 50
     {"90", "d8", "ab", "00", "8c", "bc", "d3", "0a", "f7", "e4", "58", "05", "b8", "b3", "45", "06"}, // 60
     {"d0", "2c", "1e", "8f", "ca", "3f", "0f", "02", "c1", "af", "bd", "03", "01", "13", "8a", "6b"}, // 70
     {"3a", "91", "11", "41", "4f", "67", "dc", "ea", "97", "f2", "cf", "ce", "f0", "b4", "e6", "73"}, // 80
     {"96", "ac", "74", "22", "e7", "ad", "35", "85", "e2", "f9", "37", "e8", "1c", "75", "df", "6e"}, // 90
     {"47", "f1", "1a", "71", "1d", "29", "c5", "89", "6f", "b7", "62", "0e", "aa", "18", "be", "1b"}, // a0
     {"fc", "56", "3e", "4b", "c6", "d2", "79", "20", "9a", "db", "c0", "fe", "78", "cd", "5a", "f4"}, // b0
     {"1f", "dd", "a8", "33", "88", "07", "c7", "31", "b1", "12", "10", "59", "27", "80", "ec", "5f"}, // c0
     {"60", "51", "7f", "a9", "19", "b5", "4a", "0d", "2d", "e5", "7a", "9f", "93", "c9", "9c", "ef"}, // d0
     {"a0", "e0", "3b", "4d", "ae", "2a", "f5", "b0", "c8", "eb", "bb", "3c", "83", "53", "99", "61"}, // e0
     {"17", "2b", "04", "7e", "ba", "77", "d6", "26", "e1", "69", "14", "63", "55", "21", "0c", "7d"}};// f0

    return inv_sbox[row][col];
}

std::string constant_9(int row, int col)
{
    std::string const_9[16][16] =
    // 00    01    02    03    04    05    06    07    08    09    0a    0b    0c    0d    0e    0f
    {{"00", "09", "12", "1b", "24", "2d", "36", "3f", "48", "41", "5a", "53", "6c", "65", "7e", "77"}, // 00
     {"90", "99", "82", "8b", "b4", "bd", "a6", "af", "d8", "d1", "ca", "c3", "fc", "f5", "ee", "e7"}, // 10
     {"3b", "32", "29", "20", "1f", "16", "0d", "04", "73", "7a", "61", "68", "57", "5e", "45", "4c"}, // 20
     {"ab", "a2", "b9", "b0", "8f", "86", "9d", "94", "e3", "ea", "f1", "f8", "c7", "ce", "d5", "dc"}, // 30
     {"76", "7f", "64", "6d", "52", "5b", "40", "49", "3e", "37", "2c", "25", "1a", "13", "08", "01"}, // 40
     {"e6", "ef", "f4", "fd", "c2", "cb", "d0", "d9", "ae", "a7", "bc", "b5", "8a", "83", "98", "91"}, // 50
     {"4d", "44", "5f", "56", "69", "60", "7b", "72", "05", "0c", "17", "1e", "21", "28", "33", "3a"}, // 60
     {"dd", "d4", "cf", "c6", "f9", "f0", "eb", "e2", "95", "9c", "87", "8e", "b1", "b8", "a3", "aa"}, // 70
     {"ec", "e5", "fe", "f7", "c8", "c1", "da", "d3", "a4", "ad", "b6", "bf", "80", "89", "92", "9b"}, // 80
     {"7c", "75", "6e", "67", "58", "51", "4a", "43", "34", "3d", "26", "2f", "10", "19", "02", "0b"}, // 90
     {"d7", "de", "c5", "cc", "f3", "fa", "e1", "e8", "9f", "96", "8d", "84", "bb", "b2", "a9", "a0"}, // a0
     {"47", "4e", "55", "5c", "63", "6a", "71", "78", "0f", "06", "1d", "14", "2b", "22", "39", "30"}, // b0
     {"9a", "93", "88", "81", "be", "b7", "ac", "a5", "d2", "db", "c0", "c9", "f6", "ff", "e4", "ed"}, // c0
     {"0a", "03", "18", "11", "2e", "27", "3c", "35", "42", "4b", "50", "59", "66", "6f", "74", "7d"}, // d0
     {"a1", "a8", "b3", "ba", "85", "8c", "97", "9e", "e9", "e0", "fb", "f2", "cd", "c4", "df", "d6"}, // e0
     {"31", "38", "23", "2a", "15", "1c", "07", "0e", "79", "70", "6b", "62", "5d", "54", "4f", "46"}};// f0

    return const_9[row][col];
}

std::string constant_11(int row, int col)
{
    std::string const_11[16][16] =
    // 00    01    02    03    04    05    06    07    08    09    0a    0b    0c    0d    0e    0f
    {{"00", "0b", "16", "1d", "2c", "27", "3a", "31", "58", "53", "4e", "45", "74", "7f", "62", "69"}, // 00
     {"b0", "bb", "a6", "ad", "9c", "97", "8a", "81", "e8", "e3", "fe", "f5", "c4", "cf", "d2", "d9"}, // 10
     {"7b", "70", "6d", "66", "57", "5c", "41", "4a", "23", "28", "35", "3e", "0f", "04", "19", "12"}, // 20
     {"cb", "c0", "dd", "d6", "e7", "ec", "f1", "fa", "93", "98", "85", "8e", "bf", "b4", "a9", "a2"}, // 30
     {"f6", "fd", "e0", "eb", "da", "d1", "cc", "c7", "ae", "a5", "b8", "b3", "82", "89", "94", "9f"}, // 40
     {"46", "4d", "50", "5b", "6a", "61", "7c", "77", "1e", "15", "08", "03", "32", "39", "24", "2f"}, // 50
     {"8d", "86", "9b", "90", "a1", "aa", "b7", "bc", "d5", "de", "c3", "c8", "f9", "f2", "ef", "e4"}, // 60
     {"3d", "36", "2b", "20", "11", "1a", "07", "0c", "65", "6e", "73", "78", "49", "42", "5f", "54"}, // 70
     {"f7", "fc", "e1", "ea", "db", "d0", "cd", "c6", "af", "a4", "b9", "b2", "83", "88", "95", "9e"}, // 80
     {"47", "4c", "51", "5a", "6b", "60", "7d", "76", "1f", "14", "09", "02", "33", "38", "25", "2e"}, // 90
     {"8c", "87", "9a", "91", "a0", "ab", "b6", "bd", "d4", "df", "c2", "c9", "f8", "f3", "ee", "e5"}, // a0
     {"3c", "37", "2a", "21", "10", "1b", "06", "0d", "64", "6f", "72", "79", "48", "43", "5e", "55"}, // b0
     {"01", "0a", "17", "1c", "2d", "26", "3b", "30", "59", "52", "4f", "44", "75", "7e", "63", "68"}, // c0
     {"b1", "ba", "a7", "ac", "9d", "96", "8b", "80", "e9", "e2", "ff", "f4", "c5", "ce", "d3", "d8"}, // d0
     {"7a", "71", "6c", "67", "56", "5d", "40", "4b", "22", "29", "34", "3f", "0e", "05", "18", "13"}, // e0
     {"ca", "c1", "dc", "d7", "e6", "ed", "f0", "fb", "92", "99", "84", "8f", "be", "b5", "a8", "a3"}};// f0

    return const_11[row][col];
}

std::string constant_13(int row, int col)
{
    std::string const_13[16][16] =
    // 00    01    02    03    04    05    06    07    08    09    0a    0b    0c    0d    0e    0f
    {{"00", "0d", "1a", "17", "34", "39", "2e", "23", "68", "65", "72", "7f", "5c", "51", "46", "4b"}, // 00
     {"d0", "dd", "ca", "c7", "e4", "e9", "fe", "f3", "b8", "b5", "a2", "af", "8c", "81", "96", "9b"}, // 10
     {"bb", "b6", "a1", "ac", "8f", "82", "95", "98", "d3", "de", "c9", "c4", "e7", "ea", "fd", "f0"}, // 20
     {"6b", "66", "71", "7c", "5f", "52", "45", "48", "03", "0e", "19", "14", "37", "3a", "2d", "20"}, // 30
     {"6d", "60", "77", "7a", "59", "54", "43", "4e", "05", "08", "1f", "12", "31", "3c", "2b", "26"}, // 40
     {"bd", "b0", "a7", "aa", "89", "84", "93", "9e", "d5", "d8", "cf", "c2", "e1", "ec", "fb", "f6"}, // 50
     {"d6", "db", "cc", "c1", "e2", "ef", "f8", "f5", "be", "b3", "a4", "a9", "8a", "87", "90", "9d"}, // 60
     {"06", "0b", "1c", "11", "32", "3f", "28", "25", "6e", "63", "74", "79", "5a", "57", "40", "4d"}, // 70
     {"da", "d7", "c0", "cd", "ee", "e3", "f4", "f9", "b2", "bf", "a8", "a5", "86", "8b", "9c", "91"}, // 80
     {"0a", "07", "10", "1d", "3e", "33", "24", "29", "62", "6f", "78", "75", "56", "5b", "4c", "41"}, // 90
     {"61", "6c", "7b", "76", "55", "58", "4f", "42", "09", "04", "13", "1e", "3d", "30", "27", "2a"}, // a0
     {"b1", "bc", "ab", "a6", "85", "88", "9f", "92", "d9", "d4", "c3", "ce", "ed", "e0", "f7", "fa"}, // b0
     {"b7", "ba", "ad", "a0", "83", "8e", "99", "94", "df", "d2", "c5", "c8", "eb", "e6", "f1", "fc"}, // c0
     {"67", "6a", "7d", "70", "53", "5e", "49", "44", "0f", "02", "15", "18", "3b", "36", "21", "2c"}, // d0
     {"0c", "01", "16", "1b", "38", "35", "22", "2f", "64", "69", "7e", "73", "50", "5d", "4a", "47"}, // e0
     {"dc", "d1", "c6", "cb", "e8", "e5", "f2", "ff", "b4", "b9", "ae", "a3", "80", "8d", "9a", "97"}};// f0

    return const_13[row][col];
}

std::string constant_14(int row, int col)
{
    std::string const_14[16][16] =
    // 00    01    02    03    04    05    06    07    08    09    0a    0b    0c    0d    0e    0f
    {{"00", "0e", "1c", "12", "38", "36", "24", "2a", "70", "7e", "6c", "62", "48", "46", "54", "5a"}, // 00
     {"e0", "ee", "fc", "f2", "d8", "d6", "c4", "ca", "90", "9e", "8c", "82", "a8", "a6", "b4", "ba"}, // 10
     {"db", "d5", "c7", "c9", "e3", "ed", "ff", "f1", "ab", "a5", "b7", "b9", "93", "9d", "8f", "81"}, // 20
     {"3b", "35", "27", "29", "03", "0d", "1f", "11", "4b", "45", "57", "59", "73", "7d", "6f", "61"}, // 30
     {"ad", "a3", "b1", "bf", "95", "9b", "89", "87", "dd", "d3", "c1", "cf", "e5", "eb", "f9", "f7"}, // 40
     {"4d", "43", "51", "5f", "75", "7b", "69", "67", "3d", "33", "21", "2f", "05", "0b", "19", "17"}, // 50
     {"76", "78", "6a", "64", "4e", "40", "52", "5c", "06", "08", "1a", "14", "3e", "30", "22", "2c"}, // 60
     {"96", "98", "8a", "84", "ae", "a0", "b2", "bc", "e6", "e8", "fa", "f4", "de", "d0", "c2", "cc"}, // 70
     {"41", "4f", "5d", "53", "79", "77", "65", "6b", "31", "3f", "2d", "23", "09", "07", "15", "1b"}, // 80
     {"a1", "af", "bd", "b3", "99", "97", "85", "8b", "d1", "df", "cd", "c3", "e9", "e7", "f5", "fb"}, // 90
     {"9a", "94", "86", "88", "a2", "ac", "be", "b0", "ea", "e4", "f6", "f8", "d2", "dc", "ce", "c0"}, // a0
     {"7a", "74", "66", "68", "42", "4c", "5e", "50", "0a", "04", "16", "18", "32", "3c", "2e", "20"}, // b0
     {"ec", "e2", "f0", "fe", "d4", "da", "c8", "c6", "9c", "92", "80", "8e", "a4", "aa", "b8", "b6"}, // c0
     {"0c", "02", "10", "1e", "34", "3a", "28", "26", "7c", "72", "60", "6e", "44", "4a", "58", "56"}, // d0
     {"37", "39", "2b", "25", "0f", "01", "13", "1d", "47", "49", "5b", "55", "7f", "71", "63", "6d"}, // e0
     {"d7", "d9", "cb", "c5", "ef", "e1", "f3", "fd", "a7", "a9", "bb", "b5", "9f", "91", "83", "8d"}};// f0

    return const_14[row][col];
}

std::string * get_round_constant(int r, std::string rc[])
{
    std::string round_constant[10][4] =
    {{"01", "00", "00", "00"},
     {"02", "00", "00", "00"},
     {"04", "00", "00", "00"},
     {"08", "00", "00", "00"},
     {"10", "00", "00", "00"},
     {"20", "00", "00", "00"},
     {"40", "00", "00", "00"},
     {"80", "00", "00", "00"},
     {"1b", "00", "00", "00"},
     {"36", "00", "00", "00"}};

     for (size_t i = 0; i < 4; i++)
     {
         rc[i] = round_constant[r-1][i];
     }
     return rc;
}

void print_matrix(std::string (*mtrx)[4]) 
{
    for (size_t r = 0; r < 4; r++)
    {
        for (size_t c = 0; c < 4; c++)
        {
            std::cout << mtrx[r][c] << " ";
        }
        std::cout << '\n';
    }
}

void get_curkey(std::string (*allkeys)[4][4], std::string (*curkeymtrx)[4], const size_t n)
{
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            curkeymtrx[i][j] = allkeys[n][i][j];
        }
    }
}

void print_matrix3(int mtrx[4][4][8]) 
{
    for (size_t r = 0; r < 4; r++)
    {
        for (size_t c = 0; c < 4; c++)
        {
            for (size_t i = 0; i < 8; i++)
            {
               std::cout << mtrx[r][c][i];
            }
            std::cout << " ";
        }
        std::cout << '\n';
    }
}

void create_4x4(char hbuf[], std::string (*mtrx)[4])
{
    // 4x4 = state array
    // 16 byte matrix
    // each cell represents 1 byte
    // 4 bytes = 1 word
    // each state array is rep by 4 words
    // b0  b4  b8  b12
    // b1  b5  b9  b13
    // b2  b6  b10 b14
    // b3  b7  b11 b15
    std::string temp = "";
    int in = 0;

    for (size_t r = 0; r < 4; r++)
    {
        for (size_t c = 0; c < 4; c++)
        {
            temp = "";
            temp.push_back(hbuf[in]);
            temp.push_back(hbuf[in+1]);
            mtrx[c][r] = temp;
            in += 2;
        }
    }
}

std::string * rot_word(std::string w[4], std::string rw[4], int shift)
{
    int t = 0;
    for (size_t i = shift; i < 4; i++)
    {
        rw[t] = w[i];
        t++;
    }
    for (size_t i = 0; i < shift; i++)
    {
        rw[t] = w[i];
        t++;
    }
    return rw;
}

void fill_keys(std::string (*allkeys)[4][4], std::string (*key)[4], size_t n)
{
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            allkeys[n][i][j] = key[i][j];
        }
    }
}

void print_word(std::string w[4])
{
    for (size_t i = 0; i < 4; i++)
    {
        std::cout << w[i] << " ";
    }
    std::cout << '\n';
}

std::string * sub_word(std::string w[4], std::string sw[4])
{
    int first = 0;
    int second = 0;
    std::string temp = "";
    for (size_t i = 0; i < 4; i++)
    {
        temp = w[i];
        first = hex_to_dec_single(temp[0]);
        second = hex_to_dec_single(temp[1]);
        sw[i] = get_sbox_val(first, second);
    }
    return sw;
}

std::string * rev_sub_word(std::string w[4], std::string sw[4])
{
    int first = 0;
    int second = 0;
    std::string temp = "";
    for (size_t i = 0; i < 4; i++)
    {
        temp = w[i];
        first = hex_to_dec_single(temp[0]);
        second = hex_to_dec_single(temp[1]);
        sw[i] = get_inverse_sbox(first, second);
    }
    return sw;
}

void sub_bytes(std::string m[4][4], std::string (*sm)[4])
{
    for (size_t i = 0; i < 4; i++)
    {
        sub_word(m[i], sm[i]);
    }
    
}

void rev_sub_bytes(std::string m[4][4], std::string (*sm)[4])
{
    for (size_t i = 0; i < 4; i++)
    {
        rev_sub_word(m[i], sm[i]);
    }
    
}

void get_word_bin(std::string w[4], int (*wordbin)[8])
{
    std::string wbuf = "";
    int decbuf[2];
    int binbuf[2*4];

    for (size_t i = 0; i < 4; i++)
    {
        wbuf = w[i];
        decbuf[0] = hex_to_dec_single(wbuf[0]);
        decbuf[1] = hex_to_dec_single(wbuf[1]);
        dec_to_bin4(decbuf, binbuf, 2);
        for (size_t j = 0; j < 8; j++)
        {
            wordbin[i][j] = binbuf[j];
        }
    }
}

void get_matrix_bin(std::string m[4][4], int (*mbin)[4][8])
{
    std::string tempw[4];
    int tempb[4][8];
    for (size_t r = 0; r < 4; r++)
    {
        for (size_t c = 0; c < 4; c++)
        {
            tempw[c] = m[r][c];
        }
        get_word_bin(tempw, tempb);
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 8; j++)
            {
                mbin[r][i][j] = tempb[i][j];
            }
        }
    }
}

std::string convert_toString(char cbuf[], const size_t len)
{
    std::string temp = "";
    for (size_t i = 0; i < len; i++)
    {
        temp = temp + cbuf[i];
    }
    return temp;
}

std::string * get_word_hex(int w[4][8], std::string h[4])
{
    char cbuf[2];
    int dbuf[2];
    for (size_t i = 0; i < 4; i++)
    {
        bin4_to_dec(w[i], dbuf, 8);
        dec_to_hex(dbuf, cbuf, 2);
        h[i] = convert_toString(cbuf, 2);
    }
    return h;
}

void bin_to_hex_matrix(std::string (*mhex)[4], int mbin[4][4][8])
{
    for (size_t i = 0; i < 4; i++)
    {
        get_word_hex(mbin[i], mhex[i]);
    }
}

void xor_word(int w1[4][8], int w2[4][8], int (*w3)[8])
{
    for (size_t i = 0; i < 4; i++)
    {
        b_XOR_b(w1[i], w2[i], w3[i],8);
    }
}

void xor_matrix(int pmb[4][4][8], int cmb[4][4][8], int (*xm)[4][8])
{
    for (size_t i = 0; i < 4; i++)
    {
        xor_word(pmb[i], cmb[i], xm[i]);
    }
}

void print_wordint(int (*w)[8])
{
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            std::cout << w[i][j];
        }
        std::cout << " ";
    }
}

void g(std::string w[], int (*xorword)[8], int round)
{
    // rotword = {b1, b2, b3, b0}
    // subword = sub_byte rotword with aes sbox
    // subword xor round constant

    std::string rotword[4];
    std::string subword[4];
    rot_word(w, rotword, 1);
    sub_word(rotword, subword);
    
    std::string round_const[4];
    get_round_constant(round, round_const);

    int wordbin[4][8];
    int rcbin[4][8];
    get_word_bin(subword, wordbin);
    get_word_bin(round_const, rcbin);
    xor_word(wordbin, rcbin, xorword);
}

void fill_subkey(std::string (*subkeymtrx)[4], std::string w1[], std::string w2[], std::string w3[], std::string w4[])
{
    for (size_t i = 0; i < 4; i++)
    {
        subkeymtrx[i][0] = w1[i];
    }
    for (size_t i = 0; i < 4; i++)
    {
        subkeymtrx[i][1] = w2[i];
    }
    for (size_t i = 0; i < 4; i++)
    {
        subkeymtrx[i][2] = w3[i];
    }
    for (size_t i = 0; i < 4; i++)
    {
        subkeymtrx[i][3] = w4[i];
    }
}


void key_expansion(std::string (*keymtrx)[4], std::string (*subkeymtrx)[4], int round)
{
    // n+1 keys
    // n = # of rounds
    // 4x4 matrix
    
    //key -> 128 bits -> hex (0x00 <-- 1 byte)
    // b1 b2 b3 b4 b5 b6 b7 b8 b9 b10 b11 b12 b13 b14 b15 b16

    // 4x4
    // b0  b1  b2  b3   <- w0
    // b4  b5  b6  b7   <- w1
    // b8  b9  b10 b11  <- w2
    // b12 b13 b14 b15  <- w3

    // w0 w1 w2  w3    <--- words.... 1word = 4bytes = 32bits
    // need w0 to w43....we have w0 to w3
    // every 4 words will be used to generate the next 4 words
        // every 4 words = subkey ... subkey is used for each round
    
    // how to expand
    // g(w3) xor w0 = w4
    // w4 xor w1 = w5
    // w5 xor w2 = w6
    // w6 xor w3 = w7
    std::string w0[4] = {keymtrx[0][0], keymtrx[1][0], keymtrx[2][0], keymtrx[3][0]};
    std::string w1[4] = {keymtrx[0][1], keymtrx[1][1], keymtrx[2][1], keymtrx[3][1]};
    std::string w2[4] = {keymtrx[0][2], keymtrx[1][2], keymtrx[2][2], keymtrx[3][2]};
    std::string w3[4] = {keymtrx[0][3], keymtrx[1][3], keymtrx[2][3], keymtrx[3][3]};

    std::string w4[4];
    std::string w5[4];
    std::string w6[4];
    std::string w7[4];

    int g_word[4][8];
    int w_word[4][8];
    int next_word1[4][8];
    int next_word2[4][8];

    // w4 = w0 xor g(w3)
    g(w3, g_word, round);
    get_word_bin(w0, w_word);
    xor_word(w_word, g_word, next_word1); // next_word1 = w4 bin
    get_word_hex(next_word1, w4);

    // w5 = w4 xor w1
    get_word_bin(w1, w_word);
    xor_word(w_word, next_word1, next_word2); // next_word2 = w5 bin
    get_word_hex(next_word2, w5);

    // w6 = w5 xor w2
    get_word_bin(w2, w_word);
    xor_word(w_word, next_word2, next_word1); // next_word1 = w6 bin
    get_word_hex(next_word1, w6);

    // w7 = w6 xor w3
    get_word_bin(w3, w_word);
    xor_word(w_word, next_word1, next_word2); // next_word2 = w7 bin
    get_word_hex(next_word2, w7);

    fill_subkey(subkeymtrx, w4, w5, w6, w7);
    
}

void shift_rows(std::string m[4][4], std::string (*shm)[4])
{
    // left shift
    std::string temp = "";
    for (size_t i = 0; i < 4; i++)
    {
        rot_word(m[i], shm[i], i);
    }
}

void rev_shift_rows(std::string m[4][4], std::string (*shm)[4])
{
    // right shift
    std::string temp = "";
    int k = 1;
    rot_word(m[0], shm[0], 0);
    for (int i = 3; i > 0; i--)
    {
        rot_word(m[k], shm[k], i);
        k++;
    }
}

int * bin_addition(int bbuf1[8], int bbuf2[8], int bbuf3[8], int &overflow)
{
    overflow = 0;
    for (int i = 7; i >= 0; i--)
    {
        if (bbuf1[i] == 0 && bbuf2[i] == 0)
        {
            bbuf3[i] = 0;
            if (overflow == 1) 
            { 
                bbuf3[i] = 1;
                overflow = 0;
            }
        } 
        else if ((bbuf1[i] == 0 && bbuf2[i] == 1) || (bbuf1[i] == 1 && bbuf2[i] == 0))
        {
            bbuf3[i] = 1;
            if (overflow == 1) 
            { 
                bbuf3[i] = 0;
                overflow = 1;
            }
        } 
        else if (bbuf1[i] == 1 && bbuf2[i] == 1)
        {
            bbuf3[i] = 0;
            if (overflow == 1) 
            { 
                bbuf3[i] = 1;
            }
            overflow = 1;
        }
    }
    return bbuf3;
}

int * xor4(int mr[4][8], int x[])
{
    for (size_t i = 0; i < 8; i++)
    {
        x[i] = 0;
    }
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            if (mr[i][j] == 1)
            {
                x[j]++;
            }
        }
    }
    for (size_t i = 0; i < 8; i++)
    {
        if (x[i] % 2 == 0) { x[i] = 0; }
        else {x[i] = 1; }
    }
    return x;
}

std::string row_col_multiplication(int mtrxrow[4], int mtrxcol[4][8])
{
    int overflow = 0;
    int temp[8];
    int mul_result[4][8];
    int x8[] = {0, 0, 0, 1, 1, 0, 1, 1};
    for (size_t i = 0; i < 4; i++)
    {
        if (mtrxrow[i] == 1)
        {
            for (size_t j = 0; j < 8; j++)
            {
                mul_result[i][j] = mtrxcol[i][j];
            }
        } 
        else if (mtrxrow[i] == 2)
        {
            bin_addition(mtrxcol[i], mtrxcol[i], temp, overflow);
            if (overflow == 1)
            {
                b_XOR_b(temp, x8, temp, 8/4);
            } 
            for (size_t j = 0; j < 8; j++)
            {
                mul_result[i][j] = temp[j];
            }
        } 
        else if (mtrxrow[i] == 3)
        {
            bin_addition(mtrxcol[i], mtrxcol[i], temp, overflow);
            if (overflow == 1)
            {
                b_XOR_b(temp, x8, temp, 8/4);
            } 
            b_XOR_b(temp, mtrxcol[i], temp, 8/4);

            for (size_t j = 0; j < 8; j++)
            {
                mul_result[i][j] = temp[j];
            }
        }
    }

    int x[8];
    xor4(mul_result, x);
    char hbuf[2];
    int dbuf[2];
    bin4_to_dec(x, dbuf, 8);
    dec_to_hex(dbuf, hbuf, 2);
    std::string result = "";
    for (size_t i = 0; i < 2; i++)
    {
        result = result + hbuf[i];
    }
    
    return result;
}

std::string rev_row_col_multiplication(int mtrxrow[4], std::string mtrxcol[4])
{
    std::string mul_result [4];
    int mul_re[4][8];
    int x8[] = {0, 0, 0, 1, 1, 0, 1, 1};
    int row, col = 0;

    for (size_t i = 0; i < 4; i++)
    {
        row = hex_to_dec_single(mtrxcol[i][0]);
        col = hex_to_dec_single(mtrxcol[i][1]);
        if (mtrxrow[i] == 9)
        {
            mul_result[i] = constant_9(row, col);
        }
        else if (mtrxrow[i] == 11)
        {
            mul_result[i] = constant_11(row, col);
        }
        else if (mtrxrow[i] == 13)
        {
            mul_result[i] = constant_13(row, col);
        }
        else if (mtrxrow[i] == 14)
        {
            mul_result[i] = constant_14(row, col);
        }
    }

    get_word_bin(mul_result, mul_re);
    int x[8];
    xor4(mul_re, x);
    char hbuf[2];
    int dbuf[2];
    bin4_to_dec(x, dbuf, 8);
    dec_to_hex(dbuf, hbuf, 2);
    std::string result = "";
    for (size_t i = 0; i < 2; i++)
    {
        result = result + hbuf[i];
    }
    return result;
}

void get_matrix_col_bin(int m[8][4][8], int (*cm)[8], int col)
{
    // int temp[4][8];
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            cm[i][j] = m[i][col][j];
        }
    }
}

std::string * get_matrix_col(std::string bmtrx2[4][4], std::string colword[4], int col)
{
    for (size_t i = 0; i < 4; i++)
    {
        colword[i] = bmtrx2[i][col];
    }
    return colword;
}

void matrix_multiplication(int bmtrx1[4][4], int bmtrx2[4][4][8], std::string (*bmtrx3)[4])
{
    // matrix multiplication -> row x col
    int tcol[4][8];
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            // reset tcol
            for (size_t n = 0; n < 4; n++)
            {
                for (size_t m = 0; m < 8; m++)
                {
                    tcol[n][m] = 0;
                }
            }
            get_matrix_col_bin(bmtrx2, tcol, j);
            bmtrx3[i][j] = row_col_multiplication(bmtrx1[i], tcol);
        }
    }
}

void rev_matrix_multiplication(int bmtrx1[4][4], std::string bmtrx2[4][4], std::string (*bmtrx3)[4])
{
    // matrix multiplication -> row x col
    std::string tcol[4];
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            get_matrix_col(bmtrx2, tcol, j);
            bmtrx3[i][j] = rev_row_col_multiplication(bmtrx1[i], tcol);
        }
    }
}

void mix_cols(std::string m[4][4], std::string (*mc)[4])
{
    int constant_matrix[4][4] =
    {{2, 3, 1, 1},
     {1, 2, 3, 1},
     {1, 1, 2, 3},
     {3, 1, 1, 2}};

    int bmtrx[4][4][8];
    get_matrix_bin(m, bmtrx);
    matrix_multiplication(constant_matrix, bmtrx, mc);
}

void rev_mix_col(std::string m[4][4], std::string (*mc)[4])
{
    int inverse_constant[4][4] =
    {{14, 11, 13, 9},
     {9, 14, 11, 13},
     {13, 9, 14, 11},
     {11, 13, 9, 14}};

    rev_matrix_multiplication(inverse_constant, m, mc);
}

std::string get_ciphertext(std::string m[4][4])
{
    std::string cipher = "";
    for (size_t r = 0; r < 4; r++)
    {
        for (size_t c = 0; c < 4; c++)
        {
            cipher = cipher + m[c][r];
        }
    }
    return cipher;
}

std::string hex_to_str(std::string s)
{
    int x, y, z = 0;
    char t;

    t = s[0];
    if (isdigit(t)) { x = t - 48;}
    else if(tolower(t) > 96 && tolower(t < 123)) {x = tolower(t) - 87;}

    t = s[1];
    if (isdigit(t)) { y = t - 48;}
    else if(tolower(t) > 96 && tolower(t < 123)) {y = tolower(t) - 87;}
    z = x*16 + y;
    t = z;

    std::string temp = "";
    temp = temp + t;
    return temp;
}

std::string get_plaintext(std::string m[4][4])
{
    std::string cipher = "";
    char cbuf[3];
    int dbuf[2];
    int hbuf[4];
    int bbuf[2*8];
    for (size_t r = 0; r < 4; r++)
    {
        for (size_t c = 0; c < 4; c++)
        {
            cipher = cipher + hex_to_str(m[c][r]);
        }
    }
    return cipher;
}

std::string aes_128_encrypt(char pthex[], std::string all_keys[11][4][4])
{
    std::string pt_matrix[4][4];
    int pt_matrix_bin[4][4][8];
    std::string curkey_matrix[4][4];
    int curkey_matrix_bin[4][4][8];
    std::string x_matrix[4][4];
    int xor_matrix_bin[4][4][8];
    std::string sub_matrix[4][4];
    std::string shift_matrix[4][4];
    std::string mix_matrix[4][4];

    create_4x4(pthex, pt_matrix);
    get_matrix_bin(pt_matrix, pt_matrix_bin);
    get_curkey(all_keys, curkey_matrix, 0);
    get_matrix_bin(curkey_matrix, curkey_matrix_bin);
    xor_matrix(pt_matrix_bin, curkey_matrix_bin, xor_matrix_bin);
    bin_to_hex_matrix(x_matrix, xor_matrix_bin);

    for (size_t i = 1; i < 11 ; i++)
    {
        sub_bytes(x_matrix, sub_matrix);
        shift_rows(sub_matrix, shift_matrix);

        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                for (size_t k = 0; k < 8; k++)
                {
                    pt_matrix_bin[i][j][k] = 0;
                    curkey_matrix_bin[i][j][k] = 0;
                    xor_matrix_bin[i][j][k] = 0;
                }
            }
        }

        if (i != 10)
        {
            mix_cols(shift_matrix, mix_matrix);
            get_matrix_bin(mix_matrix, pt_matrix_bin);
        }
        else
        {
            get_matrix_bin(shift_matrix, pt_matrix_bin);
        }
        
        get_curkey(all_keys, curkey_matrix, i);
        get_matrix_bin(curkey_matrix, curkey_matrix_bin);
        xor_matrix(pt_matrix_bin, curkey_matrix_bin, xor_matrix_bin);
        bin_to_hex_matrix(x_matrix, xor_matrix_bin);
    }
    
    std::string ciphertext = get_ciphertext(x_matrix);
    return ciphertext;
}

std::string aes_128_decrypt(char ciphhex[], std::string all_keys[11][4][4])
{
    std::string ciph_matrix[4][4];
    int ciph_matrix_bin[4][4][8];
    std::string curkey_matrix[4][4];
    int curkey_matrix_bin[4][4][8];
    std::string x_matrix[4][4];
    int xor_matrix_bin[4][4][8];
    std::string revsub_matrix[4][4];
    std::string revshift_matrix[4][4];
    std::string revmix_matrix[4][4];

    create_4x4(ciphhex, ciph_matrix);

    for (int i = 10; i >= 1; i--)
    {
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                for (size_t k = 0; k < 8; k++)
                {
                    ciph_matrix_bin[i][j][k] = 0;
                    curkey_matrix_bin[i][j][k] = 0;
                    xor_matrix_bin[i][j][k] = 0;
                }
                
            }
            
        }

        // XOR
        get_matrix_bin(ciph_matrix, ciph_matrix_bin);
        get_curkey(all_keys, curkey_matrix, i);
        get_matrix_bin(curkey_matrix, curkey_matrix_bin);
        xor_matrix(ciph_matrix_bin, curkey_matrix_bin, xor_matrix_bin);
        bin_to_hex_matrix(x_matrix, xor_matrix_bin);

        if(i == 10)
        {
            // REV SHIFT
            rev_shift_rows(x_matrix, revshift_matrix);

            // REV SUB
            rev_sub_bytes(revshift_matrix, revsub_matrix);
        }
        else
        {
            // REV MIX
            rev_mix_col(x_matrix, revmix_matrix);

            // REV SHIFT
            rev_shift_rows(revmix_matrix, revshift_matrix);

            // REV SUB
            rev_sub_bytes(revshift_matrix, revsub_matrix);
        }
        
        for (size_t r = 0; r < 4; r++)
        {
            for (size_t c = 0; c < 4; c++)
            {
                ciph_matrix[r][c] = revsub_matrix[r][c];
            }
        }
    }
    
    // XOR K0
    get_curkey(all_keys, curkey_matrix, 0);
    get_matrix_bin(curkey_matrix, curkey_matrix_bin);
    get_matrix_bin(revsub_matrix, ciph_matrix_bin);
    xor_matrix(ciph_matrix_bin, curkey_matrix_bin, xor_matrix_bin);
    bin_to_hex_matrix(x_matrix, xor_matrix_bin);

    std::string text = get_plaintext(x_matrix);
    return text;
}

bool is_block_equal(std::string block1, std::string block2)
{
    for (size_t i = 0; i < block1.length(); i++)
    {
        if(block1[i] != block2[i]) { return false;}
    }
    return true;
}

std::string * get_blocks(std::string blocks[], std::string cipher_line, int &num)
{
    num = 0;
    std::string block = "";
    for (size_t i = 0; i < cipher_line.length(); i++)
    {
        
        block = block + cipher_line[i];
        
        if ((i+1)%32 == 0) 
        {
            blocks[num] = block;
            num++;
            block = "";
        }
    }
    return blocks;
}