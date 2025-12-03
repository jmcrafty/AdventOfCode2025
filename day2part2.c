#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define u64_t unsigned long long

// return 1 if odd number
#define IS_ODD(X) (((X)%2==0) ? (0) : (1))

// 64 bit
u64_t id_sum;

// return number of digits in a number
int digit_count(u64_t value) {
    int digits = 1;
    while (value != 0) {
        value = value / 10ULL;
        value -= value % 10ULL;
        digits++;
    }
    return digits;
}


// checks to see if the pattern is valid for a number
int check_pattern(u64_t number, int length, u64_t pattern) {
    u64_t value = number;

    while (value >= (u64_t)pow(10, length)) {
        value = value / (u64_t)pow(10, length);
        u64_t test = value % (u64_t)pow(10, length);
        if (pattern == test) {
            continue;
        } else {
            return 0;
        }
    }
    return 1;
}


// get ids in the range
void process_ids(u64_t min, u64_t max) {
    //printf("%llu - %llu\r\n", min, max);
    u64_t index;
    int digits;
    
    for (index = min; index <= max; index++) {
        digits = digit_count(index);

        // skip single digit ids
        if (index < 10) {
            continue;
        }

        // iterate over the lengths of digits patterns
        for (int length = 1; length <= digits / 2; length++) {
            // skip pattern lengths that arent factors of the id length
            if (digits % length != 0) {
                continue;
            }
            // get the pattern to match
            u64_t pattern = index % (u64_t)pow(10, length);

            if (check_pattern(index, length, pattern)) {
                id_sum += index;
                break;
            }
        }
    }
}


void parse_file() {
    FILE *fp;
    char digit;
    u64_t min, max = 0;
    u64_t *minmax_ptr;
    
    // open file for read only
    fp = fopen("2_ids.txt", "r");

    // point at min
    minmax_ptr = &min;

    // iterate over each char in the file
    while ((digit = getc(fp)) != EOF) {
        if (digit == ',') {
            // process id range
            process_ids(min, max);

            // reset min and max
            min = max = 0;

            // point at min
            minmax_ptr = &min;
        }
        else if (digit == '-') {
            // point at max
            minmax_ptr = &max;
        }
        else {
            *minmax_ptr *= 10ULL;
            *minmax_ptr += (u64_t)(digit - '0');
        }
    }
    // last input
    process_ids(min, max);
}


int main() {
    parse_file();
    printf("id_sum: %llu\r\n", id_sum);
    return 0;
}