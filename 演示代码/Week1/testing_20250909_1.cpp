#include <iostream>
using namespace std;

int main(){
    int a,b;
    cout << "Please enter a: ";
    cin >> a;
    cout << "Hello World!" << endl;
    cout << a << endl;

    cout << "Please enter b: ";
    cin >> b;

    if(a==b){
        cout << "They are equal" << endl;
    }
    else{
        cout << "Different." << endl;
    }

    int sum = 0;
    for(int i=0;i<=a;i+=2){
        sum += i;
    }
    cout << "Summing from 0 to " << a << " is " << sum << endl;

    while(sum!=0){
        sum = sum/2;
        cout << sum << endl;
    }



    return 0;
}
