#include "../BaseHeader.h"

CParticleGun::CParticleGun(CCamera* camera){
	_camera          = camera;
	_size            = 0.8f;
	_vbSize          = 2048;
	_vbOffset        = 0;  
	_vbBatchSize     = 512; 
}

void CParticleGun::resetParticle(Attribute* attribute){
	attribute->_isAlive = true;

	D3DXVECTOR3 cameraPos;
	_camera->GetPosition(&cameraPos);

	D3DXVECTOR3 cameraDir;
	_camera->GetLook(&cameraDir);

	// 파티클 위치에 카메라 위치를 이용한다.
	attribute->_position = cameraPos;
	attribute->_position.y -= 1.0f;	// 카메라보다 약간 아래쪽으로 이동해
									// 총을 들고 있는 것 같은 효과를 얻는다.

	// 카메라가 바라보는 방향으로 발사한다.
	attribute->_velocity = cameraDir * 100.0f;

	// 녹색
	attribute->_color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

	attribute->_age = 0.0f;
	attribute->_lifeTime = 1.0f;	// 수명은 1초
}

void CParticleGun::update(float timeDelta){
	std::list<Attribute>::iterator i;

	for(i = _particles.begin(); i != _particles.end(); i++){
		i->_position += i->_velocity * timeDelta;

		i->_age += timeDelta;

		if(i->_age > i->_lifeTime)	// kill
			i->_isAlive = false;
	}
	removeDeadParticles();
}