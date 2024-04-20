#ifndef DATE_H
#define DATE_H

class Date {
    private:
        short year; 
        short month;
        short day;
    
    public:
        Date(short year, short month, short day): year(year), month(month), day(day) {}
        int getYear() const noexcept;
        int getMonth() const noexcept;
        int getDay() const noexcept;
        bool isDateValid() const noexcept;
        explicit operator bool() const noexcept;
        bool operator<(const Date& rhs) const noexcept;
        bool operator>(const Date& rhs) const noexcept;
        bool operator==(const Date& rhs) const noexcept;
        bool operator<=(const Date& rhs) const noexcept;
        bool operator>=(const Date& rhs) const noexcept;
};

Date* dateGenerator(const Date date_min, const Date date_max);
Date* dateBuilder(const int year, const int month, const int day);
Date* tryToGenerateDate(const short year, const short month, const short day, const int max_tries);
inline short generateNumBetween(const short min, const short max) noexcept;

int process_date(const Date& date);

#endif // DATE_H