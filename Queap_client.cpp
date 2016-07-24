#include <iostream>
#include <algorithm>
using namespace std;

#include "Queap.h"

int main()
{
	
	char ch;
	cout<<"A queap containing integer elements is created\n";
	Queap<Element<int,int>> Q;
	cout<<"For executing Queap functions, enter:\na to instert \nb to delete ";
	cout<<"\nc to find \nd to replace\ne to display\nf to find minimum element\ng to delete minimum element\nh to exit\n";
	//i dont have minimum element and delete minimum element functions 
	cin>>ch;
	int key,value;
	while(ch!='h')
	{
		switch(ch)
		{
			case 'a':cout<<"Enter the key and value of an element to be inserted\n";
				cin>>key;
				cin>>value;
				Q.insertNode(Element<int,int>(key,value));
				break;
			case 'b':cout<<"Enter the key and value of element to be deleted\n";
				cin>>key;
				cin>>value;
				if(Q.find(Q.begin(),Q.end(),Element<int,int>(key,value))==Q.end())
				{
					cout<<"Node with this key-value element doesn't exist in the queap\n";
					break;
				}
				if(Q.deleteNode(Element<int,int>(key,value)))
				{
					cout<<"Node deleted";
				}
				else
				{
					cout<<"Node not deleted";
				}
				break;
			case 'c':cout<<"Enter the key and value of element to be found\n";
				cin>>key;
				cin>>value;
				if(Q.find(Q.begin(),Q.end(),Element<int,int>(key,value))!=Q.end())
				{ 
					cout<<"The node exist in the tree.\n ";
					 //cout<<"It is element number"<<Q.find(Q.begin(),Q.end(),Element<int,int>(key,value))-Q.begin();
				}
				else
				{
					cout<<"The node doesn't exist in the tree.\n ";
				}
				break;
			case 'd':cout<<"Enter the key and value of element to be replaced \n";
				cin>>key;
				cin>>value;
				if(Q.find(Q.begin(),Q.end(),Element<int,int>(key,value))==Q.end())
				{
					cout<<"Node with this key-value element doesn't exist in the queap\n";
					break;
				}
				cout<<"Enter the key and value of new element\n";
				int key1,value1;
				cin>>key1;
				cin>>value1;
				Q.replace(Q.begin(),Q.end(),Element<int,int>(key,value),Element<int,int>(key1,value1));
				break;
			case 'e':for_each(Q.begin(),Q.end(),[](auto e){cout<<e;});
				break;
			case 'f':cout << "Minimum element is " << Q.minimum();
					break;
			case 'g':Q.deleteMin();
					break;
			default:
				cout<<"Incorrect option\n";
				break;
		}
		cout<<"For executing Queap functions, enter:\na to instert \nb to delete ";
		cout<<"\nc to find \nd to replace\ne to display\nf to find minimum element\ng to delete minimum element\nh to exit\n";
		cin>>ch;

	}
	Queap<Element<int,int>> Q1;
	Q1=Q;
	cout<<"Copy assignment demo:\n";
	for_each(Q1.begin(),Q1.end(),[](auto e){cout<<e;});
	Queap<Element<int,int>> Q2;
	Q2=move(Q);
	cout<<"Move assignment demo:\n";
	for_each(Q2.begin(),Q2.end(),[](auto e){cout<<e;});


	return 0;
	/*Queap<Element<int,int>> Q;
	Q.insertNode(Element<int,int>(1,1));
	Q.insertNode(Element<int,int>(2,2));
	Q.insertNode(Element<int,int>(3,3));
	Q.insertNode(Element<int,int>(4,4));
	Q.insertNode(Element<int,int>(5,5));
	Q.insertNode(Element<int,int>(6,6));
	Q.insertNode(Element<int,int>(7,7));
	Q.insertNode(Element<int,int>(8,8));
	Q.insertNode(Element<int,int>(9,9));
	Q.insertNode(Element<int,int>(10,10));
	Q.insertNode(Element<int,int>(11,11));
	// cout<<*Q.t_.begin();
	// Q.t_.insertNode(Element<int,int>(3,3));

	Queap<Element<int,int>> R;
	R = move(Q);
	// Q.t_.insertNode(Element<char,char>('d','d'));
	// Q.t_.insertNode(Element<char,char>('e','e'));
	// Q.t_.insertNode(Element<char,char>('f','f'));
	// Q.t_.traverseTree();

	// cout<<*Q.find(Q.begin(),Q.end(),Element<char,char>('d','d'));
	// Q.replace(Q.begin(),Q.end(),Element<char,char>('d','d'),Element<char,char>('t','t'));
	// auto e = Q.begin();

	for_each(R.begin(),R.end(),[](auto e){
		cout<<e;		
	});

	cout << "min: " << R.minimum();

	R.deleteMin();
	// // R.deleteNode(Element<int,int>(3,3));
	for_each(R.begin(),R.end(),[](auto e){
		cout<<e;		
	});
	cout << "min: " << R.minimum();
	R.insertNode(Element<int,int>(3,3));
	for_each(R.begin(),R.end(),[](auto e){
		cout<<e;		
	});
	// // cout<<*e<<*++e<<*++e;
	// // cout << "min ele: "<< R.deleteMin();
	cout << "+++++++++++++++++++\n";
	R.replace(R.begin(), R.end(), Element<int,int>(3,3), Element<int,int>(12,12));
	for_each(R.begin(),R.end(),[](auto e){
		cout<<e;		
	});*/
}
