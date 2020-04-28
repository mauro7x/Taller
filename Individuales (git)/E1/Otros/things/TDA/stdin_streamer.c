#include "stdin_streamer.h"

void stdin_streamer_create(stdin_streamer_t *self, callback_t callback) {
	self->callback = callback;
}

void stdin_streamer_run(stdin_streamer_t *self, void *context) {
	while (!feof(stdin)) {
		char buffer[5] = "";
		size_t rv = fread(buffer, 1, sizeof(buffer), stdin);
		self->callback(buffer, rv, context);
	}
}

void stdin_streamer_destroy(stdin_streamer_t *self) {

}