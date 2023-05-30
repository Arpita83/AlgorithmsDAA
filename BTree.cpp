#include<iostream>
using namespace std;
#define  order 5
struct Btree
{
  int* d;
  Btree**childptr;
  bool l;
  int n;
}*r=NULL,*np=NULL,*x=NULL;
Btree* init()
{
    int i;
    np=new Btree;
    np->d=new int [order];
    np->childptr= new Btree*[order+1];
    np->l=true;
    np->n=0;
    for (i = 0; i < 7; i++) {
      np->childptr[i] = NULL;
   }
   return np;
}
void traverse(Btree* p)
{
     cout<<endl;
     int i;
     for (i=0;i<p->n;i++)
     {
        if(p->l==false)
        {
        traverse(p->childptr[i]);
        }
        cout<<" "<<p->d[i];
     }
     if(p->l==false)
     {
        traverse(p->childptr[i]);
     }
     cout<<endl;
}
void sort(int*p,int n)
{
    int i, j, t;
   for (i = 0; i < n; i++) {
      for (j = i; j <= n; j++) {
         if (p[i] >p[j]) {
            t = p[i];
            p[i] = p[j];
            p[j] = t;
         }
      }
   
}
}
int splitchild(Btree *x, int i) {
   int j, mid;
   Btree *np1, *np3, *y;
   np3 = init();//create new node
   np3->l = true;
   if (i == -1) {
      mid = x->d[2];//find mid
      x->d[2] = 0;
      x->n--;
      np1 = init();
      np1->l= false;
      x->l= true;
      for (j = (order/2); j < order; j++) {
         np3->d[j -(order/2)] = x->d[j];
         np3->childptr[j - (order/2)] = x->childptr[j];
         np3->n++;
         x->d[j] = 0;
         x->n--;
      }
      for (j = 0; j < order; j++) {
         x->childptr[j] = NULL;
      }
      np1->d[0] = mid;
      np1->childptr[np1->n] = x;
      np1->childptr[np1->n + 1] = np3;
      np1->n++;
      r = np1;
   } else {
      y = x->childptr[i];
      mid = y->d[order/2];
      y->d[order/2] = 0;
      y->n--;
      for (j = (order/2); j <order ; j++) {
         np3->d[j - (order/2)] = y->d[j];
         np3->n++;
         y->d[j] = 0;
         y->n--;
      }
      x->childptr[i + 1] = y;
      x->childptr[i + 1] = np3;
   }
   return mid;
}
void insert(int a)
{
    int i,t;
    x=r;
    if(x==NULL)
    {
        r=init();
        x=r;
    }
    else{
        if(x->l==true && x->n==5)
        {
            t=splitchild(x,-1);
            x=r;
             for (i = 0; i < (x->n); i++) {
            if ((a >x->d[i]) && (a < x->d[i + 1])) {
               i++;
               break;
            } else if (a < x->d[0]) {
               break;
            } else {
               continue;
            }
            x=x->childptr[i];
         }
        }
         else
         {
            while(x->l==false)
            {
                for (i = 0; i < (x->n); i++) {
               if ((a >x->d[i]) && (a < x->d[i + 1])) {
                  i++;
                  break;
               } else if (a < x->d[0]) {
                  break;
               } else {
                  continue;
               }
            }
            if ((x->childptr[i])->n == 5) {
               t = splitchild(x, i);
               x->d[x->n] = t;
               x->n++;
               continue;
            } else {
               x = x->childptr[i];
            }
            }
            
         }
    }
     x->d[x->n] = a;
   sort(x->d, x->n);
   x->n++;
}
int main() {
   int i, n, t;
   cout<<"enter the no of elements to be inserted\n";
   cin>>n;
   for(i = 0; i < n; i++) {
      cout<<"enter the element\n";
      cin>>t;
      insert(t);
   }
   cout<<"traversal of constructed B tree\n";
   traverse(r);
}