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


// get ids in the range
void process_ids(u64_t min, u64_t max) {
    //printf("%llu - %llu\r\n", min, max);
    u64_t index;
    int digits;
    u64_t top_half, bot_half;
    
    for (index = min; index <= max; index++) {
        // skip numbers with odd number of digits
        digits = digit_count(index);
        if (IS_ODD(digits)) {
            continue;
        }

        // split the number
        top_half = index / (u64_t)pow(10, digits / 2);
        bot_half = index % (u64_t)pow(10, digits / 2);

        // if id is invalid, add to the sum
        if (top_half == bot_half) {
            id_sum += index;
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