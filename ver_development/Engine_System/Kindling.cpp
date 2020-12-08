#include "../BaseHeader.h"

CKindling::CKindling(d3d::BoundingBox* boundingBox, int numParticles){
	_boundingBox = *boundingBox;
	_size = 12.0f;
	_vbSize = 2048;
	_vbOffset = 0;
	_vbBatchSize = 512;

	for(int i =0;i<numParticles; i++)
		addParticle();

	init(EngineMgr->GetpDevice(), "./Image/Particle/kindling.dds");
}

void CKindling::resetParticle(Attribute* attribute){
	attribute->_isAlive = true;

	// �Ҿ��� ��ġ ���������� ������ x, z ��ǥ�� ��´�.
	d3d::GetRandomVector(
		&attribute->_position,
		&_boundingBox._min,
		&_boundingBox._max);

	// ���� (y-��ǥ)�� �׻� ��� ������ ���ϴ��� �ȴ�.
	attribute->_position.y = _boundingBox._min.y;

	// �Ҿ��� �������� ���.
	attribute->_velocity.x = 0.0f;
	attribute->_velocity.y = d3d::GetRandomFloat(0.1f, 0.6f)*100.0f;
	attribute->_velocity.z = 0.0f;

	// ���� �Ҿ�
	attribute->_color = d3d::WHITE;
}

void CKindling::update(float timeDelta){
	std::list<Attribute>::iterator i;
	for(i = _particles.begin(); i != _particles.end(); i++){
		i->_position.y += i->_velocity.y * 0.02f;
		i->_position.x += sin(i->_position.y*0.07f);

		// ����Ʈ�� ��踦 ����°�?
		if(_boundingBox.isPointInside(i->_position) == false){
			// ��踦 ��� ��ƼŬ�� ��Ȱ���Ѵ�.
			resetParticle(&(*i));
		}
	}
}