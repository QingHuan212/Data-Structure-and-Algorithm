#include <iostream>
using namespace std;

/* Question 3 UPLOAD START */
int mod(int n)
{
    return (n % 10000019 + 10000019) % 10000019;
}


int numOfFriendPairs(int n){
    // return the number of pairings with n people mod 10000019
    // max of n will be 150 in this problem
    if(n==0||n==1)return 1;
    int num[n+1];
    for(int i=0;i<=n;i++)
    {
        num[i]=-1;
    }
    num[0]=1;num[1]=1;num[2]=2;
    for(int i=2;i<=n;i++)
    {
        num[i]=mod(num[i-1])+mod(num[i-2]*(i-1));
        num[i]=mod(num[i]);
    }
    return num[n];
}
/* Question 3 UPLOAD END */

void test(){
    for(int i=0;i<20;i++){
        cout << (3*i) << ": " << numOfFriendPairs(3*i) << endl;
    }
}

int main(){
    test();
    return 0;
}
