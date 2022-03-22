#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
namespace bite
{
	// List的节点类
	template<class T>
	struct ListNode
	{
		ListNode(const T& val = T()): _pPre(nullptr), _pNext(nullptr), _val(val)
		{}
		ListNode<T>* _pPre;
		ListNode<T>* _pNext;
		T _val;
	};
	//List的迭代器类
	template<class T, class Ref, class Ptr>
	class ListIterator
	{
		template<class T>
		friend class list;
		typedef ListNode<T>* PNode;
		typedef ListIterator<T, Ref, Ptr> Self;
	public:
		ListIterator(PNode pNode = nullptr) :_pNode(pNode)
		{}
		ListIterator(const Self& l)
		{
			_pNode = l._pNode;
		}
		T& operator*()
		{
			return (_pNode->_val);
		}
		T* operator->()
		{
			return &(_pNode->_val);
		}
		Self& operator++()
		{
			_pNode = _pNode->_pNext;
			return *this;
		}
		Self operator++(int)
		{
			Self temp(*this);
			_pNode = _pNode->_pNext;
			return temp;
		}
		Self& operator--()
		{
			_pNode = _pNode->_pPre;
			return *this;
		}
		Self operator--(int)
		{
			Self temp = *this;
			_pNode = _pNode->_pPre;
			return temp;
		}
		bool operator!=(const Self& l)
		{
			return _pNode != l._pNode;
		}
		bool operator==(const Self& l)
		{
			return _pNode == l._pNode;
		}
	private:
		PNode _pNode;
	};
	//list类
	template<class T>
	class list
	{
		typedef ListNode<T> Node;
		typedef Node* PNode;
	public:
		typedef ListIterator<T, T&, T*> iterator;
		typedef ListIterator<T, const T&, const T&> const_iterator;
	public:
		///////////////////////////////////////////////////////////////
		// List的构造
		list()
		{
			CreateHead();
		}
		list(int n, const T& value = T())
		{
			CreateHead();
			while (n > 0)
			{
				push_back(value);
				n--;
			}
		}
		template <class Iterator>
		list(Iterator first, Iterator last)
		{
			CreateHead();
			while (first != last)
			{
				push_back(*first);
				first++;
			}
		}
		list(const list<T>& l)
		{
			CreateHead();
			list<T> temp(l.begin(), l.end());
			this->swap(temp);
		}
		list<T>& operator=(const list<T> l)
		{
			this->swap(l);
			return *this;
		}
		~list()
		{
			clear();
			delete _pHead;
			_pHead = nullptr;
		}
		///////////////////////////////////////////////////////////////
		// List Iterator
		iterator begin()
		{
			return (iterator(_pHead->_pNext));
		}
		iterator end()
		{
			return (iterator(_pHead));
		}
		const_iterator begin()const
		{
			return (const_iterator(_pHead->_pNext));
		}
		const_iterator end()const
		{
			return (const_iterator(_pHead));
		}
		///////////////////////////////////////////////////////////////
		// List Capacity
		size_t size()const
		{
			size_t size = 0;
			PNode p = _pHead->_pNext;
			while (p != _pHead)
			{
				size++;
				p = p->_pNext;
			}
			return size;
		}
		bool empty()const
		{
			return _pHead->_pNext == _pHead;
		}
		////////////////////////////////////////////////////////////
		// List Access
		T& front()
		{
			return (*begin());
		}
		const T& front()const
		{
			return (*begin());
		}
		T& back()
		{
			return (*end);
		}
		const T& back()const
		{
			return (*end);
		}
		////////////////////////////////////////////////////////////
		// List Modify
		void push_back(const T& val)
		{
			insert(begin(), val);
		}
		void pop_back()
		{
			erase(--end());
		}
		void push_front(const T& val)
		{
			insert(begin(), val);
		}
		void pop_front()
		{
			erase(begin());
		}
		// 在pos位置前插入值为val的节点
		iterator insert(iterator pos, const T& val)
		{
			PNode _S = new Node(val);
			_S->_pNext = pos._pNode;
			_S->_pPre = pos._pNode->_pPre;
			_S->_pPre->_pNext = _S;
			_S->_pNext->_pPre = _S;
			return pos;
		}
		// 删除pos位置的节点，返回该节点的下一个位置
		iterator erase(iterator pos)
		{
			PNode _S = (pos._pNode++);
			_S->_pNext->_pPre = _S->_pPre;
			_S->_pPre->_pNext = _S->_pNext;
			delete _S;
			return pos;
		}
		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				erase(it++);
			}
		}
		void swap(const list<T>& l)
		{
			PNode tmp = _pHead;
			_pHead = l._pHead;
			
		}
	private:
		void CreateHead()
		{
			_pHead = new Node;
			_pHead->_pNext = _pHead;
			_pHead->_pPre = _pHead;
		}
		PNode _pHead;
	};
};
using namespace bite; template<class T>
void PrintList(const bite::list<T>& l)
{
	auto it = l.begin();
	while (it != l.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
void main()
{
	/*bite::list<int> l1;
	bite::list<int> l2(10, 5);
	PrintList(l2);
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	bite::list<int> l3(array, array + sizeof(array) / sizeof(array[0]));
	PrintList(l3);
	bite::list<int> l4(l3);
	PrintList(l4);
	l1 = l4;
	PrintList(l1);
	PrintList(l1);*/
	//////////////////////////////////////
	//bite::list<int> l;
	//l.push_back(1);
	//l.push_back(2);
	//l.push_back(3);
	//PrintList(l);
	//l.pop_back();
	//l.pop_back();
	//PrintList(l);
	//l.pop_back();
	//cout << l.size() << endl;
	//// 测试PushFront与PopFront
	//l.push_front(1);
	//l.push_front(2);
	//l.push_front(3);
	//PrintList(l);
	//l.pop_front();
	//l.pop_front();
	//PrintList(l);
	//l.pop_front();
	//cout << l.size() << endl;
	int array[] = { 1, 2, 3, 4, 5 };
	bite::list<int> l(array, array + sizeof(array) / sizeof(array[0]));
	auto pos = l.begin();
	l.insert(l.begin(), 0);
	PrintList(l);
	++pos;
	l.insert(pos, 2);
	PrintList(l);
	l.erase(l.begin());
	l.erase(pos);
	PrintList(l);
	// pos指向的节点已经被删除，pos迭代器失效
	cout << *pos << endl;
	auto it = l.begin();
	while (it != l.end())
	{
		it = l.erase(it);
	}
	cout << l.size() << endl;
}