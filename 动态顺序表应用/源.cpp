#include<iostream>//输入输出流
#include<string>//STL中的字符串容器
#define MAX 1000//标识符常量 方便以后修改
using namespace std;//标准命名空间
class Person//自定义数据类型(顺序表存储的数据类型)
{
public://公共属性
	friend ostream& operator<<(ostream& out, Person& p);//全局函数作友元，因为要输出Person中的私有属性，不能直接访问，所以要作友元
	//因为类外不能直接访问私有属性，我们需要提供一些接口
	string get_m_Name()//对外提供m_Name的接口
	{
		return this->m_Name;//返回成员属性的值
	}
	void setName(string name)//对私有属性（m_Name）进行修改
	{
		this->m_Name = name;
	}
	void setSex(int sex)//对私有属性（m_Sex）进行修改
	{
		this->m_Sex = sex;
	}
	void setAge(int age)//对私有属性（m_Age）进行修改
	{
		this->m_Age;
	}
	void setPhone(string phone)//对私有属性（m_Phone）进行修改
	{
		this->m_Phone = phone;
	}
	void setAddr(string addr)//对私有属性（m_Addr）进行修改
	{
		this->m_Addr = addr;
	}
	Person() {}//Person类的无参构造（因为下面写了有参构造，编译器不提供无参，所以自己写一个空实现）
	Person(string name, int sex, int age, string phone, string addr)//有参构造
	{
		this->m_Name = name;
		this->m_Sex = sex;
		this->m_Age = age;
		this->m_Phone = phone;
		this->m_Addr = addr;
	}
private://一般属性设为私有，行为设为公共
	string m_Name;//姓名
	int m_Sex;//性别
	int m_Age;//年龄
	string m_Phone;//电话号码
	string m_Addr;//住址
};
class Sq_List//动态顺序表类
{
public:
	Sq_List()//动态顺序表的无参构造
	{
		this->initList();//创建对象时，自动初始化
	}
	void initList();//初始化
	bool insertElem(int pos, Person p);//插入数据，两个参数分别是前插入的逻辑位置，和要插入的数据，插入成功返回true,失败则返回false
	void printSqList();//打印顺序表所有数据的内容
	bool deleteElem(int n);//删除逻辑位置上的数据，若成功返回true，失败则返回false
	int isExistElem(string name);//根据传入的名字，寻找这个数据是否存在，如果存在返回存储位置的下标，若不存在返回-1，为什么写这个成员函数？因为下面的两个成员函数都需要这个功能
	void findElem();//查找数据
	void modifyElem();//修改数据
	void cleanSqList();//清空数据
private://私有属性
	Person* elem;//因为是动态顺序表，我们只需要把存放数据的数组指针的首地址赋给elem
	int length;//顺序表的长度
};
/*关于静态顺序表该怎么写？
* 静态顺序表的存储大小是固定的，一旦创建就不能改变，而动态顺序表是创建一个虚拟的空间，相比于静态来说，动态比较省空间
* 所以要想静态存储的顺序表，我们只需要创建一个数据就可以了，Person elem[MAX],初始化时，只需要把length=0就可以了
* 我还有另一种方法创建静态顺序表（面向对象）
* 静态存储和动态存储有相似的地方（length，一些成员函数），也有不同的地方（存储方式）
* 我们可以把他们公共的属性或者行为作为基类（父类），不一样的属性和行为作为两个派生类（子类）
* 派生类分别对基类进行公共继承，我们需要什么类型的顺序表，只需把父类的指针或引用指向子类对象，触发多态
* 这样的好处是：根据需要建立对象
*/
ostream& operator<<(ostream& out, Person& p)//<<运算符重载 输出流是ostream类型的，参数要引用，函数的返回也要返回引用，否则不可以链式
{
	out << "姓名：" << p.m_Name << "\t" //打印内容
		<< "性别：" << (p.m_Sex == 1 ? "男" : "女") << "\t"//三目运算符，如果sex==1就输出"男",否则输出"女"
		<< "年龄：" << p.m_Age << "\t"
		<< "电话号：" << p.m_Phone << "\t"
		<< "地址： " << p.m_Addr << "\t";
	return out;//返回值
}
void Sq_List::initList()//初始化顺序表
{
	this->elem = new Person[MAX];//在堆区创建一个数字指针，并把首地址返回给顺序表的elem
	this->length = 0;//设长度为0
}
bool Sq_List::insertElem(int pos, Person p)//类内定义，类外实现，要加上作用域
{
	if (this->length >= MAX)//判断还能不能插入，如果长度超出最大长度，直接退出
	{
		cout << "存储已超出最大范围" << endl;
		return false;
	}
	if (pos < 1 || pos>this->length + 1)//判断插入的位置是否合理
	{
		cout << "插入的数据不合理" << endl;
		return false;
	}
	for (int i = this->length - 1; i >= pos - 1; i--)//我们需要把要插入的数据的后面数据全部后移，一定是从后往前一个一个的覆盖
	{
		elem[i + 1] = elem[i];
	}
	this->elem[pos - 1] = p;//数据移完之后，该位置就可以插入了，存储位置=逻辑位置-1
	this->length++;//插入一个数据后顺序表长度+1
	return true;//
}
bool Sq_List::deleteElem(int i)
{
	if (i<1 || i>this->length)//判断要删除的数据是否合理
	{
		cout << "数据不合理！无法删除" << endl;
		return false;
	}
	for (int j = i; j <= this->length - 1; j++)//我们只要删除的数据的后一个数据，不断往前覆盖，理论上最后一个数据没有变动，但是length--之后，就访问不到最后一个了
	{
		this->elem[j - 1] = this->elem[j];//覆盖操作
	}
	this->length--;
	return true;//成功返回
}
void Sq_List::printSqList()//打印所有数据
{
	if (this->length == 0)//没有数据，直接退出
	{
		cout << "通讯录为空！" << endl;
		return;
	}
	for (int i = 0; i < this->length; i++)//不断打印数组中的数据
	{
		cout << this->elem[i] << endl;
	}
}
int  Sq_List::isExistElem(string name)//根据名字寻找数据
{
	for (int i = 0; i < this->length; i++)//遍历所有数据，并进行对比
	{
		if (name == this->elem[i].get_m_Name())//对比成功
		{
			return i;//返回该数据的逻辑位置
		}
	}
	return -1;//全遍历一次，还是没有找到，返回-1
}
void Sq_List::findElem()//查找数据
{
	cout << "你想查找哪个联系人？请输入名字：" << endl;
	string name;
	cin >> name;
	int pos = this->isExistElem(name);//上面那个函数，找到返回存储位置
	if (pos == -1)
	{
		cout << "查无此人" << endl;
	}
	else
	{
		cout << "找到了：" << endl;
		cout << this->elem[pos] << "   逻辑位置：" << pos + 1 << endl;//因为重载"<<"了，直接输出就行了
	}
}
void Sq_List::modifyElem()//修改数据
{
	cout << "你想修改谁的数据？请输入该联系人的名字：" << endl;
	string name;
	cin >> name;
	int pos = this->isExistElem(name);//是否存在此人
	if (pos == -1)
	{
		cout << "查无此人！" << endl;
		return;
	}
	cout << "请输入你要修改的内容：" << endl
		<< "1---姓名" << endl
		<< "2---性别" << endl
		<< "3---年龄" << endl
		<< "4---电话" << endl
		<< "5---住址" << endl;
	int select;
	while (true)//为什么要死循环？要让用户输入有效的选择（1,2,3,4,5）输入其他的数字，就会一直选择，直到选择正确为主
	{
		cin >> select;
		if (select == 1)
		{
			cout << "请输入新姓名：" << endl;
			string name;
			cin >> name;
			this->elem[pos].setName(name);//因为成员属性是私有的，要利用Person类的接口对数据进行修改
			break;
		}
		else if (select == 2)
		{
			cout << "请输入新性别：" << endl;
			int sex;
			while (true)//死循环，用户必须选择正确才能退出
			{
				cin >> sex;
				if (sex == 1 || sex == 2)
				{
					this->elem[pos].setSex(sex);//接口
					break;
				}
				cout << "输入有误!请重新输入" << endl;
			}
			break;
		}
		else if (select == 3)
		{
			cout << "请输入新年龄：" << endl;
			int age;
			cin >> age;
			this->elem[pos].setAge(age);//接口
			break;
		}
		else if (select == 4)
		{
			cout << "请输入新电话号码：" << endl;
			string phone;
			cin >> phone;
			this->elem[pos].setPhone(phone);//接口
			break;
		}
		else if (select == 5)
		{
			cout << "请输入新地址：" << endl;
			string addr;
			cin >> addr;
			this->elem[pos].setAddr(addr);//接口
			break;
		}
		cout << "输入有误，请重新输入！" << endl;
	}
	cout << "修改成功！" << endl;
}
void Sq_List::cleanSqList()
{
	cout << "你确定要清空通讯录吗？" << endl;
	cout << "1-----确定" << endl
		<< "2-----返回" << endl;
	int ret;
	while (true)//死循环，正确选择可退出
	{
		cin >> ret;
		if (ret == 1 || ret == 2)
		{
			if (ret == 1)
			{
				this->initList();//清空的操作直接调用初始化
				cout << "清空成功！" << endl;
			}
			return;
		}
		cout << "输入有误！请重新输入" << endl;
	}
}
void showMenu()//菜单，提示用户操作
{
	cout << "*************************" << endl;
	cout << "***** 1、添加联系人 *****" << endl;
	cout << "***** 2、显示联系人 *****" << endl;
	cout << "***** 3、删除联系人 *****" << endl;
	cout << "***** 4、查找联系人 *****" << endl;
	cout << "***** 5、修改联系人 *****" << endl;
	cout << "***** 6、清空联系人 *****" << endl;
	cout << "***** 0、退出通讯录 *****" << endl;
	cout << "*************************" << endl;
	cout << "请输入你的选项：";
}
int main()//主函数，程序入口
{
	Sq_List L;//创建动态顺序表的对象实例
	while (true)//死循环，做出正确操作可退出
	{
		showMenu();//显示菜单
		int select = 0;
		cin >> select;//输入选择
		switch (select)
		{
		case 1://添加联系人
		{
			string name, phone, addr;//用来存储用户的信息
			int sex, age, pos;//同上，pos是要插入数据的逻辑位置
			cout << "请输入联系人的姓名：" << endl;
			cin >> name;
			cout << "请输入联系人的性别：" << endl;
			cout << "1-----男" << endl
				<< "2-----女" << endl;
			while (true)//死循环，做出正确选择退出
			{
				cin >> sex;
				if (sex == 1 || sex == 2)
				{
					break;
				}
				cout << "输入有误，请重新" << endl;
			}
			cout << "请输入联系人的年龄：" << endl;
			cin >> age;
			cout << "请输入联系人的电话号码：" << endl;
			cin >> phone;
			cout << "请输入联系人的地址：" << endl;
			cin >> addr;
			Person p(name, sex, age, phone, addr);
			cout << "你想添加到第几个数据的前面：" << endl;
			while (true)
			{
				cin >> pos;
				if (L.insertElem(pos, p))//调用类的成员函数
				{
					break;
				}
				cout << "请重新插入！" << endl;
			}
			cout << "添加成功！" << endl;
			system("pause");//按任意键继续，停顿操作
			system("cls");//清屏
		}
		break;
		case 2://显示联系人
			L.printSqList();
			system("pause");
			system("cls");
			break;
		case 3://删除联系人
		{
			cout << "你想删除哪个位置上的数据：" << endl;
			int pos;
			cin >> pos;
			if (L.deleteElem(pos))//判断是否删除成功
			{
				cout << "删除成功！" << endl;
			}
			system("pause");
			system("cls");
		}
		break;
		case 4://查找联系人
			L.findElem();//调用类的成员函数
			system("pause");
			system("cls");
			break;
		case 5://修改联系人
			L.modifyElem();//调用类的成员函数
			system("pause");
			system("cls");
			break;
		case 6://清空联系人
			L.cleanSqList();//调用类的成员函数
			system("pause");
			system("cls");
			break;
		default://退出
			cout << "欢迎下次使用!" << endl;
			system("pause");
			return 0;
			break;
		}
	}
}
