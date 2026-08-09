#include <iostream>
using namespace std;

/* UPLOAD START */

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


// In the class below, we assume it is meaningful to put 0 as a value for the type T.
template <class T>
class SparseMatrix {
private:
    VecList<int>*listr;
    VecList<int>*listc;
    VecList<T>*liste;
    int row,column;
public:
    SparseMatrix() {
        // default is 10 rows, 10 columns
        row = 10;
        column = 10;
        listr=new VecList<int>();
        listc=new VecList<int>();
        liste=new VecList<T>();
    }
    SparseMatrix(int r, int c) {
        row = r;
        column = c;
        listr=new VecList<int>();
        listc=new VecList<int>();
        liste=new VecList<T>();
    }
    ~SparseMatrix() {
        delete listr;
        delete listc;
        delete liste;
    }
    void setEntry(int rPos, int cPos, T x) {
        int r,l,i,p=0;
        l = listr->getLength();
        r = listr->locateEle(rPos);
        if(x==0)return;
        else if(liste->getLength()==0)
        {
            listr->insertEleAtPos(0,rPos);
            listc->insertEleAtPos(0,cPos);
            liste->insertEleAtPos(0,x);
        }
        else if (rPos > listr->getEleAtPos(l-1))
        {
            listr->insertEleAtPos(l, rPos);
            listc->insertEleAtPos(l, cPos);
            liste->insertEleAtPos(l, x);
        }
        else if(rPos<listr->getEleAtPos(0))
        {
            listr->insertEleAtPos(0, rPos);
            listc->insertEleAtPos(0, cPos);
            liste->insertEleAtPos(0, x);
        }
        else if(r!=-1)
        {
            for(i=r;i<l&&listr->getEleAtPos(i) == rPos;i++)
            {
                if(listc->getEleAtPos(i)==cPos)
                {
                        liste->setEleAtPos(i,x);
                        p=1;
                        break;
                }
                if(listc->getEleAtPos(i)>cPos)
                {
                    //cout << cPos<<" "<< listc->getEleAtPos(i)<<" "<<i << endl;
                    listr->insertEleAtPos(i,rPos);
                    listc->insertEleAtPos(i,cPos);
                    liste->insertEleAtPos(i,x);
                    p=1;
                    break;
                }
            }
            //cout<< cPos << " " << listc->getEleAtPos(i) << " " << i << endl;
            if ((i==l&&p==0 )||( listr->getEleAtPos(i) > rPos&&p==0))
            {
                    listr->insertEleAtPos(i, rPos);
                    listc->insertEleAtPos(i, cPos);
                    liste->insertEleAtPos(i, x);
            }
        }
        else
        {
            for(i=0;i<l;i++)
            {
                if(rPos<listr->getEleAtPos(i))
                {
                    listr->insertEleAtPos(i,rPos);
                    listc->insertEleAtPos(i,cPos);
                    liste->insertEleAtPos(i,x);
                    break;
                }
            }
        }
        //listr->printList(); cout << endl;
        //listc->printList(); cout << endl;
        //liste->printList(); cout << endl;
        //printMatrix();
        //cout << endl;
    }
    void addEntry(int rPos, int cPos, T x) {
        int r,l,i,p=0;
        l = listr->getLength();
        r = listr->locateEle(rPos);
        if(x==0) return;
        else if(liste->getLength()==0)
        {
            listr->insertEleAtPos(0,rPos);
            listc->insertEleAtPos(0,cPos);
            liste->insertEleAtPos(0,x);
        }
        else if (rPos > listr->getEleAtPos(l-1))
        {
            listr->insertEleAtPos(l, rPos);
            listc->insertEleAtPos(l, cPos);
            liste->insertEleAtPos(l, x);
        }
        else if(rPos<listr->getEleAtPos(0))
        {
            listr->insertEleAtPos(0, rPos);
            listc->insertEleAtPos(0, cPos);
            liste->insertEleAtPos(0, x);
        }
        else if(r!=-1)
        {
            for(i=r;i<l&&listr->getEleAtPos(i) == rPos;i++)
            {
                if(listc->getEleAtPos(i)==cPos)
                {
                    if(liste->getEleAtPos(i) + x!=0)
                    {
                        liste->setEleAtPos(i,liste->getEleAtPos(i)+x);
                        p=1;
                        break;
                    }
                    if(liste->getEleAtPos(i) + x==0)
                    {
                        //cout<<"begin"<<endl;
                        //cout<<rPos<<" "<<cPos<<" "<<x<<endl;
                        listr->deleteEleAtPos(i);
                        listc->deleteEleAtPos(i);
                        liste->deleteEleAtPos(i);
                        //printNZMatrix();
                        //cout<<"end"<<endl;
                        p=1;
                        break;
                    }
                }
                if(listc->getEleAtPos(i)>cPos)
                {
                    //cout << cPos<<" "<< listc->getEleAtPos(i)<<" "<<i << endl;
                    listr->insertEleAtPos(i,rPos);
                    listc->insertEleAtPos(i,cPos);
                    liste->insertEleAtPos(i,x);
                    p=1;
                    break;
                }
            }
            //cout<< cPos << " " << listc->getEleAtPos(i) << " " << i << endl;
            if ((i==l&&p==0 )||( listr->getEleAtPos(i) > rPos&&p==0))
            {
                //cout<<"y"<<rPos<<" "<<cPos<<" "<<x<<" "<<i<<" "<<l<<" "<<listr->getEleAtPos(i)<<endl;
                    listr->insertEleAtPos(i, rPos);
                    listc->insertEleAtPos(i, cPos);
                    liste->insertEleAtPos(i, x);
            }
        }
        else
        {
            for(i=0;i<l;i++)
            {
                if(rPos<listr->getEleAtPos(i))
                {
                    listr->insertEleAtPos(i,rPos);
                    listc->insertEleAtPos(i,cPos);
                    liste->insertEleAtPos(i,x);
                    break;
                }
            }
        }
    }
    void subEntry(int rPos, int cPos, T x) {
        int r,l,i,p=0;
        l = listr->getLength();
        r = listr->locateEle(rPos);
        if(x==0) return;
        if(liste->getLength()==0)
        {
            listr->insertEleAtPos(0,rPos);
            listc->insertEleAtPos(0,cPos);
            liste->insertEleAtPos(0,-x);
        }
        else if (rPos > listr->getEleAtPos(l-1))
        {
            listr->insertEleAtPos(l, rPos);
            listc->insertEleAtPos(l, cPos);
            liste->insertEleAtPos(l, -x);
        }
        else if(rPos<listr->getEleAtPos(0))
        {
            listr->insertEleAtPos(0, rPos);
            listc->insertEleAtPos(0, cPos);
            liste->insertEleAtPos(0, -x);
        }
        else if(r!=-1)
        {
            for(i=r;i<l&&listr->getEleAtPos(i) == rPos;i++)
            {
                if(listc->getEleAtPos(i)==cPos)
                {
                    if(liste->getEleAtPos(i) - x!=0)
                    {
                        liste->setEleAtPos(i,liste->getEleAtPos(i)-x);
                        p=1;
                        break;
                    }
                    else
                    {
                        listr->deleteEleAtPos(i);
                        listc->deleteEleAtPos(i);
                        liste->deleteEleAtPos(i);
                        p=1;
                        break;
                    }
                }
                if(listc->getEleAtPos(i)>cPos)
                {
                    //cout << cPos<<" "<< listc->getEleAtPos(i)<<" "<<i << endl;
                    listr->insertEleAtPos(i,rPos);
                    listc->insertEleAtPos(i,cPos);
                    liste->insertEleAtPos(i,-x);
                    p=1;
                    break;
                }
            }
            //cout<< cPos << " " << listc->getEleAtPos(i) << " " << i << endl;
            if ((i==l&&p==0 )||( listr->getEleAtPos(i) > rPos&&p==0))
            {
                    listr->insertEleAtPos(i, rPos);
                    listc->insertEleAtPos(i, cPos);
                    liste->insertEleAtPos(i, -x);
            }
        }
        else
        {
            for(i=0;i<l;i++)
            {
                if(rPos<listr->getEleAtPos(i))
                {
                    listr->insertEleAtPos(i,rPos);
                    listc->insertEleAtPos(i,cPos);
                    liste->insertEleAtPos(i,-x);
                    break;
                }
            }
        }
    }
    T getEntry(int rPos, int cPos) {
        for (int i = 0; i < liste->getLength(); i++)
        {
            if (listr->getEleAtPos(i) == rPos && listc->getEleAtPos(i) == cPos)
                return liste->getEleAtPos(i);
        }
        if(rPos<=row&&cPos<=column)
        {
            return 0;
        }
    }
    SparseMatrix<T>* add(SparseMatrix<T>* B) {
        if (row != B->row || column != B->column)throw"Matrices have incompatible sizes";
        SparseMatrix<T>* t = new SparseMatrix<T>(row, column);
        for(int i=0;i<liste->getLength();i++)
        {
            t->setEntry(listr->getEleAtPos(i), listc->getEleAtPos(i), liste->getEleAtPos(i));
            //t->printNZMatrix();
        }
       //cout<<"tr:";B->listr->printList();cout<<endl;
       //cout<<"tc:";B->listc->printList();cout<<endl;
       //cout<<"te:";B->liste->printList();cout<<endl;
        for (int k = 0; k < B->liste->getLength(); k++)
        {
                    //cout<<"tr:";t->listr->printList();cout<<endl;
      // cout<<"tc:";t->listc->printList();cout<<endl;
       //cout<<"te:";t->liste->printList();cout<<endl;
            //cout << B->listr->getEleAtPos(k) << " " << B->listc->getEleAtPos(k) << " " << B->liste->getEleAtPos(k) << endl;
            t->addEntry(B->listr->getEleAtPos(k),B->listc->getEleAtPos(k), B->liste->getEleAtPos(k));
            //cout<<"1"<<endl;t->printNZMatrix();cout<<"2"<<endl;
            //t->printMatrix();cout<<endl;
        }
        return t;
    }
    SparseMatrix<T>* subtract(SparseMatrix<T>* B) {
        if (row != B->row || column != B->column)throw"Matrices have incompatible sizes";
        SparseMatrix<T>* t = new SparseMatrix<T>(row, column);
        for (int i = 0; i < liste->getLength(); i++)
        {
            t->setEntry(listr->getEleAtPos(i), listc->getEleAtPos(i), liste->getEleAtPos(i));
            // t->printMatrix();
        }
        for (int k = 0; k < B->liste->getLength(); k++)
        {
            //cout << B->listr->getEleAtPos(k) << " " << B->listc->getEleAtPos(k) << " " << B->liste->getEleAtPos(k) << endl;
            t->subEntry(B->listr->getEleAtPos(k), B->listc->getEleAtPos(k), B->liste->getEleAtPos(k));
            //t->printMatrix();
        }
        return t;
    }

    SparseMatrix<T>* multiply(SparseMatrix<T>* B) {
        //perform multiplication if the sizes of the matrices are compatible.
        if (column != B->row)throw"Matrices have incompatible sizes";
        if (B->liste->getLength() == 0 || liste->getLength() == 0)
        {
        SparseMatrix<T>* zero = new SparseMatrix<T>(row,B->column);
        return zero;
        }
        SparseMatrix<T>* t = new SparseMatrix<T>(row,B->column);
        int sum=0,z=0;
        VecList<int>*zlistr;
        VecList<int>*zlistc;
        VecList<T>*zliste;
        zlistr=new VecList<int>();
        zlistc=new VecList<int>();
        zliste=new VecList<T>();
        for (int i = 0; i < B->column; i++)
        {
            for (int j = 0; j < B->liste->getLength(); j++)
            {
                if (B->listc->getEleAtPos(j) == i)
                    {
                        zlistr->insertEleAtPos(z,B->listr->getEleAtPos(j));
                        zlistc->insertEleAtPos(z,i);
                        zliste->insertEleAtPos(z,B->liste->getEleAtPos(j));
                        z++;
                    }
            }
        }
        /*cout << "B:" << endl;
        B->listr->printList(); cout << endl;
        B->listc->printList(); cout << endl;
        B->liste->printList(); cout << endl;
        cout << "zB:"<<endl;
        zlistr->printList(); cout << endl;
        zlistc->printList(); cout << endl;
        zliste->printList(); cout << endl;
        cout << "t:"<<endl;
        listr->printList(); cout << endl;
        listc->printList(); cout << endl;
        liste->printList(); cout << endl;*/
        int k,l,h,w=0;int zr,zc;
        for(int i=0;i<row;i++)
        {
               zr=listr->locateEle(i);
               if(zr==-1)continue;
               for(int j=0;j<B->column;j++)
               {
                   sum=0;
                   zc=zlistc->locateEle(j);
                   //cout << zc;
                   //cout << j << endl;
                   if(zc==-1)continue;
                   for(k=zr;k<listr->getLength()&&listr->getEleAtPos(k)==i;k++)
                   {
                       h = listc->getEleAtPos(k);
                       //cout << "1"<<endl;
                       for (l = zc; l < zlistc->getLength() && zlistc->getEleAtPos(l) == j; l++)
                       {
                           //cout << zc;
                           //cout << l<< zlistc->getLength();
                           //cout << j <<" "<<h << endl;
                           if (zlistr->getEleAtPos(l) == h)
                           {
                               //cout << "3" << endl;
                               sum = sum + (liste->getEleAtPos(k) * zliste->getEleAtPos(l));
                               //cout << "2" << endl;
                           }
                       }
                   }
                   if (sum != 0)
                   {
                       t->listr->insertEleAtPos(w, i);
                       t->listc->insertEleAtPos(w, j);
                       t->liste->insertEleAtPos(w, sum);
                       w++;
                   }
               }
        }
        delete zlistr;
        delete zlistc;
        delete zliste;
        return t;
    }


    // Only call this function if you know the size of matrix is reasonable.
    void printMatrix() {
        int i,j;
        int nz;
        for(i=0;i<row;i++)
        {
            nz=listr->locateEle(i);
            for(j=0;j<column;j++)
            {
                    if(nz==-1||nz>=listr->getLength())cout<<"0 ";
                    else if(listr->getEleAtPos(nz)==i&&listc->getEleAtPos(nz)==j)
                    {
                        cout<<liste->getEleAtPos(nz)<<" ";
                        nz++;
                    }
                    else cout<<"0 ";
            }
            cout<<endl;
        }
    }

    //This is for printing only non-zero entries
    void printNZMatrix() {
        for(int i=0;i<liste->getLength();i++)
        {
            cout<<listr->getEleAtPos(i)<<" "<<listc->getEleAtPos(i)<<" "<<liste->getEleAtPos(i)<<endl;
        }
    }
};

/* UPLOAD END */

int main() {
    SparseMatrix<int> X, Y, Z, W;
    X.setEntry(2, 3, 4);
    X.setEntry(2, 2, 6);
    X.setEntry(2, 5, 0);
    X.setEntry(1, 6, 6);
    X.setEntry(7, 2, 8);
    X.setEntry(2, 9, 9);
    X.setEntry(1, 3, 9);
    X.setEntry(6, 6, 9);
    X.setEntry(1, 9, 9);
    Y.setEntry(1, 3, 4);
    Y.setEntry(1, 7, 5);
    Y.setEntry(7, 7, 2);
    Y.setEntry(1, 3, 5);
    Y.setEntry(1, 7, 5);
    Y.setEntry(3, 1, -1);
    X.setEntry(3, 1, 1);
    X.setEntry(0, 0, 0);
    X.setEntry(1, 1, 5);
    X.setEntry(1, 1, 0);
    X.printMatrix();
    cout << endl;
    Y.printMatrix();
    cout << endl;
    cout<<Y.getEntry(9,9);
    X.printNZMatrix();
    cout << endl;
    Z.printMatrix();
    cout << endl;
    Z.printNZMatrix();
    cout << endl;
    X.add(&Y)->printNZMatrix();
    cout<<endl;
   // X.add(&Y)->printMatrix();
    cout << endl;
    X.subtract(&Y)->printMatrix();
    cout << endl;
    Y.multiply(&X)->printMatrix();
    cout << endl;
    X.multiply(&Y)->printMatrix();
    return 0;
}
