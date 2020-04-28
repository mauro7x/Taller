#include <stdio.h>
#include "stdin_streamer.h"

void my_callback(char* buffer, size_t len, void *ctx) {
    
    fwrite(buffer, sizeof(char), len, stdout);
}


int main(int argc, const char* argv[]) {

    stdin_streamer_t stdin_streamer;
    stdin_streamer_create(&stdin_streamer, my_callback);

    stdin_streamer_run(&stdin_streamer, NULL);

    stdin_streamer_destroy(&stdin_streamer);


    return 0;
}