#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

static int dial;
static int zero_counter;

void init() {
    dial = 50;
    zero_counter = 0;
}


static void move_dial(int distance) {
    printf("dial = %i, turn = %i", dial, distance);
    if (dial + distance < 0) {
        dial = dial + distance + 100;
    } else if (dial + distance > 99) {
        dial = dial + distance - 100;
    } else {
        dial = dial + distance;
    }
    printf(", dial = %i\r\n", dial);
}


void solve_puzzle() {

    FILE * fp;
    char line[8];
    
    // 
    int turn;

    // Open the sequence file for read-only
    fp = fopen("1_sequence.txt", "r");

    // Read each line and determine if the turn is left or right and by what amount
    while (fgets(line, sizeof(line), fp) != NULL) {
        turn = 0;
        
        // get the turn distance
        // 3 digits (we don't actually care about the hundreds digit)
        if (line[3] >= 48 && line[3] <= 57) {
            turn += (line[3] - 48);
            if (line[2] >= 48 && line[2] <= 57) {
                turn += (line[2] - 48) * 10;
            }
        } else {
            // 2 digits
            if (line[2] >= 48 && line[2] <= 57) {
                turn += (line[2] - 48);
                if (line[1] >= 48 && line[1] <= 57) {
                    turn += (line[1] - 48) * 10;
                }
            } else {
                // 1 digit
                if (line[1] >= 48 && line[1] <= 57) {
                    turn += (line[1] - 48);
                }
            }
        }
        
        // get the sign on the turn
        if (strchr(line, 'L') == NULL) {
            turn = turn;
        } else if (strchr(line, 'R') == NULL) {
            turn = -turn;
        } else {
            printf("Invalid input: %s", line);
        }

        move_dial(turn);
        if (dial == 0) {
            zero_counter++;
        }
    }

    // Close file and empty memory
    fclose(fp);

}

int main() {
    init();
    solve_puzzle();

    printf("password: %u", zero_counter);
    return 0;
}