#include <stdio.h>
#include <string.h>
#include <math.h>

#define u64_t unsigned long long

#define NUM_DIGITS 12

u64_t joltage;

void parse_file() {
    FILE *fp;
    char line[256];
    int index;
    int test;
    int length;
    u64_t number;
    u64_t max_digit;
    int max_index;

    // open file for read only
    fp = fopen("3_input.txt", "r");
    while (fgets(line, sizeof(line), fp) != NULL) {
        length = strlen(line);
        max_index = 0;
        number = 0;
        // interate for each digit in the number
        for (u64_t offset = 0; offset < NUM_DIGITS; offset++) {
            max_digit = 0;
            // start parsing after the index of the previous maximum
            index = max_index;
            
            // starting at the index after the previous maximum, iterate over
            // the remaining digits less than the number of total digits
            while (index < length - (NUM_DIGITS - offset)) {
                test = line[index] - '0';
                index++;
                // update if the digit is bigger
                if (test > max_digit) {
                    max_digit = test;
                    max_index = index;
                }
            }
            // Add the max digit to the number
            number += max_digit * (u64_t)pow(10, ((u64_t)NUM_DIGITS-offset-1));
        }

        joltage += number;
    }
}


int main() {
    parse_file();
    printf("joltage: %llu\r\n", joltage);
    return 0;
}