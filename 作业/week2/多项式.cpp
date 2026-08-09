#include <iostream>
using namespace std;

/* UPLOAD START */
// You can use VecList, LinkList or none of these structures in writing the IntPolynomial class
template <class T>
class VecList{
    private:
        int capacity;
        int length;
        T* arr;
        void doubleListSize(){
            T * oldArr = arr;
            arr = new T[2*capacity];
            capacity = 2 * capacity;
            for(int i=0;i<length;i++){
                arr[i] = oldArr[i];
            }
            delete [] oldArr;
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
            for(int i=0;i<n;i++){
                arr[i] = a[i];
            }
        }
        ~VecList(){
            delete [] arr;
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void insertEleAtPos(int i, T x){
            if(length==capacity)
                doubleListSize();
            if(i > length || i < 0)
                throw "Illegal position";
            for(int j=length;j>i;j--)
                arr[j] = arr[j-1];
            arr[i] = x;
            length++;
        }
        T deleteEleAtPos(int i){
            if(i >= length || i < 0)
                throw "Illegal position";
            T tmp = arr[i];
            for(int j=i;j<length-1;j++)
                arr[j] = arr[j+1];
            length--;
            return tmp;
        }
        void setEleAtPos(int i, T x){
            if(i >= length || i < 0)
                throw "Illegal position";
            arr[i] = x;
        }
        T getEleAtPos(int i){
            if(i >= length || i < 0)
                throw "Illegal position";
            return arr[i];
        }
        int locateEle(T x){
            for(int i=0;i<length;i++){
                if(arr[i]==x)
                    return i;
            }
            return -1;
        }
        void printList(){
            for(int i=0;i<length;i++)
                cout << arr[i] << " ";
        }
};

class IntPolynomial{
    private:
        VecList<int>* x,* m;
        int length;
    public:
        IntPolynomial(){
            x=new VecList<int>;
            m=new VecList<int>;
            length=0;
        }
        IntPolynomial(int * c, int * d, int n){
            length = 0;
            x = new VecList<int>;
            m = new VecList<int>;
            for (int i = 0; i < n; i++)
            {
                if (c[i] == 0)
                    continue;
                int p = m->locateEle(d[i]);
                if (p != -1)
                {
                    int h = x->getEleAtPos(p) + c[i];
                    if (h== 0)
                    {
                        x->deleteEleAtPos(p);
                        m->deleteEleAtPos(p);
                        length--;
                    }
                    else
                    {
                        x->setEleAtPos(p, h);
                    }
                    continue;
                }
                int j;
                for (j = 0; j < length; j++)
                {
                    if (d[i] < m->getEleAtPos(j))
                        break;
                }
                x->insertEleAtPos(j, c[i]);
                m->insertEleAtPos(j, d[i]);
                length++;
            }
        }
        ~IntPolynomial(){
            delete x;
            delete m;
        }
        int getDegree(){
            if (length == 0)return -1;
            else return(m->getEleAtPos(length - 1));
        }
        IntPolynomial* Add(IntPolynomial* b){
            int i,h,j,t;
            IntPolynomial* tmp = new IntPolynomial;
            if (length == 0)
            {
                for (i = 0; i < b->length; i++)
                {
                    tmp->x->insertEleAtPos(i, b->x->getEleAtPos(i));
                    tmp->m->insertEleAtPos(i, b->m->getEleAtPos(i));
                }
                tmp->length = b->length;
                return tmp;
            }
            for (i = 0; i < length; i++)
            {
                tmp->x->insertEleAtPos(i, x->getEleAtPos(i));
                tmp->m->insertEleAtPos(i, m->getEleAtPos(i));
            }
            tmp->length = length;
            if (b->length == 0)return tmp;
            for (i = 0; i < b->length; i++)
            {
                t = tmp->m->locateEle(b->m->getEleAtPos(i));
                if (t + 1)
                {
                    h = tmp->x->getEleAtPos(t) + b->x->getEleAtPos(i);
                    if (h == 0)
                    {
                        tmp->x->deleteEleAtPos(t);
                        tmp->m->deleteEleAtPos(t);
                        tmp->length--;
                        continue;
                    }
                    tmp->x->setEleAtPos(t, h);
                    continue;
                }
                else if (b->m->getEleAtPos(i) > tmp->m->getEleAtPos(tmp->length - 1))
                {
                    tmp->x->insertEleAtPos(tmp->length, b->x->getEleAtPos(i));
                    tmp->m->insertEleAtPos(tmp->length, b->m->getEleAtPos(i));
                    tmp->length++;
                    continue;
                }
                else
                {
                    for (j = 0; j < tmp->length; j++)
                    {
                        if (b->m->getEleAtPos(i) < tmp->m->getEleAtPos(j))
                        {
                            tmp->x->insertEleAtPos(j, b->x->getEleAtPos(i));
                            tmp->m->insertEleAtPos(j, b->m->getEleAtPos(i));
                            tmp->length++;
                            break;
                        }
                    }
                }
            }
            return tmp;
        }
        IntPolynomial* Subtract(IntPolynomial* b){
            int i, h, j, t;
            IntPolynomial* tmp = new IntPolynomial;
            if (length == 0)
            {
                for (i = 0; i < b->length; i++)
                {
                    tmp->x->insertEleAtPos(i, -(b->x->getEleAtPos(i)));
                    tmp->m->insertEleAtPos(i, b->m->getEleAtPos(i));
                }
                tmp->length = b->length;
                return tmp;
            }
            for (i = 0; i < length; i++)
            {
                tmp->x->insertEleAtPos(i, x->getEleAtPos(i));
                tmp->m->insertEleAtPos(i, m->getEleAtPos(i));
            }
            tmp->length = length;
            if (b->length == 0)return tmp;
            for (i = 0; i < b->length; i++)
            {
                t = tmp->m->locateEle(b->m->getEleAtPos(i));
                if (t + 1)
                {
                    h = tmp->x->getEleAtPos(t) - b->x->getEleAtPos(i);
                    if (h == 0)
                    {
                        tmp->x->deleteEleAtPos(t);
                        tmp->m->deleteEleAtPos(t);
                        tmp->length--;
                        continue;
                    }
                    tmp->x->setEleAtPos(t, h);
                    continue;
                }
                else if (b->m->getEleAtPos(i) > tmp->m->getEleAtPos(tmp->length - 1))
                {
                    tmp->x->insertEleAtPos(tmp->length, -(b->x->getEleAtPos(i)));
                    tmp->m->insertEleAtPos(tmp->length, b->m->getEleAtPos(i));
                    tmp->length++;
                    continue;
                }
                else
                {
                    for (j = 0; j < tmp->length; j++)
                    {
                        if (b->m->getEleAtPos(i) < tmp->m->getEleAtPos(j))
                        {
                            tmp->x->insertEleAtPos(j, -(b->x->getEleAtPos(i)));
                            tmp->m->insertEleAtPos(j, b->m->getEleAtPos(i));
                            tmp->length++;
                            break;
                        }
                    }
                }
            }
            return tmp;
        }
        IntPolynomial* Multiply(IntPolynomial* b){
            int i,j;
            IntPolynomial* sum = new IntPolynomial;
            if (length == 0 || b->length == 0)return sum;         
            for (i = 0; i < length; i++)
            {
                IntPolynomial* tmp = new IntPolynomial;
                for (j = 0; j < b->length; j++)
                {
                    tmp->x->insertEleAtPos(j, x->getEleAtPos(i) * b->x->getEleAtPos(j));
                    tmp->m->insertEleAtPos(j, m->getEleAtPos(i) + b->m->getEleAtPos(j));
                    tmp->length++;
                }
                IntPolynomial* newSum = sum->Add(tmp);
                delete sum; 
                delete tmp; 
                sum = newSum;
             }
            return sum;
        }
        void printPolynomial(){
            int i,tmpx,tmpm;
            if (length == 0)cout << "0";
            else {
                tmpx = x->getEleAtPos(0);
                tmpm = m->getEleAtPos(0);
                if (tmpx == 0);
                else if (tmpm == 0)cout << tmpx;
                else if (tmpx == -1)cout << "-";
                else if (tmpx == 1);
                else cout << tmpx;


                if (tmpm == 1)cout << "x";
                else if (tmpm == 0);
                else cout << "x^" << tmpm;
                for (i = 1; i < length; i++)
                {
                    tmpx = x->getEleAtPos(i);
                    tmpm = m->getEleAtPos(i);

                    if (tmpx == 0);
                    else if (tmpm == 0 || tmpx < -1)cout << tmpx;
                    else if (tmpx == -1)cout << "-";
                    else if (tmpx == 1)cout << "+";
                    else cout << "+" << tmpx;

                    if (tmpm == 0);
                    else if (tmpm == 1) cout << "x";
                    else if (tmpx == 0);
                    else cout << "x^" << tmpm;
                }
            }
            cout << endl;
        }
};

/* UPLOAD END */

void test1() {
    int p1c[3] = { 3};
    int p1d[3] = { 2};
    IntPolynomial p1(p1c, p1d,1);

    int p4c[5] = { -3,1,6,-6,-1 };
    int p4d[5] = { 1,3,7,7,11 };
    IntPolynomial p4(p4c, p4d, 5);
    p1.printPolynomial();
}

void test2() {
    int p1c[3] = { 3,5,-6 };
    int p1d[3] = { 0,1,4 };
    IntPolynomial p1;

    int p4c[5] = { -3,-5,6,1,-1 };
    int p4d[5] = { 1,3,7,9,11 };
    IntPolynomial p4(p4c, p4d, 5);

    //int p2c[4] = { 1,1,6,10 };
    //int p2d[4] = { 0,3,20,40 };
    //IntPolynomial p2(p2c, p2d, 4);

    p1.Add(&p4)->printPolynomial();
    p4.Subtract(&p1)->printPolynomial();

    p4.Add(&p4)->printPolynomial();
    p4.Subtract(&p4)->printPolynomial();


}

void test3() {
    int p1c[3] = { 1,-1,5 };
    int p1d[3] = { 0,3,7 };
    IntPolynomial p1(p1c, p1d, 3);

    int p2c[4] = { 1,1,6,10 };
    int p2d[4] = { 0,3,20,40 };
    IntPolynomial p2(p2c, p2d, 4);

    p1.Multiply(&p2)->printPolynomial();
}

int main() {
    int x;
    cin >> x;
    switch (x) {
    case 1: test1(); break;
    case 2: test2(); break;
    case 3: test3();
    default:
        ;
    }
    return 0;
}
