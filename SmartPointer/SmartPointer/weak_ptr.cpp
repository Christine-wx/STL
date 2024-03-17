#include<iostream>
#include<memory>
using namespace std;

//weak_ptr:用于解决share_ptr循环引用计数问题
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

	//循环引用计数
	p1->catName = p2;
	p2->animalType = p1;

	//解决方法：
	//将任意一个shared_ptr换为weak_ptr;

	return 0;
}