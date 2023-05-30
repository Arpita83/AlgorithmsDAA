#include<iostream>
#include<vector>
#include<queue>
#include<time.h>

using namespace std;

struct node
{
  int val;
  struct node* left;
  struct node* right;  
};

node* newNode(int x)
{
  node* temp = new node;
  temp->val=x;
  temp->left=NULL;
  temp->right=NULL; 
  return temp; 
}

int main()
{
  node* root = newNode(1); 
  clock_t start,end;
  
  root->left = newNode(3);
  root->right = newNode(2);
  root->left->left = newNode(7);
  root->left->right = newNode(6);
  root->right->left = newNode(4);
  root->right->right = newNode(5);
 
  cout<<"BFS traversal : ";
  start = clock();
  queue<node *> q;
  q.push(root);

  while(q.empty()==false)
    {
       node* Node = q.front();
       cout<<Node->val<<" ";
       q.pop();
       if(Node->left!= NULL)
         {
           q.push(Node->left);
         } 
       if(Node->right!=NULL)
         {
           q.push(Node->right); 
         }  
    }
  end = clock();
  double totaltime = double(end-start) / double (CLOCKS_PER_SEC);
  cout<<endl<<"Execution Time : "<<totaltime<<endl;  
  return 0;  
}