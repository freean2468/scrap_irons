/////////////////////////////////////////////////////////////////
// RTTI�� ���õ� ��� ����� ����
/////////////////////////////////////////////////////////////////

#ifndef _Stdafx_H_
#define _Stdafx_H_

// �޽��� �� ��ũ��
#define DECLARE_MESSAGE_MAP()	static MessageMap messageMap[];
#define BEGIN_MESSAGE_MAP(class_name) MessageMap class_name::messageMap[]={
#define END_MESSAGE_MAP()	{0, NULL}};

// RTTI ��ũ��
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

// CRuntimeClass ����ü
// CRuntimeClass�� Ŭ������ �̸��� ũ�� �׸��� ��ü ���� �Լ��� �ּҸ� ������ ���� ����ü��.
struct CRuntimeClass{
	char	m_lpszClassName[21];		// Ŭ���� �̸�
	int		m_nObjectSize;				// ��ü�� ũ��
	CObject* (*pfnCreateObject)();		// �ڽ� �ڽ��� �����ϴ� �Լ��� �����ּҸ� ���� �Լ� ������

	CObject* CreateObject();			// �Լ� �����͸� �̿��Ͽ� �Լ��� ȣ��
};// struct CRunTimeClass

//�޽��� �� ����ü
class CView;

typedef void (CView::*CViewFunPointer)(WPARAM,LPARAM);

typedef struct tagMessageMap{
	UINT iMsg;
	CViewFunPointer fp;
}MessageMap;

#endif