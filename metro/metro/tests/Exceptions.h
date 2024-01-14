#ifndef METRO_TEST_EXCEPTIONS_H
#define METRO_TEST_EXCEPTIONS_H

#include <stdexcept>
#include "../search/Search.h"

namespace metro {
    class TestException : public std::runtime_error {
    public:
        explicit TestException(const char *msg);
    };

    class MethodDidntMatchTheReferenceException : TestException {
    public:
        MethodDidntMatchTheReferenceException(RouteSearchMethod method, RouteSearchMethod reference_method);

        RouteSearchMethod method;
        RouteSearchMethod reference_method;
    };
}

#endif //METRO_TEST_EXCEPTIONS_H
