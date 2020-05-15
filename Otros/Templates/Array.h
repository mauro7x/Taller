#ifndef __ARRAY_H__
#define __ARRAY_H__

//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------


class Array {
    private:
        int data[64];

    public:
        Array();
        ~Array();
        void set(int p, int v);
        int get(int p);

        template <class X>
        void saludar(X x) {
            std::cout << "Generico: " << x << "\n";
        }  
};

//-----------------------------------------------------------------------------
#endif //__ARRAY_H__
