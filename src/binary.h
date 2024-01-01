#ifndef BINARY_FILE
#define BINARY_FILE

int hexCharToDecimal(char hex_digit);
int hexToDecimal(const char *hex_string);
char* decimalToBinary(int decimal);
char* big_endian_to_little_endian(const char *hex_string);

char* binaryConvert(char* hex_string); //Only use this function outside binary.c scope
char* binaryConvert(char* hex_string);

#endif