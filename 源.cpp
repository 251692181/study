#include"resource.h"
#include<windows.h>
#include<stdio.h>

double GetDlgItemDouble(HWND hwnd,UINT nID){
	char s[256];
	GetDlgItemText(hwnd, nID, s, sizeof(s));
	return atof(s);
}
void SetGetDlgItemDouble(HWND hwnd, UINT nID,double num) {
	char s[256];
	sprintf_s(s, "%lf", num);
	SetDlgItemText(hwnd, nID, s);
	
}

   //窗口居中
void OnInitDialog(HWND hwndDlg) {

	RECT rect;
	GetWindowRect(hwndDlg, &rect);//得到显示器大小
	int cx = GetSystemMetrics(SM_CXFULLSCREEN);
    int cy= GetSystemMetrics(SM_CYFULLSCREEN);
	
	int x = (cx - rect.right) / 2;
	int y = (cy - rect.bottom) / 2;
	//屏幕居中
	MoveWindow(hwndDlg, x, y, rect.right, rect.bottom, FALSE);
}

void OnCal(HWND hwndDlg) {

	double x = GetDlgItemDouble(hwndDlg, IDC_L1);
	double y = GetDlgItemDouble(hwndDlg, IDC_R1);
	SetGetDlgItemDouble(hwndDlg, IDC_RE, x + y);

	x = GetDlgItemDouble(hwndDlg, IDC_L2);
	y = GetDlgItemDouble(hwndDlg, IDC_R2);
	SetGetDlgItemDouble(hwndDlg, IDC_RE2, x - y);

	x = GetDlgItemDouble(hwndDlg, IDC_L3);
	y = GetDlgItemDouble(hwndDlg, IDC_R3);
	SetGetDlgItemDouble(hwndDlg, IDC_RE3, x * y);

	x = GetDlgItemDouble(hwndDlg, IDC_L4);
	y = GetDlgItemDouble(hwndDlg, IDC_R4);
	if (x != 0)
		SetGetDlgItemDouble(hwndDlg, IDC_RE4, x / y);
	else
		SetDlgItemText(hwndDlg, IDC_RE4, "除数不能为0");

	/*
	double x = GetDlgItemInt(hwndDlg, IDC_L1, NULL, TRUE);
	double y = GetDlgItemInt(hwndDlg, IDC_R1, NULL, TRUE);
	SetDlgItemInt(hwndDlg, IDC_RE, x + y, TRUE);

	x = GetDlgItemInt(hwndDlg, IDC_L2, NULL, TRUE);
	y = GetDlgItemInt(hwndDlg, IDC_R2, NULL, TRUE);
	SetDlgItemInt(hwndDlg, IDC_RE2, x - y, TRUE);

	x = GetDlgItemInt(hwndDlg, IDC_L3, NULL, TRUE);
	y = GetDlgItemInt(hwndDlg, IDC_R3, NULL, TRUE);
	SetDlgItemInt(hwndDlg, IDC_RE3, x * y, TRUE);

	x = GetDlgItemInt(hwndDlg, IDC_L4, NULL, TRUE);
	y = GetDlgItemInt(hwndDlg, IDC_R4, NULL, TRUE);
	if (x!=0)
	SetDlgItemInt(hwndDlg, IDC_RE4, x / y, TRUE);
	else
	SetDlgItemText(hwndDlg, IDC_RE4, "除数不能为0");

	SetDlgItemInt(hwndDlg, IDC_RE4, x / y, TRUE);*/

}


INT_PTR CALLBACK pro(HWND hwndDlg,UINT uMsg, WPARAM wParam, LPARAM lParam)
{	
	switch (uMsg) {

	case WM_INITDIALOG:
		OnInitDialog(hwndDlg);
		
		return TRUE;	

	case WM_COMMAND://命令消息
		if (LOWORD(wParam) == IDOK)
		{
			OnCal(hwndDlg);
			return TRUE;
		}

		if (LOWORD(wParam)==IDCANCEL)
		{
			EndDialog(hwndDlg, IDCANCEL);
		}
		break;

		
	}
	return 0;
}




void Onlogin(HWND hWndDlg) {
	//登录界面
	char name[32], PWD[32];
	GetDlgItemText(hWndDlg, IDC_user, name, sizeof(name));
	GetDlgItemText(hWndDlg, IDC_PWD, PWD, sizeof(PWD));
	if (strcmp(name,"hacker")||strcmp(PWD,"123456"))
	{
		MessageBox(hWndDlg, "用户名或者密码错误！请重新输入", "错误",MB_OK);
		return ;
	}
	EndDialog(hWndDlg, IDOK);

}

INT_PTR CALLBACK logPro(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg)
	{
	case WM_INITDIALOG:
		OnInitDialog(hwndDlg);
		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam)==IDCANCEL)
		{
			EndDialog(hwndDlg, IDCANCEL);  //退出程序
			return TRUE;
		}
		if (LOWORD(wParam) == IDOK)
		{
			Onlogin(hwndDlg);   // goto 登录界面
			return TRUE;
		}
	
	}


	return FALSE;
}


int APIENTRY  WinMain(HINSTANCE hInstance,HINSTANCE hPrev,LPSTR lpCmd,int nCmadShow) {

	if (DialogBox(hInstance, (LPCTSTR)IDD_LOGIN, NULL, logPro)==IDCANCEL)
		return 0;
	DialogBox(hInstance, (LPCTSTR)ID_MAIN, NULL, pro);



/*
	HWND hk = FindWindow(NULL,"666.txt - 画图" );
	MessageBox(hk, "只狼：DLC苇名城的大鸡鸡", "温馨提示", MB_OKCANCEL | MB_ICONEXCLAMATION);

	*/

	return 0;
}