////////////////////////////////////////////////////
// 눈동자 클래스
////////////////////////////////////////////////////
#ifndef _Pupil_H_
#define _Pupil_H_

class CPupil : public COrgan{
public:

public:
	CPupil(){}
	CPupil(Type p_type, D3DXVECTOR3 p_vPos, D3DXVECTOR3 p_vSca, D3DXVECTOR3 p_vRot, D3DXVECTOR3 p_vCen);
	~CPupil();

	////////////////////////////////////////////////
	// Get함수
	virtual int GetRow(){return _row;}
	virtual int GetCol(){return _col;}
};

#endif