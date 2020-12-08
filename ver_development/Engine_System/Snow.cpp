#include "../BaseHeader.h"

CSnow::CSnow(d3d::BoundingBox* boundingBox, int numParticles){
	_boundingBox = *boundingBox;
	_size = 40.0f;
	_vbSize = 2048;
	_vbOffset = 0;
	_vbBatchSize = 512;

	for(int i =0;i<numParticles; i++)
		addParticle();
}

void CSnow::resetParticle(Attribute* attribute){
	attribute->_isAlive = true;

	// �������� ��ġ ���������� ������ x, z ��ǥ�� ��´�.
	d3d::GetRandomVector(
		&attribute->_position,
		&_boundingBox._min,
		&_boundingBox._max);

	// ���� (y-��ǥ)�� �׻� ��� ������ �ֻ���� �ȴ�.
	attribute->_position.y = _boundingBox._max.y;

	// �����̴� �Ʒ������� �������� �ణ ������ ���Ѵ�.
	attribute->_velocity.x = d3d::GetRandomFloat(0.0f, 1.0f)*-120.0f;
	attribute->_velocity.y = d3d::GetRandomFloat(0.0f, 1.0f)*-400.0f;
	attribute->_velocity.z = 0.0f;

	// ȸ���� ������
	attribute->_color = d3d::WHITE;
}

void CSnow::update(float timeDelta){
	std::list<Attribute>::iterator i;
	for(i = _particles.begin(); i != _particles.end(); i++){
		i->_position += i->_velocity * timeDelta;

		// ����Ʈ�� ��踦 ����°�?
		if(_boundingBox.isPointInside(i->_position) == false){
			// ��踦 ��� ��ƼŬ�� ��Ȱ���Ѵ�.
			resetParticle(&(*i));
		}
	}
}