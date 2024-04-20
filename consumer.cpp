#include "date.hpp"

int process_date(const Date& date) {
    static Date last_date(0, 0, 0);

    if (!last_date) {
        last_date = date;
        return 42;
    }

    if (date < last_date) {
        last_date = date;
        return -1;
    }

    if (date == last_date) {
        return 0;
    }

    last_date = date;
    return 1;
}