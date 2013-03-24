#include "wndproc.h"
#include "initialize_ui.h"
#include "constant.h"

//////////////////////////////////////////////////////////////////////////

//�����ڻص�����
LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	static HWND hBtn[4];
	LOGFONT		lf;
	HDC			hdc;
	PAINTSTRUCT ps;
	char		btnLab[10];
	HFONT		hFont;

	strcpy( lf.lfFaceName, "Arial" );
	lf.lfWidth			= 6;
	lf.lfHeight			= 12;
	lf.lfEscapement		= 0;
	lf.lfOrientation	= 0;
	lf.lfWeight			= FW_NORMAL;
	lf.lfItalic			= 0;
	lf.lfUnderline		= 0;
	lf.lfStrikeOut		= 0;
	lf.lfCharSet		= GB2312_CHARSET;

	switch( message )
	{
	case WM_CREATE:
		regVirtualMouseHotKey( hwnd );
		InitWndUI( hwnd, ((LPCREATESTRUCT)lParam)->hInstance, hBtn );
		return 0;

	case WM_COMMAND:
		dealWithBtnMsg( hwnd, wParam, hBtn );	return 0;

	case WM_HOTKEY:
		dealWithHotKey( hwnd, wParam );			return 0;

	case WM_PAINT:
		hdc = BeginPaint (hwnd, &ps) ;
		hFont = CreateFontIndirect (&lf);
		SelectObject (hdc, hFont ) ;
		SetBkColor( hdc, RGB(236, 233, 216) );
		drawTipText( hdc );
		DeleteObject( hFont );
		EndPaint (hwnd, &ps) ;
		return 0;

	case WM_DESTROY:
		GetWindowText( hBtn[0], btnLab, 10 );
		if( strcmp( btnLab, "��ͣģ��" ) == 0 )			//���ȼ�û�б�ע��ʱ
		{
			destroyRegedHotKey( hwnd );					//ע��ģ���ȼ�
			UnregisterHotKey( hwnd, ID_HOT_WND_HIDE );	//ע������������ȼ�
			UnregisterHotKey( hwnd, ID_HOT_PAUSE );		//ע����ͣ\�����ȼ�
		}
		PostQuitMessage( 0 );					return 0;
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
	RegisterHotKey( hwnd, ID_HOT_PAUSE,			MOD_CONTROL, VK_F10 );			//ע�� Ctrl + 10 , ��ͣ\�����ȼ�
}

//////////////////////////////////////////////////////////////////////////

//����ע����ȼ�
void destroyRegedHotKey( HWND hwnd )
{
	int hotID = ID_HOT_UP;
	for( hotID; hotID <= ID_HOT_MIDDLE_PRESS; hotID++ )
		UnregisterHotKey( hwnd, hotID );
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

	case ID_HOT_WND_HIDE:		//����������
		ShowWindow( hwnd, SW_SHOWNORMAL );
		SetForegroundWindow(hwnd);	break;

	case ID_HOT_PAUSE:			//��ͣ\�����ȼ�
		SendMessage( hwnd, WM_COMMAND, ID_BTN_PAUSE|BN_CLICKED, 0 );	break;
	}
	SetCursorPos( ptCorPos.x, ptCorPos.y );
}

//////////////////////////////////////////////////////////////////////////

//����ť��Ϣ
void dealWithBtnMsg( HWND hwnd,  WPARAM wParam, HWND *hBtn )
{
	char btnLab[10];

	switch( LOWORD(wParam) )
	{
	case ID_BTN_HIDE:
		ShowWindow( hwnd, SW_MINIMIZE );		//����С��
		ShowWindow( hwnd, SW_HIDE );			//������
		break;

	case ID_BTN_PAUSE:
		GetWindowText( hBtn[0], btnLab, 10 );
		if( strcmp( btnLab, "��ͣģ��" ) == 0 )
		{
			destroyRegedHotKey( hwnd );
			SetWindowText( hBtn[0], TEXT("����ģ��") );
		}
		else
		{
			regVirtualMouseHotKey( hwnd );
			SetWindowText( hBtn[0], TEXT("��ͣģ��") );
		}
		break;

	case ID_BTN_EXIT:
		SendMessage( hwnd, WM_DESTROY, 0, 0 );
		break;
	}
}

//////////////////////////////////////////////////////////////////////////

//������ʾ��Ϣ
void drawTipText( HDC hdc )
{
	int i = 1, x = 10, y = 30;
	TCHAR szTip[][128] = {
		TEXT("ע��: �������־�ָС�������֡�"),
		TEXT("________________________________________"),
		TEXT("�ƶ�ָ��: Ctrl + 1, 2, 3, 4, 6, 7, 8, 9"),
		TEXT("С�����ƶ�: Ctrl + ����� ��,��,��,��"),
		TEXT("�������: Ctrl + 5"),
		TEXT("�����Ҽ�: Ctrl + Enter"),
		TEXT("�����м�: Ctrl + . (Del)"),
		TEXT("��������: Ctrl + num -"),
		TEXT("��������: Ctrl + num +"),
		TEXT("��ͣ/����ģ��: Ctrl + F10"),
		TEXT("����������: Ctrl + F12")
	};
	TextOut ( hdc, 10, 5, szTip[0], lstrlen (szTip[0]) ) ;
	for( i; i < sizeof( szTip ) / sizeof( szTip[0] ); i++ )
	{
		TextOut ( hdc, x, y, szTip[i], lstrlen (szTip[i]) ) ;
		y += 20;
	}
}