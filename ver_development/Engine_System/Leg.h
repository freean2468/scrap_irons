////////////////////////////////////////////////////
// �ٸ� Ŭ����
////////////////////////////////////////////////////
#ifndef _Leg_H_
#define _Leg_H_

class CLeg : public COrgan{
public:
	// ���� ����
	// �ִ��� true, �ּҶ�� false
	bool _angleState;
public:
	CLeg(){}
	CLeg(Type p_type, D3DXVECTOR3 p_vPos, D3DXVECTOR3 p_vSca, D3DXVECTOR3 p_vRot, D3DXVECTOR3 p_vCen);
	virtual ~CLeg();

	virtual void Rotation(TYPE p_type, float timeDelta);
};

#endif