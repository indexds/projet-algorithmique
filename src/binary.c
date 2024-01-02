#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

int hexCharToDecimal(char hex_digit) {
    int decimal_value;

    if (hex_digit >= '0' && hex_digit <= '9') {
        decimal_value = hex_digit - '0';
    } else if (hex_digit >= 'A' && hex_digit <= 'F') {
        decimal_value = hex_digit - 'A' + 10;
    } else if (hex_digit >= 'a' && hex_digit <= 'f') {
        decimal_value = hex_digit - 'a' + 10;
    } else {
        printf("Invalid hex digit: %c\n", hex_digit);
        exit(EXIT_FAILURE);
    };
    return decimal_value;
};

int hexToDecimal(const char *hex_string) {
    int decimal = 0;
    int power = strlen(hex_string)-1;

    for (size_t i = 0; i < strlen(hex_string); ++i) {
        decimal += hexCharToDecimal(hex_string[i]) * (int)pow(16, power);
        power--;
    };
    return decimal;
};

uint32_t decimalToBinary(uint32_t decimal) {
    if (decimal == 0) {
        return 0;
    };
    uint32_t binary = 0;
    uint32_t placeValue = 1;

    while (decimal > 0) {
        binary += (decimal & 1) * placeValue;
        decimal >>= 1;
        placeValue *= 10;
    };
    return binary;
};

uint32_t be_to_le(uint32_t be_binary) {
    uint32_t le_binary = 0;

    // Calculate the size of an integer in bytes
    uint32_t size = sizeof(uint32_t);

    // Loop through each byte of the big-endian binary number
    for (uint32_t i = 0; i < size; ++i) {
        // Extract the ith byte from the big-endian binary
        uint32_t byte = (be_binary >> ((size - 1 - i) * 8)) & 0xFF;

        // Place the byte in the corresponding position in the little-endian binary
        le_binary |= byte << (i * 8);
    }

    return le_binary;
}

uint32_t le_to_be(uint32_t le_binary) {
    uint32_t be_binary = 0;

    // Calculate the size of an integer in bytes
    uint32_t size = sizeof(uint32_t);

    // Loop through each byte of the little-endian binary number
    for(uint32_t i = 0; i < size; ++i) {
        // Extract the ith byte from the little-endian binary
        uint32_t byte = (le_binary >> (i * 8)) & 0xFF;

        // Place the byte in the corresponding position in the big-endian binary
        be_binary |= byte << ((size - 1 - i) * 8);
    };

    return be_binary;
};


uint32_t binaryConvert(char* hex_string){
    return be_to_le(decimalToBinary(hexToDecimal(hex_string)));
};