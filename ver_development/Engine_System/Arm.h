////////////////////////////////////////////////////////////////////////////////
// ÆÈ Å¬·¡½º
////////////////////////////////////////////////////////////////////////////////
#ifndef _Arm_H_
#define _Arm_H_

class CArm : public COrgan{
public:
	
public:
	CArm(){}
	CArm(Type p_type, D3DXVECTOR3 p_vPos, D3DXVECTOR3 p_vSca, D3DXVECTOR3 p_vRot, D3DXVECTOR3 p_vCen);
	virtual ~CArm();

	virtual void Rotation(TYPE p_type, float timeDelta);
};

#endif