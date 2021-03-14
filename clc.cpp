#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;


int main()
{
    string s, s1, s2;
    char sign;
    getline(cin,s);
    int n = s.size();
    int fl = 0;
    for (int i = 0; i < n; i++)
    {
        if (fl == 0) s1 += s[i];
        if (fl == 1) sign = s[i];
        if (fl == 3) s2 += s[i];
        if (s[i] == ' ' || s[i] == '+' || s[i] == '-' || s[i] == '/' || s[i] == '*') fl++;

    }
    int a,b;
    a = atoi(s1.c_str());
    b = atoi(s2.c_str());
    cout << a << ' ' << b;
    return 0;
}
