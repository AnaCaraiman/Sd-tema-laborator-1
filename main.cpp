#include <iostream>
#include<cstdlib>
#include<algorithm>
#include<ctime>
#include<vector>

#define CUTOFF 12
using namespace std;

// Print an array
void printArray(int array[], int size) {
    int i;
    for (i = 0; i < size; i++)
        cout << array[i] << " ";
    cout << endl;
}//radix:
int getMax(int v[], int n) {
    int Max = v[0];
    for (int i = 1; i < n; i++)
        if (Max < v[i])
            Max = v[i];
    return Max;
}

void countSort(int v[], int n, int c) {
    int *output = new int[n + 1];
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(v[i] / c) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(v[i] / c) % 10] - 1] = v[i];
        count[(v[i] / c) % 10]--;
    }

    for (int i = 0; i < n; i++)
        v[i] = output[i];
    delete[] output;
}

void radixSort(int v[], int n) {
    int Max = getMax(v, n);

    for (int c = 1; Max / c > 0; c *= 10) {
        countSort(v, n, c);
    }
}
//merge:

void mergeArrays(int v[], int left, int m, int right) {
    int i, j, k;
    int nl = m - left + 1;
    int nr = right - m;

    int *L = new int[nl];
    int *R = new int[nr];

    for (i = 0; i < nl; i++)
        L[i] = v[left + i];
    for (j = 0; j < nr; j++)
        R[j] = v[m + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < nl && j < nr) {
        if (L[i] <= R[j]) {
            v[k] = L[i];
            i++;
        } else {
            v[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < nl) {
        v[k++] = L[i];
        i++;
    }

    while (j < nr) {
        v[k++] = R[j];
        j++;
    }
    delete[] L;
    delete[] R;
}

void mergeSort(int v[], int left, int right) {
    if (left < right) {
        int m = left + (right - left) / 2;
        mergeSort(v, left, m);
        mergeSort(v, m + 1, right);
        mergeArrays(v, left, m, right);
    }
}
//shellsort:
void shellSort(int array[], int n) {
    for (int interval = n / 2; interval > 0; interval /= 2) {
        for (int i = interval; i < n; i += 1) {
            int temp = array[i];
            int j;
            for (j = i; j >= interval && array[j - interval] > temp; j -= interval) {
                array[j] = array[j - interval];
            }
            array[j] = temp;
        }
    }
}
//heapsort:
void heapify(int arr[], int n, int i) {

    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;


    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);


    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);

        heapify(arr, i, 0);
    }
}
//quicksort - mediana din 3:
void exchange(int* v, int A, int B) {
    int t = v[A];
    v[A] = v[B];
    v[B] = t;
}


void insertion_sort(int* a, int lo, int hi) {
    for (int i = hi; i > lo; i--) {
        if (a[i] < a[i-1]) exchange(a, i-1, i);
    }
    for (int i = lo+2; i <= hi; i++) {
        int j = i;
        int v = a[i];
        while (v < a[j-1]) {
            a[j] = a[j-1];
            j--;
        }
        a[j] = v;
    }
}

int partition(int* a, int lo, int hi) {
    int i = lo, j = hi+1;
    int v = a[lo];
    while(1) {
        while (a[++i] < v) {
            if (i == hi) break;
        }
        while (v < a[--j]) {
            if (j == lo) break;
        }
        if (i >= j) break;
        exchange(a, i, j);
    }
    exchange(a, lo, j);
    return j;
}


int median_of_3(int* a, int lo, int hi) {
    int mid = lo + (hi-lo)/2;
    if (a[hi] < a[lo]) exchange(a, lo, hi);
    if (a[mid] < a[lo]) exchange(a, lo, mid);
    if (a[hi] < a[mid]) exchange(a, mid, hi);
    return mid;
}


void quick_sort(int* a, int lo, int hi) {
    if (hi <= lo + CUTOFF - 1) {
        insertion_sort(a, lo, hi);
        return;
    }
    int median = median_of_3(a, lo, hi);
    exchange(a, lo, median);
    int j = partition(a, lo, hi);
    quick_sort(a, lo, j-1);
    quick_sort(a, j+1, hi);
}



int main() {
    clock_t start;
    clock_t end;
    int N=1,T,Max=1,p,f;
    cout<<"Puterea lui 10 pentru numere="; cin>>f;
    cout<<"T="; cin>>T;
    cout<<"Puterea lui 10 pentru maxim="; cin>>p;
    for(int i=1; i<=p;i++ )
        Max=Max*10;
    for(int i=1; i<=f;i++ )
        N=N*10;
    srand((unsigned) time(NULL));
int *V;
    for(int i=1; i<=T; i++)
    {
        V=new int[N];
        //generare numere:

        for(int j=0; j<N; j++)
        {V[j]=rand() % (Max + 1);}

        double time_start=clock();
         //radixSort(V, N);
        //mergeSort(V, 0, N - 1);
        //shellSort(V, N);
        //heapSort(V, N);
        quick_sort(V,0,N-1);
        double time_final=clock();

        double time_dif=double(time_final-time_start)/(double)CLOCKS_PER_SEC;



        delete[] V;
        cout<<time_dif<<" "<<"\n";










    }


    return 0;
}
