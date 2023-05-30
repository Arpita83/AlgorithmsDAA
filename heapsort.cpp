#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;
void heapSort(int pq[], int n) {
//build heap in input array
for(int i=1; i< n; i++){
int childIndex = i;
while(childIndex>0){
int parentIndex = (childIndex-1)/2;
if(pq[childIndex]< pq[parentIndex]){
int temp = pq[childIndex];
pq[childIndex]= pq[parentIndex];
pq[parentIndex]= temp;
}
else {
break;
}
childIndex= parentIndex;
}
}
//Remove Elements
int size =n;
int iter=1;
while (size>1){
int temp = pq[0];
pq[0]= pq[size-1];
pq[size-1] = temp;
size--;
int parentIndex = 0;
int leftchildIndex = 2*parentIndex +1 ;
int rightchildIndex = 2*parentIndex +2;
while (leftchildIndex <size){
int minIndex = parentIndex;
if (pq[minIndex]> pq[leftchildIndex]){minIndex = leftchildIndex;}
if (rightchildIndex< size and pq[minIndex]>
pq[rightchildIndex]){minIndex = rightchildIndex;}
if (minIndex== parentIndex){
break;
}
int temp = pq[minIndex];
pq[minIndex]= pq[parentIndex];
pq[parentIndex]= temp;
parentIndex= minIndex;
leftchildIndex = 2*parentIndex +1 ;
rightchildIndex = 2*parentIndex +2;
cout<<"PASS"<<iter<<" ";
iter++;
for(int i=0; i< n; i++){
cout<<pq[i]<<" ";
}
cout<<endl;
}
cout<<"PASS"<<iter<<" ";
iter++;
for(int i=0; i< n; i++){
cout<<pq[i]<<" ";
}
cout<<endl;
}
}
int main() {
int size;
cin >> size;
int *input = new int[size];
for (int i = 0; i < size; i++) {
cin >> input[i];
}
auto start = chrono::steady_clock::now();
heapSort(input, size);
auto end = chrono::steady_clock::now();
auto diff = end - start;
for (int i = 0; i < size; i++) {
cout << input[i] << " ";
}
cout<< "Time:" << chrono::duration <double, milli> (diff).count() << " ms"
<< endl;
cout<< "Bytes:" << size*sizeof(input[0])+ sizeof(int) + 3*sizeof(int
*)<<endl;
delete[] input;
}