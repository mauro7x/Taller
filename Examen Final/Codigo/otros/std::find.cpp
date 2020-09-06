#include <algorithm>
#include <iostream>
#include <list>

template <class T>
std::list<T> intersect(const std::list<T>& a, const std::list<T>& b) {
    std::list<T> res;
    for (auto it = a.begin(); it != a.end(); it++) {
        if (std::find(b.begin(), b.end(), *it) != b.end()) {
            res.push_back(*it);
        }
    }

    return res;
}

int main(int argc, char* argv[]) {
    std::list<int> a = {1, 2, 3, 4, 5};
    std::list<int> b = {2, 4};
    std::list<int> c = intersect(a, b);

    for (auto it : c) {
        std::cout << it << std::endl;
    }

    return 0;
}
