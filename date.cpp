#include "date.hpp"
#include "exceptions.hpp"

int Date::getYear() const noexcept {
    return this->year;
}

int Date::getMonth() const noexcept {
    return this->month;
}

int Date::getDay() const noexcept {
    return this->day;
}

bool Date::isDateValid() const noexcept {
    if (year < 0) {return false;}
    if (month < 1 or month > 12) {return false;}
    if (day < 1 || day > 31) {return false;}
    if (month == 2) {
        if  ((year % 4 != 0) && day > 28) {return false;}
        if  (((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && day > 29) {return false;}
    } else {
        if ((month / 8 + month) % 2 == 1) {
            return day < 32;
        }
        else {
            return day < 31;
        }
    }
    return true;
}

Date::operator bool() const noexcept {
    return isDateValid();
}

bool Date::operator<(const Date &rhs) const noexcept {
    if (this->year < rhs.getYear()) {
        return true;
    }
    if (this->month < rhs.getMonth()) {
        return true;
    }
    if (this->day < rhs.getDay()) {
        return true;
    }
    return false;
}

bool Date::operator>(const Date &rhs) const noexcept {
    return rhs < *this;
}

bool Date::operator==(const Date &rhs) const noexcept {
    return !(rhs < *this || *this < rhs);
}

bool Date::operator<=(const Date &rhs) const noexcept {
    return !(rhs < *this);
}

bool Date::operator>=(const Date &rhs) const noexcept {
    return !(*this < rhs);
}

Date* dateBuilder(const int year, const int month, const int day) {
    Date* date = new Date(year, month, day);
    if (date->isDateValid()) {
        return date;
    } else {
        throw bad_date_exception();
    }
}

inline short generateNumBetween(const short min, const short max) noexcept {
    return (rand() % (max - min + 1)) + min;
}

Date* tryToGenerateDate(const short year, const short month, const short day, const int max_tries) {
    static int tries = 0;
    for (; tries < max_tries; ++tries) {
        try {
            Date* random_date = dateBuilder(year, month, day);
            tries = 0;
            return random_date;
        }
        catch (const bad_date_exception &e) {
            return nullptr;
        }
    }
    throw terrible_random_exception();
}

Date* dateGenerator(const Date date_min, const Date date_max) {
    const int max_tries = 10;
    while (true) {
        if (date_min > date_max) {throw std::runtime_error("The max date has to be greater than the min date!");}
        short random_year = generateNumBetween(date_min.getYear(), date_max.getYear());
        if (date_min.getYear() == date_max.getYear()) {
            short random_month = generateNumBetween(date_min.getMonth(), date_max.getMonth());
            if (date_min.getMonth() == date_max.getMonth()) {
                short random_day = generateNumBetween(date_min.getDay(), date_max.getDay());
                return tryToGenerateDate(random_year, random_month, random_day, max_tries);
            }
            else {
                short random_day = generateNumBetween(0, 31);
                return tryToGenerateDate(random_year, random_month, random_day, max_tries);
            }
        }
        else {
            short random_month = generateNumBetween(1, 12);
            short random_day;
            if ((random_month / 8 + random_month) % 2 == 1) {
                random_day = generateNumBetween(0, 31);
            } else {
                random_day = generateNumBetween(0, 30);
            }
            return tryToGenerateDate(random_year, random_month, random_day, max_tries);
        }
    }
}