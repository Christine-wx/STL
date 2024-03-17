#include<iostream>
#include<memory>
using namespace std;

//weak_ptr:���ڽ��share_ptrѭ�����ü�������
struct cat;
struct animal 
{
public:
	string type;
	shared_ptr<cat> catName;
	~animal() 
	{
		std::cout << "animal id destory!" << std::endl;
	}
};

struct cat 
{
public:
	string name;
	weak_ptr<animal> animalType;
	~cat() 
	{
		std::cout << "cat is destory!" << std::endl;
	}
};


int main() 
{
	auto p1 = make_shared<animal>();
	auto p2 = make_shared<cat>();

	//ѭ�����ü���
	p1->catName = p2;
	p2->animalType = p1;

	//���������
	//������һ��shared_ptr��Ϊweak_ptr;

	return 0;
}