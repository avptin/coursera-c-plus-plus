#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
  vector<string> result;

  auto word_begin = begin(s);
  auto word_end = end(s);
  do {
    auto word_end = find(word_begin, end(s), ' ');
    result.push_back({word_begin, word_end});
    /*
        if (word_end != end(s)) {
          word_begin = ++word_end;
        } else {
          word_begin = end(s);
        }
      } while (word_begin != end(s));
    */
    word_begin = word_end + 1;
  } while (word_end != end(s));

  return result;
}

int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;

  return 0;
}