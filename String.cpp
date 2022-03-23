#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<assert.h>
using namespace std;
//�ִ�����
class String
{
public:
	String(char* str = "")//ע�⣬��ʱ��str������Ϊnullptr�����strΪ��
		                                                     //�ͻᱻ��Ϊ����Ƿ���
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
		//	delete[]m_data;//������������ֺ�����Σ�ճ�����Ϊ����ڿռ��ڴ治��ȥ���ٿռ䣬
		                   //�����������ͷ���m_data�еĿռ���Դ�����Ի����˫�����ڴ涪ʧ��
		//	m_data = new char[strlen(str.m_data) + 1];
		//	strcpy(m_data, str.m_data);
		//}
		//return *this;
		if (this != &str)//�ִ���д������������������ʱ���ڱ������ŵ㣨��������������ʹ����ͻ��Զ��ͷ��Լ����ڴ�ռ䣩��
		{
			/*swap(m_data, str.m_data);//���ڴ�������str��const���ǲ������޸ĵģ�����ͨ��swap�ĵ��ã����޸�str��ָ�����Ա��벻ͨ����
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

//��ͳ��д��
//class String
//{
//public:
//	String(char* str = "") :m_data(new char[strlen(str) + 1])//ע�⣬��ʱ��str������Ϊnullptr�����strΪ��
//		                                                     //�ͻᱻ��Ϊ����Ƿ���
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
//		//	delete[]m_data;//������������ֺ�����Σ�ճ�����Ϊ����ڿռ��ڴ治��ȥ���ٿռ䣬
//		                   //�����������ͷ���m_data�еĿռ���Դ�����Ի����˫�����ڴ涪ʧ��
//		//	m_data = new char[strlen(str.m_data) + 1];
//		//	strcpy(m_data, str.m_data);
//		//}
//		//return *this;
//		if (this != &str)//��ͳ��д��
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