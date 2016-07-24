#ifndef QUEAP_H
#define QUEAP_H

#include "header.h"
#include "QueapList.h"
#include "QueapTree.h"

template <typename T>
class Queap
{
	private:
		int n_; // number of elements in the list
		int k_; // number of elements in the Queaptree
		QueapList<T> l_; // the qeap list
		
		T minL_; // minimum element in the list
	public: 
		QueapTree<T> t_; // the queap tree
		Queap(); // default constructor
		Queap(const Queap<T>& rhs); // copy constructor
		Queap(Queap<T>&& rhs); // move constructor
		Queap<T>& operator=(const Queap<T>& rhs); // copy assignment
		Queap<T>& operator=(Queap<T>&& rhs);// move assignment
		~Queap(); //destructor


		class MyIterator
		{
			private:
				typename QueapTree<T>::MyIterator t_it_;
				typename QueapList<T>::MyIterator l_it_;
				
			public:
				bool inTree;
				MyIterator(typename QueapTree<T>::MyIterator t_it,typename QueapList<T>::MyIterator l_it,bool intree);
				// all defaults
				bool operator==(const MyIterator& rhs) const;
				bool operator!=(const MyIterator& rhs) const;
				T& operator*();
				MyIterator& operator++();
				MyIterator operator++(int);

				friend void Queap<T>::replace(MyIterator begin, MyIterator end, T oldvalue, T ele);
				

		};
		MyIterator begin();
		MyIterator end();

		void insertNode(T ele);
		T minimum();
		bool deleteNode(T ele);
		T deleteMin();

		MyIterator find(MyIterator begin, MyIterator end, T ele);
		// void copy(MyIterator begin_src, MyIterator end_src, MyIterator begin_dest);
		void replace(MyIterator begin, MyIterator end, T oldvalue, T ele);
		
};

#include "Queap.cpp"

#endif