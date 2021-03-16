#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


string s, s1, s2, mist, why = " ";
int fl = 0, n, fi = 0, mi = 0;

void check ()
{
    int k = 0, zn = 0, pzn = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == ' ') k++;


        if (s[i] != '+' && s[i] != '-' && s[i] != '/' &&
             s[i] != '*' && s[i] != ' ' && s[i] != '0' &&
              s[i] != '1' && s[i] != '2' && s[i] != '3' &&
               s[i] != '4' && s[i] != '5' && s[i] != '6' &&
                s[i] != '7' && s[i] != '8' && s[i] != '9')
                {
                    mist[i] = '^';
                    why = "Error: unsupported operator.";
                    return;
                }


        if (s[i] == '+' || s[i] == '-' || s[i] == '/' || s[i] == '*')
        {

            if (s[i] != '-' || (s[i] != '-' || (s[i+1] != '0' &&
                                                s[i+1] != '1' && s[i+1] != '2' && s[i+1] != '3' &&
                                                s[i+1] != '4' && s[i+1] != '5' && s[i+1] != '6' &&
                                                s[i+1] != '7' && s[i+1] != '8' && s[i+1] != '9')))
                                                    {
                                                        zn++;
                                                        pzn++;
                                                    }

        }


        if (pzn == 2 && zn <= 1)
        {
            mist[i] = '^';
            why = "Error: expected end of expression.";
            return;
        }


        if (s[i] != '+' && s[i] != '-' && s[i] != '/' && s[i] != '*' && s[i] != ' ' && k != 0 && zn == 0)
        {
            int j = i - 1;
            while (s[j] == ' ')
            {
                mist[j] = '^';
                j--;
            }
            why = "Error: expected operator.";
            return;
        }
        if (s[i] != '+' && s[i] != '-' && s[i] != '/' && s[i] != '*' && s[i] != ' ' && zn > 1)
        {
            int j = i;
            while (s[j] != '+' && s[j] != '-' && s[j] != '/' && s[j] != '*')
            {
                j--;
                if (s[j] == '+' || s[j] == '-' || s[j] == '/' || s[j] == '*')
                {
                    while (s[j - 1] == '+' || s[j - 1] == '-' || s[j - 1] == '/' || s[j - 1] == '*')
                        j--;
                    mist[j + 1] = '^';
                    why = "Error : extra sign.";
                    return;
                }
            }
        }
        if (s[i] != '+' && s[i] != '-' && s[i] != '/' && s[i] != '*' && s[i] != ' ' && (k == 0 || zn != 0))
        {
            k = 0;
            zn = 0;
        }
    }

}

int main()
{
    char sign = ' ';
    getline(cin,s);
    mist.resize(s.size());
    n = s.size();
    check();
    mi = 0;
    fi = 0;
    if (s[0] == '-' && (s[1] == '0' || s[1] == '1' ||
                        s[1] == '2' || s[1] == '3' ||
                        s[1] == '4' || s[1] == '5' ||
                        s[1] == '6' || s[1] == '7' ||
                        s[1] == '8' || s[1] == '9'))
                        {
                        fi = 1;
                        }

    for (int i = fi; i < n; i++)
    {
//        cout << s[i];
        if (sign != ' ' && s[i] != '-') s2 += s[i];
        if (s[i] == '+' || s[i] == '-' || s[i] == '/' || s[i] == '*') fl++;
        if (fl == 0) s1 += s[i];
        if (s[i] == '-' && sign != ' ') mi = 1;
        else
        if (s[i] == '+' || s[i] == '-' || s[i] == '/' || s[i] == '*') sign = s[i];

    }

    if (why != " ")
    {
        cout << mist << endl;
        cout << why;
        return 0;
    }

    int a,b;
    a = atoi(s1.c_str());
    b = atoi(s2.c_str());
    if (fi == 1) a *= -1;
    if (mi == 1) b *= -1;
    if (sign == '+') cout << a + b;
    if (sign == '*') cout << a * b;
    if (sign == '-') cout << a - b;
    if (sign == '/') cout << a / b;
    return 0;
}
