/*
CWndŬ������ ��� ������ Ŭ������ ���̽� Ŭ������ ���ȴ�.
������ �ڵ��� �ʿ���ϴ� ��� ������ API�Լ����� ���ϰ� �ְ�, ������ �ʿ��� �����Լ����� �����Ѵ�.
*/
#ifndef _Wnd_H_
#define	_Wnd_H_

class CWnd : public CObject{
public:
	DECLARE_DYNCREATE(CWnd)

	HWND m_hWnd;

public:
	HWND GetSafeHwnd();
	BOOL ShowWindow(int nCmdShow);
	BOOL UpdateWindow();

	//{{AFX_VIRTUAL
	virtual void PreCreateWindow(CREATESTRUCT& cs);	// �����츦 �����ϱ� �ٷ� ���� ����
	//}}AFX_VIRTUAL
};	// class CWnd

#endif