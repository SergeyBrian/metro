#ifndef METRO_EXCEPTIONS_H
#define METRO_EXCEPTIONS_H

#include <stdexcept>

namespace metro {
    class InvalidVersionException : public std::runtime_error {
    public:
        InvalidVersionException();
    };
}

#endif //METRO_EXCEPTIONS_H
