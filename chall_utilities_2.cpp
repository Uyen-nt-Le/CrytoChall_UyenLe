#include <iostream>
#include <cmath>

#include "chall_utilities.h"

char dec_to_hex(int dec)
{
    char hex;
    if (dec < 10) {hex = dec + '0';}
    else if (dec < 16) {hex = dec - 10 + 'a';}
    else {std::cout << "DEC to HEX ERROR!\n";}
    return hex;
}

void get_hex(int bin[8], std::string &hex)
{
    int pow_ = 3;
    int dec = 0;
    
    for (size_t i = 0; i < 8; i++)
    {
        if (bin[i] == 1)
        {
            dec += pow(2, pow_);
        }
        pow_--;
        if ((i+1)%4 == 0) 
        {
            hex = hex + dec_to_hex(dec);
            dec = 0;
            pow_ = 3;
        }
    }
}

std::string get_pad_hex(int num)
{
    std::string hex = "";
    int bin[8];
    get_bin(num, bin, 8);
    get_hex(bin, hex);
    return hex;
}

void pkcs7(std::string &block, int bytes_req)
{
    int block_size = block.length();
    if (bytes_req-block_size < 0) {std::cout << "ERROR! NO PADDING REQUIRED.\n";}
    int padnum = bytes_req - block_size;
    std::string hex = get_pad_hex(padnum);

    for (size_t i = 0; i < padnum; i++)
    {
        block = block + hex;
    }
}

