#include<iostream>
#include<memory>
using namespace std;

struct pd { int i = 123; };
struct pf { pd p; };

//int main() 
//{
//	//初始化
//	shared_ptr<int> p = make_shared<int>(1);
//	cout << p.use_count() << endl;
//	
//	//调用
//	shared_ptr<pf> p2 = make_shared<pf>();
//	cout << p2.use_count() << endl;
//	
//	//等同
//	shared_ptr<pd> p3 = make_shared<pd>();
//	cout << p3.use_count() << endl;
//	shared_ptr<pd> p4(p2, &(p2->p)); //访问类的成员变量
//	cout << p4.use_count() << endl;
//
//	//释放
//	p.reset();
//	return 0;
//}