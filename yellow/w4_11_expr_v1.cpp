// https://www.coursera.org/learn/c-plus-plus-yellow/programming/SwfxR/postroieniie-arifmietichieskogho-vyrazhieniia

#include <iostream>
#include <string>
#include <sstream>
#include <deque>

using namespace std;

int main (void){
    int n;
    int count;
    string tmp;
    deque<string> exp;

    cin >> n;
    exp.push_back(to_string(n));

    cin >> count;
    if (count != 0) {
        exp.push_back(")");
        exp.push_front("(");
    }

    while (count != 0){
        count--;

        char tmp = cin.get();
        while ((tmp != '*') && (tmp != '+') && (tmp != '-') && (tmp != '/')){
            tmp = cin.get();
        }
        if (tmp == '*'){
            exp.push_back(" * ");
        } else if (tmp == '+'){
            exp.push_back(" + ");
        } else if (tmp == '-'){
            exp.push_back(" - ");
        } else if (tmp == '/'){
            exp.push_back(" / ");
        } else {
        }

        cin >> n;
        exp.push_back(to_string(n));
        if (count != 0){
            exp.push_back(")");
            exp.push_front("(");
        }
    }

    for (const auto& e : exp){
        cout << e;
    }

    cout << endl;
    return 0;
}