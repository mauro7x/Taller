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

class QueueClosedException : public std::exception {};

class IntThreadSafeBlockingQueue {
   private:
    std::mutex m;
    std::condition_variable cv;
    std::queue<int> queue;
    bool closed;

   public:
    IntThreadSafeBlockingQueue() : closed(false) {}
    ~IntThreadSafeBlockingQueue() {}

    void push(int val) {
        std::unique_lock<std::mutex> l(m);
        queue.push(val);
        cv.notify_all();
    }

    int pop() {
        std::unique_lock<std::mutex> l(m);

        if (queue.empty()) {
            if (closed) {
                throw QueueClosedException();
            }

            cv.wait(l);
        }

        int val = queue.front();
        queue.pop();
        return val;
    }

    void close() {
        std::unique_lock<std::mutex> l(m);
        closed = true;
        cv.notify_all();
    }
};

class FileWritter {
   private:
    std::ofstream& file;
    IntThreadSafeBlockingQueue& queue;

   public:
    FileWritter(std::ofstream& file, IntThreadSafeBlockingQueue& queue)
        : file(file), queue(queue) {}
    ~FileWritter() {}

    void operator()() {
        fprintf(stderr, "[FILE WRITTER] Comenzando ejecución.\n");

        try {
            int val;
            while (true) {
                val = queue.pop();
                file << val;
                file << '\n';
            }

        } catch (const QueueClosedException) {
        }

        fprintf(stderr, "[FILE WRITTER] Finalizando ejecución.\n");
    }
};

class ListParser {
   private:
    std::list<int>& ints;
    IntThreadSafeBlockingQueue& queue;

   public:
    ListParser(std::list<int>& ints, IntThreadSafeBlockingQueue& queue)
        : ints(ints), queue(queue) {}
    ~ListParser() {}

    void operator()() {
        fprintf(stderr, "[LIST PARSER] Comenzando ejecución.\n");

        for (auto it = ints.begin(); it != ints.end(); it++) {
            if (!(*it % 2)) {
                queue.push(*it);
            }
        }

        queue.close();

        fprintf(stderr, "[LIST PARSER] Finalizando ejecución.\n");
    }
};

int main() {
    std::list<int> enteros;

    for (int i = 1; i <= 100; i++) {
        enteros.push_back(i);
    }

    std::ofstream file("out.txt", std::ostream::out | std::ostream::app);

    IntThreadSafeBlockingQueue pares;
    ListParser list_parser(enteros, pares);
    FileWritter file_writter(file, pares);

    std::thread t1(list_parser);
    std::thread t2(file_writter);

    t1.join();
    t2.join();

    file.close();
    return 0;
}