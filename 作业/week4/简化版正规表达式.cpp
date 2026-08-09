#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int* getNext(string T)
{
    int tLen = T.length();
    int* next = new int[tLen];
    if (tLen == 0) return next;
    next[0] = -1;
    if (tLen == 1) return next;
    next[1] = 0;
    for (int j = 2; j < tLen; j++) {
        // calculate next[i]
        int k = next[j - 1];
        while (k != -1 && T[k] != T[j - 1]) {
            k = next[k];
        }
        next[j] = k + 1;
    }
    return next;
}
int KMP(string S, string T)
{
    int i = 0, j = 0;
    int sLen = S.length();
    int tLen = T.length();
    int* next = getNext(T);
    if (tLen == 0) return 0;
    if (sLen == 0) return -1;
    while (i < sLen && j < tLen) {
        if (j == -1 || S[i] == T[j]) {
            i++;
            j++;
        }
        else {
            j = next[j];
        }
    }
    if (j == tLen) {
        return i - j;
    }
    else
        return -1;
}
int simplePatternMatch(string s, string p)
{
    int length = 0;
    int starg = 0,w=-1;
    int *starw=new int[p.length()];
    if (s.length()==0)
    {
        return -1;
    }
    if (p.length() == 0)
    {
        return 0;
    }
    starw[0] = -1;
    for (int i = 0; i < p.length(); i++)
    {
        if (i == 0&& p[i] == '*')
        {
            starw[0] = 0;
            continue;
        }
        if (p[i] == '*')
        {
            starw[starg + 1] = i;
            starg++;
        }
    }
    starw[starg + 1] = p.length();
    //for (int i = 0; i <= starg + 1; i++)
    //{
    //    cout << starw[i] << endl;
    //}
    string zs,zp;
    for (int i = 0; i <= starg; i++)
    {
        if (starw[i] + 1 == starw[i + 1])continue;
        for (int j = starw[i]+1; j < starw[i+1]; j++)
        {
            zp.push_back(p[j]);
        }
        for (int j = length; j < s.length(); j++)
        {
            zs.push_back(s[j]);
        }
        if (i == 0) w = KMP(zs, zp);
        //cout << i << ":" << zs << endl;
        //cout << i << ":" << zp << endl;
        //cout << length << endl;
        if (KMP(zs, zp) == -1)return -1;
        length = length+KMP(zs, zp)+zp.length();
        if (length == s.length()&& starw[i + 1]!=p.length())return -1;
        zp.clear();
        zs.clear();
    }
    if (p[0] == '*')return 0;
    else return w;
}

int main() {
    int x;
    cin >> x;
    string s1 = "aaccdabbcaa";
    string s2 = "";
    switch (x) {
    case 1:
        cout << simplePatternMatch(s1+s1, "cd**aaa*ca") << endl;
        cout << simplePatternMatch(s1, "***a") << endl;
        cout << simplePatternMatch(s1, "ccdb") << endl;
        break;
    case 2:
        cout << simplePatternMatch(s1, "aa*ab") << endl;
        cout << simplePatternMatch(s1, "*cb*ca") << endl;
        cout << simplePatternMatch(s1, "aa*d") << endl;
        break;
    case 3:
        cout << simplePatternMatch(s1, "aa**aa*aa") << endl;
        cout << simplePatternMatch(s1, "ac*cb*a") << endl;
        cout << simplePatternMatch(s1, "ac*cd*ca") << endl;
    default:;
    }
    return 0;
}
