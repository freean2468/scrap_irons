////////////////////////////////////////////////////////////////////////////////
// BaseEffect Å¬·¡½º
////////////////////////////////////////////////////////////////////////////////
#ifndef _BaseEffect_H_
#define _BaseEffect_H_

#include "./Engine_System/BaseManager.h"

class CBaseEffect : public COrganEntity{
	SMALLSCALEEFFECTTYPE _effectType;
	bool _bIsDie;

public:
	CBaseEffect(SMALLSCALEEFFECTTYPE p_Type);
	~CBaseEffect();

	virtual void CalculationOrgan(float timeDelta){}

	virtual SMALLSCALEEFFECTTYPE GetEffectType(){return _effectType;}

	virtual bool GetIsDie(){return _bIsDie;}
	virtual void SetIsDie(bool p_bool){_bIsDie = p_bool;}
};

#endif