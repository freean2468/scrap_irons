////////////////////////////////////////////////////
// 머리 클래스
////////////////////////////////////////////////////
#ifndef _Brain_H_
#define _Brain_H_

class CBrain : public COrgan{
public:

public:
	CBrain(){}
	CBrain(Type p_type, D3DXVECTOR3 p_vPos, D3DXVECTOR3 p_vSca, D3DXVECTOR3 p_vRot, D3DXVECTOR3 p_vCen);
	~CBrain();
};

#endif