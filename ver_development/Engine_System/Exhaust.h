////////////////////////////////////////////////////////////////////////////////
// 매연 효과
////////////////////////////////////////////////////////////////////////////////
#ifndef _Exhaust_H_
#define _Exhaust_H_

class CParticle;

class CExhaust : public CParticle{
public:
	CExhaust(d3d::BoundingBox* boundingBox, D3DXVECTOR3* origin,int numParticles);
	void resetParticle(Attribute* attribute);
	void update(float itmeDelta);
};

#endif