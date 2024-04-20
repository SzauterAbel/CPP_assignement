#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>

class bad_date_exception : std::runtime_error {
    public:
        bad_date_exception() : std::runtime_error("There is no such a date!") {}
};

class terrible_random_exception : std::runtime_error {
    public:
        terrible_random_exception() : std::runtime_error("The RNG does not loves you.") {}
};

#endif // EXCEPTIONS_H