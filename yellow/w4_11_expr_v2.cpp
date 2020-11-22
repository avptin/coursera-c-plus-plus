// https://www.coursera.org/learn/c-plus-plus-yellow/programming/SwfxR/postroieniie-arifmietichieskogho-vyrazhieniia

#include <iostream>
#include <string>
#include <sstream>
#include <deque>

using namespace std;


int main (void){
    int n;
    int count;
    deque<string> exp;
    char prev = '*';

    cin >> n;
    exp.push_back(to_string(n));

    cin >> count;
    while (count != 0){
        count--;

        char tmp = cin.get();
        while ((tmp != '*') && (tmp != '+') && (tmp != '-') && (tmp != '/')){
            tmp = cin.get();
        }

        if (tmp == '*'){
            if ((prev == '+') || (prev == '-')){
                exp.push_back(")");
                exp.push_front("(");
            }
            exp.push_back(" * ");
        } else if (tmp == '+'){
            exp.push_back(" + ");
        } else if (tmp == '-'){
            exp.push_back(" - ");
        } else if (tmp == '/'){
            if ((prev == '+') || (prev == '-')){
                exp.push_back(")");
                exp.push_front("(");
            }
            exp.push_back(" / ");
        } else {
        }

        cin >> n;
        exp.push_back(to_string(n));
        prev = tmp;
    }

    for (const auto& e : exp){
        cout << e;
    }
    cout << endl;

    return 0;
}