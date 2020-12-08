#include "../BaseHeader.h"

CFirework::CFirework(D3DXVECTOR3* origin, int numParticles)
{
	_origin        = *origin;
	_size          = 0.9f;
	_vbSize        = 2048;
	_vbOffset      = 0;   
	_vbBatchSize   = 512; 

	for(int i = 0; i < numParticles; i++)
		addParticle();
}

void CFirework::resetParticle(Attribute* attribute){
	attribute->_isAlive = true;
	attribute->_position = _origin;

	D3DXVECTOR3 min = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	D3DXVECTOR3 max = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	d3d::GetRandomVector(&attribute->_velocity,
		&min,
		&max);

	// ��ü�� ����� ���� ����ȭ
	D3DXVec3Normalize(
		&attribute->_velocity,
		&attribute->_velocity);

	attribute->_velocity *= 400.0f;

	attribute->_color = D3DXCOLOR(
		d3d::GetRandomFloat(0.0f, 1.0f),
		d3d::GetRandomFloat(0.0f, 1.0f),
		d3d::GetRandomFloat(0.0f, 1.0f),
		1.0f);

	attribute->_age = 0.0f;
	attribute->_lifeTime = 2.0f;	// 2�� ������ ������ ������.
}

void CFirework::update(float timeDelta){
	std::list<Attribute>::iterator i;

	for(i = _particles.begin();i!=_particles.end(); i++){
		// ������ ��ƼŬ�� �����Ѵ�.
		if(i->_isAlive){
			i->_position += i->_velocity * timeDelta;

			i->_age += timeDelta;

			if(i->_age > i->_lifeTime) // ���δ�.
				i->_isAlive = false;
		}
	}
}

void CFirework::preRender(){
	CParticle::preRender();

	_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// z-���� �б�� ���������� ����� ������ �ʴ´�.
	_device->SetRenderState(D3DRS_ZWRITEENABLE, false);
}

void CFirework::postRender(){
	CParticle::postRender();

	_device->SetRenderState(D3DRS_ZWRITEENABLE, true);
}