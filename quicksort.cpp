#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;
void swap(int* a, int* b)
{
int t = *a;
*a = *b;
*b = t;
}
int partition(int arr[], int low, int high)
{
int pivot = arr[high]; // pivot
int i
= (low- 1);
for (int j = low; j <= high - 1; j++) {
// If current element is smaller than the pivot
if (arr[j] < pivot) {
i++;
swap(&arr[i], &arr[j]);
}
}
swap(&arr[i + 1], &arr[high]);
return (i + 1);
}
void quickSort(int arr[], int low, int high)
{
if (low < high) {
/* pi is partitioning index, arr[p] is now
at right place */
int pi = partition(arr, low, high);
quickSort(arr, low, pi - 1);
quickSort(arr, pi + 1, high);
}
}
void printArray(int arr[], int size)
{
int i;
for (i = 0; i < size; i++)
cout << arr[i] << " ";
cout << endl;
}
// Driver Code
int main()
{
int n,k;
cout<<"Enter the number of elements: ";
cin>>n;
int arr[n];
cout<<"Enter the elements: ";
cout<<endl;
for(k=0;k<n;k++)
{
    cin>>arr[k];
}
cout << "Sorted array:";
auto start = chrono::steady_clock::now();
quickSort(arr, 0, n - 1);
auto end = chrono::steady_clock::now();
auto diff = end - start;
printArray(arr, n);
cout<< "Time:" << chrono::duration <double, milli> (diff).count() << " ms"
<< endl;
cout<< "Bytes:" << n*sizeof(arr[0])+ 2*sizeof(int) + 3*sizeof(int
*)+sizeof(start)<<endl;
return 0;
}