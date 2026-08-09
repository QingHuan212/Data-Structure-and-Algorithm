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

    void flipList() {
        T b;
        for (int i = 0; i < length / 2; i++)
        {
            b = arr[i];
            arr[i] = arr[length - 1 - i];
            arr[length - 1 - i] = b;
        }
    }
    void rotateList(int n) {
        int k = n % length;
        T c;
        int j;
        for (int i = 1; i <= k; i++)
        {
            c = arr[length - 1];
            for (j = length - 1; j >= 0; j--)
            {
                arr[j] = arr[j - 1];
            }
            arr[0] = c;
        }
    }
};