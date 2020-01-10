#pragma once
#include <iostream>

using namespace std;

template <class T>
//To create a listnode struct for my linkedlist based stack i defined listnode struct 
struct Listnode{
T info;// T type data
Listnode<T> *next;// pointer for the next listnode

Listnode (): next(NULL) {};
Listnode(const T & a, Listnode *n=NULL):info(a) ,next(n) {};
};


template <class T>
class Stack {
	private:
		
		Listnode<T> *topstack;

	public:
		Stack();

		void push(T coor);
		void pop(T &a);

		T top();
		bool isEmpty();

		const static T noItem;
};

// constructor
template <class T>
Stack<T> :: Stack ()
{
	topstack=NULL;
}

//returns true if the stack is empty
template <class T>
bool Stack<T> :: isEmpty()
{
	if(topstack==NULL)
		return true;
	else
		return false;
}

// this function adds new listnode to stack 
template <class T>
void Stack<T> :: push (T data)
{
	
		Listnode<T> *p = new Listnode<T> (data,topstack); 
		topstack=p;
	
}

//this function removes T type data from the stack
template <class T>
void Stack<T> :: pop (T & a)
{
	if(!isEmpty())//i checked if the stack is empty or not
	{
		a= topstack->info;
		Listnode<T> *oldTop = topstack;
		topstack=topstack->next;
		delete oldTop;
	}
	else
		cout<<"Stack is empty"<<endl;
}

//it returns the top T type data of my stack
template <class T>
T Stack<T> :: top()
{
	if(!isEmpty())
		return topstack->info;
}
