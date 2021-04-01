#include <stdio.h>
#include <iostream>
#include <string>
#include <set>
using namespace std;

char sign = ' ';
string glavstr, mist, why = "";
int n;
set <char> cifri;
set <char> znaki;

// Заполняет set
void zapoln(){
    for (char i = '0'; i <= '9'; i++){
        cifri.insert(i);
    }
    znaki.insert('-');
    znaki.insert('+');
    znaki.insert('*');
    znaki.insert('/');
    znaki.insert(' ');
}

void check (){
    int kolprob = 0, kolznak = 0, pzn = 0, kolcifr = 0;
    for (int i = 0; i < n; i++){
        if (glavstr[i] == ' ' && kolcifr != 0) kolprob++;// Подсчитывание пробелов
        if (cifri.count(glavstr[i]) != 0){
            kolcifr++;   // Подсчитывание цифр
        }

        // Проверка не поставлен ли неизвестный знак.
        if (cifri.count(glavstr[i]) == 0 && znaki.count(glavstr[i]) == 0){
            mist[i] = '^';
            why = "Error: unsupported operator.";
            return;
        }

        // Подсчитывание знаков.
        if (znaki.count(glavstr[i]) != 0 && glavstr[i] != ' '){

            if (glavstr[i] != '-' || cifri.count(glavstr[i+1]) == 0){
                kolznak++;
                pzn++;
            }

        }

        // Проверяется законченно ли выражение.
        if (pzn == 2 && kolznak <= 1){
            cout << pzn << endl;
            mist[i] = '^';
            why = "Error: expected end of expression.";
            return;
        }

        // Проверяется не пропущен ли знак.
        if (znaki.count(glavstr[i]) == 0 && kolprob != 0 && kolznak == 0){
            int j = i - 1;
            while (glavstr[j] == ' '){
                mist[j] = '^';
                j--;
            }
            why = "Error: expected operator.";
            return;
        }
        // Проверяется не поставлен ли лишний знак.
        if (glavstr[i] != '+' && glavstr[i] != '-' && glavstr[i] != '/' && glavstr[i] != '*' && glavstr[i] != ' ' && kolznak > 1){
            int j = i;
            while (glavstr[j] != '+' && glavstr[j] != '-' && glavstr[j] != '/' && glavstr[j] != '*'){
                j--;
                if (glavstr[j] == '+' || glavstr[j] == '-' || glavstr[j] == '/' || glavstr[j] == '*'){
                    while (glavstr[j - 1] == '+' || glavstr[j - 1] == '-' || glavstr[j - 1] == '/' || glavstr[j - 1] == '*')
                        j--;
                    mist[j + 1] = '^';
                    why = "Error : extra sign.";
                    return;
                }
            }
        }
        if (znaki.count(glavstr[i]) == 0 && (kolprob == 0 || kolznak != 0)){
            kolprob = 0;
            kolznak = 0;
        }
    }

}

int main()
{
    zapoln();
    while (1){

        getline(cin,glavstr);

        string firstch = "",secondch = "";

        sign = ' ';

        why = "";

        if (glavstr == "quit") return 0;

        mist="";

        mist.resize(glavstr.size());

        n = glavstr.size();

        int schetchik = 0, minusfir = 0, minussec = 0;


        if ((glavstr[0] == '-' && cifri.count(glavstr[1]) == 0) || glavstr[0] == '+' || glavstr[0] == '/' || glavstr[0] == '*'){
            mist[0] = '^';
            why = "Error : extra sign.";
        }

        if (glavstr[0] == '-' && cifri.count(glavstr[1]) != 0){
            minusfir = 1;
        }

        // Проверка на ошибки.
        if (why == "") check();

        for (int i = minusfir; i < n; i++){
            if (sign != ' ' && glavstr[i] != '-') secondch += glavstr[i];

            if (glavstr[i] == '+' || glavstr[i] == '-' || glavstr[i] == '/' || glavstr[i] == '*') schetchik++;

            if (schetchik == 0) firstch += glavstr[i];

            if (glavstr[i] == '-' && sign != ' ') minussec = 1;
            else if (glavstr[i] == '+' || glavstr[i] == '-' || glavstr[i] == '/' || glavstr[i] == '*') sign = glavstr[i];
        }

        // Если есть ошибка, то программа выводит место, где была совершена ошибка, и причину ошибки.
        if (why != ""){
            int f = 0;
            for (int i = 0; i < n; i++){
                if (mist[i] != '^' || f == 1) mist[i] = '.';
                if (mist[i] == '^') f = 1;
            }
            cout << mist << endl;
            cout << why << endl;
            continue;
        }

        int _firstch, _secondch;
        _firstch = 0;
        _secondch = 0;
        _firstch = atoi(firstch.c_str());
        _secondch = atoi(secondch.c_str());

        if (minusfir == 1) _firstch *= -1;
        if (minussec == 1) _secondch *= -1;

        // Если не было совешенно ошибок, то программа выводит ответ.
        if (sign == '+') cout << _firstch + _secondch << endl;
        if (sign == '*') cout << _firstch * _secondch << endl;
        if (sign == '-') cout << _firstch - _secondch << endl;
        if (sign == '/') cout << _firstch / _secondch << endl;
    }
}
