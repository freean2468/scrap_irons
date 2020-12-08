////////////////////////////////////////////////////
// 다리 클래스
////////////////////////////////////////////////////
#ifndef _Leg_H_
#define _Leg_H_

class CLeg : public COrgan{
public:
	// 각도 상태
	// 최대라면 true, 최소라면 false
	bool _angleState;
public:
	CLeg(){}
	CLeg(Type p_type, D3DXVECTOR3 p_vPos, D3DXVECTOR3 p_vSca, D3DXVECTOR3 p_vRot, D3DXVECTOR3 p_vCen);
	virtual ~CLeg();

	virtual void Rotation(TYPE p_type, float timeDelta);
};

#endif