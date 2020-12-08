////////////////////////////////////////////////////
// 목 클래스
////////////////////////////////////////////////////
#ifndef _Throat_H_
#define _Throat_H_

class CThroat : public COrgan{
public:

public:
	CThroat(){}
	CThroat(Type p_type, D3DXVECTOR3 p_vPos, D3DXVECTOR3 p_vSca, D3DXVECTOR3 p_vRot, D3DXVECTOR3 p_vCen);
	~CThroat();
};

#endif