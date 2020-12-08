#include "../BaseHeader.h"

IMPLEMENT_DYNCREATE(CWnd)

HWND CWnd::GetSafeHwnd(){
	return this == NULL ? NULL : m_hWnd;
}//CWnd::GetSafeHwnd()

BOOL CWnd::ShowWindow(int nCmdShow){
	return ::ShowWindow(GetSafeHwnd(), nCmdShow);
}//CWnd::ShowWindow(int nCmdShow)

BOOL CWnd::UpdateWindow(){
	return ::UpdateWindow(GetSafeHwnd());
}//CWnd::UpdateWindow()

/*virtual*/ void CWnd::PreCreateWindow(CREATESTRUCT& cs){

}//CWnd::PreCreateWindow(CREEATESTRUCT& cs)