// #include <iostream>
// using namespace std;
// #include "header.h"



template <typename T>
LinkNode<T>::LinkNode(T ele, LinkNode<T>* next, LinkNode<T>* prev)
:ele_(ele), next_(next), prev_(prev)
{
}

// **************************************CONSTRUCTORS**************************************

template <typename T>
QueapList<T>::QueapList()
: head_(nullptr), tail_(nullptr)
{

}

template <typename T>
QueapList<T>::QueapList(const QueapList& rhs)
: head_(new LinkNode<T>(rhs.head_->ele_, nullptr, nullptr)), tail_(head_)
{
	LinkNode<T> *pointer;
	pointer = rhs.head_->next_;

	while(pointer!=nullptr)
	{
		
		LinkNode<T> *temp = new LinkNode<T>(pointer->ele_, nullptr, tail_);
		tail_->next_ = temp;
		tail_ = temp;
		pointer = pointer->next_;
	}

}

template <typename T>
QueapList<T>::QueapList(QueapList&& rhs)
: head_(rhs.head_), tail_(rhs.tail_)
{
	rhs.head_ = nullptr;
	rhs.tail_ = nullptr;
}

// **************************************ASSIGNMENT FUNCTIONS*****************************

template <typename T>
QueapList<T>& QueapList<T>::operator=(const QueapList& rhs) // copy assignment
{
	if(this != &rhs)
	{
		if(head_!=nullptr)
		{
			LinkNode<T> *pointer;
			pointer = head_->next_;

			while(pointer!=nullptr)
			{
				delete pointer->prev_;
				pointer = pointer->next_;
			}
		}

		if(rhs.head_!=nullptr)
		{
			head_ = new LinkNode<T>(rhs.head_->ele_, nullptr, nullptr);
			tail_ = head_;

			LinkNode<T> *pointer;
			pointer = rhs.head_->next_;

			while(pointer!=nullptr)
			{
				
				LinkNode<T> *temp = new LinkNode<T>(pointer->ele_, nullptr, tail_);
				tail_->next_ = temp;
				tail_ = temp;
				pointer = pointer->next_;
			}
		}
		else
		{
			head_=tail_=nullptr;
		}
	}
	return *this;
}

		
template <typename T>
QueapList<T>& QueapList<T>::operator=(QueapList&& rhs) //move assignment
{
	if(this != &rhs)
	{
		// cout << "cpy assgn\n";
		if(head_!=nullptr)
		{
			LinkNode<T> *pointer;
			pointer = head_->next_;

			while(pointer!=nullptr)
			{
				delete pointer->prev_;
				pointer = pointer->next_;
			}
		}

		head_ = rhs.head_;
		tail_ = rhs.tail_;
		rhs.head_ = nullptr;
		rhs.tail_ = nullptr;
	}
	return *this;

}

// **************************************DESTRUCTOR**************************************

template <typename T>
QueapList<T>::~QueapList()
{
	clear();
}

// **************************************OTHER FUNCTIONS*********************************

template <typename T>
void QueapList<T>::clear()
{
	if(head_!=nullptr)
	{
		LinkNode<T> *pointer;
		pointer = head_->next_;

		while(pointer!=nullptr)
		{
			delete pointer->prev_;
			pointer = pointer->next_;
		}
	}

	head_ = tail_ = nullptr;
}


template <typename T>
void QueapList<T>::insertNode(T ele)
{
	if(head_==nullptr)
	{
		LinkNode<T> *temp = new LinkNode<T>(ele, nullptr, nullptr);
		head_ = temp;
		tail_ = temp;
	}
	else
	{
		LinkNode<T> *temp = new LinkNode<T>(ele, nullptr, tail_);
		tail_->next_ = temp;
		tail_ = temp;	
	}

}

template <typename T>
void QueapList<T>::deleteNode(T ele)
{

	LinkNode<T> *pointer;

	pointer = head_;

	while(pointer!=nullptr && pointer->ele_.key_!=ele.key_ && pointer->ele_.value_!=ele.value_)
	{
		pointer = pointer->next_;
	}

	if(pointer != nullptr)
	{
		if(pointer==head_)
		{
			head_->next_->prev_ = nullptr;
			head_ = head_->next_;
		}
		else if(pointer==tail_)
		{
			tail_->prev_->next_ = nullptr;
			tail_ = tail_->prev_;
		}
		else
		{
			pointer->next_->prev_ = pointer->prev_;
			pointer->prev_->next_ = pointer->next_;
		}

		delete pointer;
	}
	
}

template <typename T>
void QueapList<T>::display()
{

	LinkNode<T> *pointer;
	pointer = head_;

	while(pointer!=nullptr)
	{
		cout << pointer->ele_.key_ << "\t" << pointer->ele_.value_<< "\n";

		pointer = pointer->next_;
	}

}

// **************************************GENERIC FUNCTIONS*********************************

template<typename T>
typename QueapList<T>::MyIterator QueapList<T>::find(MyIterator begin,MyIterator end, T ele)
{
	
	while (begin!=end) {
		// cout << *begin;
    	if ((*begin).key_ == ele.key_) 
    		return begin;
    	++begin;
	}
	return begin;
}

template<typename T>
void QueapList<T>::replace(MyIterator begin, MyIterator end, T oldvalue, T ele)
{
	while(begin != end)
	{
		if(*begin == oldvalue)
		{
			*begin = ele;
		}
		++begin;
	}
}

// **************************************ITERATOR*********************************

template <typename T>
QueapList<T>::MyIterator::MyIterator(LinkNode<T> *p_it) 
: p_it_(p_it) 
{ 
}

template <typename T>
bool QueapList<T>::MyIterator::operator==(const MyIterator& rhs) const //check for equality
{
	return p_it_ == rhs.p_it_;
}

template <typename T>
bool QueapList<T>::MyIterator::operator!=(const MyIterator& rhs) const //check for unequality
{
	return !(*this == rhs);
}

template <typename T>
T& QueapList<T>::MyIterator::operator*() //dereference
{
	return p_it_->ele_;
} 

template <typename T>
typename QueapList<T>::MyIterator& QueapList<T>::MyIterator::operator++() // pre incr
{
	p_it_ = p_it_->next_;
	return *this;
}

template <typename T>
typename QueapList<T>::MyIterator QueapList<T>::MyIterator::operator++(int) // post incr
{
	MyIterator temp(*this);
	++*this;
	return temp;
}

template <typename T>
typename QueapList<T>::MyIterator QueapList<T>::begin()
{
	return MyIterator(head_);
}

template <typename T>
typename QueapList<T>::MyIterator QueapList<T>::end()
{
	return MyIterator(nullptr);
}

// **************************************OSTREAM FUNCTIONS*********************************

template <typename T>
ostream& operator<<(ostream& o, const LinkNode<T>& node)
{
	return o << node.ele_;
	// return o;
}
