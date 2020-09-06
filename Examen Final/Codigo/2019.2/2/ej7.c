// includes
#include <stdio.h>

typedef struct ejemplo_t {
    int a;
    char b;
} ejemplo;

typedef struct ejemplo2_t {
    int a;
    char b;
}__attribute__( (packed) ) ejemplo2;

int main(int argc, char* argv[]) {
    
    ejemplo e = {1, 'a'};
    ejemplo2 e2 = {1, 'a'};
 
    
    printf("sizeof e = %lu, sizeof e2 = %lu\n", sizeof(e), sizeof(e2));

    return 0;
}

// definiciones
