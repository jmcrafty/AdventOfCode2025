// insertion sort ranges
// merge ranges
// sort inputs
// 
// iterate over inputs
//     count values in range

#include <stdio.h>  // printf, NULL
#include <string.h>
#include <stdlib.h> // strtoull

#define u64_t unsigned long long
#define MAX_RANGES 256
#define MAX_INPUTS 1024

u64_t ranges[MAX_RANGES][2] = {0};
u64_t inputs[MAX_INPUTS] = {0};

int counter = 0;

void insert_into_ranges(u64_t lower, u64_t upper) {
    static int elements = 0;
    ranges[elements][0] = lower;
    ranges[elements][1] = upper;
    elements++;
}

void insert_into_inputs(u64_t value) {
    static int elements = 0;
    inputs[elements] = value;
    elements++;
}

void print_ranges() {
    int i = 0;
    while (ranges[i][0] != 0) {
        printf("%llu-%llu\r\n", ranges[i][0], ranges[i][1]);
        i++;
    }
}

void print_inputs() {
    int i = 0;
    while (inputs[i] != 0) {
        printf("%llu\r\n", inputs[i]);
        i++;
    }
}

// unga-bunga
void brute_force() {
    int i = 0;
    int j = 0;
    while (inputs[i] != 0) {
        while (ranges[j][0] != 0) {
            if (inputs[i] >= ranges[j][0] && inputs[i] <= ranges[j][1]) {
                counter++;
                break;
            }
            j++;
        }
        i++;
        j = 0;
    }
}

void parse_file() {
    FILE *fp;
    char line[256];
    int input_flag = 0;
    int good = 0;
    u64_t lower, upper;
    fp = fopen("5_input.txt", "r");
    while (fgets(line, sizeof(line), fp) != NULL) {
        // blank line (or last line)
        if (strlen(line) <= 1) {
            continue;
        }

        // if theres a dash its a range
        char* str_ptr = strchr(line, '-');
        if (str_ptr == NULL) {
            // no dash its an input
            insert_into_inputs(strtoull(line, NULL, 10));
            continue;
        }
        // split range into upper and lower
        upper = strtoull(str_ptr + 1, NULL, 10);
        *str_ptr = '\0';
        lower = strtoull(line, NULL, 10);
        insert_into_ranges(lower, upper);
        
    }
}

int main() {
    parse_file();
    brute_force();
    printf("counter: %i", counter);
    return 0;
}