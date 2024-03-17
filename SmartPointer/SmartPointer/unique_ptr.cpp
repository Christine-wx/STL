#include<iostream>
#include<memory>

using namespace std;

void func(int& val) 
{
	std::cout << "use func!" << std::endl;
}
void func1(int* val) 
{
	std::cout << "use func1!" << std::endl;
}

//int main() 
//{
//	//unique_ptr: 使用示例
//	//初始化
//	std::unique_ptr<int> p1 = make_unique<int>(10); //建议
//	std::unique_ptr<int> p2(new int(5));
//
//	//返回裸指针
//	int* ptr = p1.get();
//
//	//移动复制
//	std::unique_ptr<int> p3 = move(p1);
//	std::unique_ptr<int> p4(p3.release());
//	//函数调用
//	func(*p4);
//	func1(p4.get());
//
//	//释放p4指向的空间，p4指向p5指向的空间
//	//重置
//	int* p5 = new int();
//	p4.reset(p5);
//	
//	
//	return 0;
//}