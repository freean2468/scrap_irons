////////////////////////////////////////////////////////////////////////////////
// ������ �������� ȿ��
////////////////////////////////////////////////////////////////////////////////
#ifndef _Dirt_H_
#define _Dirt_H_

class CParticle;

class CDirt : public CParticle{
public:
	CDirt(d3d::BoundingBox* boundingBox, int numParticles);
	void resetParticle(Attribute* attribute);
	void update(float itmeDelta);
};

#endif