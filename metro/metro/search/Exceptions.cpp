#include "Exceptions.h"

metro::SearchException::SearchException(const char *msg) : runtime_error(msg) {}


metro::InvalidSearchMethodException::InvalidSearchMethodException() : SearchException(
        "Invalid search method selected"
) {}
