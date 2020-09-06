// includes
#include <stdio.h>
#include <stdbool.h>

// defines

// declaraciones
int char2int(char c);

int main(int argc, char* argv[]) {
    
    char c;
    int aux, current_number = 0, total_sum = 0;
    bool done = false;
    bool receiving = false;

    while (!done) {
        while ((c = fgetc(stdin)) != '=') {
            if (c == '\n') {
                continue;
            }

            receiving = true;

            if (c == '+') {
                total_sum += current_number;
                current_number = 0;
            } else {
                current_number *= 10;
                current_number += char2int(c);
            }
        }

        if (receiving) {
            total_sum += current_number;
            printf("%d\n", total_sum);
            current_number = 0;
            total_sum = 0;
            receiving = false;
        } else {
            done = true;
        }
    }

    return 0;
}

// definiciones
int char2int(char c) {
    return (int) c - (int) '0';
}