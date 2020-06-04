#ifndef __PARTICULAR_H__
#define __PARTICULAR_H__

//-----------------------------------------------------------------------------
#include "Exception.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

class Particular : public Exception {
   public:
    template <typename... Args>
    explicit Particular(const char* fmt, Args&&... args) noexcept
        : Exception(fmt, std::forward<Args>(args)...) {}
};

//-----------------------------------------------------------------------------
#endif  // __PARTICULAR_H__
