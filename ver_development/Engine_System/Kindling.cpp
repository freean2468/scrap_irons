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

	// 불씨의 위치 지정을위해 임의의 x, z 좌표를 얻는다.
	d3d::GetRandomVector(
		&attribute->_position,
		&_boundingBox._min,
		&_boundingBox._max);

	// 높이 (y-좌표)는 항상 경계 상자의 최하단이 된다.
	attribute->_position.y = _boundingBox._min.y;

	// 불씨는 위쪽으로 상승.
	attribute->_velocity.x = 0.0f;
	attribute->_velocity.y = d3d::GetRandomFloat(0.1f, 0.6f)*100.0f;
	attribute->_velocity.z = 0.0f;

	// 붉은 불씨
	attribute->_color = d3d::WHITE;
}

void CKindling::update(float timeDelta){
	std::list<Attribute>::iterator i;
	for(i = _particles.begin(); i != _particles.end(); i++){
		i->_position.y += i->_velocity.y * 0.02f;
		i->_position.x += sin(i->_position.y*0.07f);

		// 포인트가 경계를 벗어났는가?
		if(_boundingBox.isPointInside(i->_position) == false){
			// 경계를 벗어난 파티클을 재활용한다.
			resetParticle(&(*i));
		}
	}
}