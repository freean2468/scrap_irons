////////////////////////////////////////////////////////////////////////////////
// ´«ÀÌ ¶³¾îÁö´Â È¿°ú
////////////////////////////////////////////////////////////////////////////////
#ifndef _Snow_H_
#define _Snow_H_

class CParticle;

class CSnow : public CParticle{
public:
	CSnow(d3d::BoundingBox* boundingBox, int numParticles);
	void resetParticle(Attribute* attribute);
	void update(float itmeDelta);
};

#endif