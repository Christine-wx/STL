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
//	//unique_ptr: ʹ��ʾ��
//	//��ʼ��
//	std::unique_ptr<int> p1 = make_unique<int>(10); //����
//	std::unique_ptr<int> p2(new int(5));
//
//	//������ָ��
//	int* ptr = p1.get();
//
//	//�ƶ�����
//	std::unique_ptr<int> p3 = move(p1);
//	std::unique_ptr<int> p4(p3.release());
//	//��������
//	func(*p4);
//	func1(p4.get());
//
//	//�ͷ�p4ָ��Ŀռ䣬p4ָ��p5ָ��Ŀռ�
//	//����
//	int* p5 = new int();
//	p4.reset(p5);
//	
//	
//	return 0;
//}