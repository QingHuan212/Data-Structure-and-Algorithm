#include <iostream>
#include <iomanip>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

template <class T>
void bubbleAsc(T*& arr, int n) {
    bool swapped = false;
    do {
        swapped = false;
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                T tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                swapped = true;
            }
        }
    } while (swapped);
}

template <class T>
void bubbleAscS(T*& arr, int n) {
    int lastSwap = n - 1;
    while (lastSwap > 0) {
        int bound = lastSwap;
        lastSwap = 0;
        for (int i = 0; i < bound; i++) {
            if (arr[i] > arr[i + 1]) {
                T tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                lastSwap = i + 1;
            }
        }
    }
}

template <class T>
void insertionAsc(T*& arr, int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (arr[j + 1] < arr[j]) {
                T tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

template <class T>
void insertionAscB(T*& arr, int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (arr[j + 1] < arr[j]) {
                T tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
            else
                break;
        }
    }
}

template <class T>
void shellAsc(T*& arr, int n) {
    // we play separation of n/2, then n/4, n/8, etc...
    int curSep = n;
    do {
        curSep = curSep / 2;
        for (int i = curSep; i < n; i++) {
            for (int j = i - curSep; j >= 0; j -= curSep) {
                if (arr[j + curSep] < arr[j]) {
                    T tmp = arr[j];
                    arr[j] = arr[j + curSep];
                    arr[j + curSep] = tmp;
                }
            }
        }
    } while (curSep > 1);
}

template <class T>
void shellAscB(T*& arr, int n) {
    // we play separation of n/2, then n/4, n/8, etc...
    int curSep = n;
    do {
        curSep = curSep / 2;
        for (int i = curSep; i < n; i++) {
            for (int j = i - curSep; j >= 0; j -= curSep) {
                if (arr[j + curSep] < arr[j]) {
                    T tmp = arr[j];
                    arr[j] = arr[j + curSep];
                    arr[j + curSep] = tmp;
                }
                else
                    break;
            }
        }
    } while (curSep > 1);
}

template <class T>
int quickPivot(T*& arr, int n, int sIndex, int eIndex) { //use first element as pivot, put pivot in correct position, return index
    int le = sIndex;
    int ri = eIndex;
    while (le < ri) {
        while (le < ri && arr[le] <= arr[ri]) ri--;
        if (le < ri) {
            T tmp = arr[le];
            arr[le] = arr[ri];
            arr[ri] = tmp;
            le++;
        }
        while (le < ri && arr[le] <= arr[ri]) le++;
        if (le < ri) {
            T tmp = arr[le];
            arr[le] = arr[ri];
            arr[ri] = tmp;
            ri--;
        }
    }
    return le;
}

template <class T>
void quickAsc(T*& arr, int n, int sIndex, int eIndex) { //start index, end index inclusive
    if (sIndex >= eIndex) return;
    int pivotPos = quickPivot(arr, n, sIndex, eIndex);
    quickAsc(arr, pivotPos, sIndex, pivotPos - 1);
    quickAsc(arr, n - pivotPos - 1, pivotPos + 1, eIndex);
}

template <class T>
void selectionAsc(T*& arr, int n) {
    for (int j = n - 1; j >= 1; j--) {
        // choose largest in the range 0 to j
        //即每一次选择排序都能将最大值交换到最后
        T max = arr[0];
        int maxIdx = 0;
        for (int i = 1; i <= j; i++) {
            if (arr[i] > max) {
                max = arr[i];
                maxIdx = i;
            }
        }//找到无序列中的最大值
        if (maxIdx == j) continue;//这样不用交换
        T tmp = arr[maxIdx];
        arr[maxIdx] = arr[j];
        arr[j] = tmp;//进行交换
    }
}

template <class T>
void mergeSortAsc(T*& arr, int n) {
    int curLen = 1;//当前长度
    while (curLen < n) {
        T* arr2 = new T[n];
        for (int z = 0; z < n; z += 2 * curLen) {
            // merge [z,z+curLen) and [z+curLen,z+2*curLen)
            int i = z;
            int j = z + curLen;
            int k = z;
            //和链表并集一样的方法进行归并
            while (i < n && i < z + curLen && j < n && j < z + 2 * curLen) {
                if (arr[i] <= arr[j]) {
                    arr2[k] = arr[i];
                    i++;
                    k++;
                }
                else {
                    arr2[k] = arr[j];
                    j++;
                    k++;
                }
            }
            while (i < n && i < z + curLen) {
                arr2[k] = arr[i];
                i++;
                k++;
            }
            while (j < n && j < z + 2 * curLen) {
                arr2[k] = arr[j];
                j++;
                k++;
            }
        }
        //归并完之后每个集合的长度都是原来的两倍
        curLen = curLen * 2;
        delete[] arr;
        arr = arr2;
    }
}

int* generateRandom(int num, int min, int max) { //generate random numbers between min and max, inclusive
    int* tmp = new int[num];
    for (int i = 0; i < num; i++)
        tmp[i] = rand() % (max + 1 - min) + min;
    return tmp;
}

template <class T>
T* dupArray(T* arr, int n) {
    T* tmp = new T[n];
    for (int i = 0; i < n; i++) {
        tmp[i] = arr[i];
    }
    return tmp;
}


void printIArr(int* arr, int n) {
    // print, at most 10 per row
    int count = 0;
    for (int i = 0; i < n; i++) {
        cout << left << setw(10) << arr[i];
        count = (count + 1) % 10;
        if (count == 0) cout << endl;
    }
    if (count != 0) cout << endl;
    cout << endl;
}

int main() {
    srand(time(NULL));
    int* seq1 = generateRandom(70, 0, 100);
    int* seq2 = generateRandom(2000, 0, 100000);

    int* tmp = NULL;

    cout << "Sequence 1:" << endl;
    printIArr(seq1, 70);

    tmp = dupArray<int>(seq1, 70);
    insertionAsc<int>(tmp, 70);

    cout << "Insertion: " << endl;
    printIArr(tmp, 70);
    delete[] tmp;

    tmp = dupArray<int>(seq1, 70);
    insertionAscB<int>(tmp, 70);

    cout << "Insertion with Break: " << endl;
    printIArr(tmp, 70);
    delete[] tmp;

    tmp = dupArray<int>(seq1, 70);
    shellAsc<int>(tmp, 70);

    cout << "Shell: " << endl;
    printIArr(tmp, 70);
    delete[] tmp;

    cout << "Sequence 1:" << endl;
    printIArr(seq1, 70);

    tmp = dupArray<int>(seq1, 70);
    bubbleAsc<int>(tmp, 70);

    cout << "Bubble: " << endl;
    printIArr(tmp, 70);
    delete[] tmp;

    tmp = dupArray<int>(seq1, 70);
    bubbleAscS<int>(tmp, 70);

    cout << "Better Bubble: " << endl;
    printIArr(tmp, 70);
    delete[] tmp;

    tmp = dupArray<int>(seq1, 70);
    quickAsc<int>(tmp, 70, 0, 69);

    cout << "Quick Sort: " << endl;
    printIArr(tmp, 70);
    delete[] tmp;

    tmp = dupArray<int>(seq1, 70);
    selectionAsc<int>(tmp, 70);

    cout << "Selection Sort: " << endl;
    printIArr(tmp, 70);
    delete[] tmp;

    tmp = dupArray<int>(seq1, 70);
    cout << tmp << endl;
    mergeSortAsc<int>(tmp, 70);
    cout << tmp << endl;

    cout << "Merge Sort: " << endl;
    printIArr(tmp, 70);
    delete[] tmp;

    cout << "Insertion 70: ";
    clock_t start = clock();
    for (int i = 0; i < 10000; i++) {
        tmp = dupArray<int>(seq1, 70);
        insertionAsc<int>(tmp, 70);
        delete[] tmp;
    }
    clock_t end = clock();
    double timess = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Insertion 70 with break: ";
    start = clock();
    for (int i = 0; i < 10000; i++) {
        tmp = dupArray<int>(seq1, 70);
        insertionAscB<int>(tmp, 70);
        delete[] tmp;
    }
    end = clock();
    timess = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Shell 70: ";
    start = clock();
    for (int i = 0; i < 10000; i++) {
        tmp = dupArray<int>(seq1, 70);
        shellAsc<int>(tmp, 70);
        delete[] tmp;
    }
    end = clock();
    timess = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Shell with break 70: ";
    start = clock();
    for (int i = 0; i < 10000; i++) {
        tmp = dupArray<int>(seq1, 70);
        shellAscB<int>(tmp, 70);
        delete[] tmp;
    }
    end = clock();
    timess = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Bubble 70: ";
    start = clock();
    for (int i = 0; i < 10000; i++) {
        tmp = dupArray<int>(seq1, 70);
        bubbleAsc<int>(tmp, 70);
        delete[] tmp;
    }
    end = clock();
    timess = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Better Bubble 70: ";
    start = clock();
    for (int i = 0; i < 10000; i++) {
        tmp = dupArray<int>(seq1, 70);
        bubbleAscS<int>(tmp, 70);
        delete[] tmp;
    }
    end = clock();
    timess = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Quick Sort 70: ";
    start = clock();
    for (int i = 0; i < 10000; i++) {
        tmp = dupArray<int>(seq1, 70);
        quickAsc<int>(tmp, 70, 0, 69);
        delete[] tmp;
    }
    end = clock();
    timess = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Selection 70: ";
    start = clock();
    for (int i = 0; i < 10000; i++) {
        tmp = dupArray<int>(seq1, 70);
        selectionAsc<int>(tmp, 70);
        delete[] tmp;
    }
    end = clock();
    timess = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Merge Sort 70: ";
    start = clock();
    for (int i = 0; i < 10000; i++) {
        tmp = dupArray<int>(seq1, 70);
        mergeSortAsc<int>(tmp, 70);
        delete[] tmp;
    }
    end = clock();
    timess = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Insertion 2000: ";
    start = clock();
    for (int i = 0; i < 1000; i++) {
        tmp = dupArray<int>(seq2, 2000);
        insertionAsc<int>(tmp, 2000);
        delete[] tmp;
    }
    end = clock();
    timess = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Insertion 2000 with break: ";
    start = clock();
    for (int i = 0; i < 1000; i++) {
        tmp = dupArray<int>(seq2, 2000);
        insertionAscB<int>(tmp, 2000);
        delete[] tmp;
    }
    end = clock();
    timess = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Shell 2000: ";
    start = clock();
    for (int i = 0; i < 1000; i++) {
        tmp = dupArray<int>(seq2, 2000);
        shellAsc<int>(tmp, 2000);
        delete[] tmp;
    }
    end = clock();
    timess = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Shell with break 2000: ";
    start = clock();
    for (int i = 0; i < 1000; i++) {
        tmp = dupArray<int>(seq2, 2000);
        shellAscB<int>(tmp, 2000);
        delete[] tmp;
    }
    end = clock();
    timess = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Bubble 2000: ";
    start = clock();
    for (int i = 0; i < 1000; i++) {
        tmp = dupArray<int>(seq2, 2000);
        bubbleAsc<int>(tmp, 2000);
        delete[] tmp;
    }
    end = clock();
    timess = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Better Bubble 2000: ";
    start = clock();
    for (int i = 0; i < 1000; i++) {
        tmp = dupArray<int>(seq2, 2000);
        bubbleAscS<int>(tmp, 2000);
        delete[] tmp;
    }
    end = clock();
    timess = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Quick Sort 2000: ";
    start = clock();
    for (int i = 0; i < 1000; i++) {
        tmp = dupArray<int>(seq2, 2000);
        quickAsc<int>(tmp, 2000, 0, 1999);
        delete[] tmp;
    }
    end = clock();
    timess = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Selection 2000: ";
    start = clock();
    for (int i = 0; i < 1000; i++) {
        tmp = dupArray<int>(seq2, 2000);
        selectionAsc<int>(tmp, 2000);
        delete[] tmp;
    }
    end = clock();
    timess = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;

    cout << "Merge Sort 2000: ";
    start = clock();
    for (int i = 0; i < 1000; i++) {
        tmp = dupArray<int>(seq2, 2000);
        mergeSortAsc<int>(tmp, 2000);
        delete[] tmp;
    }
    end = clock();
    timess = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << timess << endl;
}