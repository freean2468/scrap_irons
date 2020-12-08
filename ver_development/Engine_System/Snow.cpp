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

	// 눈송이의 위치 지정을위해 임의의 x, z 좌표를 얻는다.
	d3d::GetRandomVector(
		&attribute->_position,
		&_boundingBox._min,
		&_boundingBox._max);

	// 높이 (y-좌표)는 항상 경계 상자의 최상단이 된다.
	attribute->_position.y = _boundingBox._max.y;

	// 눈송이는 아래쪽으로 떨어지며 약간 왼쪽을 향한다.
	attribute->_velocity.x = d3d::GetRandomFloat(0.0f, 1.0f)*-120.0f;
	attribute->_velocity.y = d3d::GetRandomFloat(0.0f, 1.0f)*-400.0f;
	attribute->_velocity.z = 0.0f;

	// 회색의 눈송이
	attribute->_color = d3d::WHITE;
}

void CSnow::update(float timeDelta){
	std::list<Attribute>::iterator i;
	for(i = _particles.begin(); i != _particles.end(); i++){
		i->_position += i->_velocity * timeDelta;

		// 포인트가 경계를 벗어났는가?
		if(_boundingBox.isPointInside(i->_position) == false){
			// 경계를 벗어난 파티클을 재활용한다.
			resetParticle(&(*i));
		}
	}
}