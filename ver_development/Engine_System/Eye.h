////////////////////////////////////////////////////
// ´« Å¬·¡½º
////////////////////////////////////////////////////
#ifndef _Eye_H_
#define _Eye_H_

class CEye : public COrgan{
public:

public:
	CEye(){}
	CEye(Type p_type, D3DXVECTOR3 p_vPos, D3DXVECTOR3 p_vSca, D3DXVECTOR3 p_vRot, D3DXVECTOR3 p_vCen);
	~CEye();
};

#endif