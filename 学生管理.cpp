#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

struct sClass {

	int nUmber;
	string name;
	float vale;
}SBClass[10];

int login() {
	    string user;
		string psd;
	puts("�������˺�");
	getline(cin, user);
	puts("����������");
	getline(cin, psd);

	if (user=="anatagasuki"&&psd=="abc123")
		return 0;
	else {
		return 1;
	}
}



void menu() {
	puts("1.���ѧ����Ϣ");
	puts("2.���ѧ����Ϣ");
	puts("3.ɾ��ѧ����Ϣ");
	puts("4.�޸�ѧ����Ϣ");
	puts("5.����ѧ����Ϣ");
	puts("0.�˳�---");
	
}


void save() {

	FILE * pf = fopen("student.fp", "w");
	int i = 0;
	if (!pf)
	{
		puts("��������ʧ��");
		return ;
	}
	while (SBClass[i].nUmber)
	{
		if (-1 != SBClass[i].nUmber)
			fwrite(&SBClass[i], 1, sizeof(sClass), pf);
		i++;	
	}
	fclose(pf);
}

void Read() {
	FILE * pf = fopen("student.fp", "r");
	if (!pf)
	{
		puts("��ȡ����ʧ��");
		return;
	}
	int i = 0;
	while (fread(&SBClass[i], 1, sizeof(sClass), pf) > 0) i++;

	fclose(pf);

}
void see() {

	int i = 0;
	while (SBClass[i].nUmber)
	{
		if(SBClass[i].nUmber>0)
		cout << "ѧ�ţ�" << SBClass[i].nUmber << "  ������" << SBClass[i].name << "   �ɼ���" << SBClass[i].vale << endl;
		i++;

	}
	cout << "һ����" << i << "������" << endl;
	
	system("pause");

}

void add(){
	int i = 0;
	char c=0;
	while (1)
	{
		while (SBClass[i].nUmber>0)i++;
		while (true)
		{
			puts("������ѧ�ţ�");
			cin >> SBClass[i].nUmber;
			cin.get();
			puts("������������");
			getline(cin, SBClass[i].name);
			puts("������ɼ���");
			cin >> SBClass[i].vale;
			cin.get();
			cout << "�����ѧ���ǣ�" << SBClass[i].nUmber << "   ����������ǣ�" << SBClass[i].name << "   ����ĳɼ��ǣ�" << SBClass[i].vale << endl;
			if (cin.fail())
			{
				cout << "����������\a" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				continue;
			}
			break;
		}
		save();
		puts("�Ƿ����....Y/N");
		while (1) {
			cin >> c;
			cin.get();
			if (c == 'n' || c == 'N' || c == 'y' || c == 'Y') {
				system("cls");
				break;
			}
			else {
				cout << "����������\a" << endl;
				cin.clear();
				cin.ignore(100, '\n');
			}
		
		}
		if (c == 'n' || c == 'N')break;
	}
}

void delt(){
	see();
	int num;
	char c;
	while (true)
	{
		puts("����Ҫɾ����ѧ�ţ�");
		cin >> num;
		int i = 0;
		while (SBClass[i].nUmber != num)i++;
		SBClass[i].nUmber = -1;
		save();
		while (1) {
			puts("�Ƿ����....Y/N");
			cin >> c;
			cin.get();
			if (c == 'n' || c == 'N' || c == 'y' || c == 'Y') {
				break;
			}
			else {
				cout << "����������\a" << endl;
				cin.clear();
				cin.ignore(100, '\n');
			}
		}
		if (c == 'n' || c == 'N')break;
	}
}

void change(){
	int num=0;
	char c=1;
	int x;
	see();
		puts("����Ҫ�޸ĵ�ѧ�ţ�");
		cin >> num;
		cin.get();
		int i = 0;
		while (SBClass[i].nUmber != num)i++;
		while (c)
		{
			puts("��ѡ���޸ĵĹ���:");
			puts("1.�޸�ѧ��---");
			puts("2.�޸�����---");
			puts("3.�޸ĳɼ�---");
			puts("0.�������˵�--");
			cin >> x;
			cin.get();
			switch (x)
			{
			case 1:
				puts("������Ҫ�޸ĵ�ѧ�ţ�");
				cin >> SBClass[i].nUmber;
			//	SBClass[i].nUmber = nUmber;
				cin.get();
				break;
			case 2:
				puts("������Ҫ�޸ĵ�������");
				getline(cin, SBClass[i].name);
			//	SBClass[i].name = name;
				break;
			case 3:
				puts("������Ҫ�޸ĵĳɼ���");
				cin >> SBClass[i].vale;
			//	SBClass[i].vale = vale;
				cin.get();
				break;
			case 0:
				c = 0;
				break;
			default:
				puts("���������룡����");
				break;
			}

		}
		save();
			cout << "ѧ���ǣ�" << SBClass[i].nUmber << "   �����ǣ�" << SBClass[i].name << "   �ɼ��ǣ�" << SBClass[i].vale << endl;
			system("pause");
}

void fid() {

	int i = 0;
	int num = 0;
	puts("����Ҫ���ҵ�ѧ�ţ�");
	while (1) {
		cin >> num;
		if (cin.fail())
		{
			cout << "����������\a" << endl;
			cin.clear();
			cin.ignore(100, '\n');
			continue;
		}
		break;
	}
		while (SBClass[i].nUmber != num)i++;
		cout << "ѧ���ǣ�" << SBClass[i].nUmber << "   �����ǣ�" << SBClass[i].name << "   �ɼ��ǣ�" << SBClass[i].vale << endl;

		system("pause");


}


int main() {
	Read();
	/*while (login()) {
		system("cls");
		cout << "�˺Ż�������������������룡" << endl;
	}
*/

	while (true)
	{
		system("cls");
		menu();
		int x = 0;
		cout << "��ѡ��";
		cin >> x;

		switch (x)
		{
		case 1:
			see();
			break;
		case 2:
			add();
			break;
		case 3:
			system("cls");
			delt();
			break;
		case 4:
			change();
			break;
		case 5:
			fid();
			break;
		case 0:
			return 0;
		default:
			puts("����������");
			break;
		}	
	}


	system("pause");
	return 0;
}