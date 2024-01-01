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

char* decimalToBinary(int decimal) {
    // Determine the number of bits needed
    int numBits = 0;
    int temp = decimal;
    while (temp > 0) {
        temp /= 2;
        numBits++;
    }

    // Allocate memory for the binary representation (+1 for null terminator)
    char* binary = (char*)malloc((numBits + 1) * sizeof(char));

    // Convert decimal to binary
    for (int i = numBits - 1; i >= 0; i--) {
        binary[i] = (decimal % 2) + '0';
        decimal /= 2;
    }

    // Add null terminator
    binary[numBits] = '\0';

    return binary;
}


char* big_endian_to_little_endian(const char *hex_string) {
    if (strlen(hex_string) != 4) {
        fprintf(stderr, "Input string must be exactly 4 characters long\n");
        exit(EXIT_FAILURE);
    }

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

char* binaryConvert(char* hex_string){
    return decimalToBinary(hexToDecimal(big_endian_to_little_endian(hex_string)));
};
