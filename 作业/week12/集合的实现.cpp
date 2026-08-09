#include <iostream>
#include <iomanip>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

/* UPLOAD START */

template <class T>
class ASet{ // for now we assume datatype T can be sorted
    private:
        int capacity;
        int length;
        T* aset;
        void doubleListSize()
        {
            T * oldAset = aset;
            aset = new T[2*capacity];
            capacity = 2 * capacity;
            for(int i=0;i<length;i++)
            {
                aset[i] = oldAset[i];
            }
            delete [] oldAset;
        }
    public:
        ASet(){
            length = 0;
            capacity = 100;
            aset = new T[capacity];
        }
        ASet(T* arr, int n){ //incoming array is guaranteed not to have duplicates.
            length = 0;
            capacity = 100 + 2*n;
            aset = new T[capacity];
            for(int i=0;i<n;i++)
            {
                addEle(arr[i]);
            }
        }
        ~ASet(){
            delete[] aset;
        }
        void addEle(T x){
            if(hasEle(x))return;
            if(length==capacity)doubleListSize();
            int pos=-1;
            for(int i=0;i<length;i++)
            {
                if(x<aset[i])
                {
                    pos=i;
                    break;
                }
            }
            if(pos==-1)
            {
                aset[length]=x;
                length++;
            }
            else
            {
                for(int i=length;i>pos;i--)
                {
                    aset[i]=aset[i-1];
                }
                aset[pos]=x;
                length++;
            }
        }
        bool isEmpty(){
            return length==0;
        }
        bool removeEle(T x){
            // returns true if removed.
            // returns false if it is not in the set
            int pos=-1;
            for(int i=0;i<length;i++)
            {
                if(aset[i]==x)
                {
                    pos=i;
                    break;
                }
            }
            if(pos==-1)return false;
            for(int i=i;i<length-1;i++)
            {
                aset[i]=aset[i+1];
            }
            length--;
            return true;
        }
        bool hasEle(T x){
            for(int i=0;i<length;i++)
            {
                if(aset[i]==x)return true;
            }
            return false;
        }
        bool isSubsetOf(ASet<T>* S){
            for(int i=0;i<length;i++)
            {
                if(!S->hasEle(aset[i]))return false;
            }
            return true;
        }
        bool containsSet(ASet<T>* S){
            for(int i=0;i<S->length;i++)
            {
                if(!hasEle(S->aset[i]))return false;
            }
            return true;
        }
        bool isDisjointFrom(ASet<T>* S){
            for(int i=0;i<length;i++)
            {
                if(S->hasEle(aset[i]))return false;
            }
            return true;
        }
        int cardinality(){
            return length;
        }
        ASet<T>* setUnion(ASet<T>* S){
            ASet<T>* tmp=new ASet<T>;
            for(int i=0;i<length;i++)
            {
                tmp->addEle(aset[i]);
            }
            for(int i=0;i<S->length;i++)
            {
                tmp->addEle(S->aset[i]);
            }
            return tmp;
        }
        ASet<T>* intersect(ASet<T>* S){
            ASet<T>* tmp=new ASet<T>;
            for(int i=0;i<length;i++)
            {
                if(S->hasEle(aset[i]))tmp->addEle(aset[i]);
            }
            return tmp;
        }
        ASet<T>* subtract(ASet<T>* S){
            ASet<T>* tmp=new ASet<T>;
            for(int i=0;i<length;i++)
            {
                if(!S->hasEle(aset[i]))tmp->addEle(aset[i]);
            }
            return tmp;
        }
        ASet<T>* symDiff(ASet<T>* S){
             ASet<T>* tmp=new ASet<T>;
             ASet<T>* tmpUnion=new ASet<T>;
             ASet<T>* tmpintersect=new ASet<T>;
             tmpUnion=setUnion(S);
             tmpintersect=intersect(S);
             for(int i=0;i<tmpUnion->length;i++)
             {
                 if(!tmpintersect->hasEle(tmpUnion->aset[i]))tmp->addEle(tmpUnion->aset[i]);
             }
             delete tmpUnion;
             delete tmpintersect;
              return tmp;
        }
        void printSet(){ //print the elements of S in ascending order
            if(length==0)
            {
                cout<<"{}"<<endl;
                return;
            }
            cout<<"{";
            for(int i=0;i<length-1;i++)
            {
                cout<<aset[i]<<",";
            }
            cout<<aset[length-1]<<"}"<<endl;
        }
};

/* UPLOAD END */

void simpleTest(){
    ASet<int> A;
    for(int i=1;i<=4;i++){
        A.addEle(i);
    }
    cout << "Set A: ";
    A.printSet();
    cout << "Cardinality of A: " << A.cardinality() << endl << endl;

    int tmpB[4] = {3,6,5,4};
    ASet<int> B(tmpB,4);
    cout << "Set B: ";
    B.printSet();
    cout << "Cardinality of B: " << B.cardinality() << endl << endl;

    ASet<int>* C = A.intersect(&B);
    ASet<int>* D = A.subtract(&B);

    cout << "Intersecting A and B gets set C, ";
    C->printSet();
    cout << "Union of A and B is ";
    (A.setUnion(&B))->printSet();
    cout << "Let set D be the set of elements in A but not B. Then set D is ";
    D->printSet();
    cout << "Symmetric difference of A and B is ";
    (A.symDiff(&B))->printSet();

    cout << endl << "Checking subset relations:" << endl;
    cout << "A " << (A.containsSet(C) ? "contains" : "does not contain") << " set C" << endl;
    cout << "B " << (B.containsSet(D) ? "contains" : "does not contain") << " set D" << endl;
    cout << "C is " << (C->isSubsetOf(&A) ? "" : "not ") << "a subset of A" << endl;
    cout << "D is " << (D->isSubsetOf(&B) ? "" : "not ") << "a subset of B" << endl;
}

int main(){
    simpleTest();
    return 0;
}
