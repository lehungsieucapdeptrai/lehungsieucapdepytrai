#include <bits/stdc++.h>
#define _for(i,a,b) for(int i=(a),_b=(b);i<_b;++i)

using namespace std;

const string FOLDER_NAME = "Test";
const string TAIL = ".inp";
const int N = 1e6;
const int MAX = 1e6 + 9;

string FILE_NAME[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};

/// Sinh Test
double fRand(double fMin, double fMax)
{
    double f1 = (double)rand() * rand();
    double f2 = (double)RAND_MAX * RAND_MAX;
    double f = f1 / f2;
    return fMin + f * (fMax - fMin);
}

void CreateFile(string NAME)
{
    freopen((FOLDER_NAME + "/test" + NAME + TAIL).c_str(), "w", stdout);

    cout.precision(3);

    vector<double> a;

    for (int i=0; i<N; ++i)
    {
        double bound = fRand(0.0, N);
        a.push_back(fRand(-bound, bound));
    }

    if (NAME == "1")
        sort(a.begin(), a.end());
    else if (NAME == "2")
        sort(a.begin(), a.end(), greater<double>());

    for (auto i: a)
        cout << fixed << i << " ";
}

void SinhTest()
{
    srand(time(NULL));

    for (auto NAME: FILE_NAME)
    {
        CreateFile(NAME);
    }
}

vector<double> VectorInput, a;

/// Heap sort
double h[MAX];
int s;
void up(int i)
{
    if(i == 1) return;
    if (h[i] < h[i/2])
    {
        swap(h[i], h[i/2]);
        up(i/2);
    }
}

void down(int i)
{
    int pos = i;
    if (i*2 <=s && h[pos] > h[i*2]) pos = 2*i;
    if (i*2 + 1 <= s && h[pos] > h[i*2 + 1]) pos = i*2 + 1;
    if (pos != i)
    {
        swap(h[pos], h[i]);
        down(pos);
    }
}

void push(int val)
{
    h[++s] = val;
    up(s);
}
void pop()
{
    h[1] = h[s--];
    down(1);
}
void heapsort()
{
    for (int i = 1; i <= N; i++)
    {
        push(a[i]);
    }
    for(int i = 1; i <= N; i++)
    {
        a[i] = h[1];
        pop();
    }
}

/// Merge sort
void Merge(int low, int mid, int high)
{
    int i, j, k;
    int n1 = mid - low + 1;
    int n2 =  high - mid;

    vector<double> L, R;

    for (i=0; i<n1; ++i)
        L.push_back(a[low + i]);
    for (j=0; j<n2; ++j)
        R.push_back(a[mid + 1 + j]);

    i = 0;
    j = 0;
    k = low;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            a[k] = L[i];
            i++;
        }
        else
        {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        a[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        a[k] = R[j];
        j++;
        k++;
    }
}

void mergesort(int low, int high)
{
    if (low < high)
    {
        int mid = low + ((high-low) >> 1);

        mergesort(low, mid);
        mergesort(mid+1, high);

        Merge(low, mid, high);
    }
}

void quicksort (int l, int r){
    if (l == r)
        return;
    else{
        int mid = (l+r)>>1;
        int i = l , j = r;
        while (i <= j){
            while(a[i] < a[mid]) i++;
            while(a[j] > a[mid]) j--;
            if (i <= j){
                swap(a[i],a[j]);
                i++;
                j--;
            }
        }
        if (l < j) quicksort(l,j);
        if (r > i) quicksort(i,r);
    }
}

vector<double> Time;

void ChamBai(string NAME)
{
    double time_use;
    clock_t start, end;

    a = VectorInput;
    start = clock();
    heapsort();
    end = clock();
    time_use = (double)(end - start)/CLOCKS_PER_SEC;
    Time.push_back(time_use);

    a = VectorInput;
    a.erase(a.begin());
    start = clock();
    mergesort(0, N-1);
    end = clock();
    time_use = (double)(end - start)/CLOCKS_PER_SEC;
    Time.push_back(time_use);

    a = VectorInput;
    start = clock();
    quicksort(1, N);
    end = clock();
    time_use = (double)(end - start)/CLOCKS_PER_SEC;
    Time.push_back(time_use);

    a = VectorInput;
    a.erase(a.begin());
    start = clock();
    sort(a.begin(), a.end());
    end = clock();
    time_use = (double)(end - start)/CLOCKS_PER_SEC;
    Time.push_back(time_use);
}

int main()
{
//    SinhTest();

    for (auto NAME: FILE_NAME)
    {
        ifstream cin((FOLDER_NAME + "/test" + NAME + TAIL).c_str());
        VectorInput.clear();
        VectorInput.push_back(0);
        for (int i=0; i<N; ++i)
        {
            double x;
            cin >> x;
            VectorInput.push_back(x);
        }
        ChamBai(NAME);
    }

    freopen("TimeReport.csv", "w", stdout);

    cout << "id,Heap Sort,Merge Sort,Quick Sort,Sort C++\n";
    int i = 0;
    for (int j=1; j<=10; ++j)
    {
        cout << j << ",";
        for (int k=0; k<3; ++k)
            cout << Time[i++] * 1000.0 << ",";
        cout << Time[i++] * 1000.0 << "\n";
    }

    return 0;
}
