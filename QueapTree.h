#ifndef TREE_H
#define TREE_H
#include <vector>
#include <limits>

template <typename T>
class TreeNode
{
	private:
		T ele_;
		TreeNode<T>* child_[4];
		TreeNode<T>* parent_;
		TreeNode<T>* p_;
		bool hvcv_; // to check whether the pointer p_ is hv or cv
		int count_;

	public:
		TreeNode(T ele);

		template<typename Z> friend class QueapTree;
		template<typename Z> friend class Queap;
		template<typename X>friend ostream& operator<<(ostream&,const TreeNode<X>&);

};

template <typename T>
class QueapTree
{
	private:
		TreeNode<T> *root_, *x0_;
		long height_;
	public:
		QueapTree(); // default constructor
		~QueapTree(); // destructor
		QueapTree(const QueapTree&); // copy constructor
		QueapTree(QueapTree&&); // move constructor

		QueapTree& operator=(const QueapTree&); // copy assignment
		QueapTree& operator=(QueapTree&&); //move assignment


		class MyIterator
		{
			private:
				TreeNode<T>* p_it_;
				long height_;
				long *count_;
			public:
				MyIterator(TreeNode<T> *p_it,long height);
				// all defaults
				bool operator==(const MyIterator& rhs) const;
				bool operator!=(const MyIterator& rhs) const;
				T& operator*();
				MyIterator& operator++();
				MyIterator operator++(int);
				TreeNode<T>* nextSibling(TreeNode<T>* node,long level);
				template<typename Z> friend class Queap;
				friend void QueapTree<T>::deleteLeaf(T ele); 
				friend void QueapTree<T>::deleteNodes(MyIterator el);

		};
		MyIterator begin();
		MyIterator end();



		bool addNode(TreeNode<T>* parent, T ele,int height = 0);
		void insertNode(T ele);
		void deleteNode(TreeNode<T>* node);
		void deleteLeaf(T ele);
		void deleteNodes(MyIterator el);
		void clear();
		void traverseTree();
		void traverse(TreeNode<T>* node, void (QueapTree<T>::*f)(TreeNode<T>* node));
		void traverseLeaf(TreeNode<T>* node, void (QueapTree<T>::*f)(T ele));
		void displayNode(TreeNode<T>* node);

		void updatePointerPath(TreeNode<T>* node);
		TreeNode<T>* minPointer(vector<TreeNode<T>*> pointerList);

		MyIterator find(MyIterator begin, MyIterator end, T ele);
		// void copy(MyIterator begin_src, MyIterator end_src, MyIterator begin_dest);
		void replace(MyIterator begin, MyIterator end, T oldvalue, T ele);

		template<typename Z> friend class Queap;

		
};

#include "QueapTree.cpp"

#endif