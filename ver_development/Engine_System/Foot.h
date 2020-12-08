////////////////////////////////////////////////////
// 발 클래스
////////////////////////////////////////////////////
#ifndef _Foot_H_
#define _Foot_H_

class CFoot : public COrgan{
public:

public:
	CFoot(){}
	CFoot(Type p_type, D3DXVECTOR3 p_vPos, D3DXVECTOR3 p_vSca, D3DXVECTOR3 p_vRot, D3DXVECTOR3 p_vCen);
	~CFoot();
};

#endif