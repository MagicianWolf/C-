#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
namespace My_string
{
	class string
	{
	public:
		typedef char* iterator;
		friend ostream& operator<<(ostream& _cout, const My_string::string& s);
		friend istream& operator>>(istream& _cin, My_string::string& s);
	//四大函数均采用现代的做法
	public:
		string(const char* str = "")//构造函数
		{
			m_capacity = m_size = strlen(str);
			m_str = new char[m_capacity + 1];
			strcpy(m_str, str);
		}
		string(const string &str) :m_str(nullptr), m_capacity(0), m_size(0)//拷贝构造函数
		{
			string str_tmp(str.m_str);
			this->Swap(str_tmp);
		}
		string& operator=(string str)//赋值语句
		{
			this->Swap(str);
			return *this;
		}
		~string()//析构函数
		{
			if (m_str)
			{
				m_capacity = m_size = 0;
				delete[] m_str;
				m_str = nullptr;
			}
		}
	//迭代器部分
	public:
		iterator begin()
		{
			return (iterator)m_str;
		}
		iterator end()
		{
			return (iterator)m_str[m_size];
		}
	//修改部分（modify）
	public:
		void push_back(char c)
		{
			//判断是否扩容；
			if (m_size == m_capacity)
			{
				reserve(2 * m_capacity + 1);
			}
			//尾加字符
			m_str[m_size++] = c;
			m_str[m_size] = '\0';
		}
		string& operator+=(char c)
		{
			push_back(c);
			return *this;
		}
		void append(const char* str)
		{
			/*for (int i = 0; i <= strlen(str); ++i)
				push_back(str[i]);*/
			size_t len = strlen(str);
			while(len + m_size > m_capacity)
				reserve(2 * m_capacity + 1);
			strcpy(m_str+m_size, str);
			m_size += len;
		}
		string& operator+=(const char* str)
		{
			append(str);
			return *this;
		}
		void clear()
		{
			m_size = 0;
			m_str[m_size] = '\0';
		}
		const char* c_str()const
		{
			return m_str;
		}
		//容量部分
	public:
		size_t size()
		{
			return m_size;
		}
		size_t capacity()
		{
			return m_capacity;
		}
		bool empty()
		{
			return m_size == 0;
		}
		void resize(size_t newSize, char c = '\0')
		{
			if (newSize > m_size)
			{
				// 如果newSize大于底层空间大小，则需要重新开辟空间
				if (newSize > m_capacity)
				{
					reserve(newSize);
				}
				memset(m_str +m_size, c, newSize - m_size);
			}
			m_size = newSize;
			m_str[newSize] = '\0';
		}
		void reserve(size_t New_capacity)
		{
			if (New_capacity > m_capacity)
			{
				char* str = new char[New_capacity];
				strcpy(str, m_str);
				//释放原来空间使用新空间
				delete[] m_str;
				m_str = str;
				m_capacity = New_capacity;
			}
		}
	public:
		char& operator[](size_t index)
		{
			if (index < m_size)
			    return m_str[index];
		}
		const char& operator[](size_t index)const
		{
			if (index < m_size)
				return m_str[index];
		}
		bool operator<(const string& s)
		{
			return strcmp(m_str, s.m_str) > 0;
		}
		bool operator<=(const string& s)
		{
			return strcmp(m_str, s.m_str) <= 0;
		}
		bool operator>(const string& s)
		{
			return strcmp(m_str, s.m_str) > 0;
		}
		bool operator>=(const string& s)
		{
			return strcmp(m_str, s.m_str) >= 0;
		}
		bool operator==(const string& s)
		{
			return strcmp(m_str, s.m_str) == 0;
		}
		bool operator!=(const string& s)
		{
			return strcmp(m_str, s.m_str) != 0;
		}
		//返回字符c出现在string中的第一个位置
		size_t find(char c, size_t pos = 0) const
		{
			for (int i = pos; i < m_size; ++i)
			{
				if (m_str[i] == c)
					return i;
			}
			return -1;
		}
		//返回字符串s出现在string中的第一个位置
	    size_t find(const char* s, size_t pos = 0) const
		{
			for (int i = 0; i < m_size; ++i)
			{
				if (m_str[i] == s[0])
				{
					int count = i;
					int j = 0;
					for (; j < strlen(s) && count < m_size; ++j,++count)
					{
						if (m_str[count] != s[j])
							break;
					}
					if (j == strlen(s))
						return i;
				}
			}
			return -1;
		}
		//在pos位置上插入字符c，并返回该字符的位置
		string& insert(size_t pos, char c)
		{
			//判断容量是否够；
			if (m_size + 1 > m_capacity)
			{
				reserve(2 * m_capacity + 1);
			}
			//插入数据
			for (int i = m_size - 1; i >= pos; --i)
			{
				m_str[i+1] = m_str[i];
			}
			m_str[pos] = c;
			m_size++;
			m_str[m_size] = '\0';
			return *this;
		}
		//在pos位置上插入字符串str，并返回该字符的位置
		string& insert(size_t pos, const char* str)
		{
			int len = strlen(str);
			//判断是否扩容
			while (m_size + len > m_capacity)
			{
				reserve(2 * m_capacity + 1);
			}
			//插入字符串
			for (int i = m_size - 1; i >= pos; --i)
				m_str[i+3] = m_str[i];
			for (int i = 0; i < len; ++i)
			{
				m_str[pos] = str[i];
				pos++;
			}
			m_size += len;
			m_str[m_size] = '\0';
			return *this;
		}
		// 删除pos位置上的元素，并返回该元素的下一个位置
		string& erase(size_t pos)
		{
			for (int i = pos; i < m_size; ++i)
			{
				m_str[i] = m_str[i + 1];
			}
			m_str[--m_size] = '\0';
			return *this;
		}

	public:
		void Swap(string &str)
		{
			swap(m_str, str.m_str);
			swap(m_capacity, str.m_capacity);
			swap(m_size, str.m_size);
		}
	private:
		char* m_str;
		size_t m_capacity;
		size_t m_size;
	};
	ostream& operator<<(ostream& out, const My_string::string& s)
	{
		for (int i = 0; i < s.m_size; ++i)
			out << s.m_str[i];
		return out;
	}
	istream& operator>>(istream& in, My_string::string& s)
	{
		while (1)
		{
			char c;
			c = in.get();
			if (c == '\0' || c == ' ')
				break;
			else
			{
				s.push_back(c);
			}
			return in;
		}
	}
}
void main()
{
	My_string::string s1("hello");
	s1.push_back(' ');
	s1.push_back('b');
	s1 += 't';
	cout << s1 << endl;
	cout << s1.size() << endl;
	cout << s1.capacity() << endl;
	// 利用迭代器打印string中的元素
	My_string::string::iterator it = s1.begin();
	while (it != s1.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	// 这里可以看到一个类只要支持的基本的iterator，就支持范围for
	for (auto ch : s1)
		cout << ch << " ";
	cout << endl;
}