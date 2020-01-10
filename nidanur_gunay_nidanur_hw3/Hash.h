#pragma once
#include <iostream>
#include <vector>
#include <string>
#include<cmath>
using namespace std;
int TABLE_SIZE = 53;


int hashfunc(string & key)
{
	int h=0;
 
	for(int i=0; i<key.length();  i++)
	{
		h+=(i*37)+key.at(i) ;
		
	}

	return h%TABLE_SIZE;
}

template< class V>
struct HashEntry
{
	string key;
	V value;
	HashEntry<V> * next;
	HashEntry(string &k,V&v)
	{
		key=k;
		value=v;
		next=NULL;
	};
	HashEntry(){};
};

template < class V>
class Hashtable
{
private:
		HashEntry<V> ** table;
		  int size;
public:

	Hashtable();
	~Hashtable();
	void insert(string & key, V& value);
	double loadfactor();
	void rehash();
	int getsize();
	bool ifexist(string & k);
	HashEntry<V>* get(string & k);
};

template < class V>
Hashtable<V>::Hashtable()
{
	size=0;
	table= new HashEntry<V>*[TABLE_SIZE];
	for(int i=0; i<TABLE_SIZE;i++)
		table[i]=NULL;
}

template < class V>
Hashtable<V> :: ~Hashtable()
{
	for (int i = 0; i < TABLE_SIZE; i++)
     {   if (table[i] != NULL)
           delete table[i];
	}
      delete[] table;
}

template < class V>
void Hashtable<V> ::insert(string & key, V& value)
{

	int h= hashfunc(key);//h storest the hash value of given string
	int j=0;//count for linear probing
	HashEntry<V>* k=table[h];

	//////************QUADRATIC PROBING **********////////////
	int c=1;
		int lim= log(TABLE_SIZE);

	while(  c<10   &&  (k!=NULL) && k->key!=key)//this code for quadratic probing and the chain size is max 5
	{
		h=(h+c*c)%TABLE_SIZE;
		k=table[h];
		c++;
	}

	/*************CHAINING********////////
	while(k!=NULL && k->key!=key)
	{
		while(k->next!=NULL && k->key!=key)
			k=k->next;
		k=k->next;
	}
	 
	if(table[h]==NULL && loadfactor()<0.9)
	{
		table[h]=new HashEntry<V>(key,value);
		size++;
	}
	else if(k==NULL && loadfactor()<0.9)// if the calculated hash value is available for the data//****for linear and quadratic probig 
	{
		HashEntry<V> * temp=table[h];
		while(temp->next!=NULL)
			temp=temp->next;
		temp->next= new HashEntry<V>(key,value);
		size+=1;
	}
	
	else if(loadfactor()>=0.9  )
	{	
		rehash();
		insert(key,value);
	}
}

template < class V>
double Hashtable<V> ::loadfactor()
{
	return size*1.0 / TABLE_SIZE;
}

template < class V>
void Hashtable<V> :: rehash()
{
	cout<<"rehashed...\n";
	int oldtabsize=TABLE_SIZE;// i stored the old table size
	cout<<"previous table size:" <<TABLE_SIZE<< ",";
	TABLE_SIZE = TABLE_SIZE * 2 + 15;// it is our new table size
	cout<<" new table size: "<< TABLE_SIZE<< ", current unique word count "<< getsize()<< ","<< "current load factor: "<< loadfactor()<<endl;
	HashEntry<V>** newhash= new HashEntry<V>*[TABLE_SIZE];// it will be our new table
	
	//////*******INITIALIZATION OF NEWHASH*********//////
	for(int i=0; i<TABLE_SIZE; i++)
			newhash[i]=NULL;
	
	////////********THIS IS FOR INSERTING OLD DATA TO NEW HASH************/////////////
	/*********************************************************************************/
	HashEntry<V>* n;
	for(int i= 0; i<oldtabsize;i++)
	{
		n=table[i];
		if(n!=NULL)//if the given number of hash entry contains a value
		{
			string key=n->key;
			V value=n->value;
			HashEntry<V>* he= new HashEntry<V>(key,value);// my new hash entry
			
			// i store the data to my new hashentry node
			int h=hashfunc(n->key);
			HashEntry<V>* p= newhash[h];// my new hash entry

			//int j=0;//count for linear probing
			//while(newhash[h]!=NULL &&( p->key!=key && j<5))//max linear probing count is 5
			//{
			//	h= (h+1) % TABLE_SIZE;//linear probing
			//	p= newhash[h];
			//	j++;
			//}
			//p=newhash[h];
			int c=1;
				int lim= log(TABLE_SIZE);

			while( newhash[h]!=NULL &&c<10 )//this code for quadratic probing and the chain size is max 5
			{
				h= (h+c*c)%TABLE_SIZE;
				p= newhash[h];
				c++;
			}
			while(p!=NULL )///this is for chaining
			{
				while(p->next!=NULL)
					p=p->next;
				p=p->next;
			}
		
			if(newhash[h]==NULL && loadfactor()<0.9)
			{
				newhash[h]=he;
			}

			else if(p==NULL && loadfactor()<0.9)
			{
				p= he;

			}
		
		}
		if(n!=NULL && n->next!=NULL)
		{
			HashEntry<V>* temp=n;
			while(temp->next!=NULL)
			{
				temp=temp->next;
				string key=temp->key;
				V value=temp->value;
				HashEntry<V>* he= new HashEntry<V>(key,value);// my new hash entry
			
				// i store the data to my new hashentry node
				int h=hashfunc(temp->key);
				HashEntry<V>* p= newhash[h];// my new hash entry

			
				int c=1;
					int lim= log(TABLE_SIZE);

				while( newhash[h]!=NULL &&c<10 )//this code for quadratic probing and the chain size is max 5
				{
					h= (h+c*c)%TABLE_SIZE;
					p= newhash[h];
					c++;
				}
				while(p!=NULL )///this is for chaining
				{
					while(p->next!=NULL)
						p=p->next;
					p=p->next;
				}
		
				if(newhash[h]==NULL && loadfactor()<0.9)
				{
					newhash[h]=he;
				}

				else if(p==NULL && loadfactor()<0.9)
				{

					HashEntry<V>*temp=newhash[h];
					 while(temp->next!=NULL)
						 temp=temp->next;
				
						temp->next= he;
			
				}
			}
		}
	}	
	table=newhash;
}

template < class V>
int Hashtable<V>:: getsize()
{
	return size;
}

template < class V>
bool Hashtable<V> :: ifexist (string & k)
{
	int n=hashfunc(k);
	HashEntry<V> *p=table[n];
	int j=0;
	if(p!=NULL){
		if(p->key == k)//for the linear probing search
			return true;
	}


	int c=1;
		int lim= log(TABLE_SIZE);

	while( table[n]!=NULL && (p->key!=k && c<10 ))//this code for search of quadratic probing
	{
		if(p->key == k)
			return true;
		n=(n+c*c)%TABLE_SIZE;
		p= table[n];
		c++;
	}
	
	 while(p!=NULL && p->key!= k)
	 {
		 while(p->next!=NULL)
		 {
			 if(p->key==k)
				 return true;
			 p=p->next;
		 }
		 p=p->next;
	 }
	
	 if(table[n]!=NULL &&p!=NULL && p->key==k)
		return true;

	else  if(table[n]!=NULL && p==NULL)
	 {
		 HashEntry<V>*temp=table[n];
		 while(temp->next!=NULL)
			 temp=temp->next;
		 if(temp->key==k)
			 return true;
	 }
	else
	 return false;

}	

template < class V>
HashEntry<V> * Hashtable<V>:: get(string & k)
{
	int n= hashfunc(k);
	HashEntry<V> *p=table[n];
		if(p!=NULL){
		if(p->key == k)//for the linear probing search
			return table[n];
		}
	

	int c=1;
		int lim= log(TABLE_SIZE);

	while( table[n]!=NULL && p->key!=k && c<10 )//this code for search of quadratic probing
	{
		if(p->key == k)
			return table[n];
		n=(n+c*c)%TABLE_SIZE;
		p= table[n];
		c++;
	}

	 
	 while(p!=NULL && p->key!= k)
	 {
		 while(p->next!=NULL)
		 {
			 if(p->key==k)
				 return p;
			 p=p->next;
		 }
	 }
		
	 if(p!=NULL && p->key==k)
		 return p;
	
	 else if(table[n]!=NULL && p==NULL )
	 {
		  HashEntry<V>*temp=table[n];
		 while(temp->next!=NULL)
			 temp=temp->next;
		 if(temp->key==k)
			 return temp;
	 }
}
