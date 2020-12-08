/*
CObject�� Application�� �����ϴ� ���� ��κ� Ŭ������ ���� �����̴�.
��ü�� ���� ������ ���ؼ��� CRuntimeClass ��ü�� �ּҸ� ���� �ϰ�, �̸� ���� ������ ��ü��
�� Ÿ���� �˷����� �ʾ����Ƿ�, ���� ���� ��ü���� ���� ������ CObject*�� ���ϵȴ�.
*/
#ifndef _Object_H_
#define _Object_H_

class CObject{
public:
	virtual CRuntimeClass* GetRuntimeClass() const;
	virtual ~CObject(){}

protected:
	CObject(){}
};//class CObject

#endif