#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<assert.h>
using namespace std;
//现代做法
class String
{
public:
	String(char* str = "")//注意，此时的str不可以为nullptr，如果str为空
		                                                     //就会被认为程序非法。
	{
		if (str == nullptr)
		{
			str = "";
		}
		m_data = new char[strlen(str) + 1];
		strcpy(m_data, str);
	}
	String(const String& str) :m_data(nullptr)
	{
		String tmp(str.m_data);
		swap(m_data,tmp.m_data);
	}
	String& operator=(const String& str)
	{
		//if (this != &str)
		//{
		//	delete[]m_data;//但是这样会出现函数的危险程序，因为会存在空间内存不够去开辟空间，
		                   //但又由于先释放了m_data中的空间资源，所以会造成双发的内存丢失。
		//	m_data = new char[strlen(str.m_data) + 1];
		//	strcpy(m_data, str.m_data);
		//}
		//return *this;
		if (this != &str)//现代的写法：完美的利用了临时存在变量的优点（所处的生命周期使用完就会自动释放自己的内存空间）。
		{
			/*swap(m_data, str.m_data);//由于传进来的str是const，是不可以修改的，但是通过swap的调用，会修改str的指向，所以编译不通过。
			return *this;*/
			String tmp(str);
			swap(m_data, tmp.m_data);
		}
		return *this;
	}
	~String()
	{
		if (m_data)
		{
			delete[]m_data;
			m_data = nullptr;
		}
	}
private:
	char *m_data;
};

//传统的写法
//class String
//{
//public:
//	String(char* str = "") :m_data(new char[strlen(str) + 1])//注意，此时的str不可以为nullptr，如果str为空
//		                                                     //就会被认为程序非法。
//	{
//		if (str == nullptr)
//		{
//			assert(false);
//			return;
//		}
//		strcpy(m_data, str);
//	}
//	String(const String& str) :m_data(new char[strlen(str.m_data) + 1])
//	{
//		strcpy(m_data, str.m_data);
//	}
//	String& operator=(const String& str)
//	{
//		//if (this != &str)
//		//{
//		//	delete[]m_data;//但是这样会出现函数的危险程序，因为会存在空间内存不够去开辟空间，
//		                   //但又由于先释放了m_data中的空间资源，所以会造成双发的内存丢失。
//		//	m_data = new char[strlen(str.m_data) + 1];
//		//	strcpy(m_data, str.m_data);
//		//}
//		//return *this;
//		if (this != &str)//传统的写法
//		{
//			char* tmp = new char[strlen(str.m_data) + 1];
//			strcpy(tmp, str.m_data);
//			delete[] m_data;
//			m_data = tmp;
//		}
//		return *this;
//	}
//	~String()
//	{
//		if (m_data)
//		{
//			delete[]m_data;
//			m_data = nullptr;
//		}
//	}
//private:
//	char *m_data;
//};
int main()
{
	String s("abc");
	String s1 = s;
	String s2;
	s2 = s1;
	return 0;
}