#include <iostream>
using namespace std;

template <class T>
class VecList{ // vector list
    private:
        int capacity;
        int length;
        T* arr;
        void doubleListSize(){
            capacity = 2*capacity;
            T* newArr = new T[capacity];
            for(int i=0;i<length;i++){
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
        }
    public:
        VecList(){
            length = 0;
            capacity = 100;
            arr = new T[capacity];
        }
        VecList(T* a, int n){
            length = n;
            capacity = 100 + 2*n;
            arr = new T[capacity];
            for(int i=0;i<n;i++)
                arr[i] = a[i];
        }
        ~VecList(){
            delete[] arr;
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void insertEleAtPos(int i, T x){
            if(i<0 || i > length){
                throw "Illegal position";
            }
            if(length==capacity){
                doubleListSize();
            }
            for(int j=length-1;j>=i;j--){
                arr[j+1] = arr[j];
            }
            arr[i] = x;
            length++;
        }
        T deleteEleAtPos(int i){
            if(i<0 || i >= length){
                throw "Illegal position";
            }
            T x = arr[i];
            for(int j=i+1;j<length;j++){
                arr[j-1] = arr[j];
            }
            length--;
            return x;
        }
        void setEleAtPos(int i, T x){
            if(i<0 || i >= length){
                throw "Illegal position";
            }
            arr[i] = x;
        }
        T getEleAtPos(int i){
            if(i<0 || i >= length){
                throw "Illegal position";
            }
            return arr[i];
        }
        int locateEle(T x){
            for(int i=0;i<length;i++){
                if(arr[i] == x){
                    return i;
                }
            }
            return -1;
        }
        void printList(){
            for(int i=0;i<length;i++){
                cout << arr[i] << " ";
            }
        }
};

int main(){
    string SS[3] = {"AA","BB","CCC"};
    VecList<string> ListS(SS,3);
    cout << (ListS.isEmpty() ? "Empty" : "Non-empty") << endl;
    cout << ListS.getLength() <<endl;
    ListS.printList();
    cout << endl;
    ListS.setEleAtPos(2,"CC");
    ListS.printList();
    cout << endl;
    cout << endl;

    VecList<int> ListI;
    cout << (ListI.isEmpty() ? "Empty" : "Non-empty") << endl;
    for(int i=1;i<=31;i+=2){
        ListI.insertEleAtPos(0,i);
    }
    ListI.printList();
    cout << endl;

    for(int i=0;i<=500;i++){
        ListI.insertEleAtPos(ListI.getLength(),i);
    }
    ListI.printList();
    cout << endl;

    VecList<int> ListJ;
    for(int j=0;j<5;j++){
        ListJ.insertEleAtPos(ListJ.getLength(),j);
    }
    ListJ.printList();
    cout << endl;

    try{
        ListJ.insertEleAtPos(0,500);
        ListJ.insertEleAtPos(10,7);
        ListJ.insertEleAtPos(0,100);
    }
    catch(const char* s){
        cout << s << endl;
    }
    ListJ.printList();
    cout << endl;

    cout << "Deleted element: " << ListJ.deleteEleAtPos(3) << endl;
    ListJ.printList();
    cout << endl;
    cout << ListJ.getLength() << endl;

    cout << ListJ.getEleAtPos(4) << endl;
    cout << "Position of 3: "<< ListJ.locateEle(3) << endl;
    cout << "Position of 500: "<< ListJ.locateEle(500) << endl;
    cout << "Position of 2: " << ListJ.locateEle(2) << endl;

    return 0;
}
