#include<iostream>//���������
#include<string>//STL�е��ַ�������
#define MAX 1000//��ʶ������ �����Ժ��޸�
using namespace std;//��׼�����ռ�
class Person//�Զ�����������(˳���洢����������)
{
public://��������
	friend ostream& operator<<(ostream& out, Person& p);//ȫ�ֺ�������Ԫ����ΪҪ���Person�е�˽�����ԣ�����ֱ�ӷ��ʣ�����Ҫ����Ԫ
	//��Ϊ���ⲻ��ֱ�ӷ���˽�����ԣ�������Ҫ�ṩһЩ�ӿ�
	string get_m_Name()//�����ṩm_Name�Ľӿ�
	{
		return this->m_Name;//���س�Ա���Ե�ֵ
	}
	void setName(string name)//��˽�����ԣ�m_Name�������޸�
	{
		this->m_Name = name;
	}
	void setSex(int sex)//��˽�����ԣ�m_Sex�������޸�
	{
		this->m_Sex = sex;
	}
	void setAge(int age)//��˽�����ԣ�m_Age�������޸�
	{
		this->m_Age;
	}
	void setPhone(string phone)//��˽�����ԣ�m_Phone�������޸�
	{
		this->m_Phone = phone;
	}
	void setAddr(string addr)//��˽�����ԣ�m_Addr�������޸�
	{
		this->m_Addr = addr;
	}
	Person() {}//Person����޲ι��죨��Ϊ����д���вι��죬���������ṩ�޲Σ������Լ�дһ����ʵ�֣�
	Person(string name, int sex, int age, string phone, string addr)//�вι���
	{
		this->m_Name = name;
		this->m_Sex = sex;
		this->m_Age = age;
		this->m_Phone = phone;
		this->m_Addr = addr;
	}
private://һ��������Ϊ˽�У���Ϊ��Ϊ����
	string m_Name;//����
	int m_Sex;//�Ա�
	int m_Age;//����
	string m_Phone;//�绰����
	string m_Addr;//סַ
};
class Sq_List//��̬˳�����
{
public:
	Sq_List()//��̬˳�����޲ι���
	{
		this->initList();//��������ʱ���Զ���ʼ��
	}
	void initList();//��ʼ��
	bool insertElem(int pos, Person p);//�������ݣ����������ֱ���ǰ������߼�λ�ã���Ҫ��������ݣ�����ɹ�����true,ʧ���򷵻�false
	void printSqList();//��ӡ˳����������ݵ�����
	bool deleteElem(int n);//ɾ���߼�λ���ϵ����ݣ����ɹ�����true��ʧ���򷵻�false
	int isExistElem(string name);//���ݴ�������֣�Ѱ����������Ƿ���ڣ�������ڷ��ش洢λ�õ��±꣬�������ڷ���-1��Ϊʲôд�����Ա��������Ϊ�����������Ա��������Ҫ�������
	void findElem();//��������
	void modifyElem();//�޸�����
	void cleanSqList();//�������
private://˽������
	Person* elem;//��Ϊ�Ƕ�̬˳�������ֻ��Ҫ�Ѵ�����ݵ�����ָ����׵�ַ����elem
	int length;//˳���ĳ���
};
/*���ھ�̬˳������ôд��
* ��̬˳���Ĵ洢��С�ǹ̶��ģ�һ�������Ͳ��ܸı䣬����̬˳����Ǵ���һ������Ŀռ䣬����ھ�̬��˵����̬�Ƚ�ʡ�ռ�
* ����Ҫ�뾲̬�洢��˳�������ֻ��Ҫ����һ�����ݾͿ����ˣ�Person elem[MAX],��ʼ��ʱ��ֻ��Ҫ��length=0�Ϳ�����
* �һ�����һ�ַ���������̬˳����������
* ��̬�洢�Ͷ�̬�洢�����Ƶĵط���length��һЩ��Ա��������Ҳ�в�ͬ�ĵط����洢��ʽ��
* ���ǿ��԰����ǹ��������Ի�����Ϊ��Ϊ���ࣨ���ࣩ����һ�������Ժ���Ϊ��Ϊ���������ࣨ���ࣩ
* ������ֱ�Ի�����й����̳У�������Ҫʲô���͵�˳���ֻ��Ѹ����ָ�������ָ��������󣬴�����̬
* �����ĺô��ǣ�������Ҫ��������
*/
ostream& operator<<(ostream& out, Person& p)//<<��������� �������ostream���͵ģ�����Ҫ���ã������ķ���ҲҪ�������ã����򲻿�����ʽ
{
	out << "������" << p.m_Name << "\t" //��ӡ����
		<< "�Ա�" << (p.m_Sex == 1 ? "��" : "Ů") << "\t"//��Ŀ����������sex==1�����"��",�������"Ů"
		<< "���䣺" << p.m_Age << "\t"
		<< "�绰�ţ�" << p.m_Phone << "\t"
		<< "��ַ�� " << p.m_Addr << "\t";
	return out;//����ֵ
}
void Sq_List::initList()//��ʼ��˳���
{
	this->elem = new Person[MAX];//�ڶ�������һ������ָ�룬�����׵�ַ���ظ�˳����elem
	this->length = 0;//�賤��Ϊ0
}
bool Sq_List::insertElem(int pos, Person p)//���ڶ��壬����ʵ�֣�Ҫ����������
{
	if (this->length >= MAX)//�жϻ��ܲ��ܲ��룬������ȳ�����󳤶ȣ�ֱ���˳�
	{
		cout << "�洢�ѳ������Χ" << endl;
		return false;
	}
	if (pos < 1 || pos>this->length + 1)//�жϲ����λ���Ƿ����
	{
		cout << "��������ݲ�����" << endl;
		return false;
	}
	for (int i = this->length - 1; i >= pos - 1; i--)//������Ҫ��Ҫ��������ݵĺ�������ȫ�����ƣ�һ���ǴӺ���ǰһ��һ���ĸ���
	{
		elem[i + 1] = elem[i];
	}
	this->elem[pos - 1] = p;//��������֮�󣬸�λ�þͿ��Բ����ˣ��洢λ��=�߼�λ��-1
	this->length++;//����һ�����ݺ�˳�����+1
	return true;//
}
bool Sq_List::deleteElem(int i)
{
	if (i<1 || i>this->length)//�ж�Ҫɾ���������Ƿ����
	{
		cout << "���ݲ������޷�ɾ��" << endl;
		return false;
	}
	for (int j = i; j <= this->length - 1; j++)//����ֻҪɾ�������ݵĺ�һ�����ݣ�������ǰ���ǣ����������һ������û�б䶯������length--֮�󣬾ͷ��ʲ������һ����
	{
		this->elem[j - 1] = this->elem[j];//���ǲ���
	}
	this->length--;
	return true;//�ɹ�����
}
void Sq_List::printSqList()//��ӡ��������
{
	if (this->length == 0)//û�����ݣ�ֱ���˳�
	{
		cout << "ͨѶ¼Ϊ�գ�" << endl;
		return;
	}
	for (int i = 0; i < this->length; i++)//���ϴ�ӡ�����е�����
	{
		cout << this->elem[i] << endl;
	}
}
int  Sq_List::isExistElem(string name)//��������Ѱ������
{
	for (int i = 0; i < this->length; i++)//�����������ݣ������жԱ�
	{
		if (name == this->elem[i].get_m_Name())//�Աȳɹ�
		{
			return i;//���ظ����ݵ��߼�λ��
		}
	}
	return -1;//ȫ����һ�Σ�����û���ҵ�������-1
}
void Sq_List::findElem()//��������
{
	cout << "��������ĸ���ϵ�ˣ����������֣�" << endl;
	string name;
	cin >> name;
	int pos = this->isExistElem(name);//�����Ǹ��������ҵ����ش洢λ��
	if (pos == -1)
	{
		cout << "���޴���" << endl;
	}
	else
	{
		cout << "�ҵ��ˣ�" << endl;
		cout << this->elem[pos] << "   �߼�λ�ã�" << pos + 1 << endl;//��Ϊ����"<<"�ˣ�ֱ�����������
	}
}
void Sq_List::modifyElem()//�޸�����
{
	cout << "�����޸�˭�����ݣ����������ϵ�˵����֣�" << endl;
	string name;
	cin >> name;
	int pos = this->isExistElem(name);//�Ƿ���ڴ���
	if (pos == -1)
	{
		cout << "���޴��ˣ�" << endl;
		return;
	}
	cout << "��������Ҫ�޸ĵ����ݣ�" << endl
		<< "1---����" << endl
		<< "2---�Ա�" << endl
		<< "3---����" << endl
		<< "4---�绰" << endl
		<< "5---סַ" << endl;
	int select;
	while (true)//ΪʲôҪ��ѭ����Ҫ���û�������Ч��ѡ��1,2,3,4,5���������������֣��ͻ�һֱѡ��ֱ��ѡ����ȷΪ��
	{
		cin >> select;
		if (select == 1)
		{
			cout << "��������������" << endl;
			string name;
			cin >> name;
			this->elem[pos].setName(name);//��Ϊ��Ա������˽�еģ�Ҫ����Person��Ľӿڶ����ݽ����޸�
			break;
		}
		else if (select == 2)
		{
			cout << "���������Ա�" << endl;
			int sex;
			while (true)//��ѭ�����û�����ѡ����ȷ�����˳�
			{
				cin >> sex;
				if (sex == 1 || sex == 2)
				{
					this->elem[pos].setSex(sex);//�ӿ�
					break;
				}
				cout << "��������!����������" << endl;
			}
			break;
		}
		else if (select == 3)
		{
			cout << "�����������䣺" << endl;
			int age;
			cin >> age;
			this->elem[pos].setAge(age);//�ӿ�
			break;
		}
		else if (select == 4)
		{
			cout << "�������µ绰���룺" << endl;
			string phone;
			cin >> phone;
			this->elem[pos].setPhone(phone);//�ӿ�
			break;
		}
		else if (select == 5)
		{
			cout << "�������µ�ַ��" << endl;
			string addr;
			cin >> addr;
			this->elem[pos].setAddr(addr);//�ӿ�
			break;
		}
		cout << "�����������������룡" << endl;
	}
	cout << "�޸ĳɹ���" << endl;
}
void Sq_List::cleanSqList()
{
	cout << "��ȷ��Ҫ���ͨѶ¼��" << endl;
	cout << "1-----ȷ��" << endl
		<< "2-----����" << endl;
	int ret;
	while (true)//��ѭ������ȷѡ����˳�
	{
		cin >> ret;
		if (ret == 1 || ret == 2)
		{
			if (ret == 1)
			{
				this->initList();//��յĲ���ֱ�ӵ��ó�ʼ��
				cout << "��ճɹ���" << endl;
			}
			return;
		}
		cout << "������������������" << endl;
	}
}
void showMenu()//�˵�����ʾ�û�����
{
	cout << "*************************" << endl;
	cout << "***** 1�������ϵ�� *****" << endl;
	cout << "***** 2����ʾ��ϵ�� *****" << endl;
	cout << "***** 3��ɾ����ϵ�� *****" << endl;
	cout << "***** 4��������ϵ�� *****" << endl;
	cout << "***** 5���޸���ϵ�� *****" << endl;
	cout << "***** 6�������ϵ�� *****" << endl;
	cout << "***** 0���˳�ͨѶ¼ *****" << endl;
	cout << "*************************" << endl;
	cout << "���������ѡ�";
}
int main()//���������������
{
	Sq_List L;//������̬˳���Ķ���ʵ��
	while (true)//��ѭ����������ȷ�������˳�
	{
		showMenu();//��ʾ�˵�
		int select = 0;
		cin >> select;//����ѡ��
		switch (select)
		{
		case 1://�����ϵ��
		{
			string name, phone, addr;//�����洢�û�����Ϣ
			int sex, age, pos;//ͬ�ϣ�pos��Ҫ�������ݵ��߼�λ��
			cout << "��������ϵ�˵�������" << endl;
			cin >> name;
			cout << "��������ϵ�˵��Ա�" << endl;
			cout << "1-----��" << endl
				<< "2-----Ů" << endl;
			while (true)//��ѭ����������ȷѡ���˳�
			{
				cin >> sex;
				if (sex == 1 || sex == 2)
				{
					break;
				}
				cout << "��������������" << endl;
			}
			cout << "��������ϵ�˵����䣺" << endl;
			cin >> age;
			cout << "��������ϵ�˵ĵ绰���룺" << endl;
			cin >> phone;
			cout << "��������ϵ�˵ĵ�ַ��" << endl;
			cin >> addr;
			Person p(name, sex, age, phone, addr);
			cout << "������ӵ��ڼ������ݵ�ǰ�棺" << endl;
			while (true)
			{
				cin >> pos;
				if (L.insertElem(pos, p))//������ĳ�Ա����
				{
					break;
				}
				cout << "�����²��룡" << endl;
			}
			cout << "��ӳɹ���" << endl;
			system("pause");//�������������ͣ�ٲ���
			system("cls");//����
		}
		break;
		case 2://��ʾ��ϵ��
			L.printSqList();
			system("pause");
			system("cls");
			break;
		case 3://ɾ����ϵ��
		{
			cout << "����ɾ���ĸ�λ���ϵ����ݣ�" << endl;
			int pos;
			cin >> pos;
			if (L.deleteElem(pos))//�ж��Ƿ�ɾ���ɹ�
			{
				cout << "ɾ���ɹ���" << endl;
			}
			system("pause");
			system("cls");
		}
		break;
		case 4://������ϵ��
			L.findElem();//������ĳ�Ա����
			system("pause");
			system("cls");
			break;
		case 5://�޸���ϵ��
			L.modifyElem();//������ĳ�Ա����
			system("pause");
			system("cls");
			break;
		case 6://�����ϵ��
			L.cleanSqList();//������ĳ�Ա����
			system("pause");
			system("cls");
			break;
		default://�˳�
			cout << "��ӭ�´�ʹ��!" << endl;
			system("pause");
			return 0;
			break;
		}
	}
}
