#ifndef __STDIN_STREAMER_H__
#define __STDIN_STREAMER_H__

#include <stdio.h>

typedef void (*callback_t)(char* buffer, size_t len, void *ctx);

typedef struct stdin_streamer {
	callback_t callback;
} stdin_streamer_t;

void stdin_streamer_create(stdin_streamer_t *self, callback_t callback);

void stdin_streamer_run(stdin_streamer_t *self, void *context);

void stdin_streamer_destroy(stdin_streamer_t *self);


#endif