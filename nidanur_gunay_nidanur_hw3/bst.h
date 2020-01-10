#pragma once
#include <iostream>
#include <string>

using namespace std;

template<class t, class y> class BST;
template<class t, class y> class Binarynode;

template <class t, class y>
class Binarynode{
public:
	t data;
	y element;
	Binarynode* left;
	Binarynode* right;

	Binarynode(){};

	Binarynode(const t & d,const y & a, Binarynode* l, Binarynode* r) : data(d), element(a), left(l), right(r){};

	friend class BST<t,y>;
};


template <class t, class y>
class BST 
{
private:
	Binarynode<t,y>* root;
	void remove1( const t & x, Binarynode<t,y> * & p ) const;
	Binarynode<t,y> * findMin( Binarynode<t,y> * p ) const;
	Binarynode<t,y> * findMax( Binarynode<t,y> * p ) const;
	void makeempty( Binarynode<t,y> * & p ) const;
public:
	BST();
	~BST();
	Binarynode<t,y> * find( const t & x ) ;
	bool ifexist(const t & x);
	void insert(const t & a , const y & b);
	void makeempty();
	void remove(const t &x);
	};

//constructor
template <class t, class y>
BST<t,y> ::BST()
{
	root=NULL;
}

// insert function
template <class t, class y>
void BST<t,y> :: insert (const t & a , const y & b)
{
	Binarynode<t,y>* temp=root;

	if (root == NULL)
	{
		root = new Binarynode<t,y>(a,b,NULL,NULL);
	}
	else
	{
		bool check=true;
		while((temp->right!=NULL || temp->left!=NULL)&& check)
		{
			if(a < temp->data && temp->left !=NULL)
				temp=temp->left;
			else if(a> temp->data && temp->right!=NULL)
				temp=temp->right;
			else if((a < temp->data && temp->left ==NULL) || (a> temp->data && temp->right==NULL))
				check=false;
		}

		if(a<temp->data)
		temp->left= new Binarynode<t,y>(a,b,NULL,NULL);
		else
		temp->right= new Binarynode<t,y>(a,b,NULL,NULL);
	}
}

template <class t, class y>
Binarynode <t,y>* BST<t,y> :: find(const t & x)
{
	Binarynode<t,y> * temp=root;
	if(ifexist(x))
	{
		while(temp->data!=x)
		{
			if(x>temp->data)
				temp=temp->right;
			else
				temp=temp->left;
		}
		return temp;
	}
	else
		return NULL;
}

template <class t, class y>
bool BST<t,y>:: ifexist(const t & x)
{
	Binarynode<t,y> *temp=root;
	bool check=true;
	while(temp!=NULL && check)
	{
		if(temp->data==x)
			check=false;
		else if(temp->data < x)
			temp=temp->right;
		else if (temp->data > x)
			temp=temp->left;
		
	}
	if(temp!=NULL && temp->data==x)
			check=false;
	
	return !check;
}
 
 template <class t, class y>
void BST<t,y>::makeempty( Binarynode<t,y> * & p ) const
{
	if( p != NULL )
	{
		makeempty( p->left );	
		makeempty( p->right );
		delete p;
	}

	p = NULL;
}
template <class t, class y>
void BST <t,y> :: makeempty()
{
		makeempty( root );
}


template <class t, class y>
void BST <t,y>::remove(const t & x )
{
	remove( x, root );
}

template <class t, class y>
void BST <t,y> :: remove1( const t & x, Binarynode<t,y> * & a )const
{
	if( a == NULL )
	return; // Item not found; do nothing

	if( x < a->data )
	remove1( x, a->left );

	else if( a->data < x )
	remove1( x, a->right );

	else if( a->left != NULL && t->right != NULL ) // Two children
	{
		a->data = findMin( a->right )->data;
		remove1( a->element, a->right );
	}

	else // one or no children
	{

		Binarynode<t,y> *oldNode = a;
		a = ( a->left != NULL ) ? a->left : a->right;
		delete oldNode;
	}

}

template <class t, class y>
Binarynode<t,y> * BST<t,y>::findMax( Binarynode<t,y> *p )const
{
	if( p != NULL )
		while(p->right != NULL )
	p = p->right;
	return p;
}

template <class t,class y>
Binarynode<t,y> *BST<t,y>::findMin( Binarynode<t,y> *p )const
{
	if( p == NULL )
		return NULL;

	if( p->left == NULL )
		return p;

	return findMin( p->left );
}


template <class t,class y>
BST<t,y>::~BST( )
{
	makeempty( );
}




