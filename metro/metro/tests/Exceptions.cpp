#include "Exceptions.h"

metro::TestException::TestException(const char *msg) : runtime_error(msg) {}


metro::MethodDidntMatchTheReferenceException::MethodDidntMatchTheReferenceException(metro::RouteSearchMethod method,
                                                                                    metro::RouteSearchMethod reference_method)
        :
        TestException("The search method did not match the reference method") {
    this->method = method;
    this->reference_method = reference_method;
}
