#include "phone_number.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

PhoneNumber::PhoneNumber(const string &international_number) {
  stringstream ss;

  ss.str(international_number);
  vector<string> tmp;
  string string_tmp;

  if (ss.get() != '+') {
    throw invalid_argument("Invalid format");
  }

  while (getline(ss, string_tmp, '-')) {
    tmp.push_back(string_tmp);
  }

  if (tmp.size() < 3) {
    throw invalid_argument("Wrong phone number format");
  }

  PhoneNumber::local_number_.clear();
  bool first = true;
  for (size_t i = 0; i < tmp.size(); i++) {
    if (i == 0) {
      PhoneNumber::country_code_ = tmp[0];
    } else if (i == 1) {
      PhoneNumber::city_code_ = tmp[1];
    } else {
      if (!first) {
        PhoneNumber::local_number_.append("-");
      }
      PhoneNumber::local_number_.append(tmp[i]);
      first = false;
    }
  }
}

string PhoneNumber::GetCountryCode() const {
  return PhoneNumber::country_code_;
}

string PhoneNumber::GetCityCode() const { return PhoneNumber::city_code_; }

string PhoneNumber::GetLocalNumber() const {
  return PhoneNumber::local_number_;
}
string PhoneNumber::GetInternationalNumber() const {
  stringstream ss;

  ss << "+" << PhoneNumber::country_code_ << "-" << PhoneNumber::city_code_
     << "-" << PhoneNumber::local_number_;

  return ss.str();
}
/*
int main() {
  PhoneNumber pn("+7-495-111-22-33");
  cout << pn.GetInternationalNumber();

  return 0;
}
*/