#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
        decimal += hexCharToDecimal(hex_string[i]) * pow(16, power);
        power--;
    };
    return decimal;
};

int decimalToBinary(int decimal) {
    if (decimal == 0) {
        return 0;
    }

    int binary = 0;
    int placeValue = 1;

    while (decimal > 0) {
        // Extract the least significant bit and add it to the binary representation
        binary += (decimal & 1) * placeValue;

        // Right shift the decimal number to move to the next bit
        decimal >>= 1;

        // Multiply the place value by 10 for the binary representation
        placeValue *= 10;
    };

    return binary;
};


char* be_to_le(const char *hex_string) {
    if (strlen(hex_string) != 4) {
        fprintf(stderr, "Input string must be exactly 4 characters long\n");
        exit(EXIT_FAILURE);
    };

    // Convert hex string to integer
    unsigned int big_endian_value;
    sscanf(hex_string, "%x", &big_endian_value);

    // Convert integer to little endian format
    unsigned int little_endian_value = ((big_endian_value & 0xFF) << 8) | ((big_endian_value & 0xFF00) >> 8);

    // Allocate memory for the result string
    char *result_hex_string = (char*)malloc(5);

    // Convert little endian value to hexadecimal string
    sprintf(result_hex_string, "%04X", little_endian_value);

    return result_hex_string;
};


int le_to_be(int le_binary) {
    int be_binary = 0;

    // Calculate the size of an integer in bytes
    int size = sizeof(int);

    // Loop through each byte of the little-endian binary number
    for (int i = 0; i < size; ++i) {
        // Extract the ith byte from the little-endian binary
        int byte = (le_binary >> (i * 8)) & 0xFF;

        // Place the byte in the corresponding position in the big-endian binary
        be_binary |= byte << ((size - 1 - i) * 8);
    };

    return be_binary;
};


int binaryConvert(char* hex_string){
    return decimalToBinary(hexToDecimal(be_to_le(hex_string)));
};
