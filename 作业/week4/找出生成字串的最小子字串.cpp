#include <iostream>
#include <string>
using namespace std;

void generate(string s)
{
    int n = s.length();
    char* t = new char[n];
    int length = 1;
    t[0] = s[0];

    if (n == 1)
    {
        cout << length << endl;
        cout << t[0];
    }
    else
    {
        int found = 0;
        while (found == 0 && length < n)
        {
            if (n % length == 0)
            {
                int k = 1;
                for (int i = length; i < n && k == 1; i++)
                {
                    if (s[i] != t[i % length])
                    {
                        k = 0;
                    }
                }
                if (k)
                {
                    found = 1;
                    break;
                }
            }
            if (found == 0)
            {
                t[length] = s[length];
                length++;
            }
        }

        cout << length << endl;
        for (int i = 0; i < length; i++)
        {
            cout << t[i];
        }
    }
    delete[] t;
}

int main()
{
    string s;
    cin >> s;
    generate(s);
    return 0;
}