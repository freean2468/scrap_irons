#include "../BaseHeader.h"

CObject* CRuntimeClass::CreateObject(){
	return (*pfnCreateObject)();	// 함수포인터를 이용하여 간접적으로 함수를 호출한다.
}//CRuntimeClass::CreateObject()
