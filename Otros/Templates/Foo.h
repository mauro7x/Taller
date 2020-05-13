#ifndef __FOO_H__
#define __FOO_H__

//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------

template<class T> void foo(T t) {
    std::cout << t << "\n";
}

template <> void foo<char>(char c) {
    std::cout << "Especializacion para char!" << "\n";
}

//-----------------------------------------------------------------------------
#endif // __FOO_H__
