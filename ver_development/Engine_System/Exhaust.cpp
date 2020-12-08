#include "../BaseHeader.h"

CExhaust::CExhaust(d3d::BoundingBox* boundingBox, D3DXVECTOR3* origin, int numParticles){
	_boundingBox = *boundingBox;
	_origin = *origin;
	_size = 40.0f;
	_vbSize = 2048;
	_vbOffset = 0;
	_vbBatchSize = 1024;

	for(int i =0;i<numParticles; i++)
		addParticle();

	init(EngineMgr->GetpDevice(), "./Image/Particle/Exhaust.dds");
}

void CExhaust::resetParticle(Attribute* attribute){
	attribute->_isAlive = true;
	attribute->_position = _origin;

	// �ſ� ������ ���� ���Ѵ�.
	attribute->_velocity.x = d3d::GetRandomFloat(-1.0f, 1.0f)*600.0f;
	attribute->_velocity.y = d3d::GetRandomFloat(0.2f, 0.9f)*300.0f;
	attribute->_velocity.z = d3d::GetRandomFloat(0.0f, 1.0f)*10.0f; // ���� ��������� ���� Ŀ���鼭 ���������� ���� ȿ��

	// ��ƼŬ �� ����
	attribute->_color = d3d::WHITE;
	attribute->_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

void CExhaust::update(float timeDelta){
	std::list<Attribute>::iterator i;
	for(i = _particles.begin(); i != _particles.end(); i++){
		i->_position += i->_velocity * 0.001f/* * timeDelta */;

		// ����Ʈ�� ��踦 ����°�?
		if(_boundingBox.isPointInside(i->_position) == false){
			// ��踦 ��� ��ƼŬ�� ��Ȱ���Ѵ�.
			resetParticle(&(*i));
		}
	}
}