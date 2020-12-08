////////////////////////////////////////////////////////////////////////////////
// Event Entity Å¬·¡½º
////////////////////////////////////////////////////////////////////////////////
#ifndef _EventEntity_H_
#define _EventEntity_H_

class CEventEntity : public COrganEntity{
public:
	CEventEntity(int id);
	~CEventEntity();
public:
	virtual void Update(){CalculationOrgan(EngineMgr->GetTimeDelta());}
	virtual bool HandleMessage(const Telegram& msg){return false;}
	
	virtual void CalculationOrgan(float timeDelta);
};

#endif