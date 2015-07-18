#include "Date.h"
#include <sstream>
#include <stdlib.h>

bool isLeapYear(int year) {
  if (!(year % 100)) {
    if (!(year % 400)) {
      return true;
    } else {
      return false;
    }
  } else {
    if (!(year % 4)) {
      return true;
    } else {
      return false;
    }
  }
}
int daysOfMonth(int month, bool isLeapYear) {
  switch(month) {
  case 1 :
    return 31;
    break;
  case 2 :
    if (isLeapYear) {
      return 29;
    } else {
      return 28;
    }
    break;
  case 3:
    return 31;
    break;
  case 4 :
    return 30;
    break;
  case 5 :
    return 31;
    break;
  case 6 :
    return 30;
    break;
  case 7 :
    return 31;
    break;
  case 8 :
    return 31;
    break;
  case 9 :
    return 30;
    break;
  case 10 :
    return 31;
    break;
  case 11 :
    return 30;
    break;
  case 12:
    return 31;
    break;
  }
}
    
Date::Date() {
  year_ = 0;
  month_ = 0;
  day_ = 0;
  hour_ = 0;
  minute_ = 0;
}
Date::Date(int y, int m, int d, int h, int mi) {
  year_ = y;
  month_ = m;
  day_ = d;
  hour_ = h;
  minute_ = mi;
}
int Date::getYear(void) const {
  return year_;
}
void Date::setYear(int year) {
  year_ = year;
}
int Date::getMonth(void) const {
  return month_;
}
void Date::setMonth(int month) {
  month_ = month;
}
int Date::getDay(void) const {
  return day_;
}
void Date::setDay(int day) {
  day_ = day;
}
int Date::getHour(void) const {
  return hour_;
}
void Date::setHour(int hour) {
  hour_ = hour;
}
int Date::getMinute(void) const {
  return minute_;
}
void Date::setMinute(int minute) {
  minute_ = minute;
}
bool Date::isValid(Date date) {
  if (date.year_ > 9999 || date.year_ <1000) return false;
  bool judge = isLeapYear(date.year_);
  if (date.month_ > 12 || date.month_ < 1) return false;
  if (date.day_ > daysOfMonth(date.month_, judge) ||
      date.day_ < 1) return false;
  if (date.hour_ > 23 || date.hour_ < 0) return false;
  if (date.minute_ > 59 || date.minute_ < 0) return false;
  return true;
}
Date Date::stringToDate(std::string dateString) {
  Date newDate;
  std::string tem;
  std::stringstream ss;
  int num;
  std::string::iterator iter = dateString.begin();
  for (; *iter != '-'; iter++) {  // set the year
    tem.push_back(*iter);
  }
  ss << tem;
  ss >> num;
  newDate.setYear(num);
  ss.str("");
  ss.clear();
  tem = "";
  for (iter++; *iter != '-'; iter++) {  // set the month
    tem.push_back(*iter);
  }
  ss << tem;
  ss >> num;
  newDate.setMonth(num);
  ss.str("");
  ss.clear();
  tem = "";
  for (iter++; *iter != '/'; iter++) {  // set the day
    tem.push_back(*iter);
  }
  ss << tem;
  ss >> num;
  newDate.setDay(num);
  ss.str("");
  ss.clear();
  tem = "";
  for (iter++; *iter != ':'; iter++) {  // set the hour
    tem.push_back(*iter);
  }
  ss << tem;
  ss >> num;
  newDate.setHour(num);
  ss.str("");
  ss.clear();
  tem = "";
  for (iter++; iter != dateString.end(); iter++) {  // set the minute
    tem.push_back(*iter);
  }
  ss << tem;
  ss >> num;
  newDate.setMinute(num);
  ss.str("");
  ss.clear();
  tem = "";
  return newDate;
}
std::string Date::dateToString(Date date) {
  std::string tem, sum;
  std::stringstream ss;
  ss << date.year_;  // input the year
  ss >> tem;
  sum += tem;
  sum += "-";
  if (date.month_ < 10) sum += "0";  // input the month
  ss.str("");  // clear the ss
  ss.clear();
  tem.clear();
  ss << date.month_;
  ss >> tem;
  sum += tem;
  sum += "-";
  if (date.day_ < 10) sum += "0";  // input the day
  ss.str("");  // clear the ss
  ss.clear();
  tem.clear();
  ss << date.day_;
  ss >> tem;
  sum += tem;
  sum += "/";
  if (date.hour_ < 10) sum += "0";  // input the hour
  ss.str("");  // clear the ss
  ss.clear();
  tem.clear();
  ss << date.hour_;
  ss >> tem;
  sum += tem;
  sum += ":";
  if (date.minute_ < 10) sum += "0";  // input the minute
  ss.str("");  // clear the ss
  ss.clear();
  tem.clear();
  ss << date.minute_;
  ss >> tem;
  sum += tem;
  return sum;
}
Date& Date::operator=(const Date& date) {
  if (this != &date) {
    this -> year_ = date.year_;
    this -> month_ = date.month_;
    this -> day_ = date.day_;
    this -> hour_ = date.hour_;
    this -> minute_ = date.minute_;
  }
  return *this;
}
bool Date::operator==(const Date& date) const {
  if (year_ != date.year_) return false;
  if (month_ != date.month_) return false;
  if (day_ != date.day_) return false;
  if (hour_ != date.hour_) return false;
  if (minute_ != date.minute_) return false;
  return true;
}
bool Date::operator>(const Date& date) const {
  if (year_ > date.year_) {
    return true;
  } else if (year_ < date.year_) {
    return false;
  } else {
    if (month_ > date.month_) {
      return true;
    } else if (month_ < date.month_) {
      return false;
    } else {
      if (day_ > date.day_) {
	return true;
      } else if (day_ < date.day_) {
	return false;
      } else {
	if (hour_ > date.hour_) {
	  return true;
	} else if (hour_ < date.hour_) {
	  return false;
	} else {
	  if (minute_ > date.minute_) {
	    return true;
	  } else {
	    return false;
	  }
	}
      }
    }
  }
}
bool Date::operator<(const Date& date) const {
  if (*this > date) {
    return false;
  } else {
    return true;
  }
}
bool Date::operator>=(const Date& date) const {
  if (*this > date || *this == date) {
    return true;
  } else {
    return false;
  }
}
bool Date::operator<=(const Date& date) const {
  if (*this < date || *this == date) {
    return true;
  } else {
    return false;
  }
}
