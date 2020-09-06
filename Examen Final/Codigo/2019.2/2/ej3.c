// includes
#include <stdio.h>

// defines

// declaraciones

int main(int argc, char* argv[]) {
    
    int *Pi=1000;
    Pi++;
    printf("Pi apunta a la direccion: %ld\n", (long)Pi);
    printf("sizeof de int: %ld\n", sizeof(int));

    return 0;
}

// definiciones
