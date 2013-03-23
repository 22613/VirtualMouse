#include "wndproc.h"
#include "initialize_ui.h"
#include "constant.h"

//////////////////////////////////////////////////////////////////////////

//�����ڻص�����
LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	static HWND hBtn[4];

	switch( message )
	{
	case WM_CREATE:
		regVirtualMouseHotKey( hwnd );
		InitWndUI( hwnd, ((LPCREATESTRUCT)lParam)->hInstance, hBtn );
		break;

	case WM_COMMAND:
		dealWithBtnMsg( hwnd, wParam );
		break;

	case WM_HOTKEY:
		dealWithHotKey( hwnd, wParam );
		break;

	case WM_DESTROY:
		PostQuitMessage( 0 );
		return 0;
	}

	return DefWindowProc( hwnd, message, wParam, lParam );
}

//////////////////////////////////////////////////////////////////////////

//ע���ȼ�
void regVirtualMouseHotKey( HWND hwnd )
{
	RegisterHotKey( hwnd, ID_HOT_UP,	MOD_CONTROL, VK_NUMPAD8 );			//Ctrl + 8, ��
	RegisterHotKey( hwnd, ID_HOT_DOWN,	MOD_CONTROL, VK_NUMPAD2 );			//Ctrl + 2, ��
	RegisterHotKey( hwnd, ID_HOT_LEFT,	MOD_CONTROL, VK_NUMPAD4 );			//Ctrl + 4, ��
	RegisterHotKey( hwnd, ID_HOT_RIGHT, MOD_CONTROL, VK_NUMPAD6 );			//Ctrl + 6, ��

	RegisterHotKey( hwnd, ID_HOT_SL_UP,		MOD_CONTROL, VK_UP );			//Ctrl + UP,	΢��, ��
	RegisterHotKey( hwnd, ID_HOT_SL_DOWN,	MOD_CONTROL, VK_DOWN );			//Ctrl + DOWN,	΢��, ��
	RegisterHotKey( hwnd, ID_HOT_SL_LEFT,	MOD_CONTROL, VK_LEFT );			//Ctrl + LEFT,	΢��, ��
	RegisterHotKey( hwnd, ID_HOT_SL_RIGHT,	MOD_CONTROL, VK_RIGHT );		//Ctrl + RIGHT,	΢��, ��

	RegisterHotKey( hwnd, ID_HOT_TOPLEFT,	MOD_CONTROL, VK_NUMPAD7 );		//ע�� Ctrl + 7, ����
	RegisterHotKey( hwnd, ID_HOT_TOPRIGHT,	MOD_CONTROL, VK_NUMPAD9 );		//ע�� Ctrl + 9, ����
	RegisterHotKey( hwnd, ID_HOT_BOTLEFT,	MOD_CONTROL, VK_NUMPAD1 );		//ע�� Ctrl + 1, ����
	RegisterHotKey( hwnd, ID_HOT_BOTRIGHT,	MOD_CONTROL, VK_NUMPAD3 );		//ע�� Ctrl + 3, ����

	RegisterHotKey( hwnd, ID_HOT_LEFT_CLICK,	MOD_CONTROL, VK_NUMPAD5 );		//ע�� Ctrl + 5, �������
	RegisterHotKey( hwnd, ID_HOT_RIGHT_CLICK,	MOD_CONTROL, VK_RETURN );		//ע�� Ctrl + Enter, �Ҽ�����

	RegisterHotKey( hwnd, ID_HOT_MIDDLE_UP,		MOD_CONTROL, VK_SUBTRACT );		//ע�� Ctrl + UP, ��������
	RegisterHotKey( hwnd, ID_HOT_MIDDLE_DOWN,	MOD_CONTROL, VK_ADD );			//ע�� Ctrl + UP, ��������
	RegisterHotKey( hwnd, ID_HOT_MIDDLE_PRESS,	MOD_CONTROL, VK_DECIMAL );		//ע�� Ctrl + . , �м�����

	RegisterHotKey( hwnd, ID_HOT_WND_HIDE,		MOD_CONTROL, VK_F12 );			//ע�� Ctrl + 12 , ��ʾ����
}


//////////////////////////////////////////////////////////////////////////

//�����ȼ���Ϣ
void dealWithHotKey( HWND hwnd, WPARAM wParam )
{
	POINT ptCorPos;
	GetCursorPos( &ptCorPos );

	switch( wParam )
	{
	case ID_HOT_UP:			ptCorPos.y -= 40;	break;			//�ƶ�, ��	
	case ID_HOT_DOWN:		ptCorPos.y += 40;	break;			//�ƶ�, ��
	case ID_HOT_LEFT:		ptCorPos.x -= 40;	break;			//�ƶ�, ��
	case ID_HOT_RIGHT:		ptCorPos.x += 40;	break;			//�ƶ�, ��
	case ID_HOT_SL_UP:		ptCorPos.y -= 10;	break;			//΢��, ��
	case ID_HOT_SL_DOWN:	ptCorPos.y += 10;	break;			//΢��, ��
	case ID_HOT_SL_LEFT:	ptCorPos.x -= 10;	break;			//΢��, ��
	case ID_HOT_SL_RIGHT:	ptCorPos.x += 10;	break;			//΢��, ��
		
	case ID_HOT_TOPLEFT:		//�ƶ�, ����
		ptCorPos.x -= 40;	ptCorPos.y -= 40;	break;

	case ID_HOT_TOPRIGHT:		//�ƶ�, ����
		ptCorPos.x += 40;	ptCorPos.y -= 40;	break;

	case ID_HOT_BOTLEFT:		//�ƶ�, ����
		ptCorPos.x -= 40;	ptCorPos.y += 40;	break;

	case ID_HOT_BOTRIGHT:		//�ƶ�, ����
		ptCorPos.x += 40;	ptCorPos.y += 40;	break;

	case ID_HOT_LEFT_CLICK:		//���
		mouse_event( MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0 );
		mouse_event( MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 );
		break;

	case ID_HOT_RIGHT_CLICK:	//�һ�
		mouse_event( MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0 );
		mouse_event( MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 );
		break;

	case ID_HOT_MIDDLE_UP:		//��������
		mouse_event( MOUSEEVENTF_WHEEL, 0, 0, (DWORD)50, 0 );	break;

	case ID_HOT_MIDDLE_DOWN:	//��������
		mouse_event( MOUSEEVENTF_WHEEL, 0, 0, (DWORD)-50, 0 );	break;

	case ID_HOT_MIDDLE_PRESS:	//�м�����
		mouse_event( MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0 );
		mouse_event( MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0 );

	case ID_HOT_WND_HIDE:
		ShowWindow( hwnd, SW_SHOWNORMAL );
		SetForegroundWindow(hwnd);	break;
	}
	SetCursorPos( ptCorPos.x, ptCorPos.y );
}

//////////////////////////////////////////////////////////////////////////

//����ť��Ϣ
void dealWithBtnMsg( HWND hwnd,  WPARAM wParam )
{
	switch( LOWORD(wParam) )
	{
	case ID_BTN_HIDE:
		ShowWindow( hwnd, SW_MINIMIZE );		//����С��
		ShowWindow( hwnd, SW_HIDE );			//������
		break;
	}
}