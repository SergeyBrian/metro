#ifndef METRO_EXCEPTIONS_H
#define METRO_EXCEPTIONS_H

#include <stdexcept>

namespace metro {
    class SearchException : public std::runtime_error {
    public:
        SearchException(const char *msg);
    };

    class InvalidSearchMethodException : public SearchException {
    public:
        InvalidSearchMethodException();
    };
}

#endif //METRO_EXCEPTIONS_H
