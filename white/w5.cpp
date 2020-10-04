#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Date {
 public:
  Date() {}

  Date(const int &y, const int &m, const int &d) {
    year = y;
    month = m;
    day = d;
  }

  int year;
  int month;
  int day;

  friend bool operator==(const Date &lhs, const Date &rhs);
  friend bool operator!=(const Date &lhs, const Date &rhs);
  friend bool operator<(const Date &lhs, const Date &rhs);
};

bool operator<(const Date &lhs, const Date &rhs) {
  if (lhs.year < rhs.year) {
    // <
    return true;
  } else if (lhs.year > rhs.year) {
    // >
    return false;
  } else {
    // ==
    if (lhs.month < rhs.month) {
      // <
      return true;
    } else if (lhs.month > rhs.month) {
      // >
      return false;
    } else {
      // ==
      if (lhs.day < rhs.day) {
        // <
        return true;
      } else if (lhs.day > rhs.day) {
        // >
        return false;
      } else {
        return false;
      }
    }
  }
}

bool operator==(const Date &lhs, const Date &rhs) {
  if ((lhs.year == rhs.year) && (lhs.month == rhs.month) &&
      (lhs.day == rhs.day)) {
    return true;
  } else {
    return false;
  }
}

bool operator!=(const Date &lhs, const Date &rhs) { return !(lhs == rhs); }

class Database {
 public:
  void AddEvent(const Date &date, const string &event);
  bool DeleteEvent(const Date &date, const string &event);
  int DeleteDate(const Date &date);

  /* ??? */  // Find(const Date &date) const;

  void Print() const;
};
map<Date, set<string>> db;

Date ConvertDate(const string &date_stream);
int CheckDate(void);

// Add Дата Событие
void CmdAdd(const vector<string> &new_cmd) {
  db[ConvertDate(new_cmd[1])].insert(new_cmd[2]);
}

// Print
void CmdPrint(const vector<string> &new_cmd) {
  for (auto [key, value] : db) {
    for (auto s : value) {
      cout << setfill('0');
      cout << setw(4) << key.year << "-" << setw(2) << key.month << "-"
           << setw(2) << key.day;
      cout << " " << s << endl;
    }
  }
}

// Find Дата
void CmdFind(const vector<string> &new_cmd) {
  Date date = ConvertDate(new_cmd[1]);
  if (db.count(date) > 0) {
    for (auto i : db.at(date)) {
      cout << i << endl;
    }
  }
}

// Del Дата
void CmdDel(const vector<string> &new_cmd) {
  if (new_cmd.size() <= 2) {
    // Del Дата
    Date date = ConvertDate(new_cmd[1]);
    int n = 0;
    if (db.count(date) > 0) {
      n = db[date].size();
      db.erase(date);
    }
    cout << "Deleted " << n << " events" << endl;
  } else {
    // Del Дата Событие
    Date date = ConvertDate(new_cmd[1]);
    if (db.count(date) > 0) {
      if (db[date].count(new_cmd[2]) > 0) {
        db[date].erase(new_cmd[2]);
        cout << "Deleted successfully" << endl;
      } else {
        cout << "Event not found" << endl;
      }
    } else {
      cout << "Event not found" << endl;
    }
  }
}

void ProcessCmd(const string &input) {
  // Debug
  /*
    cout << "Input: ";
    for (auto e : new_cmd) {
      cout << e << " ";
    }
    cout << endl;
  */
  vector<string> cmd;
  string tmp;
  stringstream ss(input);

  if (input.empty()) {
    return;
  }

  while (getline(ss, tmp, ' ')) {
    cmd.push_back(tmp);
  }

  try {
    if (cmd[0] == "Add") {
      CmdAdd(cmd);
    } else if (cmd[0] == "Del") {
      CmdDel(cmd);
    } else if (cmd[0] == "Find") {
      CmdFind(cmd);
    } else if (cmd[0] == "Print") {
      CmdPrint(cmd);
    } else {
      throw invalid_argument("Unknown command: " + cmd[0]);
    }
  } catch (invalid_argument &e) {
    cout << e.what() << endl;
    exit(2);
  }
}

int main() {
  Database db;
  string command;

  if (CheckDate() != 0) {
    cout << "Date check fails" << endl;
    return 0;
  }

  while (getline(cin, command)) {
    // cout << "Input: " << command << endl;
    ProcessCmd(command);
  }
  return 0;
}

int CheckDate(void) {
  try {
    Date date(1, 1, 1);
    string tmp = "1-1-1";
    if (date != ConvertDate(tmp)) {
      cout << "Failed for \"" << tmp << "\" date" << endl;
      return 2;
    }

    date = Date(1, 1, 1);
    tmp = "1-+1-+1";
    if (date != ConvertDate(tmp)) {
      cout << "Failed for \"" << tmp << "\" date" << endl;
      return 2;
    }

    date = Date(-1, 1, 1);
    tmp = "-1-+1-+1";
    if (date != ConvertDate(tmp)) {
      cout << "Failed for \"" << tmp << "\" date" << endl;
      return 2;
    }

    date = Date(1, 1, 1);
    tmp = "+1-+1-+1";
    if (date != ConvertDate(tmp)) {
      cout << "Failed for \"" << tmp << "\" date" << endl;
      return 2;
    }
  } catch (invalid_argument &) {
    return 2;
  }

  // Negative
  try {
    string tmp[] = {"1--13-1", "1--1-33", "1--1-1",  "1-1--1",
                    "1---1-1", "1---0-1", "1---0-0", "1---0-1"};

    for (auto t : tmp) {
      ConvertDate(t);
      cout << "Failed for \"" << tmp << "\" date" << endl;
      return 2;
    }
  } catch (invalid_argument &) {
    // Fall throug
  }

  // cout << "OK" << endl;
  return 0;
}

Date ConvertDate(const string &date_stream) {
  stringstream ss(date_stream);
  Date date;
  bool n = false;
  string tmp;

  /*
    if (ss.peek() == '-') {
      ss.ignore(1);
      n = true;
    }

    if (ss.peek() == '+') {
      ss.ignore(1);
    }
  */

  ss >> date.year;
  if (!ss) {
    throw invalid_argument("Wrong date format: " + date_stream);
  }
  if (n) {
    date.year *= -1;
  }

  // Check separator
  if (ss.peek() == '-') {
    ss.ignore(1);
  } else {
    throw invalid_argument("Wrong date format: " + date_stream);
  }

  if (ss.peek() == '+') {
    ss.ignore(1);
  }
  ss >> date.month;
  if (!ss) {
    throw invalid_argument("Wrong date format: " + date_stream);
  }

  // Check separator
  if (ss.peek() == '-') {
    ss.ignore(1);
  } else {
    throw invalid_argument("Wrong date format: " + date_stream);
  }

  /*
  if (ss.peek() == '+') {
    ss.ignore(1);
  }
  */
  ss >> date.day;
  if (!ss) {
    throw invalid_argument("Wrong date format: " + date_stream);
  }

  if ((date.month < 1) || (date.month > 12)) {
    throw invalid_argument("Month value is invalid: " + to_string(date.month));
  }

  if ((date.day < 1) || (date.day > 31)) {
    throw invalid_argument("Day value is invalid: " + to_string(date.day));
  }

  ss >> tmp;
  if (!tmp.empty()) {
    throw invalid_argument("Wrong date format: " + date_stream);
  }

  return date;
}
