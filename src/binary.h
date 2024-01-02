#ifndef BINARY_FILE
#define BINARY_FILE

#include <stdint.h>

int hexCharToDecimal(char hex_digit);
int hexToDecimal(const char *hex_string);

uint32_t decimalToBinary(uint32_t decimal);
uint32_t binaryConvert(char* hex_string); //Only use this function outside binary.c scope

uint32_t be_to_le(uint32_t be_binary);
uint32_t le_to_be(uint32_t le_binary);

#endif