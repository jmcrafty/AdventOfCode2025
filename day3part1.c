#include <stdio.h>
#include <stdlib.h>

unsigned int j_sum;

void parse_file() {
    FILE *fp;
    char line[256];
    char digit;
    int test;
    unsigned int first, second;
    unsigned int candidate;

    // open file for read only
    fp = fopen("3_input.txt", "r");
    while (fgets(line, sizeof(line), fp) != NULL) {
        //printf("line: %s ", line);
        first = 0;
        second = 0;
        candidate = 0;
        digit = 0;
        do {
            test = line[digit] - '0';
            digit++;
            // exit if \r \n or \0
            if (test < 0) {
                //printf("\'%0X\' character\r\n", line[digit]);
                break;
            }
            // update if second digit bigger
            // and if first digit has been set
            if (test > second && first != 0) {
                second = test;
                //printf("update second to %u\r\n", test);
                candidate = first * 10 + second;
            }
            // update if first digit bigger
            if (test > first) {
                first = test;
                //printf("update first to %u\r\n", test);
                second = 0;
            }
        } while (line[digit] != '\n');

        //printf("candidate: %u\r\n", candidate);
        j_sum += candidate;
    }
}


int main() {
    parse_file();
    printf("id_sum: %u\r\n", j_sum);
    return 0;
}