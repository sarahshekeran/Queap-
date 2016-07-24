#ifndef ELE_H
#define ELE_H
#include <limits>
// interface for an element
template <typename T, typename U>
class Element
{
	private: 
		T key_;
		U value_;
	public:
		Element();
		Element(T key, U value);
		Element(const Element<T,U>& rhs);

		Element<T, U>& operator=(const Element<T,U>& rhs);
		bool operator==(const Element<T, U>&  rhs);
		template<typename Z> friend class QueapList;
		template<typename Z> friend class QueapTree;
		template<typename Z> friend class Queap;
		template<typename X,typename Y>friend ostream& operator<<(ostream&,const Element<X,Y>&);
};

template <typename T, typename U>
Element<T,U>::Element()
: key_(numeric_limits<T>::max()), value_(numeric_limits<U>::max())
{
}

template <typename T, typename U>
Element<T,U>::Element(T key, U value)
: key_(key), value_(value)
{
}

template <typename T, typename U>
Element<T,U>::Element(const Element<T,U>& rhs)
: key_(rhs.key_), value_(rhs.value_)
{

}

template <typename T, typename U>
Element<T, U>& Element<T, U>::operator=(const Element<T,U>& rhs)
{
	if(this != &rhs)
	{
		key_ = rhs.key_;
		value_ = rhs.value_;
	}
	return *this;
}

template<typename T,typename U>
ostream& operator<<(ostream& o,const Element<T,U>& ele)
{
	return o << ele.key_ << "\t" << ele.value_ <<endl;
}

template <typename T, typename U>
bool Element<T, U>::operator==(const Element<T, U>& rhs)
{
	return ((key_ == rhs.key_) && (value_ == rhs.value_));
}

#endif



