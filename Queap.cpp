

// **************************************CONSTRUCTORS**************************************

template <typename T>
Queap<T>::Queap()
: n_(0) , k_(0), minL_(T())
{

}

template <typename T>
Queap<T>::Queap(const Queap& rhs)
: n_(rhs.n_), k_(rhs.k_), l_(rhs.l_), t_(rhs.t_), minL_(rhs.minL_)
{

}

template <typename T>
Queap<T>::Queap(Queap&& rhs)
: n_(rhs.n_), k_(rhs.k_), l_(move(rhs.l_)), t_(move(rhs.t_)), minL_(rhs.minL_)
{
	rhs.minL_ = T();
	cout << rhs.minL_;
	rhs.n_ = -1;
	rhs.k_ = -1;
}

// **************************************ASSIGNMENT FUNCTIONS*****************************

template <typename T>
Queap<T>& Queap<T>::operator=(const Queap& rhs) // copy assignment
{
	if(this != &rhs)
	{
		t_.clear();
		l_.clear();

		n_ = rhs.n_;
		k_ = rhs.k_;
		minL_ = rhs.minL_;
		l_ = rhs.l_;
		t_ = rhs.t_;
	}
	return *this;
}

		
template <typename T>
Queap<T>& Queap<T>::operator=(Queap&& rhs) //move assignment
{
	if(this != &rhs)
	{
		t_.clear();
		l_.clear();

		n_ = rhs.n_;
		k_ = rhs.k_;
		minL_ = rhs.minL_;
		l_ = move(rhs.l_);
		t_ = move(rhs.t_);
		rhs.n_ = -1;
		rhs.k_ = -1;
		rhs.minL_ = T();
	}
	return *this;

}

// **************************************DESTRUCTOR**************************************

template <typename T>
Queap<T>::~Queap()
{
	
}

// **************************************OTHER FUNCTIONS*********************************
template <typename T>
void Queap<T>::insertNode(T ele)
{
	if(n_ == 0)
	{
		minL_ = ele;
		n_++;
	}
		
	l_.insertNode(ele);

	if(ele.key_ < minL_.key_) // implement the == operator for ele
		minL_ = ele;

	// cout << "minL_" << minL_;

}

template <typename T>
T Queap<T>::minimum()
{
	if(t_.x0_->p_ == nullptr || minL_.key_ < t_.x0_->p_->ele_.key_)
		return minL_;
	else
		return t_.x0_->p_->ele_;
}

template <typename T>
bool Queap<T>::deleteNode(T ele)
{
	auto el = find(begin(),end(),ele);

	if(el!=end())
	{
		if(!el.inTree)
		{
			for_each(l_.begin(), l_.end(), [this](auto e)
			{
				t_.insertNode(e);
			});
			l_.clear();
			minL_ = T();
		}
		t_.deleteLeaf(ele);
		return true;
	}
	return false;
	
}

template <typename T>
T Queap<T>::deleteMin()
{
	T min = minimum();
	deleteNode(min);
	return min;
}

// **************************************ITERATOR*********************************

template <typename T>
Queap<T>::MyIterator::MyIterator(typename QueapTree<T>::MyIterator t_it,typename QueapList<T>::MyIterator l_it,bool intree) 
: t_it_(t_it),l_it_(l_it),inTree(intree)
{ 

}

template <typename T>
bool Queap<T>::MyIterator::operator==(const MyIterator& rhs) const //check for equality
{
	return t_it_ == rhs.t_it_ && l_it_ == rhs.l_it_;
}

template <typename T>
bool Queap<T>::MyIterator::operator!=(const MyIterator& rhs) const //check for unequality
{
	return !(*this == rhs);
}


template <typename T>
T& Queap<T>::MyIterator::operator*()//dereference
{
	if(inTree)
		return *t_it_;
	else
		return *l_it_;	
	
} 

template <typename T>
typename Queap<T>::MyIterator& Queap<T>::MyIterator::operator++() // pre incr
{

	if(inTree)
	{
		t_it_++;
		if(t_it_.p_it_ == nullptr) // change it t_it_.end()
			inTree = false;
	}
	else
		l_it_++;
	return *this;
}

template <typename T>
typename Queap<T>::MyIterator Queap<T>::MyIterator::operator++(int) // post incr
{
	MyIterator temp(*this);
	++*this;
	return temp;
}


template <typename T>
typename Queap<T>::MyIterator Queap<T>::begin()
{
	auto st = t_.begin();
	if(st == t_.end())
		return MyIterator(st,l_.begin(),false);
	else
		return MyIterator(++st,l_.begin(),true);
}

template <typename T>
typename Queap<T>::MyIterator Queap<T>::end()
{
	return MyIterator(t_.end(),l_.end(),false);
}


// **************************************GENERIC FUNCTIONS*********************************

template<typename T>
typename Queap<T>::MyIterator Queap<T>::find(MyIterator begin, MyIterator end, T ele)
{
	
	while (begin!=end) {
    	if (*begin == ele) 
    		return begin;
    	++begin;
	}
	return begin;
}



template<typename T>
void Queap<T>::replace(MyIterator begin, MyIterator end, T oldvalue, T ele)
{
	if(oldvalue == minL_)
		minL_ = T();
	while(begin!=end)
	{
		if(*begin == oldvalue)
		{
			if(!begin.inTree)
			{
				*begin = ele;
				
				// for_each()
			}
			else
			{
				*begin = ele;
				t_.updatePointerPath(begin.t_it_.p_it_);
				// cout << "m: "<< t_.x0_->p_->ele_;
			}
		}
		if(!begin.inTree)
		{
			if((*begin).key_ < minL_.key_)
				minL_ = *begin;
		}
		++begin;
	}
}
/*
int main()
{
	Queap<Element<int,int>> Q;
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
	});
}
*/
