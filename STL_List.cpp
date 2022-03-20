#define _CRT_SECURE_NO_WARNINGS 1
//模拟实现list
#include<iostream>
#include"memory.h"
using namespace std;

namespace m_list
{
	template<typename _Ty, class _A = my_allocator<_Ty>>
	class list
	{
		public:
		struct _Node
		{
			struct _Node* _Prev;
			struct _Node* _Next;
			_Ty _Value;
		};
	public:
		    typedef _Node* _Nodeptr;
		    typedef size_t size_type;
		    typedef _Ty*   pointer_type;
		    typedef _Ty&   reference_type;
		    typedef _Ty    value_type;
		    typedef const _Ty* const_pointer_type;
		    typedef const _Ty& const_reference_type;
	public:
		list():_Head(_BuyNode()),_Size(0)
		{}
	public:
		void push_back(value_type a)
		{
			/*_Nodeptr s = _BuyNode(_Head, _Head->_Prev);
			s->_Value = a;
			s->_Next->_Prev = s;
			s->_Prev->_Next = s;
			_Size++;*/
			insert(end(),a);
		}
		void push_front(value_type a)
		{
			insert(begin(), a);
		}
		void Pop_back()
		{
			/*_Nodeptr p = (--end())._Ptr;
			p->_Next->_Prev = p->_Prev;
			p-> _Prev->_Next = p->_Next;
			free(p);
			--_Size;
			p = nullptr;*/
			erase(--end());
		}
		void Pop_front()
		{
			/*_Nodeptr p = begin()._Ptr;
			p->_Next->_Prev = p->_Prev;
			p->_Prev->_Next = p->_Next;
			free(p);
			--_Size;
			p = nullptr;*/
			erase(begin());
		}
	public:
		class iterator//迭代器，目前我们可以用其代之指针(其实就是一个被封装了的指针)
		{
			friend class list;
		public:
			iterator()
			{}
			iterator(_Nodeptr P) :_Ptr(P)
			{}
			_Ty operator*()
			{
				return _Ptr->_Value;
			}
			_Ty* operator->()
			{
				return &(_Ptr->_Value);
			}
			iterator& operator++()
			{
				_Ptr = _Ptr->_Next;
				return (*this);
			}
			iterator operator++(int)
			{
				iterator r_Ptr = *this;
				++*this;
				return r_Ptr;
			}
			iterator& operator--()
			{
				_Ptr = _Ptr->_Prev;
				return (*this);
			}
			iterator operator--(int)
			{
				iterator r_Ptr = *this;
				--*this;
				return r_Ptr;
			}
			bool operator==(iterator& X)
			{
				return _Ptr == X._Ptr;
			}
			bool operator!=(iterator& X)
			{
				return !(_Ptr == X._Ptr);
			}
			_Nodeptr _Mynode()const
			{
				return _Ptr;
			}
		private:
			_Nodeptr _Ptr;
		};

	public:
		iterator insert(iterator _P, const _Ty& _X = _Ty())
		{
			_Nodeptr s = _P._Mynode();
			s->_Prev = _BuyNode(s, s->_Prev);
			s = s->_Prev;
			s->_Prev->_Next = s;
			s->_Value = _X;
			++_Size;
			return (iterator(s));
		}
		iterator erase(iterator _P)
		{
			_Nodeptr _S = (_P++)._Mynode();
			_S->_Next->_Prev = _S->_Prev;
			_S->_Prev->_Next = _S->_Next;
			_Size--;
			free(_S);
			_S = nullptr;
			return (iterator(_P));
		}
		iterator erase(iterator _F, iterator _L)
		{
			while (_F != _L)
				erase(_F++);
			return (_F);
		}
	public:
		iterator begin()
		{
			return iterator(_Head->_Next);//如同初始化类函数
		}
		iterator end()
		{
			return iterator(_Head);
		}
	public:
		bool empty()
		{
			return _Size == 0;
		}
		int size()
		{
			return _Size;
		}
	public:
		_Ty& front()
		{
			return _Head->_Next->_Value;
		}
		_Ty& back()
		{
			return _Head->_Prev->_Value;
		}
	public:
		void clear()
		{
			erase(begin(), end());
		}
		void swap(list<int>& L)
		{
			std::swap(_Head, L._Head);
		}
	private:
		_Nodeptr _BuyNode(_Nodeptr _Narg = 0, _Nodeptr _Parg = 0)
		{
			//_Nodeptr s = (_Nodeptr)malloc(sizeof(_Node));
			_Nodeptr s = (_Nodeptr)allocator._Charalloc(1 * sizeof (_Node));
			s->_Next = _Narg != 0 ? _Narg : s;
			s->_Prev = _Parg != 0 ? _Parg : s;
			return s;
		}
	private:
		_A allocator;
		_Nodeptr _Head;
		size_type _Size;
	};
};
int main()
{
	m_list::list<int> L;
	for (int i = 0; i < 10; i++)
	{
		L.push_back(i);
	}
	L.Pop_front();
	L.Pop_back();
	m_list::list<int>::iterator it = L.begin();
	while (it != L.end())
	{
		cout << *it << "-->";
		it++;
	}
	cout << "Over." << endl;

	return 0;
}
