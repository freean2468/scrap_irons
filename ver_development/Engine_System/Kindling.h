////////////////////////////////////////////////////////////////////////////////
// �Ҿ��� �ö󰡴� ȿ��
////////////////////////////////////////////////////////////////////////////////
#ifndef _Kindling_H_
#define _Kindling_H_

class CParticle;

class CKindling : public CParticle{
public:
	CKindling(d3d::BoundingBox* boundingBox, int numParticles);
	void resetParticle(Attribute* attribute);
	void update(float itmeDelta);
};

#endif