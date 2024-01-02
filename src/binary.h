#ifndef BINARY_FILE
#define BINARY_FILE

int hexCharToDecimal(char hex_digit);
int hexToDecimal(const char *hex_string);
int decimalToBinary(int decimal);
char* be_to_le(const char *hex_string);

int binaryConvert(char* hex_string); //Only use this function outside binary.c scope
int le_to_be(int le_binary);

#endif