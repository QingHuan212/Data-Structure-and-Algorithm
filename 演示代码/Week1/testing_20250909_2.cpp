#include <iostream>
using namespace std;

int main(){
    cout << "Hello World!" << endl;

    int a, b;
    cin >> a >> b;

    cout << "a is " << a << endl;
    cout << "b is " << b << endl;

    if(a==b){
        cout << "They are the same." << endl;
    }
    else{
        cout << "They are different." << endl;
    }

    int sum = 0;
    for(int i=0;i<=a;i++){
        sum = sum + i;
    }
    cout << "The sum is " << sum << endl;

    while(sum!=0){
        sum = sum / 2;
        cout << sum << endl;
    }

    return 0;
}
