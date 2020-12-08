////////////////////////////////////////////////////////////////////////////////
// 유동적인 로고
////////////////////////////////////////////////////////////////////////////////
#ifndef _Logo_H_
#define _Logo_H_

#include "./Engine_System/BaseManager.h"

class CLogo : public COrganEntity{
public:
	typedef enum LogoAttType {BIG = 0, SMALL} LOGOATTTYPE;

public:
	CLogo(int id);
	~CLogo();

	virtual void Update(){this->CalculationOrgan(EngineMgr->GetTimeDelta());}
	virtual bool HandleMessage(const Telegram& msg){return false;}

	virtual void CalculationOrgan(float timeDelta);
};

#endif