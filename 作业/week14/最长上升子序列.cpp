#include <iostream>
using namespace std;

/* UPLOAD START */

int longestSubsequenceLength(int* arr, int n){
    if(n==0)return 0;
    int* sub = new int[n];
    for(int i=0;i<n;i++)
    {
        sub[i] = 1;
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(arr[i]>arr[j])
            {
                sub[i] = max(sub[i],sub[j]+1);
            }
        }
    }
    int max = 1;
    for(int i=0;i<n;i++)
    {
        if(sub[i]>max)
        {
            max = sub[i];
        }
    }
    delete [] sub;
    return max;
}

/* UPLOAD END */

void test1(){
    int a[8] = {10,9,2,5,3,7,101,18};
    cout << longestSubsequenceLength(a,8) << endl; //4
}

void test2(){
    int a[7] = {1,2,3,5,3,7,8};
    cout << longestSubsequenceLength(a,7) << endl; //6
}

int main(){
    test1();
    test2();
    return 0;
}