/*
CObject는 Application을 구성하는 거의 대부분 클래스의 공통 조상이다.
객체의 동적 생성을 위해서는 CRuntimeClass 객체의 주소를 얻어야 하고, 이를 통해 생성된 객체는
그 타입이 알려지지 않았으므로, 동적 생성 객체들의 공통 조상인 CObject*로 리턴된다.
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