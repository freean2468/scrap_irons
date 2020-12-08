////////////////////////////////////////////////////////////////////////////////
// 아이템 : 설계도 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _BluePrint_H_
#define _BluePrint_H_

#include "./Engine_System/BaseManager.h"

class CBluePrint : public CItem{
public:
	typedef enum BluePrintType {WAGOO = 0, WOOWO, YAWO, KIRIT, TINKLE} BLUEPRINTTYPE;

	BLUEPRINTTYPE _eBluePrintType;
public:
	CBluePrint(int id);
	CBluePrint(BLUEPRINTTYPE p_eBluePrintType);
	~CBluePrint();

	virtual BLUEPRINTTYPE GetBluePrintType(){return _eBluePrintType;}
};

#endif