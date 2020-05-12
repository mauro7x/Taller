#include "ProtectedObject.h"

//-----------------------------------------------------------------------------

ProtectedObject::ProtectedObject() {}


void ProtectedObject::criticalSectionMethod() {
    std::unique_lock<std::mutex> l(m);
    // Hacer cosas
}


ProtectedObject::~ProtectedObject() {}       


//-----------------------------------------------------------------------------
