#include <iostream>
using namespace std;

/* Question 1 UPLOAD START */
int mod(int n,int mod_num)
{
    return (n % mod_num + mod_num) % mod_num;
}

int numStepsToN_v2(int N, int mod_num){
    // calculate the number of ways to get to N
    // allowed step on each move: +1, +2, +3
    // However, no two consecutive steps are the same.
    if(N==0||N==1||N==2)return mod(1,mod_num);
    int sum1[N+1],sum2[N+1],sum3[N+1];
    for(int i=0;i<N;i++)
    {
        sum1[i]=-1;
        sum2[i]=-1;
        sum3[i]=-1;
    }
    sum1[0]=0;sum1[1]=1;sum1[2]=0;sum1[3]=1;
    sum2[0]=0;sum2[1]=0;sum2[2]=1;sum2[3]=1;
    sum3[0]=0;sum3[1]=0;sum3[2]=0;sum3[3]=1;
    for(int i=4;i<=N;i++)
    {
        sum1[i]=mod(sum2[i-1]+sum3[i-1],mod_num);
        sum2[i]=mod(sum1[i-2]+sum3[i-2],mod_num);
        sum3[i]=mod(sum1[i-3]+sum2[i-3],mod_num);
    }
    return mod(sum1[N]+sum2[N]+sum3[N],mod_num);
}

/* Question 1 UPLOAD END */

int main(){
    for(int i=0;i<=10;i++)
        cout << i << ": " << numStepsToN_v2(i,9999999) << endl;
    return 0;
}

/*
0: 1
1: 1
2: 1
3: 3
4: 3
5: 4
6: 8
7: 9
8: 12
9: 21
10: 27
*/
