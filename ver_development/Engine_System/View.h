/////////////////////////////////////////////////////////
// 메시지 처리 클래스
// 메시지 맵을 사용
/////////////////////////////////////////////////////////
#ifndef _View_H_
#define _View_H_

//class CView 
class CView : public CWnd{
public:
	DECLARE_DYNCREATE(CView)

public:
	//{{AFX_VIRTUAL
	//virtual void PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

	//{{AFX_MESSAGE
	void OnCreate(WPARAM,LPARAM);
	void OnDraw(WPARAM,LPARAM);
	void OnDestroy(WPARAM, LPARAM);
	void OnLButtonDown(WPARAM, LPARAM);
	void OnLButtonUp(WPARAM, LPARAM);
	void OnMouseMove(WPARAM, LPARAM);
	void OnSize(WPARAM, LPARAM);
	void OnKeyDown(WPARAM, LPARAM);
	void OnKeyUp(WPARAM, LPARAM);
	void OnMouseWheel(WPARAM, LPARAM);
	void OnMciNotify(WPARAM, LPARAM);
	//}}AFX_MESSAGE

	DECLARE_MESSAGE_MAP()
};//class CView

#endif