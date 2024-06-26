#ifndef _AUTOMATIC_DIFFERENTIATION_H
#define _AUTOMATIC_DIFFERENTIATION_H

namespace trainlib {
    template<class F>   // F is differentiable
    class NewtonWithDualNumber {
        F func;
    }
}

#endif