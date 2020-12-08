#include "../BaseHeader.h"

CDirt::CDirt(d3d::BoundingBox* boundingBox, int numParticles){
	_boundingBox = *boundingBox;
	_size = 12.0f;
	_vbSize = 2048;
	_vbOffset = 0;
	_vbBatchSize = 512;

	for(int i =0;i<numParticles; i++)
		addParticle();

	init(EngineMgr->GetpDevice(), "./Image/Particle/Dirt.dds");
}

void CDirt::resetParticle(Attribute* attribute){
	attribute->_isAlive = true;

	// ������ ��ġ ���������� ������ x, z ��ǥ�� ��´�.
	d3d::GetRandomVector(
		&attribute->_position,
		&_boundingBox._min,
		&_boundingBox._max);

	// ���� (y-��ǥ)�� �׻� ��� ������ �ֻ���� �ȴ�.
	attribute->_position.y = _boundingBox._max.y;

	// ������ �Ʒ������� �������� �ణ ������ ���Ѵ�.
	attribute->_velocity.x = d3d::GetRandomFloat(0.3f, 1.0f)*-120.0f;
	attribute->_velocity.y = d3d::GetRandomFloat(0.3f, 1.0f)*-400.0f;
	attribute->_velocity.z = 0.0f;

	// ȸ���� ����
	attribute->_color = d3d::RED;
}

void CDirt::update(float timeDelta){
	std::list<Attribute>::iterator i;
	for(i = _particles.begin(); i != _particles.end(); i++){

		if((rand() % 2) == 0)
			i->_velocity.x+=1.0f;
		else
			i->_velocity.x-=1.0f;

		i->_position += i->_velocity * 0.02f;

		// ����Ʈ�� ��踦 ����°�?
		if(_boundingBox.isPointInside(i->_position) == false){
			// ��踦 ��� ��ƼŬ�� ��Ȱ���Ѵ�.
			resetParticle(&(*i));
		}
	}
}