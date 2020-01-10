#include <iostream>
#include <string>
#include<sstream>
#include <fstream>
#include<chrono>
#include <vector>
#include "Hash.h"
#include "bst.h"
#include <chrono>
#include<cmath>
using namespace std;



/////////////////////////////////////////////////////////////************************************************************/////////////////////////////////
////////////////////////////////////CHRONOMETER SOMETIMES WORK PROPERLY SOMETIMES NOT///////////////////////////////////









/////***********struct for the store the txt
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

//////////*********checks if the given word exist in hash*********////////
bool existhash(HashEntry< wordItem> * p, int & index,  string & f )
{
	int k = p->value.docvec.size();
	for (int i =0 ; i< k ; i++)
	{
		if (p->value.docvec[i].txt==f)
		{
			index=i;
			return true;
		}
	}
	return false;
}
/////////////***********checks if the given word exist in bst*********//////////
bool existBST(Binarynode<string, wordItem> * p, int & index, const string f )
{
	int k=p->element.docvec.size();
	for(int i=0; i<k ; i++)
	{
		if (p->element.docvec[i].txt==f)
		{
			index=i;
			return true;
		}
	}
	return false;
}

string  noncapital(string &s)
{
	string word="";
	for(unsigned int j=0;j < s.length(); j++)
	{
		char c = s.at(j);	
		if(s.at(j)<91 && s.at(j)>64) // if the char is upper char
		{
			c=c+32;
			word+=c;
		}
		else if ( s.at(j)>96 && s.at(j)<123 )// if the char is lower char
			word+=s.at(j);
		else 
			word+=' ';

	}
	return word;
}

using namespace std;
int main()
{
	string a;
	cout<<"Enter number of input files: ";
	getline(cin,a);
	stringstream ss(a);
	int c= 0;
	ss>>c;// i returned the given string  a to integer c 
	BST<string,wordItem> b;
	Hashtable< wordItem> h;

	vector <string > filenames;
	///////******store the filenmaes in a vector******///////
	for(int i =0; i<c; i++)
	{
		ifstream input;
		string file;
		cout<<"Enter "<< i+1<<". file name: ";
		cin.clear();
		getline(cin,file);
		filenames.push_back(file);
	}


	for(int i=0; i<filenames.size();i++)
	{
		ifstream input;
		input.open(filenames[i].c_str());
		string line, word1; 

		while(getline(input,line))
		{
			istringstream iss(line);
			while(iss>>word1)
			{
				word1=noncapital(word1);
				istringstream iss3(word1);
				string word2;
				while(iss3>>word2)
				{   ////////////////////////********************************///////////////////////
							  /////////////************HASH PART************///////////
					//////////////////////**********************************//////////////////////
					
					if(!h.ifexist(word2))//if the hashtable  does not contain the words
					{
						document d(filenames[i],1);//i create a document struct
						wordItem w(word2,d);//i create a worditem and put that documnet file in it
						h.insert(word2,w);

					}
					else//if hashtablecontains that word
					{
						HashEntry< wordItem> * p = h.get(word2); // i found the existing words address in the binarysearchtree
						document d(filenames[i],1);
						int x=0;

						if(existhash(p,x,filenames[i]))// if teh gi
							p->value.docvec[x].num+=1;//i incremented the num of that words in the file
						else
						{
							// if it is a new files 
							p->value.docvec.push_back(d);
						}
					}	



					///////////////////////***********************************////////////////////////
							//////////////*************BST PART**************/////////////
					/////////////////////***********************************/////////////////////////
					
					if(!b.ifexist(word2))//if the binary searc three does not contain the words
					{
						document d(filenames[i],1);//i create a document struct
						wordItem w(word2,d);//i create a worditem and put that documnet file in it
						b.insert(word2,w);
					}
					else
					{
						Binarynode<string, wordItem> * a = b.find(word2); // i found the existing words address in the binarysearchtree
						document d(filenames[i],1);
						int x=0;
						//		if(i < p->element.docvec.size())//if the words in the same file///// burasi buyukihtimalle yanlis 
						if(existBST(a,x,filenames[i]))
							a->element.docvec[x].num+=1;//i incremented the num of that words in the file
						else
						{

							// if it is a new files 
							a->element.docvec.push_back(d);
						}
					}		
				}

			}
		}
	}

	cout<<"\n\nAfter preprocessing, the unique word count is "<<h.getsize()<< ". Current load ratio is "<<h.loadfactor()<<endl;
		string querywords;

		cout<<"Enter queried words in one line: ";
		cin.clear();
		getline(cin,querywords);
		querywords=noncapital(querywords);
		istringstream iss2(querywords);
		string keyword;

		/**********STORE THE KEYWORDS IN VECTOR**********/
		vector<string> keywords;
		while(iss2>>keyword)
		{
			keywords.push_back(keyword);// i store the querywords in a vector
		}

		//////////////////////******************TIME FOR HASH*********************////////////////

		int x=20;
		vector<tobeprinted> printvecHASH;
		auto start = std::chrono::high_resolution_clock::now();
		for(int l=0; l<x ;l++)
		{
			for(int i=0; i<keywords.size() ;i++)
			{
				if(h.ifexist(keywords[i]))// if the given queryword exst in my tree
				{
					HashEntry< wordItem> * p = h.get(keywords[i]); // i founf the adress
					for(int j=0; j<p->value.docvec.size(); j++)
					{
						string txt =p->value.docvec[j].txt;
						string word=p->key;
						int n= p->value.docvec[j].num;
						bool check=true;
						for(int k=0; k< printvecHASH.size();k++)
						{
							if(printvecHASH[k].txtname== txt)//if keywords txt file already in the printvec
							{
								check=false;
								printvecHASH[k].svec.push_back(word);// i store the keyword in the given txt files stringvec
								printvecHASH[k].ivec.push_back(n);// i store yhe keywords num in thr given tct files intvec
							}
						}

						if(check)// if the keywords txt files didnt inserted to the printvec
						{					
							tobeprinted tbp(txt,word,n);// create a struct for the new txt files 
							printvecHASH.push_back(tbp);//
						}				
					}
				}
			}
		}

		auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds> 
(std::chrono::high_resolution_clock::now() - start);

		/////////////****************TIME FOR BST**********************////////////////////
start = std::chrono::high_resolution_clock::now();			vector<tobeprinted> printvec;
			Binarynode<string, wordItem> * p;
		for(int i=0; i<keywords.size() ;i++)
		{
			if(b.ifexist(keywords[i]))// if the given queryword exst in my tree
			{
				 p = b.find(keywords[i]); // i founf the adress
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
						cout<<".\n";
				}
			}
		}
	
		if(!check)
		{
			cout<<"No document contains the given query"<<endl;
		}
				
auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds> 
(std::chrono::high_resolution_clock::now() - start);




		 check=false;
		for(int i=0; i<printvecHASH.size();i++)
		{
			if(keywords.size()==(printvecHASH[i].svec.size()/x))// if te all the given querywords exist in the same file
			{
				check=true;
				cout<<"in Document "<<printvecHASH[i].txtname<<", ";
				for(int j=0; j<keywords.size();j++)
				{
					cout<<printvecHASH[i].svec[j]<< " found "<< printvecHASH[i].ivec[j] <<" times";
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






		int bsttime=BSTTime.count();
		int hashtime= HTTime.count();

		if(hashtime==0)
		{
			cout<<endl<< "hash time close to constant thus it is 0"<<endl;
		}
		






			
		cout << "\nTime: " << BSTTime.count()/x << "\n";
		cout << "\nTime: " << HTTime.count() /x << "\n";
		double speed=bsttime*1.0/hashtime*1.0;
		cout<<"Speed up: "<<speed<<endl;
		system("pause");

		return 0;
	}