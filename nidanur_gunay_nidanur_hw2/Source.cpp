#include <iostream>				
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "bst.h"

using namespace std;
// i create a struct for  document and the number of the given words in that document
struct document
{
	string txt;
	int num;
	document (string t, int n): txt(t), num(n){};
	document () {};
};
//it is struct for the last part of the program for printing
struct tobeprinted
{
	string txtname;
	vector<string> svec;
	vector<int> ivec;
	tobeprinted(string a, string b, int c):txtname(a)
	{
		svec.push_back(b);
		ivec.push_back(c);
	};
	tobeprinted(){};
};

// in that struct for the soratio of the documents for a word in the document for my BST
struct wordItem
{
	string w;
	vector<document> docvec;
	wordItem(string a,document d) :w(a) {
	docvec.push_back(d);
	};
	wordItem(){};	
};

// it is the function that make the capital letters to noncapital ones.
string & noncapital(string &s)
{
	for(unsigned int j=0;j < s.length(); j++)
		{
			char c = s.at(j);	
			if(s.at(j)<97&& s.at(j)>64) 
			{
				c=c+32;
				s.at(j)=c;
			}
		}
	return s;
}
int main()
{
	
	string a;
	cout<<"Enter number of input files: ";
	getline(cin,a);
	stringstream ss(a);
	int c= 0;
	ss>>c;// i returned the given string  a to integer c 
	BST<string,wordItem> b;// i create my BST b
	for(int i =0; i<c; i++)
	{
		ifstream input;
		string file;
		cout<<"Enter "<< i+1<<". file name: ";
		cin.clear();
		getline(cin,file);
		input.open(file.c_str());
		
		string line, word1;
		
		while(getline(input,line))
		{
			istringstream iss(line);
			while(iss>>word1)
			{
				word1=noncapital(word1);// i make the word's all the letters to noncpital
				if(!b.ifexist(word1))//if the binary searc three does not contain the words
				{
					document d(file,1);//i create a document struct
					wordItem w(word1,d);//i create a worditem and put that documnet file in it
					b.insert(word1,w);
				}
				else
				{
					Binarynode<string, wordItem> * p = b.find(word1); // i found the existing words address in the binarysearchtree
					if(i < p->element.docvec.size())//if the words in the same file
						p->element.docvec[i].num+=1;//i incremented the num of that words in the file
					else
					{
						document d(file,1);// if it is a new files 
						p->element.docvec.push_back(d);
					}
				}		
			}			
		}
	}

	string querywords;
	
	cout<<"Enter queried words in one line: ";
	cin.clear();
	getline(cin,querywords);
	querywords=noncapital(querywords);
	istringstream iss2(querywords);
	string keyword;
	vector<string> keywords;
	while(iss2>>keyword)
	{
		keywords.push_back(keyword);// i store the querywords in a vector
	}
	vector<tobeprinted> printvec;
	for(int i=0; i<keywords.size() ;i++)
	{
		if(b.ifexist(keywords[i]))// if the given queryword exst in my tree
		{
			Binarynode<string, wordItem> * p = b.find(keywords[i]); // i founf the adress
			for(int j=0; j<p->element.docvec.size(); j++)
			{
				string txt =p->element.docvec[j].txt;
				string word=p->data;
				int n= p->element.docvec[j].num;
				bool check=true;
				for(int k=0; k< printvec.size();k++)
				{
					if(printvec[k].txtname== txt)//if keywords txt file already in the printvec
					{
						check=false;
						printvec[k].svec.push_back(word);// i store the keyword in the given txt files stringvec
						printvec[k].ivec.push_back(n);// i store yhe keywords num in thr given tct files intvec
					}
				}

				if(check)// if the keywords txt files didnt inserted to the printvec
				{					
					tobeprinted tbp(txt,word,n);// create a struct for the new txt files 
					printvec.push_back(tbp);//
				}				
			}
		}
	}
	bool check=false;
	for(int i=0; i<printvec.size();i++)
	{
		if(keywords.size()==printvec[i].svec.size())// if te all the given querywords exist in the same file
		{
			check=true;
			cout<<"in Document "<<printvec[i].txtname<<", ";
			for(int j=0; j<keywords.size();j++)
			{
				cout<<printvec[i].svec[j]<< " found "<< printvec[i].ivec[j] <<" times";
				if(j!=keywords.size()-1)
					cout<< ", ";
				else
					cout<<"."<<endl;
			}

		}
	}
	if(!check)
	{
		cout<<"No document contains the given query"<<endl;
	}
	cout<<endl;
	b.makeempty();// i deleted my bst for free to my memory.
	system("pause");
	return 0;
}