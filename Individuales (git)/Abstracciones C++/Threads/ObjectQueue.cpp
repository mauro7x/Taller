#include "ObjectQueue.h"

//-----------------------------------------------------------------------------
#include <queue>
#include <mutex>
#include <condition_variable>

#include <exception>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

ObjectQueue::ObjectQueue() : permanently_closed(false) {}


void ObjectQueue::push(Object object) {
    std::unique_lock<std::mutex> l(m);
    queue.push(object);
    cv.notify_all();
}


Object ObjectQueue::pop() {
    std::unique_lock<std::mutex> l(m);
    while (queue.empty()) {
        if (permanently_closed) {
            std::exception QueueClosed;
            throw QueueClosed;
        }

        cv.wait(l);
    }

    Object object = queue.front();
    queue.pop();
    return object;
}


void ObjectQueue::close() {
    std::unique_lock<std::mutex> l(m);
    permanently_closed = true;
    cv.notify_all();
}


ObjectQueue::~ObjectQueue() {}

//-----------------------------------------------------------------------------
