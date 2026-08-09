#include <iostream>
using namespace std;

template <class T>
class VecList {
private:
    int capacity;
    int length;
    T* arr;
    void doubleListSize() {
        T* oldArr = arr;
        arr = new T[2 * capacity];
        capacity = 2 * capacity;
        for (int i = 0; i < length; i++) {
            arr[i] = oldArr[i];
        }
        delete[] oldArr;
    }
public:
    VecList() {
        length = 0;
        capacity = 100;
        arr = new T[capacity];
    }
    VecList(T* a, int n) {
        length = n;
        capacity = 100 + 2 * n;
        arr = new T[capacity];
        for (int i = 0; i < n; i++) {
            arr[i] = a[i];
        }
    }
    ~VecList() {
        delete[] arr;
    }
    int getLength() {
        return length;
    }
    bool isEmpty() {
        return length == 0;
    }
    void insertEleAtPos(int i, T x) {
        if (length == capacity)
            doubleListSize();
        if (i > length || i < 0)
            throw "Illegal position";
        for (int j = length; j > i; j--)
            arr[j] = arr[j - 1];
        arr[i] = x;
        length++;
    }
    T deleteEleAtPos(int i) {
        if (i >= length || i < 0)
            throw "Illegal position";
        T tmp = arr[i];
        for (int j = i; j < length - 1; j++)
            arr[j] = arr[j + 1];
        length--;
        return tmp;
    }
    void setEleAtPos(int i, T x) {
        if (i >= length || i < 0)
            throw "Illegal position";
        arr[i] = x;
    }
    T getEleAtPos(int i) {
        if (i >= length || i < 0)
            throw "Illegal position";
        return arr[i];
    }
    int locateEle(T x) {
        for (int i = 0; i < length; i++) {
            if (arr[i] == x)
                return i;
        }
        return -1;
    }
    void printList() {
        for (int i = 0; i < length; i++)
            cout << arr[i] << " ";
    }
};

bool Dend(VecList<int>* c)
{
    for (int i = 0; i < c->getLength(); i++)
    {
        if (c->getEleAtPos(i) > 1)
        {
            return 1;
        }   
    }
    return 0;
};

void Divide(VecList<int>* c)
{
    int i,sum,max,length;
    while (Dend(c))
    {
        for ( i = c->getLength()-1; i >= 0; i--)
        {
            if (c->getEleAtPos(i) != 1)
                break;    
        }

        max = c->getEleAtPos(i) - 1;
        c->setEleAtPos(i,max);
        sum = 1;
        length = c->getLength();

        for (int j = length-1; j > i; j--)
        {
            sum += c->deleteEleAtPos(j);
        }

        for (int j = 1; ; j++)
        {
            if (sum > max)
            {
                c->insertEleAtPos(c->getLength(), max);
                sum -= max;
                i++;
            }
            if (sum == 0)break;
            if (sum <= max)
            {
                c->insertEleAtPos(c->getLength(), sum);
                break;
            }
        }

        for (int j = 0; j < c->getLength(); j++)
        {
            if (j == 0)cout << c->getEleAtPos(0);
            else
            {
                cout << "+" << c->getEleAtPos(j);
            }
        }
        cout << endl;
    }
}

int main()
{
    int *n=new int;
    cin >> *n;
    VecList<int>* c = new VecList<int>(n,1);
    cout << *n << endl;
    Divide(c);
    delete c;
    return 0;
}