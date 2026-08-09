#include <iostream>
#include <string>
using namespace std;

/* UPLOAD START */

int quickhelp(int** arr,int n,int st,int ed)
{
    int le=st;
    int ri=ed;
    while(le<ri)
    {
        while(le<ri && arr[le][0]<=arr[ri][0])ri--;
        if(le<ri)
        {
            int tmp0=arr[le][0];
            int tmp1=arr[le][1];
            arr[le][0]=arr[ri][0];
            arr[le][1]=arr[ri][1];
            arr[ri][0]=tmp0;
            arr[ri][1]=tmp1;
        }
        while(le<ri && arr[le][0]<=arr[ri][0])le++;
        if(le<ri)
        {
            int tmp0=arr[le][0];
            int tmp1=arr[le][1];
            arr[le][0]=arr[ri][0];
            arr[le][1]=arr[ri][1];
            arr[ri][0]=tmp0;
            arr[ri][1]=tmp1;
        }
    }
    return le;
}

void quicksort(int** arr,int n,int st,int ed)
{
	if(st>=ed)return;
    int div=quickhelp(arr,n,st,ed);
    quicksort(arr,n,st,div-1);
    quicksort(arr,n,div+1,ed);
}

int removesame(int**arr,int n)
{
    int length = n;
    for(int i=0;i+1<length;i++)
    {
        if(arr[i][0]==arr[i+1][0]&&arr[i][1]==arr[i+1][1])
        {
            for(int j=i+1;j+1<length;j++)
            {
                arr[j][0]=arr[j+1][0];
                arr[j][1]=arr[j+1][1];
            }
            i--;
            length--;
            continue;
        }
    }
    return length;
}

void mergeIntervals(int** arr, int n){
    /* The first interval is arr[0][0] to arr[0][1]
       The 2nd interval is arr[1][0] to arr[1][1]
       ...
       The last interval is arr[n-1][0] to arr[n-1][1]
       Print the results of merging these intervals. Assume endpoints are always included.
    */
    quicksort(arr,n,0,n-1);
    int length = removesame(arr,n);
    bool change=true;
    while(change)
    {
    	change=false;
    	for(int i=0;i+1<length;i++)
	    {
	        if(arr[i][1]>=arr[i+1][0])
	        {
	            arr[i][1]=max(arr[i][1],arr[i+1][1]);
	            for(int j=i+1;j+1<length;j++)
	            {
	                arr[j][0]=arr[j+1][0];
	                arr[j][1]=arr[j+1][1];
	            }
	            change=true;
	            i--;length--;
	            continue;
	        }
	    }
	    length = removesame(arr,length);
	}
    for(int i=0;i<length;i++)
    {
        cout<<"["<<arr[i][0]<<","<<arr[i][1]<<"]";
        if(i!=length-1)cout<<",";
    }
    cout<<endl;
}

/* UPLOAD END */

void test1(){
    int** a = new int*[2];
    a[0] = new int[2];
    a[1] = new int[2];
    a[0][0] = 1;
    a[0][1] = 4;
    a[1][0] = 4;
    a[1][1] = 5;
    mergeIntervals(a,2);
    
    int** b = new int*[4];
    b[0] = new int[2]{1,3};
    b[1] = new int[2]{2,6};
    b[2] = new int[2]{8,10};
    b[3] = new int[2]{15,18};
    mergeIntervals(b,4);
}

int main()
{
    test1();
    return 0;
}
