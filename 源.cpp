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
	puts("请输入账号");
	getline(cin, user);
	puts("请输入密码");
	getline(cin, psd);

	if (user=="anatagasuki"&&psd=="abc123")
		return 0;
	else {
		return 1;
	}
}



void menu() {
	puts("1.浏览学生信息");
	puts("2.添加学生信息");
	puts("3.删除学生信息");
	puts("4.修改学生信息");
	puts("5.查找学生信息");
	puts("0.退出---");
	
}


void save() {

	FILE * pf = fopen("student.fp", "w");
	int i = 0;
	if (!pf)
	{
		puts("保存数据失败");
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
		puts("读取数据失败");
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
		cout << "学号：" << SBClass[i].nUmber << "  姓名：" << SBClass[i].name << "   成绩：" << SBClass[i].vale << endl;
		i++;

	}
	cout << "一共有" << i << "条数据" << endl;
	
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
			puts("请输入学号：");
			cin >> SBClass[i].nUmber;
			cin.get();
			puts("请输入姓名：");
			getline(cin, SBClass[i].name);
			puts("请输入成绩：");
			cin >> SBClass[i].vale;
			cin.get();
			cout << "输入的学号是：" << SBClass[i].nUmber << "   输入的姓名是：" << SBClass[i].name << "   输入的成绩是：" << SBClass[i].vale << endl;
			if (cin.fail())
			{
				cout << "请重新输入\a" << endl;
				cin.clear();
				cin.ignore(100, '\n');
				continue;
			}
			break;
		}
		save();
		puts("是否继续....Y/N");
		while (1) {
			cin >> c;
			cin.get();
			if (c == 'n' || c == 'N' || c == 'y' || c == 'Y') {
				system("cls");
				break;
			}
			else {
				cout << "请重新输入\a" << endl;
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
		puts("输入要删除的学号：");
		cin >> num;
		int i = 0;
		while (SBClass[i].nUmber != num)i++;
		SBClass[i].nUmber = -1;
		save();
		while (1) {
			puts("是否继续....Y/N");
			cin >> c;
			cin.get();
			if (c == 'n' || c == 'N' || c == 'y' || c == 'Y') {
				break;
			}
			else {
				cout << "请重新输入\a" << endl;
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
		puts("输入要修改的学号：");
		cin >> num;
		cin.get();
		int i = 0;
		while (SBClass[i].nUmber != num)i++;
		while (c)
		{
			puts("请选择修改的功能:");
			puts("1.修改学号---");
			puts("2.修改姓名---");
			puts("3.修改成绩---");
			puts("0.返还主菜单--");
			cin >> x;
			cin.get();
			switch (x)
			{
			case 1:
				puts("请输入要修改的学号：");
				cin >> SBClass[i].nUmber;
			//	SBClass[i].nUmber = nUmber;
				cin.get();
				break;
			case 2:
				puts("请输入要修改的姓名：");
				getline(cin, SBClass[i].name);
			//	SBClass[i].name = name;
				break;
			case 3:
				puts("请输入要修改的成绩：");
				cin >> SBClass[i].vale;
			//	SBClass[i].vale = vale;
				cin.get();
				break;
			case 0:
				c = 0;
				break;
			default:
				puts("请重新输入！！！");
				break;
			}

		}
		save();
			cout << "学号是：" << SBClass[i].nUmber << "   姓名是：" << SBClass[i].name << "   成绩是：" << SBClass[i].vale << endl;
			system("pause");
}

void fid() {

	int i = 0;
	int num = 0;
	puts("输入要查找的学号：");
	while (1) {
		cin >> num;
		if (cin.fail())
		{
			cout << "请重新输入\a" << endl;
			cin.clear();
			cin.ignore(100, '\n');
			continue;
		}
		break;
	}
		while (SBClass[i].nUmber != num)i++;
		cout << "学号是：" << SBClass[i].nUmber << "   姓名是：" << SBClass[i].name << "   成绩是：" << SBClass[i].vale << endl;

		system("pause");


}


int main() {
	Read();
	/*while (login()) {
		system("cls");
		cout << "账号或者密码错误请重新输入！" << endl;
	}
*/

	while (true)
	{
		system("cls");
		menu();
		int x = 0;
		cout << "请选择：";
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
			puts("请重新输入");
			break;
		}	
	}


	system("pause");
	return 0;
}