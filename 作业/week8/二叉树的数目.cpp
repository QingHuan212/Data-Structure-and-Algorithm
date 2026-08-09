#include <iostream>
using namespace std;

/* Question 2 UPLOAD START */
int mod(int n)
{
    return (n % 30011 + 30011) % 30011;
}

int numOfBinaryTrees(int n){
    // return the number of binary trees with n nodes mod 30011
    // max of n will be 150 in this problem
    if(n==0||n==1)return mod(1);
    int c[n+1];
    for(int i=0;i<=n;i++)
    {
        c[i]=0;
    }
    c[0]=1;c[1]=1;
    for(int i=2;i<=n;i++)
    {
        for(int j=0;j<i;j++)
        {
             c[i] = mod(c[i] + mod(c[j] * c[i - 1 - j]));
        }
    }
    return mod(c[n]);
}
/* Question 2 UPLOAD END */

void test(){
    for(int i=0;i<20;i++){
        cout << i << ": " << numOfBinaryTrees(i) << endl;
    }
}

int main(){
    test();
    return 0;
}
