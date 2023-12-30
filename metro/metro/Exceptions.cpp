#include "Exceptions.h"

metro::InvalidVersionException::InvalidVersionException() : std::runtime_error(
        "Metro file was saved in incompatible version of program") {
}
