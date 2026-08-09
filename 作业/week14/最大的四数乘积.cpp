#include <iostream>
#include <stdlib.h>
using namespace std;

/* UPLOAD START */

int quickhelp(int* &arr,int n,int st,int ed)
{
    int le=st;
    int ri=ed;
    while(le<ri)
    {
        while(le<ri && arr[le]<=arr[ri])ri--;
        if(le<ri)
        {
            int tmp = arr[le];
            arr[le] = arr[ri];
            arr[ri] = tmp;
        }
        while(le<ri && arr[le]<=arr[ri])le++;
        if(le<ri)
        {
            int tmp = arr[le];
            arr[le] = arr[ri];
            arr[ri] = tmp;
        }
    }
    return le;
}

void quicksort(int* &arr,int n,int st,int ed)
{
    if(st>=ed)return;
    int div=quickhelp(arr,n,st,ed);
    quicksort(arr,n,st,div-1);
    quicksort(arr,n,div+1,ed);
}

int maxQuadProduct(int* arr, int n){
    quicksort(arr,n,0,n-1);
    return max(arr[n-1]*arr[n-2]*arr[n-3]*arr[n-4],max(arr[n-1]*arr[n-2]*arr[1]*arr[0],arr[0]*arr[1]*arr[2]*arr[3]));
}

/* UPLOAD END */

void test1(){
    int tmp1[7] = {3,7,5,1,9,10,2};
    int tmp4[10] = {-10,-8,-2,0,3,9,15,1,7,4};
    cout << "Case 1: Maximum product is " << maxQuadProduct(tmp1,7) << endl;
    cout << "Case 4: Maximum product is " << maxQuadProduct(tmp4,10) << endl;
    for(int i=0;i<10;i++)
    {
        cout<<tmp4[i]<<" ";
    }
    cout << endl;
}

int main()
{
    test1();
    return 0;
}
