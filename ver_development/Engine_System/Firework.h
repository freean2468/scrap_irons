////////////////////////////////////////////////////////////////////////////////
// ÆøÁ× ±¸Çö Å¬·¡½º
////////////////////////////////////////////////////////////////////////////////
#ifndef _Firework_H_
#define _Firework_H_

class CFirework : public CParticle{
public:
	CFirework(D3DXVECTOR3* origin, int numParticles);
	void resetParticle(Attribute* attribute);
	void update(float timeDelta);
	void preRender();
	void postRender();
};

#endif