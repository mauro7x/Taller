// includes
#include "stdin_streamer.h"
#include <stdio.h>

// defines

// --------------------------------------------------------
// definiciones

int stdin_streamer_create(stdin_streamer_t *self, callback_t callback) {
    if ((!self) || (!callback)) {
        fprintf(stderr, "Error in function: stdin_streamer_create. "
                        "Error: referencias invalidas.\n");
        return -1;
    }
    
    self->callback = callback;
    return 0;
}



int stdin_streamer_run(stdin_streamer_t *self, void *context) {
    
    while (!feof(stdin)) {
        char buffer[5] = "";
        size_t r = fread(buffer, 1, sizeof(buffer), stdin);
        printf("\nSe leyeron %ld bytes.\n", r);
        self->callback(buffer, r, context);
    }

    return 0;
}


int stdin_streamer_destroy(stdin_streamer_t *self) {

    return 0;
}

// --------------------------------------------------------
