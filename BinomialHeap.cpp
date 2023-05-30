#include<bits/stdc++.h>
using namespace std;

 
struct BNode
{
    int key;
    int order;
    
    //sibling, parent and child pointers.
    BNode *sibling, *parent, *child;
    
    //Parameterised Constructor
    BNode(int key)
    {
        this -> key = key;
        this -> order = 0;
        this -> sibling = this -> parent = this -> child = NULL;
    }
};

 
class BHeap
{
    //Node that points to the leftmost binomial tree.
    BNode *head;
    
    //Node that points to the minimum value.
    BNode *min;
    
    //Function to combine two trees.
    void combineTrees(BNode *root1, BNode *root2)
    {
        
        //Making sure that root2 has smaller key value
        if(root1->key < root2->key){
            swap(root1,root2);
        }
        
        /*
            Assuming root1->key >= root2->key
            then root2 must be parent of root1.
        */
        
        root1 -> parent = root2;
        root1 -> sibling = root2 -> child;
        root2 -> child = root1;
        
        //Increasing the order of second tree.
        root2 -> order = root2 -> order + 1;
    }
    
    
    /*
        This function will merge given two heaps 
        in non- increasing value of their orders/degrees.
    */
    
    BNode* combineHeaps(BHeap *heap1, BHeap *heap2)
    {
        //Temporary Nodes to merge two heads.
        BNode *temp1 = new BNode(0);
        BNode *temp2 = temp1;
        
        //Initializing the roots of each head.
        BNode *root1 = heap1 -> head;
        BNode *root2 = heap2 -> head;
        
        //if one of the roots is null return other one.
        if (root1 == NULL) return root2;
        if (root2 == NULL) return root1;
        
        //Combining the roots to make a new heap in increasing value of orders.
        while (root1 != NULL || root2 != NULL)
        {
            if (root1 == NULL)
            {
                temp2 -> sibling = root2;
                temp2 = temp2 -> sibling;
                root2 = root2 -> sibling;
            }
            else if (root2 == NULL)
            {
                temp2 -> sibling = root1;
                temp2 = temp2 -> sibling;
                root1 = root1 -> sibling;
            }
            else
            {
                if (root1 -> order < root2 -> order)
                {
                    temp2 -> sibling = root1;
                    temp2 = temp2 -> sibling;
                    root1 = root1 -> sibling;
                }
                else
                {
                    temp2 -> sibling = root2;
                    temp2 = temp2 -> sibling;
                    root2 = root2 -> sibling;
                }
            }
        }
        return (temp1 -> sibling);
    }

public:
 
    //Empty Heap Constructor
    BHeap() {
        this -> head = NULL;
    }
    
    //binomial heap with given node.
    BHeap(BNode* root){
        this -> head = root;
    }
    
    //Return true or false based on if the heap is empty or not.
    bool isEmpty(){
        return (this -> head == NULL);
    }
    
    void insert(BNode* root){
        
        BHeap* newHeap=new BHeap(root);
        this -> unionHeap(newHeap);
    }
    
    void unionHeap(BHeap *heap)
    {
        //New heap to hold the union of two heaps.
        BHeap *heap_final = new BHeap();
        
        //Merging two heaps.
        heap_final -> head = combineHeaps(this, heap);
        
        //If both heaps are empty, heap_final will also be empty.
        if (heap_final -> head == NULL)
        {
            this -> head = NULL;
            this -> min = NULL;
            return;
        }
        
        //three pointers prev, curr and next.
        BNode *prev = NULL;
        BNode *curr = heap_final -> head;
        BNode *next = curr -> sibling;
        
        //checking all four cases for curr and next pointer.
        while (next != NULL)
        {
            //Case 1: when order[curr]!=order[next] 
            if (curr -> order != next -> order){
                prev = curr;
                curr = next;
            }
            
            //Case 2: when order[curr]==order[next]==order[sibling(next)] 
            else if( curr -> order == next -> order && next -> sibling != NULL && next -> sibling -> order == curr -> order){
                prev = curr;
                curr = next;
            }
            
            //Case 3
            else if (curr -> key <= next -> key){
                curr -> sibling = next -> sibling;
                combineTrees(next, curr);
            }
            
            //Case 4
            else{
                if (prev == NULL) heap_final -> head = next;
                else prev -> sibling = next;
                combineTrees(curr, next);
                curr = next;
            }
            next = curr -> sibling;
        }
        
        this -> head = heap_final -> head;
        
        //Updating minimum node.
        this -> min = heap_final -> head;
        curr = this -> head;
        while (curr != NULL)
        {
            if (curr -> key < this -> min -> key) this -> min = curr;
            curr = curr -> sibling;
        }
    }
    
    BNode* first()
    {
        return this -> min;
    }
    
    BNode* extractMin()
    {
        // Minimum Node
        BNode *mini = this -> first();
        
        // Delete minimum node from the list of head
        BNode *prev = NULL;
        BNode *curr1 = this -> head;
        while (curr1 != mini)
        {
            prev = curr1;
            curr1 = curr1 -> sibling;
        }
        
        /*
            If prev is null it means starting node is itself minimum.
            So, we update head to sibling of head.
        */
        if (prev == NULL) this -> head = curr1 -> sibling;
        
        //Removing the minimum node from the heap.
        else prev -> sibling = curr1 -> sibling;
        
        // Reverse the list of minimum node children
        BNode *RevNode = NULL;
        BNode *curr2 = mini -> child;
        while (curr2 != NULL)
        {
            BNode *next = curr2 -> sibling;
            curr2 -> sibling = RevNode;
            RevNode = curr2;
            curr2 = next;
        }
        
        /*
            Merge the two heaps, the original one and the one 
            containing the children of minimum node.
        */
        BHeap *temp = new BHeap();
        temp -> head = RevNode;
        this -> unionHeap(temp);
        
        //return minimum node.
        return mini;
    }
    
    void decreaseKey(BNode *root, int val)
    {
        
        //Checking if the current val is less than root's value or not.
        if(val > root->key){
            cout<<"Error! New value greater than current key!\n";
            return;
        }
        
        //Updating the root
        root -> key = val;
        
        //Temporary nodes to update the minimum to the top of the heap.
        BNode *temp1 = root;
        BNode *temp2 = temp1 -> parent;
        while (temp2 != NULL && temp1 -> key < temp2 -> key)
        {
            // Swapping value of parent's key and current key.
            swap(temp1 -> key, temp2 -> key);
            
            temp1 = temp2;
            
            //Updating Parent node
            temp2 = temp1 -> parent;
        }
        
        //Updating the minimum node in the heap.
        if (temp1 -> key < this -> min -> key) this -> min = temp1;
    }

 
    void Delete(BNode *root)
    {
        decreaseKey(root, INT_MIN);
        extractMin();
    }
    
    //Level order traversal of the tree.
    void printTree(BNode* root){
        
        if(root==nullptr){
            return;
        }
        
        queue<BNode*> q;
		q.push(root);
		while (!q.empty()) {
			BNode* node = q.front();
			q.pop();
			cout<<node->key<<" ";

 	
			if (node->child != nullptr) {
				BNode* temp = node->child;
					while (temp != nullptr) {
						q.push(temp);
						temp = temp->sibling;
					}
			} 
		}
   }
    
    void printHeap() {
		BNode* curr = head;
		while (curr != nullptr) {
			cout<<"B"<<curr->order<<endl;
			cout<<"There are "<<pow(2, curr->order)<<" nodes in this binomial tree"<<endl;
			cout<<"The level order traversal of the tree is ";
			this->printTree(curr);
			curr = curr->sibling;
			cout<<endl<<endl;
		}
	}
};

 
int main()
{
    BHeap *heap1 = new BHeap();
    heap1->insert(new BNode(2));
    heap1->insert(new BNode(7));
    heap1->insert(new BNode(13));
    heap1->insert(new BNode(8));
    heap1->insert(new BNode(1));
    
    
    cout<<"Printing Binomial Heap !!!\n\n";
    heap1->printHeap();
    
    cout<<"Extracting Minimum value from the Heap.\n";
    cout<<"Minimum key is "<<(heap1 -> extractMin()) -> key<<endl<<endl;
    cout<<"Printing Binomial Heap After Extracting Minimum Value!!!\n\n";
    heap1->printHeap();
    
    cout<<"Extracting Minimum value from the Heap.\n";
    cout<<"Minimum key is "<<(heap1 -> extractMin()) -> key<<endl<<endl;
    cout<<"Printing Binomial Heap After Extracting Minimum Value!!!\n\n";
    heap1->printHeap();
}