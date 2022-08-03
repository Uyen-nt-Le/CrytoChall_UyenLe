#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <cstring>

#include "chall_utilities.h"
#include "chall_utilities_2.h"

void challenge9()
{
    std::cout << "-------------------------\n";
    std::cout << "Cryptographic Challenge 9\n";
    std::cout << "-------------------------\n";

    std::string block = "YELLOW SUBMARINE";
    int desired_len = 20;
    pkcs7(block, desired_len);
    std::cout << block << '\n';

    std::cout << '\n';
}

void challenge10()
{
    std::cout << "-------------------------\n";
    std::cout << "Cryptographic Challenge 10\n";
    std::cout << "-------------------------\n";

    std::string IV[4][4] = // hex
    {{"00", "00", "00", "00"},
    {"00", "00", "00", "00"},
    {"00", "00", "00", "00"},
    {"00", "00", "00", "00"}};
    int IV_bin[4][4][8];
    get_matrix_bin(IV, IV_bin);

    std::ifstream encrypted_file("chall10txt/chall10_file.txt");
    std::ofstream decrypted_file("chall10txt/chall10_decode.txt");
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
    char charbuf3[BUFSIZ];
    char hexbuf1[BUFSIZ];
    char hexbuf2[BUFSIZ];
    char hexbuf3[BUFSIZ];
    int decbuf1[BUFSIZ];
    int decbuf2[BUFSIZ];
    int decbuf3[BUFSIZ];
    int binbuf1[BUFSIZ];
    int binbuf2[BUFSIZ];
    int binbuf3[BUFSIZ];
    memset(charbuf1, 0, BUFSIZ);
    memset(charbuf2, 0, BUFSIZ);
    memset(charbuf3, 0, BUFSIZ);
    memset(hexbuf1, 0, BUFSIZ);
    memset(hexbuf2, 0, BUFSIZ);
    memset(hexbuf3, 0, BUFSIZ);
    std::string key_matrix[4][4];
    std::string subkey_matrix[4][4];
    std::string all_keys[11][4][4]; // n+1 keys

    std::string decrypt_matrix[4][4];
    int decrypt_bin_matrix[4][4][8];
    int xor_decrypt_matrix[4][4][8];

    bool run = true;
    std::string prev_ = "";
    std::string prev_matrix[4][4];
    int prev_bin_matrix[4][4][8];
    int len2 = 0;

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
            dec_to_hex(testdbuf, char_encrypt, (60*6)/4);
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
        // str_to_char(ciphertext, hexbuf1);
        // decrypt_text = aes_128_decrypt(hexbuf1, all_keys);

        str_to_char(ciphertext, hexbuf1);
        decrypt_text = aes_128_decrypt(hexbuf1, all_keys);
        len2 = decrypt_text.length();


        // REWRITE AS CBC FUNCTION!!!!!!!!!!!!!!!!
        // Reset buffers
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                for (size_t k = 0; k < 8; k++)
                {
                    decrypt_bin_matrix[i][j][k] = 0;
                    prev_bin_matrix[i][j][k] = 0;
                    xor_decrypt_matrix[i][j][k] = 0;
                }
            }
        }
        for (size_t i = 0; i < len*8; i++)
        {
            binbuf1[i] = 0;
            decbuf1[i] = 0;
            memset(charbuf1, 0, BUFSIZ);
            memset(hexbuf1, 0, BUFSIZ);
            memset(hexbuf3, 0, BUFSIZ);
        }
        
        
        
        str_to_char(decrypt_text, charbuf1);
        char_to_dec(charbuf1, decbuf1, len);
        dec_to_bin8(decbuf1, binbuf1, len);
        bin4_to_dec(binbuf1, decbuf1, len*8);
        dec_to_hex(decbuf1, hexbuf1, len*2);
        create_4x4(hexbuf1, decrypt_matrix);
        get_matrix_bin(decrypt_matrix, decrypt_bin_matrix);

        if (run)
        {
            xor_matrix(decrypt_bin_matrix, IV_bin, xor_decrypt_matrix);
            run = false;
        }
        else
        {
            str_to_char(prev_, hexbuf3);
            create_4x4(hexbuf3, prev_matrix);
            get_matrix_bin(prev_matrix, prev_bin_matrix);

            xor_matrix(decrypt_bin_matrix, prev_bin_matrix, xor_decrypt_matrix);
        }

        bin_to_hex_matrix(decrypt_matrix, xor_decrypt_matrix);
        decrypt_text = get_plaintext(decrypt_matrix);



        decrypted_file << decrypt_text;
        prev_ = ciphertext;
        
    }

    std::cout << "Check 'chall10txt/chall10_decode.txt'\n";
    std::cout << '\n';
}
