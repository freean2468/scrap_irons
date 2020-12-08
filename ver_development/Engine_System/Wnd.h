/*
CWnd클래스는 모든 윈도우 클래스의 베이스 클래스로 사용된다.
윈도우 핸들을 필요로하는 모든 윈도우 API함수들을 랩하고 있고, 구조상 필요한 가상함수들을 포함한다.
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
	virtual void PreCreateWindow(CREATESTRUCT& cs);	// 윈도우를 생성하기 바로 전에 후출
	//}}AFX_VIRTUAL
};	// class CWnd

#endif