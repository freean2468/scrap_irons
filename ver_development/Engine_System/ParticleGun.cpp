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

	// ��ƼŬ ��ġ�� ī�޶� ��ġ�� �̿��Ѵ�.
	attribute->_position = cameraPos;
	attribute->_position.y -= 1.0f;	// ī�޶󺸴� �ణ �Ʒ������� �̵���
									// ���� ��� �ִ� �� ���� ȿ���� ��´�.

	// ī�޶� �ٶ󺸴� �������� �߻��Ѵ�.
	attribute->_velocity = cameraDir * 100.0f;

	// ���
	attribute->_color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

	attribute->_age = 0.0f;
	attribute->_lifeTime = 1.0f;	// ������ 1��
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