#include<iostream>
#include<stdio.h>

using namespace std;
struct node{
		int low;
		int high;
		int maxvalue;
		node *left;
		node *right;
		node *p;
	   };
node *root;
void insert(node* z)
{	node* y=NULL;
	node* x=root;
	    while(x!=NULL)
	    {
	        y=x;
	        if(z->low<x->low)
		            x=x->left;
	        else
		            x=x->right;
    	    }
    	z->p=y;
    	if(y==NULL)
   	     root=z;
    	else if(z->low<y->low)
   	     y->left=z;
    	else
    	     y->right=z;
}
node* successor(node* z)
{
    node* y;
    if(z->right!=NULL)
    {
        while(z->left)
            z=z->left;
        return z;
    }
    y=z->p;
    while(y!=NULL && z==y->right)
    {
        z=y;
        y=y->p;
    }
    return y;
}
void delete_node(node* z)
{                        
    node* y;
    node* x;
    if(z->left==NULL || z->right==NULL)
        {y=z;}
    else
        y=successor(z);
    cout<<z->low<<endl;
    cout<<z->p->low<<endl;
    cout<<y->p->low<<endl;

    if(y->left!=NULL)
        x=y->left;
    else
        x=y->right;
   
    cout<<y->p->low<<endl;
    x->p=y->p;
    if(y->p==NULL)
        root=x;
    else if(y==y->p->left)
        y->p->left=x;
    else
        y->p->right=x;
    if(y!=z)
    {
        z->low=y->low;
    }
  
}
node* create_newnode(int a,int b)
{	node* z=new struct node;
	z->left=NULL;
	z->right=NULL;
	z->p=NULL;
	z->low=a;
	z->high=b;
	z->maxvalue=0;
	return z;
}
void display(node* x)
{	if(x==NULL)
        	return;
	else
	{	display(x->left);	
		cout<<x->low<<" "<<x->high<<" "<<x->maxvalue<<endl;
		display(x->right);
	}
}
int fixMax(node* x)
{
        int maxvalue=0;
        if(x==NULL)
        	return maxvalue;
        maxvalue = max(x->high,max(fixMax(x->left),fixMax(x->right)));
        x->maxvalue = maxvalue;
        return maxvalue;
}
node* search_node(int i,int j)
{
    node* x=root;
    while(x!=NULL && (j<x->low || i>x->high))
    {
        if(x->left!=NULL && x->left->maxvalue>=i)
            x=x->left;
        else
            x=x->right;
    }
    return x;
}

 
int main()
{	int c;int a,b;int n;char y;
     do
      { cout<<"1 INSERT "<<endl<<"2 DELETE"<<endl<<"3 SEARCH"<<endl;
        cin>>c;
	switch(c)
	
        {case 1:
         	{cout<<"Enter number of intervals";
			cin>>n;
		while(n--)
		{
		 cin>>a>>b;
	         node *newptr= create_newnode(a,b);//newptr is new node
		 insert(newptr);
		//inserting newptr into tree
		}
        	 fixMax(root);
		 display(root);//displaying
		}break;
	case 2:
		{
			cout<<"enter interval"<<endl;
			cin>>a>>b;	
			node* x=search_node(a,b);
       			if(x->low>=0)
        	{
			delete_node(x);
			fixMax(root);
			display(root);
		}
       			 else
        			cout<<"Interval not found"<<endl;
		}break;
	case 3:
		{
			cout<<"enter interval"<<endl;
			cin>>a>>b;	
			node* x=search_node(a,b);
       			if(x->low>=0)
				cout<<"Interval found"<<endl;
			else
				cout<<"Not found"<<endl;
		}break;
      default: break;
      }
     cout<<"Do you want to continue(y/n)"<<endl;
		cin>>y;
    }while(y=='y'||y=='Y');

 	return 0;
}
