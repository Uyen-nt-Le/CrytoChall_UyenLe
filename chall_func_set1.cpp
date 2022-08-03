#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <queue>

#include "chall_utilities.h"

void challenge1()
{
    std::cout << "-------------------------\n";
    std::cout << "Cryptographic Challenge 1\n";
    std::cout << "-------------------------\n";

    char hexbuf[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    const size_t H = sizeof(hexbuf)-1;
    const size_t n = 4;
    char sol[] = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
    int decbuf[H];
    int binbuf[H*4];
    char base64buf[(H*4) + 6];
    memset(base64buf, 0, (H*4) + 6);

    hex_to_dec(hexbuf, decbuf, H);
    dec_to_bin4(decbuf, binbuf, H);
    bin_to_base64(base64buf, binbuf, n, H);

    std::cout << "HEX: " << hexbuf << '\n';
    std::cout << "BASE64: " << base64buf << '\n';
    std::cout << "\nANSWER: " << sol << '\n';
}

void challenge2()
{
    std::cout << "-------------------------\n";
    std::cout << "Cryptographic Challenge 2\n";
    std::cout << "-------------------------\n";

    char hexbuf1[] = "1c0111001f010100061a024b53535009181c";
    char hexbuf2[] = "686974207468652062756c6c277320657965";
    char sol[] = "746865206b696420646f6e277420706c6179";
    const size_t H = sizeof(hexbuf1)-1;
    char hexbuf3[H];

    int decbuf1[H];
    int decbuf2[H];
    int decbuf3[H];
    int binbuf1[H*4];
    int binbuf2[H*4];
    int binbuf3[H*4];

    memset(hexbuf3, 0, H);

    hex_to_dec(hexbuf1, decbuf1, H);
    hex_to_dec(hexbuf2, decbuf2, H);
    dec_to_bin4(decbuf1, binbuf1, H);
    dec_to_bin4(decbuf2, binbuf2, H);

    b_XOR_b(binbuf1, binbuf2, binbuf3, H);
    bin4_to_dec(binbuf3, decbuf3, H*4);
    dec_to_hex(decbuf3, hexbuf3, H);

    std::cout << hexbuf1 << '\n';
    std::cout << "XOR\n";
    std::cout << hexbuf2 << '\n';
    std::cout << "=\n";
    for (size_t i = 0; i < sizeof(hexbuf3); i++)
    {
        std::cout << hexbuf3[i];
    }
    std::cout << '\n';
    std::cout << "\nANSWER: " << sol << '\n';
}

void challenge3()
{
    std::cout << "-------------------------\n";
    std::cout << "Cryptographic Challenge 3\n";
    std::cout << "-------------------------\n";

    char hexbuf[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    const size_t H = sizeof(hexbuf)-1;

    int binbuf[H*4];
    int decbuf[H];

    int a = 32; // space
    int b = 126; // ~

    hex_to_dec(hexbuf, decbuf, H);
    dec_to_bin4(decbuf, binbuf, H);
    testkeys(a, b, H*4, binbuf);
    std::cout << '\n';
}

void challenge4()
{
    std::cout << "-------------------------\n";
    std::cout << "Cryptographic Challenge 4\n";
    std::cout << "-------------------------\n";

    std::ifstream encrypt_file("chall4txt/encryptstr.txt");
    std::string encrypt_line = "";

    std::ofstream decrypt_file("chall4txt/decrypt_str.txt");

    const size_t H = 60;
    char hexbuf[H];
    memset(hexbuf,0,H);

    int binbuf[H*4];
    int decbuf[H];
    
    int a = 32; // space
    int b = 126; // ~
    size_t i = 0;

    if (encrypt_file.is_open())
    {
        while (getline(encrypt_file, encrypt_line))
        {
            if (decrypt_file.is_open())
            {
                decrypt_file << "ENCRYPT LINE #" << i+1 << ": " << encrypt_line << '\n';
            }
            str_to_char(encrypt_line, hexbuf);
            hex_to_dec(hexbuf, decbuf, H);
            dec_to_bin4(decbuf, binbuf, H);
            testkeys2(a, b, H*4, binbuf, decrypt_file);
            if (decrypt_file.is_open())
            {
                decrypt_file << '\n';
            }
            i++;
        }
    }
}


void challenge5()
{
    std::cout << "-------------------------\n";
    std::cout << "Cryptographic Challenge 5\n";
    std::cout << "-------------------------\n";

    std::string msg_line = "Burning 'em, if you ain't quick and nimble I go crazy when I hear a cymbal";
    char keys[] = "ICE";
    // char m[] = "Burning 'em, if you ain't quick and nimble";
    const size_t K = sizeof(keys)-1;
    char mcharbuf[BUFSIZ]; // message char buffer
    char mhexbuf[BUFSIZ];  // message hex buffer
    int mdecbuf[BUFSIZ];   // message decimal buffer
    int mbinbuf[BUFSIZ];   // message binary buffer
    int kbinbits[BUFSIZ];       // key binary bits
    int kbinbuf[K*8];   // key binary buffer

    int * ptr = &kbinbits[0];
    for (size_t i = 0; i < sizeof(keys)-1; i++)
    {
        get_bin(keys[i], ptr, 8);
        ptr += 8;
    }

    int msg_char_num = msg_line.length()+1;
    memset(mcharbuf, 0, msg_char_num);
    memset(mhexbuf, 0, msg_char_num);

    fill_binbuf(kbinbuf, kbinbits, msg_char_num*8, K*8);
    str_to_char(msg_line, mcharbuf);
    char_to_dec(mcharbuf, mdecbuf, msg_char_num);
    dec_to_bin8(mdecbuf, mbinbuf, msg_char_num*8);
    b_XOR_b(mbinbuf, kbinbuf, mbinbuf, msg_char_num*8);
    bin4_to_dec(mbinbuf, mdecbuf, msg_char_num*8);
    dec_to_hex(mdecbuf, mhexbuf, msg_char_num*2);
    for (size_t i = 0; i < msg_char_num*2-2; i++)
    {
        std::cout << mhexbuf[i];
        if (i == 74) { std::cout << '\n';} // To match the website
    }
    std::cout << '\n';
    std::cout << "\nANSWER: " << '\n';
    std::cout << "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272\n"
                << "a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f\n";
}

void challenge6()
{
    std::cout << "-------------------------\n";
    std::cout << "Cryptographic Challenge 6\n";
    std::cout << "-------------------------\n";
    
    /*-----Turn encrypted base64 to binary-----*/
    std::ifstream encrypt_file("chall6txt/chall6_file.txt");
    std::string encrypt_line = "";

    std::ofstream output_file("chall6txt/chall6_bin.txt");
    char charbuf[BUFSIZ];
    char hexbuf[BUFSIZ];
    int decbuf[BUFSIZ];
    int binbuf[BUFSIZ];
    memset(charbuf, 0, BUFSIZ);
    memset(hexbuf, 0, BUFSIZ);
    
    const size_t K = 39;
    int keysize[K];
    int temp = 2;
    for (size_t i = 0; i < K; i++)
    {
        keysize[i] = temp;
        temp++;
    }

    if (encrypt_file.is_open())
    {
        while (getline(encrypt_file, encrypt_line))
        {
            if (output_file.is_open())
            {
                str_to_char(encrypt_line, charbuf);
                base64_to_dec(charbuf, decbuf, encrypt_line.length());
                dec_to_bin6(decbuf, binbuf, encrypt_line.length());
                for (size_t i = 0; i < encrypt_line.length()*6-6; i++)
                {
                    output_file << binbuf[i];
                }
                output_file << '\n';
            }
        }
    }

    encrypt_file.close();
    output_file.close();

    /*-----Find KEYSIZE-----*/
    std::ifstream bin_input_file("chall6txt/chall6_bin.txt");
    std::string bin_input_line = "";
    std::string bin_input_temp = "";

    // Sample
    for (size_t i = 0; i < 18; i++)
    {
        getline(bin_input_file, bin_input_line);
        bin_input_temp = bin_input_temp + bin_input_line;
    }
    
    const size_t TEMP_SIZE = bin_input_temp.length();
    char tempcharbuf[BUFSIZ];
    int tempbinbuf[BUFSIZ];
    memset(tempcharbuf, 0, BUFSIZ);

    str_to_char(bin_input_temp, tempcharbuf);
    binchar_to_int(tempcharbuf, tempbinbuf, TEMP_SIZE);

    double ham[K];
    get_ham_dist(K, keysize, bin_input_temp.length(), tempbinbuf, ham);

    bin_input_file.close();

    int keysiz = keysize[min_el_in(ham,K)];

    bin_input_file.close();

    /*-----Store binary as blocks of KEYSIZE and Transpose-----*/
    std::ifstream bin_file2("chall6txt/chall6_bin.txt");
    std::string bin_line = "";
    
    std::ofstream bin_keysiz_block("chall6txt/chall6_bin_keysiz_block.txt");
    std::ofstream bin_block("chall6txt/chall6_bin_trans_block.txt");
    char block_matrix[1000][1000][8];
    char block_transpose_matrix[100][100][8];
    int max_col = keysiz;
    int max_row = 0;

    get_keysiz_matrix(bin_file2, bin_keysiz_block, bin_line, max_col, max_row, block_matrix);
    transpose_matrix(max_col, max_row, block_transpose_matrix, block_matrix, bin_block);

    bin_block.close();

    /*-----Find single-character XOR for the KEY-----*/
    std::ifstream tblock_file("chall6txt/chall6_bin_trans_block.txt");
    std::string tblock_line = "";

    std::ofstream xor_decode("chall6txt/chall6_decode_blocks.txt");
    int xbinbuf[BUFSIZ];
    char tbinbuf[BUFSIZ];
    memset(tbinbuf, 0, BUFSIZ);
    int a = 32; // space
    int b = 126; // ~

    char keys[100];
    size_t k_i = 0;

    if(tblock_file.is_open())
    {
        while(getline(tblock_file, tblock_line))
        {
            memset(tbinbuf, 0, BUFSIZ);
            str_to_char(tblock_line, tbinbuf);
            binchar_to_int(tbinbuf, xbinbuf, tblock_line.length());
            xor_decode << "LINE: " << tblock_line << '\n';
            testkeys3(a, b, tblock_line.length(), xbinbuf, xor_decode, keys, k_i);
            xor_decode << '\n';
        }
    }
    
    std::cout << keys << '\n';
    
    std::cout << '\n';
}

void challenge7()
{
    std::cout << "-------------------------\n";
    std::cout << "Cryptographic Challenge 7\n";
    std::cout << "-------------------------\n";

    std::ifstream encrypted_file("chall7txt/chall7_file.txt");
    std::ofstream decrypted_file("chall7txt/chall7_decode.txt");
    // std::string plaintext =  "";
    std::string ciphertext = "";
    std::string encryptkey = "YELLOW SUBMARINE";
    std::string decrypt_text = "";
    int testdbuf[BUFSIZ];
    int testbbuf[BUFSIZ];
    char char_encrypt[BUFSIZ];
    std::queue<char> encrypt_char;
    std::string encrypt_line;
    char charbuf1[BUFSIZ];
    char charbuf2[BUFSIZ];
    char hexbuf1[BUFSIZ];
    char hexbuf2[BUFSIZ];
    int decbuf1[BUFSIZ];
    int decbuf2[BUFSIZ];
    int binbuf1[BUFSIZ];
    int binbuf2[BUFSIZ];
    memset(charbuf1, 0, BUFSIZ);
    memset(charbuf2, 0, BUFSIZ);
    memset(hexbuf1, 0, BUFSIZ);
    memset(hexbuf2, 0, BUFSIZ);
    std::string key_matrix[4][4];
    std::string subkey_matrix[4][4];
    std::string all_keys[11][4][4]; // n+1 keys

    // GENERATE KEYS
    const size_t len = encryptkey.length();
    str_to_char(encryptkey, charbuf2);
    char_to_dec(charbuf2, decbuf2, len);
    dec_to_bin8(decbuf2, binbuf2, len);
    bin4_to_dec(binbuf2, decbuf2, len*8);
    dec_to_hex(decbuf2,hexbuf2, len*2);

    create_4x4(hexbuf2, key_matrix);
    fill_keys(all_keys, key_matrix, 0);
    key_expansion(key_matrix, subkey_matrix, 1);
    fill_keys(all_keys, subkey_matrix, 1);

    for (size_t i = 2; i <= 10; i++)
    {
        key_expansion(subkey_matrix,subkey_matrix, i);
        fill_keys(all_keys, subkey_matrix, i);
    }

    while(!encrypted_file.eof())
    {
        if(encrypt_char.size() < 32)
        {   // Get more characters if queue has less than 16 bytes (32 bits)
            getline(encrypted_file, encrypt_line);
            str_to_char(encrypt_line, char_encrypt);
            base64_to_dec(char_encrypt, testdbuf, 60);
            dec_to_bin6(testdbuf, testbbuf, 60);
            bin4_to_dec(testbbuf, testdbuf, 60*6);
            dec_to_hex(testdbuf, char_encrypt, 60*2);
            for (size_t i = 0; i < 60*6/4; i++)
            {
                encrypt_char.push(char_encrypt[i]);
            }
        }
        ciphertext = "";
        for (size_t i = 0; i < 32; i++)
        {
            ciphertext = ciphertext + encrypt_char.front();
            encrypt_char.pop();
        }
        
        // PLAINTEXT
        // str_to_char(plaintext, charbuf1);
        // char_to_dec(charbuf1, decbuf1, len);
        // dec_to_bin8(decbuf1, binbuf1, len);
        // bin4_to_dec(binbuf1, decbuf1, len*8);
        // dec_to_hex(decbuf1,hexbuf1, len*2);
        
        // ENCRYPTION
        // ciphertext = aes_128_encrypt(hexbuf1, all_keys);
        // std::cout << ciphertext << '\n';

        // DECRYPTIOM
        str_to_char(ciphertext, hexbuf1);
        decrypt_text = aes_128_decrypt(hexbuf1, all_keys);
        decrypted_file << decrypt_text;
    }
    std::cout << "Check 'chall7txt/chall7_decode.txt'\n";
    std::cout << '\n';
}

void challenge8()
{
    std::cout << "-------------------------\n";
    std::cout << "Cryptographic Challenge 8\n";
    std::cout << "-------------------------\n";

    std::ifstream cipher_file("chall8txt/chall8_file.txt");
    std::string cipher_line = "";
    std::string blocks[BUFSIZ];
    std::string block;
    int equal_count = 0;
    int best_count = 0;
    int num_blocks = 0;
    int len = 0;
    std::string best_line = "";
    int count = 0;

    if (cipher_file.is_open())
    {
        while (getline(cipher_file, cipher_line))
        {
            count ++;
            if(count == 134) {break;}
            len = cipher_line.length();
            equal_count = 0;
            
            get_blocks(blocks, cipher_line, num_blocks);
            
            for (size_t i = 0; i < num_blocks-1; i++)
            {
                for (size_t j = i+1; j < num_blocks; j++)
                {
                    if (is_block_equal(blocks[i], blocks[j])) {equal_count++;}
                }               
            }
            if (equal_count > best_count)
            {
                best_count = equal_count;
                best_line = cipher_line;
            }
        }
    }
    std::cout << best_line << '\n';
    std::cout << '\n';
}