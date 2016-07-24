#ifndef DLIST_H
#define DLIST_H


// interface for a link list node
template <typename T>
class LinkNode
{
	// friend class QueapList;
	private:
		T ele_;
		LinkNode<T>* next_;
		LinkNode<T>* prev_;

	public:
		LinkNode(T ele, LinkNode<T>* next,LinkNode<T>* prev);
		template<typename Z> friend class QueapList;
		template<typename Z> friend class Queap;
		template<typename X> friend ostream& operator<<(ostream&, const LinkNode<X>&);
		
};

// interface for a queap linked list
template <typename T>
class QueapList
{
	public:
		LinkNode<T> *head_, *tail_;

	public:
		QueapList(); // default constructor
		~QueapList(); // destructor
		QueapList(const QueapList&); // copy constructor
		QueapList(QueapList&&); // move constructor

		QueapList& operator=(const QueapList&); // copy assignment
		QueapList& operator=(QueapList&&); //move assignment



		class MyIterator
		{
			private:
				LinkNode<T>* p_it_;
			public:
				MyIterator(LinkNode<T> *p_it);
				// all defaults
				bool operator==(const MyIterator& rhs) const;
				bool operator!=(const MyIterator& rhs) const;
				T& operator*();
				MyIterator& operator++();
				MyIterator operator++(int);
				template<typename Z> friend class Queap;

		};
		MyIterator begin();
		MyIterator end();

		void insertNode(T ele);
		void deleteNode(T ele);
		void display();
		void clear();

		MyIterator find(MyIterator begin, MyIterator end, T ele);
		// void copy(MyIterator begin_src, MyIterator end_src, MyIterator begin_dest);
		void replace(MyIterator begin, MyIterator end, T oldvalue, T ele);

		template<typename Z> friend class Queap;
};

#include "QueapList.cpp"

#endif