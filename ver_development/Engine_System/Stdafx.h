/////////////////////////////////////////////////////////////////
// RTTI와 관련된 모든 기능을 제공
/////////////////////////////////////////////////////////////////

#ifndef _Stdafx_H_
#define _Stdafx_H_

// 메시지 맵 매크로
#define DECLARE_MESSAGE_MAP()	static MessageMap messageMap[];
#define BEGIN_MESSAGE_MAP(class_name) MessageMap class_name::messageMap[]={
#define END_MESSAGE_MAP()	{0, NULL}};

// RTTI 매크로
#define RUNTIME_CLASS(class_name) (&class_name::class##class_name)

#define DECLARE_DYNAMIC(class_name) static CRuntimeClass class##class_name;

#define IMPLEMENT_DYNAMIC(class_name) \
	CRuntimeClass class_name::class##class_name = {(#class_name), sizeof(class_name), class_name::CreateObject };

#define DECLARE_DYNCREATE(class_name) \
	DECLARE_DYNAMIC(class_name) \
	static CObject* CreateObject();

#define IMPLEMENT_DYNCREATE(class_name) \
	IMPLEMENT_DYNAMIC(class_name)	\
	CObject* class_name::CreateObject() {return new class_name;}

class CObject;

// CRuntimeClass 구조체
// CRuntimeClass는 클래스의 이름과 크기 그리고 객체 생성 함수의 주소를 가지는 작은 구조체다.
struct CRuntimeClass{
	char	m_lpszClassName[21];		// 클래스 이름
	int		m_nObjectSize;				// 객체의 크기
	CObject* (*pfnCreateObject)();		// 자시 자신을 생성하는 함수의 시작주소를 가질 함수 포인터

	CObject* CreateObject();			// 함수 포인터를 이용하여 함수를 호출
};// struct CRunTimeClass

//메시지 맵 구조체
class CView;

typedef void (CView::*CViewFunPointer)(WPARAM,LPARAM);

typedef struct tagMessageMap{
	UINT iMsg;
	CViewFunPointer fp;
}MessageMap;

#endif