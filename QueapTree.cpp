// #include <iostream>
// #include <vector>
// #include <limits>
// using namespace std;
// #include "header.h"
// #include "QueapTree.h"


template <typename T>
TreeNode<T>::TreeNode(T ele)
:ele_(ele), count_(-1) , parent_(nullptr),  hvcv_(false), p_(nullptr)
{

	for(int i = 0;i <4; i++)
	{
		child_[i] = nullptr;
	}
}

// **************************************CONSTRUCTORS**************************************

template <typename T>
QueapTree<T>::QueapTree()
: root_(new TreeNode<T>(T())) , x0_(root_) , height_(0)
{

}

template <typename T>
QueapTree<T>::QueapTree(const QueapTree& rhs)
: root_(new TreeNode<T>(T())), x0_(root_) ,height_(rhs.height_)
{
	traverseLeaf(rhs.root_, &QueapTree<T>::insertNode);
}

template <typename T>
QueapTree<T>::QueapTree(QueapTree&& rhs)
: root_(rhs.root_), x0_(rhs.x0_),height_(rhs.height_)
{
	rhs.root_ = nullptr;
	rhs.x0_ = nullptr;
	rhs.height_ = 0;
}

// **************************************ASSIGNMENT FUNCTIONS*****************************

template <typename T>
QueapTree<T>& QueapTree<T>::operator=(const QueapTree& rhs) // copy assignment
{
	if(this != &rhs)
	{
		clear();
		traverseLeaf(rhs.root_, &QueapTree<T>::insertNode);
		height_ = rhs.height_;
	}
	return *this;
}

		
template <typename T>
QueapTree<T>& QueapTree<T>::operator=(QueapTree&& rhs) //move assignment
{
	cout << "move assgn\n";
	if(this != &rhs)
	{
		traverse(root_, &QueapTree<T>::deleteNode);

		root_ = rhs.root_;
		x0_ = rhs.x0_;
		height_ = rhs.height_;
		rhs.root_ = nullptr;
		rhs.x0_ = nullptr;
		rhs.height_ = 0;
	}
	return *this;

}

// **************************************DESTRUCTOR**************************************

template <typename T>
QueapTree<T>::~QueapTree()
{
	clear();
	delete root_;
	root_ = nullptr;
	x0_ = nullptr;
}

// **************************************ITERATOR*********************************

template <typename T>
QueapTree<T>::MyIterator::MyIterator(TreeNode<T> *p_it,long height) 
: p_it_(p_it),height_(height-1),count_(new long[height]) 
{ 
	for(int i=0;i<height;i++)
	{
		count_[i] = 0;
	}
}

template <typename T>
bool QueapTree<T>::MyIterator::operator==(const MyIterator& rhs) const //check for equality
{
	return p_it_ == rhs.p_it_;
}

template <typename T>
bool QueapTree<T>::MyIterator::operator!=(const MyIterator& rhs) const //check for unequality
{
	return !(*this == rhs);
}

template <typename T>
T& QueapTree<T>::MyIterator::operator*()//dereference
{
	return p_it_->child_[count_[height_]]->ele_;
} 

template <typename T>
typename QueapTree<T>::MyIterator& QueapTree<T>::MyIterator::operator++() // pre incr
{


	count_[height_]++;
	if(count_[height_] > p_it_->count_)
	{	
		
		p_it_ = nextSibling(p_it_,height_);
		
	}		

	return *this;
}

template <typename T>
typename QueapTree<T>::MyIterator QueapTree<T>::MyIterator::operator++(int) // post incr
{
	MyIterator temp(*this);
	++*this;
	return temp;
}

template <typename T>
TreeNode<T>* QueapTree<T>::MyIterator::nextSibling(TreeNode<T>* node,long level)
{
		count_[level-1]++;
		if(node->parent_ == nullptr)
			return nullptr; // return nullptr
		else if(count_[level-1] > node->parent_->count_)
			return nextSibling(node->parent_,level-1);
		else	
		{	
			count_[level] = 0;
			return node->parent_->child_[count_[level-1]];
		}
}


template <typename T>
typename QueapTree<T>::MyIterator QueapTree<T>::begin()
{
	TreeNode<T>* pointer = root_;
	while(pointer->count_!=-1)
	{
		pointer = pointer->child_[0];
	}

	return MyIterator(pointer->parent_,height_);
}

template <typename T>
typename QueapTree<T>::MyIterator QueapTree<T>::end()
{
	return MyIterator(nullptr,1);
}


// **************************************OTHER FUNCTIONS*********************************
template <typename T>
void QueapTree<T>::clear()
{

	if(root_!=nullptr)
	{
		traverse(root_, &QueapTree<T>::deleteNode);
	}
	root_ = new TreeNode<T>(T());
	x0_ = root_;
	height_ = 0;
}


template <typename T>
void QueapTree<T>::insertNode(T ele)
{

	TreeNode<T>* pointer = root_;

	while(pointer->count_!=-1)
	{

		pointer = pointer->child_[pointer->count_];
	}
	addNode(pointer->parent_,ele);

}

template <typename T>
bool QueapTree<T>::addNode(TreeNode<T>* parent, T ele,int height)
{
	static vector<TreeNode<T>*> split;
	static vector<TreeNode<T>*> pointerList;
	if(parent == nullptr) // root
	{

		int temp_height = height;

		TreeNode<T>* temp = new TreeNode<T>(T(numeric_limits<char>::max(),numeric_limits<char>::max())); 
		root_->parent_ = temp;		
		temp->child_[0] = root_;
		root_->hvcv_ = true;
		root_->p_ = nullptr;
		root_ = temp;
		root_->count_++;

		height_+=1; // increase height of tree.

		TreeNode<T>* temp_parent = root_;
		while(temp_height--)
		{
			TreeNode<T>* temp = new TreeNode<T>(T(numeric_limits<char>::max(),numeric_limits<char>::max()));
			// cout << "bool1: "<< temp->hvcv_ << endl;
			temp->parent_ = temp_parent;
			temp_parent->count_++;
			temp_parent->child_[temp_parent->count_] = temp;

			if(!split.empty())
			{
				TreeNode<T>* t = split.back();
				
				temp->child_[++temp->count_] = t;
				t->parent_->child_[t->parent_->count_--] = nullptr;

				// recompute the pointers for the prev parent of the split node (only if the node pointer is not cv)
				if(t->parent_->hvcv_ == false)
				{
					// cout << "boob\n";
					pointerList.resize(0);
					for(int i = 0; i <= t->parent_->count_; i++)
					{
						pointerList.push_back(t->parent_->child_[i]);
					}
					t->parent_->p_ = minPointer(pointerList);	
					t->parent_->ele_ = t->parent_->p_->ele_;
				}	

				t->parent_ = temp; // change parent
				split.pop_back();
			}

			temp_parent = temp;
		}

		TreeNode<T>* temp2 = new TreeNode<T>(ele);
		temp_parent->count_++;
		temp_parent->child_[temp_parent->count_] = temp2;
		temp2->parent_ = temp_parent;
		pointerList.resize(0);
		for(int i = 0; i <= temp_parent->count_; i++)
		{
			pointerList.push_back(temp_parent->child_[i]);
		}

		temp_parent->p_ = minPointer(pointerList);
		temp_parent->ele_ = temp_parent->p_->ele_;

		updatePointerPath(temp_parent->parent_);
		

	}
	else if(parent->count_ + 1 > 3)
	{

		height++;
		split.push_back(parent->child_[3]);
		addNode(parent->parent_,ele,height);
	}
	else
	{
		int temp_height = height;
		TreeNode<T>* temp_parent = parent;
		while(temp_height--)
		{
			TreeNode<T>* temp = new TreeNode<T>(T(numeric_limits<char>::max(),numeric_limits<char>::max()));

			temp->parent_ = temp_parent;
			temp_parent->count_++;
			temp_parent->child_[temp_parent->count_] = temp;			
			temp_parent = temp;

			if(!split.empty())
			{
				TreeNode<T>* t = split.back();
				temp->child_[++temp->count_] = t;
				t->parent_->child_[t->parent_->count_--] = nullptr;

				if(t->parent_->hvcv_ == false)
				{

					pointerList.resize(0);
					for(int i = 0; i <= t->parent_->count_; i++)
					{
						pointerList.push_back(t->parent_->child_[i]);
					}
					t->parent_->p_ = minPointer(pointerList);	
					t->parent_->ele_ = t->parent_->p_->ele_;
				}	

				t->parent_ = temp; // change parent
				split.pop_back();
			}


		}

		TreeNode<T>* temp2 = new TreeNode<T>(ele);
		temp_parent->count_++;
		temp_parent->child_[temp_parent->count_] = temp2;
		temp2->parent_ = temp_parent;

		pointerList.resize(0);
		for(int i = 0; i <= temp_parent->count_; i++)
		{
			pointerList.push_back(temp_parent->child_[i]);
		}

		temp_parent->p_ = minPointer(pointerList);
		temp_parent->ele_ = temp_parent->p_->ele_;
		updatePointerPath(temp_parent->parent_);

	}

 return true;	
		
}

template <typename T>
void QueapTree<T>::updatePointerPath(TreeNode<T>* node)
{
	if(node == nullptr)
		node = root_;

	vector<TreeNode<T>*> pointerList;
	
	while(node != root_ && node->hvcv_ != true)
	{
		pointerList.resize(0);
		for(int i = 0; i <= node->count_; i++)
		{
			pointerList.push_back(node->child_[i]);
		}

		node->p_ = minPointer(pointerList);
		node->ele_ = node->p_->ele_;

		node = node->parent_;
	}
	node = node->child_[0];


	if(node->parent_ == root_)
	{

		pointerList.resize(0);
		for(int i = 1; i <= node->parent_->count_; i++)
		{
			pointerList.push_back(node->parent_->child_[i]);
		}

		node->p_ = minPointer(pointerList);

		if(node->child_[0]!=nullptr)
		{

			node->ele_ = node->p_->ele_;
		}

		node = node->child_[0];
	}

	
	while(node!=nullptr)
	{
		pointerList.resize(0);
		pointerList.push_back(node->parent_);

		for(int i = 1; i <= node->parent_->count_; i++)
		{
			pointerList.push_back(node->parent_->child_[i]);
		}

		node->p_ = minPointer(pointerList);
		if(node->child_[0]!=nullptr)
		{

			node->ele_ = node->p_->ele_;
		}

		node = node->child_[0];
		
	}

	root_->p_ = x0_->p_;
	root_->ele_ = root_->p_->ele_;
}

template <typename T>
TreeNode<T>* QueapTree<T>::minPointer(vector<TreeNode<T>*> pointerList)
{


	TreeNode<T>* min = pointerList[0];
	for(TreeNode<T>* i: pointerList)
	{

		if(i->ele_.key_ < min->ele_.key_)
		{
			min = i;
		}

	}

	return min;
} 

template <typename T>
void QueapTree<T>::traverseTree()
{
	traverse(root_, &QueapTree<T>::displayNode);
}

template <typename T>
void QueapTree<T>::traverse(TreeNode<T>* node, void (QueapTree<T>::*f)(TreeNode<T>* node))
{

	switch(node->count_)
	{
		case -1: // leaf node

			(this->*f)(node);
			break;
		case 0: // one child

			traverse(node->child_[0], f);
			(this->*f)(node);
			// cout << "--------------------\n";
			break;
		case 1: // two children
	
			traverse(node->child_[0], f);
			traverse(node->child_[1], f);
			(this->*f)(node);
			// cout << "--------------------\n";
			break;
		case 2: // three children

			traverse(node->child_[0], f);
			traverse(node->child_[1], f);
			traverse(node->child_[2], f);
			(this->*f)(node);
			// cout << "--------------------\n";
			break;
		case 3: // four children

			traverse(node->child_[0], f);
			traverse(node->child_[1], f);
			traverse(node->child_[2], f);
			traverse(node->child_[3], f);
			(this->*f)(node);
			// cout << "--------------------\n";
			break;
	}
}

template <typename T>
void QueapTree<T>::traverseLeaf(TreeNode<T>* node, void (QueapTree<T>::*f)(T ele))
{
	switch(node->count_)
	{
		case -1: // leaf node
			if(!(node->ele_== T()))
			{	
				(this->*f)(node->ele_);
			}
			
			break;
		case 0: // one child
			traverseLeaf(node->child_[0], f);
			// cout << "--------------------\n";
			break;
		case 1: // two children
			
			traverseLeaf(node->child_[0], f);
			traverseLeaf(node->child_[1], f);
			// cout << "--------------------\n";
			break;
		case 2: // three children
			
			traverseLeaf(node->child_[0], f);
			traverseLeaf(node->child_[1], f);
			traverseLeaf(node->child_[2], f);
			// cout << "--------------------\n";
			break;
		case 3: // four children
			
			traverseLeaf(node->child_[0], f);
			traverseLeaf(node->child_[1], f);
			traverseLeaf(node->child_[2], f);
			traverseLeaf(node->child_[3], f);
			// cout << "--------------------\n";
			break;
	}

}

template <typename T>
void QueapTree<T>::displayNode(TreeNode<T>* node)
{
	cout << *node;
}

template <typename T>
void QueapTree<T>::deleteNode(TreeNode<T>* node)
{
	delete node;
}

template <typename T>
void QueapTree<T>::deleteLeaf(T ele)
{
	auto el = find(begin(),end(),ele);
	if(el == end())
		return;
	else
	{
		deleteNodes(el);
	}
}

template <typename T>
void QueapTree<T>::deleteNodes(QueapTree<T>::MyIterator el)
{
		int pos = el.count_[el.height_];
		TreeNode<T>* parent  = el.p_it_;

		if(parent->count_ < 2) // less than 2 children
		{

			if(parent->parent_ == nullptr)
			{
				//make the left out node as the root.
				delete parent->child_[pos];
				TreeNode<T>* t  = parent->child_[0];

				delete parent;
				t->parent_ = nullptr;
				root_ = t;

				// reduce Tree height
				height_--;
			}
			else
			{
				int p_pos = el.count_[el.height_-1];

				if(p_pos-1 > -1 && parent->parent_->child_[p_pos-1]->count_ > 1) // left Sibling exist and if the sibling has more than 2 child
				{

						TreeNode<T>* sibling  = parent->parent_->child_[p_pos-1];
						delete parent->child_[pos];
						if(pos == 1)
							parent->child_[1] = parent->child_[0]; // make space for child[0]

						//Borrow right most child of sibling
						sibling->child_[sibling->count_]->parent_ = parent;
						parent->child_[0] = sibling->child_[sibling->count_];
						sibling->count_--;

						updatePointerPath(parent);
						updatePointerPath(sibling);
				
					
				}
				else if(p_pos+1 <= parent->parent_->count_) // right sibling exist
					{
						// cout<<"right sibling"<<parent->child_[pos];
						TreeNode<T>* sibling  = parent->parent_->child_[p_pos+1];
						if(sibling->count_ > 1) // if the sibling has more than 2 child
						{
							
							delete parent->child_[pos];
							if(pos == 0)
								parent->child_[0] = parent->child_[1]; // make space for child[1]

							//Borrow left most child of sibling
							sibling->child_[0]->parent_ = parent;						
							parent->child_[1] = sibling->child_[0];

							for(int i = 0 ; i < sibling->count_ ; i++)
								sibling->child_[i] = sibling->child_[i+1];

							sibling->count_--;

							updatePointerPath(parent);
							updatePointerPath(sibling);
						}
						else // merge with the right sibling
						{
							// cout<<"merge";
							delete parent->child_[pos];
							if(pos == 0)
								parent->child_[0] = parent->child_[1]; // make space for child[1]

							//Borrow both children from right sibling
							sibling->child_[0]->parent_ = parent;
							sibling->child_[1]->parent_ = parent;
							sibling->count_-=2;
							parent->child_[1] = sibling->child_[0];
							parent->child_[2] = sibling->child_[1];
							parent->count_++; 

							sibling->child_[0] = nullptr;
							sibling->child_[1] = nullptr;
							sibling->p_ = nullptr;
							sibling->ele_ = T();
							updatePointerPath(parent);

							// Traverse this up the root
							el.p_it_ = parent->parent_;
							el.height_--;
							el.count_[el.height_]++; // change the count to next sibling
							deleteNodes(el);

						}
					}
				else // merge with left sibling
				{
							// cout<<"merge left"<<parent->child_[pos];;
							TreeNode<T>* sibling  = parent->parent_->child_[p_pos-1];

							delete parent->child_[pos];

							//Push both children to left sibling
							if(pos == 1)
							{
								sibling->child_[2] = parent->child_[0];
								parent->child_[0]->parent_ = sibling;
							}
							else
							{
								sibling->child_[2] = parent->child_[1];
								parent->child_[1]->parent_ = sibling;
							}

							sibling->count_++;
							parent->count_ = -1;

							parent->child_[0] = nullptr;
							parent->child_[1] = nullptr;
							parent->p_ = nullptr;
							parent->ele_ = T();
							updatePointerPath(sibling);

							// Traverse this up the root
							el.p_it_ = parent->parent_;
							el.height_--;
							// el.count_[el.height_]; // change the count to next sibling
							deleteNodes(el);

				}
			}
		}
		else // more than 2 children
		{

			delete parent->child_[pos];

			for(int i = pos ; i < parent->count_ ; i++)
			{
				parent->child_[i] = parent->child_[i+1]; // Shift
			}
			parent->count_--;
			updatePointerPath(parent);
		}
}




// **************************************OSTREAM FUNCTIONS*********************************

template<typename T>
ostream& operator<<(ostream& o,const TreeNode<T>& node)
{
	return o << node.ele_;
}


// **************************************GENERIC FUNCTIONS*********************************

template <typename T>
typename QueapTree<T>::MyIterator QueapTree<T>::find(MyIterator begin,MyIterator end, T ele)
{
	while (begin!=end) {
		if ((*begin).key_ == ele.key_) 
			return begin;
		++begin;
	}
	return begin;
}

template<typename T>
void QueapTree<T>::replace(MyIterator begin,MyIterator end, T oldvalue, T ele)
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
