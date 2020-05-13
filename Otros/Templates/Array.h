#ifndef __ARRAY_H__
#define __ARRAY_H__

//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------

template <class T, int size=64> class Array {
    private:
        T data[size];

    public:
        Array() {}
        ~Array() {}

        void set(int p, T v) {
            data[p] = v;
        }

        T get(int p) {
            return data[p];
        }

        void saludar() {
            //std::cout << "Saludar(). t = " << t << "\n";
            std::cout << "Saludar().\n";
        }
};


template<>
class Array<bool> {
    public:
        void saludar() {
            //std::cout << "Saludar(). t = " << t << "\n";
            std::cout << "Soy de booleanos jeje.\n";
        }
};

//-----------------------------------------------------------------------------
#endif //__ARRAY_H__
