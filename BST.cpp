// Binary search tree and all of its operations
// code by - Suhotra Dey
#include<iostream>
#include<stdlib.h>
using namespace std;
class Node{
    public:
    Node *lchild;
    int data;
    Node *rchild;
};
Node *root;
Node* arr[100];
int top=-1;
class BST{
    public:
    BST(){
        root=NULL;
    }
    ~BST(){
        if(root!=NULL)
	    {
		    delete(root->lchild);
		    delete(root->rchild);
		    delete(root);
	    }
    }
    Node* insert(int);
    void PrintinOrder(Node*);
    void PrintpreOrder(Node*);
    void PrintpostOrder(Node*);
    Node* smallest(Node*);
    Node* largest(Node*);
    Node* minValueNode(Node*);
    Node* deleteNode(Node*,int);
    int totalNodes(Node*);
    int externalNodes(Node*);
    int internalNodes(Node*);
    int height(Node*);
    void inorderiterative(Node*);
};
Node* BST::insert(int item){
    Node *curr=new Node();
    curr->data=item;
    curr->lchild=NULL;
    curr->rchild=NULL;
    if(root==NULL){
        root=curr;
        root->lchild=NULL;
        root->rchild=NULL;
    }
    else{
        Node *temp=root;
        Node *parent=NULL;
        while(temp!=NULL){
            parent=temp;
            if(item<temp->data){
                temp=temp->lchild;
            }
            else{
                temp=temp->rchild;
            }
        }
        if(item<parent->data){
            parent->lchild=curr;
        }
        else{
            parent->rchild=curr;
        }
    }
    return root;
}
void BST::PrintinOrder(Node* root){
    if(root==NULL){
        return;
    }
    else{
        PrintinOrder(root->lchild);
        cout<<root->data<<" ";
        PrintinOrder(root->rchild);
    }
}
void BST::PrintpreOrder(Node* root){
    if(root==NULL){
        return;
    }
    else{
        cout<<root->data<<" ";
        PrintpreOrder(root->lchild);
        PrintpreOrder(root->rchild);
    }
}
void BST::PrintpostOrder(Node *root){
    if(root==NULL){
        return;
    }
    else{
        PrintpostOrder(root->lchild);
        PrintpostOrder(root->rchild);
        cout<<root->data<<" ";
    }   
}
Node* BST::smallest(Node *root){
    if((root==NULL)||(root->lchild==NULL))
		return root;
	else
		return smallest(root->lchild);
}
Node* BST::largest(Node *root){
    if((root==NULL)||(root->rchild==NULL))
		return root;
	else
		return largest(root->rchild);
}
Node *BST::minValueNode(Node *node)
{
	Node *current=node;
	while(current && current->lchild!=NULL)
		current=current->lchild;
	return current;
}
Node* BST::deleteNode(Node *root,int key)
{
	//base case
	if(root==NULL)
		return root;
	//If the key to be deleted is smaller than the root's key, then it lies in left subtree.
	if(key<root->data)             
		root->lchild=deleteNode(root->lchild,key);
	//If the key to be deleted is greater than the root's key, the it lies in right subtree.
	else if(key>root->data)
		root->rchild=deleteNode(root->rchild,key);
	//if the key is same as root's key, then this is the node to be deleted.
	else
	{
		// node with only one child or no child.
		if(root->lchild==NULL)
		{
			Node *temp=root->rchild;
			delete(root);
			return temp;
		}
		else if(root->rchild==NULL)
		{
		    Node *temp=root->lchild;
			delete(root);
			return temp;
		}
		// node with two children, get the inorder succesor (smallest in the right subtree.)
		Node *temp=minValueNode(root->rchild);
		//copy the inorder successor's content to this node.
		root->data=temp->data;
		//delete the inorder successor.
		root->rchild=deleteNode(root->rchild,temp->data);
	}
	return root;
}
int BST::totalNodes(Node *root)
{
	if(root==NULL)
		return 0;
	else
		return(totalNodes(root->lchild)+totalNodes(root->rchild)+1);
}
int BST::externalNodes(Node *root)
{
	if(root==NULL)
		return 0;
	else if((root->lchild==NULL)&&(root->rchild==NULL))
		return 1;
	else
		return (externalNodes(root->lchild)+externalNodes(root->rchild));
}
int BST::internalNodes(Node *root)
{
	if((root==NULL)||(root->lchild==NULL)&&(root->rchild==NULL))
		return 0;
	else
		return (internalNodes(root->lchild)+internalNodes(root->rchild)+1);
}
int BST::height(Node *root)
{
	int lh,rh;
	if(root==NULL)
		return 0;
	else
	{
		lh=height(root->lchild);
		rh=height(root->rchild);
		if(lh>rh)
			return (lh+1);
		else
			return (rh+1);
	}
}
void push(Node* x){
    arr[++top]=x;
}
Node* pop(){
    Node *ptr=arr[top];
    top--;
    return ptr;
}
int isEmpty(){
    if(top==-1){
        return 1;
    }
    return 0;
}
void BST::inorderiterative(Node* root){
    if(root==NULL){
        return;
    }
    Node *temp= root;
    while(temp!=NULL || !isEmpty()){
        while(temp!=NULL){
            push(temp);
            temp=temp->lchild;
        }
        temp=pop();
        cout<<temp->data<<" ";
        temp=temp->rchild;
    }
}
static int count=0;
void kthlargest(Node* root,int k){
    if(root!=NULL && count<=k){
        kthlargest(root->rchild,k);
        count++;
        if(count==k){
            cout<<root->data<<" ";
        }
        kthlargest(root->lchild,k);
    }
}
int getsum(Node* root,int l,int h){
    if(root==NULL)
        return 0;
    if (root->data < l)
        return getsum(root->rchild,l,h);
    if (root->data > h)
        return getsum(root->lchild,l,h);
    if(root->data >=l && root->data<=h)
    {
        return (getsum(root->lchild,l,h) + getsum(root->rchild,l,h) + root->data);
    }
}
int main(){
    class BST bst;
    int element,choice,l,h; 
    Node *ptr;
    while(1){
    cout<<endl;
    cout<<"...............BINARY SEARCH TREE...................."<<endl;
    cout<<"1.Insert Element."<<endl;
    cout<<"2.Print pre Order."<<endl;
    cout<<"3.Print in order."<<endl;
    cout<<"4.print post Order."<<endl;
    cout<<"5.Smallest element."<<endl;
    cout<<"6.Largest element."<<endl;
    cout<<"7.Delete element."<<endl;
    cout<<"8.total number of nodes"<<endl;
    cout<<"9.total number of external nodes"<<endl;
    cout<<"10.total number of internal nodes"<<endl;
    cout<<"11.Total Height tree"<<endl;
    cout<<"12.iterative inorder"<<endl;
    cout<<"13.kth largest element"<<endl;
    cout<<"13.Sum of elements between two numbers in tree "<<endl;
    cout<<"Enter your choice : ";
    cin >> choice;
    switch(choice){
        case 1:
            cout<<"Enter the value of the new node : ";
            cin >> element;
            bst.insert(element);
            break;
        case 2:
            cout<<"The elements of the tree are: \n";
            bst.PrintpreOrder(root);
            break;
        case 3:
            cout<<"The elements of the tree are: \n";
            bst.PrintinOrder(root);
            break;
        case 4:
            cout<<"The elements of the tree are: \n";
            bst.PrintpostOrder(root);
            break;
        case 5:
            ptr=bst.smallest(root);
            cout<<"Smallest element is: "<<ptr->data;
            break;
        case 6:
            ptr=bst.largest(root);
            cout<<"Largest element is: "<<ptr->data;
            break;
        case 7:
            cout<<"Enter the element to be deleted: ";
            cin>> element;
            bst.deleteNode(root,element);
            break;
        case 8:
            cout<<"Total no. of nodes = "<<bst.totalNodes(root);
            break;
        case 9:
            cout<<"Total no. of external nodes = "<<bst.externalNodes(root);
            break;
        case 10:
            cout<<"Total no. of internal nodes = "<<bst.internalNodes(root);
            break;
        case 11:
            cout<<"The height of the tree = "<<bst.height(root);
            break;
        case 12:
            cout<<"The elements of the tree are: \n";
            bst.inorderiterative(root);
            break;
        case 13:
            cout<<"enter the kth value : ";
            cin>>element;
            count=0;
            kthlargest(root,element);
            break;
        case 14:
            cout<<"Enter the range :";
            cin>>l>>h;
            cout<<"SUM = "<<getsum(root,l,h);
            break;
        case 15:
            exit(0);
        }
    }
}
