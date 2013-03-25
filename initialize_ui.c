#include "initialize_ui.h"
#include "constant.h"

//////////////////////////////////////////////////////////////////////////

//��ʼ��������
void InitWndUI( HWND hwnd, HINSTANCE hInstance, HWND *hwndBtn, HFONT hFont, LOGFONT lf )
{
	//////////////////////////////////////////////////////////////////////////
	//������ť
	hwndBtn[0] = CreateWindow(
		TEXT("button"), TEXT("��ͣģ��"),
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		290, 20, 80, 40,
		hwnd, (HMENU)ID_BTN_PAUSE, hInstance, NULL
	);
	SendMessage( hwndBtn[0], WM_SETFONT, (WPARAM)hFont, 0 );

	hwndBtn[1] = CreateWindow(
		TEXT("button"), TEXT("���ش���"),
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		290, 100, 80, 40,
		hwnd, (HMENU)ID_BTN_HIDE, hInstance, NULL
	);
	SendMessage( hwndBtn[1], WM_SETFONT, (WPARAM)hFont, 0 );

	hwndBtn[2] = CreateWindow(
		TEXT("button"), TEXT("�˳�ģ��"),
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		290, 180, 80, 40,
		hwnd, (HMENU)ID_BTN_EXIT, hInstance, NULL
	);
	SendMessage( hwndBtn[2], WM_SETFONT, (WPARAM)hFont, 0 );

	//////////////////////////////////////////////////////////////////////////
	//��ѡ��
	hwndBtn[3] = CreateWindow(
		TEXT("button"), TEXT("�����Զ�����"),
		WS_CHILD|WS_VISIBLE|BS_CHECKBOX,
		270, 240, 120, 20,
		hwnd, (HMENU)ID_ID_AUTORUN, hInstance, NULL
	);
	lf.lfWidth = 7;		lf.lfHeight = 16;
	SendMessage( hwndBtn[3], WM_SETFONT, (WPARAM)CreateFontIndirect(&lf), 0 );

	//////////////////////////////////////////////////////////////////////////
	//������
	lf.lfWidth			= 6;
	lf.lfHeight			= 12;
	lf.lfUnderline		= 1;
	hwndBtn[4] = CreateWindow(
		TEXT("syslink"), TEXT(""),
		WS_CHILD|WS_VISIBLE|SS_NOTIFY,
		10, 246, 180, 20,
		hwnd, (HMENU)ID_ID_HYPERLINK, hInstance, 0
	);
	SetWindowText( hwndBtn[4], TEXT("<a href=\"\">http://www.cnblogs.com/mr-wid</a>") );
	SendMessage( hwndBtn[4], WM_SETFONT, (WPARAM)CreateFontIndirect(&lf), 0 );
}
