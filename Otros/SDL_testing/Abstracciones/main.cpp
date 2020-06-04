#include <stdio.h>

#include "Exception.h"
#include "SDLException.h"
#include "View.h"

int main(int argc, char* argv[]) {
    try {
        View view;
        view();
    } catch (const SDLException& e) {
        fprintf(stderr, "%s\n", e.what());
        return 1;
    } catch (const Exception& e) {
        fprintf(stderr, "%s\n", e.what());
        return 2;
    } catch (...) {
        fprintf(stderr, "Error desconocido.\n");
        return 3;
    }

    return 0;
}