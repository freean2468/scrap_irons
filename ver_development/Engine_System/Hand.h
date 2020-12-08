////////////////////////////////////////////////////
// 손 클래스
////////////////////////////////////////////////////
#ifndef _Hand_H_
#define _Hand_H_

class CHand : public COrgan{
public:

public:
	CHand(){}
	CHand(Type p_type, D3DXVECTOR3 p_vPos, D3DXVECTOR3 p_vSca, D3DXVECTOR3 p_vRot, D3DXVECTOR3 p_vCen);
	~CHand();
};

#endif