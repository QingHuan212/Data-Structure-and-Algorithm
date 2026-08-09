#include <iostream>
#include <string>
using namespace std;

/* UPLOAD START */

void makePalindrome(string s) {
    int z, n, i=0,j,c=1;
    for (i = 0; i < s.length(); i++)
    {
        if (s[i] != s[s.length() - i - 1])c = 0;
    }
    if (c == 1)
    {
        for (j = 0; j < s.length(); j++)
        {
            cout << s[j];
        }
        cout << endl;
    }
    else
    {
        for(i=0;i<s.length();i++)
        {
            for (j = 0; j < s.length() - i; j++)
            {
                if (s[i + j] != s[s.length() - j - 1])
                {
                    c = 0;
                    break;
                }
                c = 1;
            }
            if (c == 1)break;
        }
        for (j = 0; j < s.length(); j++)
        {
            cout << s[j];
        }
        i -= 1;
        for (i; i >= 0; i--)
        {
            cout << s[i];
        }
        cout << endl;
    }
}

/* UPLOAD END */

int main() {
    int x;
    cin >> x;
    switch (x) {
    case 1:
        makePalindrome("A");
        makePalindrome("ABA");
         break;
    case 2:
        makePalindrome("AB");
        makePalindrome("ABC");
         break;
    case 3:
        makePalindrome("ABCB");
        makePalindrome("ABCC");
    default:;
    }
    return 0;
}