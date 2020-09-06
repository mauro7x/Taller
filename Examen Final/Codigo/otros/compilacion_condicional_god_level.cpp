#include <stdio.h>

#include <condition_variable>
#include <exception>
#include <fstream>
#include <iostream>
#include <list>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

#define DEBUG

#ifdef DEBUG
#define IF_DEBUG(...) __VA_ARGS__
#else
#define IF_DEBUG(...)
#endif

#define LOG(string) IF_DEBUG(fprintf(stderr, "%s\n", string))

int main() {
    LOG("hola wachines");
    return 0;
}
