////////////////////////////////////////////////////////////////////////////////
// 파티클 총 구현 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _ParticleGun_H_
#define _ParticleGun_H_

class CParticleGun : public CParticle{
public:
	CParticleGun(CCamera* camera);
	void resetParticle(Attribute* attribute);
	void update(float timeDelta);

private:
	CCamera* _camera;
};

#endif