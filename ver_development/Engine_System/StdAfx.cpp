#include "../BaseHeader.h"

CObject* CRuntimeClass::CreateObject(){
	return (*pfnCreateObject)();	// �Լ������͸� �̿��Ͽ� ���������� �Լ��� ȣ���Ѵ�.
}//CRuntimeClass::CreateObject()
