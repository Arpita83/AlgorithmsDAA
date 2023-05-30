//Selection Sort
#include<iostream>
#include<time.h>
using namespace std;
int main()
{ int n,i,j,k,l,m,temp,min;
clock_t time_req;
time_req=clock();
cout<<"enter size of the array";
cout<<endl;
cin>>n;
int a[n];
cout<<"enter elements"<<endl;
for (k=0;k<n;k++)
{cin>>a[k];}
for(i=0;i<n-1;i++)
{ min=i;
for(j=i+1;j<n;j++)
{ if(a[j]<a[min])
min=j;
{temp=a[i];
a[i]=a[min];
a[min]=temp;
}
}
cout<<"the array after pass"<<i+1<<endl;
for(l=0;l<n;l++)
{cout<<a[l]<<" ";}
cout<<endl;
}
cout<<"the sorted array is"<<endl;
for(m=0;m<n;m++)
{cout<<a[m]<<" ";}
cout<<endl;
time_req=clock()-time_req;
cout<<"the time taken is"<<endl;
cout<<(float)time_req/CLOCKS_PER_SEC<<"seconds"<<endl;
cout<<"The bytes occupied is"<<endl;
cout<<(sizeof(a[n])*n)+sizeof(temp)+sizeof(n)+sizeof(i)+sizeof(j)+sizeof(k)+sizeof(l)+sizeof(m)+sizeof(min);
}
