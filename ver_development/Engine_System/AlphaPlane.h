////////////////////////////////////////////////////////////////////////////////
// Alpha blend Plane Å¬·¡½º
////////////////////////////////////////////////////////////////////////////////
#ifndef _AlphaPlane_H_
#define _AlphaPlane_H_

#include "./Engine_System/BaseManager.h"

class CAlphaPlane : public COrganEntity{
public:
	typedef enum AlphaPlaneAttType {RECT=0, SMOKE} ALPHAPLANEATTTYPE;

private:
	int nPlaneType;

public:
	CAlphaPlane(int id);
	~CAlphaPlane();

	virtual void Update(){this->CalculationOrgan(EngineMgr->GetTimeDelta());}
	virtual bool HandleMessage(const Telegram& msg){return false;}

	virtual void TransformOrgan(float timeDelta);

	virtual void CalculationOrgan(float timeDelta);

	void SetPlaneType(int p_nPlaneType){nPlaneType = p_nPlaneType;}
	int GetPlaneType(){return nPlaneType;}
	CAttachment* GetPlane(int p_nAttType);
	void AlphaPlaneInit();
	float GetPlaneAlpha(int p_nAttType);
};

#endif