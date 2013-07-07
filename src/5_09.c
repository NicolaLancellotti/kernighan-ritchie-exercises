#include <assert.h>

static int daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

int is_leap_year(int year) {
  return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int is_date_correct(int year, int month, int day) {
  return !(year < 1 || month < 1 || month > 12 || day < 1 ||
           day > daytab[is_leap_year(year)][month]);
}

int is_yearday_correct(int year, int yearday) {
  return !(year < 1 || yearday < 1 || (!is_leap_year(year) && yearday > 365) ||
           yearday > 366);
}

int day_of_year(int year, int month, int day) {
  if (!is_date_correct(year, month, day)) {
    return -1;
  }
  int is_leap = is_leap_year(year);
  int *p = &daytab[is_leap][1];
  int *end = &daytab[is_leap][month];
  while (p < end) {
    day += *(p++);
  }
  return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday) {
  if (!is_yearday_correct(year, yearday)) {
    return -1;
  }
  int *january = &daytab[is_leap_year(year)][1];
  int *p = january;
  while (yearday > *p) {
    yearday -= *p;
    p++;
  }
  *pmonth = p - january + 1;
  *pday = yearday;
  return 1;
}

int main() {
  assert(!is_date_correct(0, 1, 1));
  assert(!is_date_correct(2000, 0, 1));
  assert(!is_date_correct(2000, 13, 1));
  assert(!is_date_correct(2000, 1, 0));
  assert(!is_date_correct(2000, 1, 32));
  assert(!is_date_correct(2001, 2, 29));
  assert(is_date_correct(2000, 2, 29));

  assert(!is_yearday_correct(-1, 1));
  assert(!is_yearday_correct(1, 0));
  assert(!is_yearday_correct(2000, 367));
  assert(!is_yearday_correct(2001, 366));

  assert(day_of_year(2000, 12, 31) == 366);
  assert(day_of_year(2004, 12, 31) == 366);
  assert(day_of_year(2001, 12, 31) == 365);
  assert(day_of_year(2100, 12, 31) == 365);
  assert(day_of_year(2000, 2, 2) == 33);

  for (int year = 1; year < 3000; ++year) {
    for (int month = 1; month < 13; ++month) {
      for (int day = 1; day < 33; ++day) {
        int yearday = day_of_year(year, month, day);
        if (yearday != -1) {
          int m, d;
          month_day(year, yearday, &m, &d);
          assert(month == m && day == d);
        }
      }
    }
  }
}
