#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// просіювання вниз
void siftDown(vector<long long>& a, int i, int size, int d) {
    while (true) {
        long long firstChild = (long long)d * i + 1;
        if (firstChild >= size) break; 

        long long lastChild = (long long)d * i + d;
        if (lastChild > size - 1) lastChild = size - 1;

        int largestChild = (int)firstChild;
        long long largestVal = a[(int)firstChild];
        for (long long c = firstChild + 1; c <= lastChild; ++c) {
            if (a[(int)c] > largestVal) {
                largestVal = a[(int)c];
                largestChild = (int)c;
            }
        }

        if (largestVal > a[i]) {
            swap(a[i], a[largestChild]);
            i = largestChild;
        }
        else {
            break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream farr("array.txt");
    if (!farr) {
        cerr << "Не вдалося відкрити array.txt\n";
        return 1;
    }
    int n;
    farr >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) farr >> a[i];

    ifstream fpar("params.txt");
    if (!fpar) {
        cerr << "Не вдалося відкрити params.txt\n";
        return 1;
    }
    int d, m;
    fpar >> d >> m;
    int p1, p2, p3;
    fpar >> p1 >> p2 >> p3;

    int size = n;

    // побудова піраміди методом флойда
    int lastParent = (size - 2) / d;
    for (int i = lastParent; i >= 0; --i) {
        siftDown(a, i, size, d);
    }
    cout << a[p1] << " " << a[p2] << " " << a[p3] << "\n";

    for (int step = 0; step < m && size > 1; ++step) {
        swap(a[0], a[size - 1]);
        --size;
        siftDown(a, 0, size, d);
    }
    cout << a[p1] << " " << a[p2] << " " << a[p3] << "\n";

    while (size > 1) {
        swap(a[0], a[size - 1]);
        --size;
        siftDown(a, 0, size, d);
    }
    cout << a[p1] << " " << a[p2] << " " << a[p3] << "\n";

    return 0;
}