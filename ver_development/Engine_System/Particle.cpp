#include "../BaseHeader.h"

const DWORD Particle::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

CParticle::CParticle(){
	_device = 0;
	_vb     = 0;
	_tex    = 0;
}

CParticle::~CParticle(){
	d3d::Release<IDirect3DVertexBuffer9*>(_vb);
	d3d::Release<IDirect3DTexture9*>(_tex);
	removeParticles();
}

// 포인트 스프라이트를 저장하기 위한 버텍스 버퍼를 만들고 텍스처를 만드는 등의
// DIrect3D의 장치 의존적인 초기화 작업을 처리한다.
bool CParticle::init(IDirect3DDevice9* device, char* texFileName){
	// vertex buffer's size does not equal the number of particles in our system.  We
	// use the vertex buffer to draw a portion of our particles at a time.  The arbitrary
	// size we choose for the vertex buffer is specified by the _vbSize variable.

	_device = device; // save a ptr to the device

	HRESULT hr = 0;

	// 동적 버텍스 버퍼 이용
	hr = device->CreateVertexBuffer(
		_vbSize * sizeof(Particle),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		Particle::FVF,
		D3DPOOL_DEFAULT, // D3DPOOL_MANAGED can't be used with D3DUSAGE_DYNAMIC 
		&_vb,
		0);
	
	if(FAILED(hr))	{
		OutputDebugString("CreateVertexBuffer() - FAILED");
		return false;
	}

	_mtrl = d3d::WHITE_MTRL;
	_mtrl.Diffuse.a = 1.0f;

	hr = D3DXCreateTextureFromFile(
		device,
		texFileName,
		&_tex);

	if(FAILED(hr))	{
		OutputDebugString("D3DXCreateTextureFromFile() - FAILED");
		return false;
	}

	return true;
}

// 이 메서드는 시스템 내의 모든 파티클 속성을 리셋한다.
void CParticle::reset(){
	std::list<Attribute>::iterator i;
	for(i = _particles.begin(); i != _particles.end(); i++){
		resetParticle(&(*i));
	}
}

// 클래스에 파티클을 추가한다. 리스트에 추가히기 전에 파티클을 초기화
void CParticle::addParticle(){
	Attribute attribute;

	resetParticle(&attribute);

	_particles.push_back(attribute);
}

// 렌더링에 앞서 지정해야 할 초기 렌더 상태를 지정한다.
void CParticle::preRender(){
	// ZBuffer 연산 꺼줌
	_device->SetRenderState(D3DRS_ZENABLE,FALSE);
	_device->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);

	_device->SetRenderState(D3DRS_LIGHTING, true);

	_device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	_device->SetRenderState(D3DRS_SPECULARENABLE, true);

	_device->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	_device->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	_device->SetRenderState(D3DRS_POINTSIZE, d3d::FtoDw(_size));
	_device->SetRenderState(D3DRS_POINTSIZE_MIN, d3d::FtoDw(0.0f));

	// 알파채널1 = 난반사 컬러로 알파 지정
	// 알파채널2 = Texture 컬러로 알파 지정
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	
	// 두 알파채널을 곱하여 조정하여 최종 결과물 결정
	_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	

	// 거리에 따른 파티클의 크기를 제어한다.
	_device->SetRenderState(D3DRS_POINTSCALE_A, d3d::FtoDw(0.0f));
	_device->SetRenderState(D3DRS_POINTSCALE_B, d3d::FtoDw(0.0f));
	_device->SetRenderState(D3DRS_POINTSCALE_C, d3d::FtoDw(1.0f));

	// 블렌딩 인수를 지정하여 알파 성분이 투명도를 결정하도록 함
	_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
}

// 특정 파티클 클래스가 지정했을 수 있는 렌더 상태를 복구하는 데 이용된다.
void CParticle::postRender(){
	_device->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	_device->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

	// ZBuffer 연산 켜줌
	_device->SetRenderState(D3DRS_ZENABLE,D3DZB_TRUE);
	_device->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	_device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

// 현재 클래스에 파티클이 없는 경우 True를 리턴
bool CParticle::isEmpty(){
	return _particles.empty();
}

// 클래스 내의 파티클이 모두 죽은 경우 True를 리턴
// 죽은 상태는 파티클이 존재하지만 죽은 것으로 표시된 상태를 의미
bool CParticle::isDead(){
	std::list<Attribute>::iterator i;
	for(i = _particles.begin(); i != _particles.end(); i++)
	{
		// is there at least one living particle?  If yes,
		// the system is not dead.
		if( i->_isAlive )
			return false;
	}
	// no living particles found, the system must be dead.
	return true;
}

// 속성 리스트 _particle을 검색하여 죽은 파티클을 리스트에서 제거한다.
void CParticle::removeDeadParticles(){
	std::list<Attribute>::iterator i;

	i = _particles.begin();

	while(i != _particles.end()){
		if(i->_isAlive == false){
			// erase는 다음 반복자를 리턴하므로 우리가 반복자를 증가시킬 필요가 없다.
			i = _particles.erase(i);
		}
		else{
			i++;	// next in list
		}
	}
}

// 모든 파티클들 삭제
void CParticle::removeParticles(){
	std::list<Attribute>::iterator i;

	i = _particles.begin();

	while(i != _particles.end()){		
		i = _particles.erase(i);
	}
}

void CParticle::render(){
	if(!_particles.empty()){
		// 렌더 상태를 지정한다.
		preRender();

		_device->SetStreamSource(0, _vb, 0, sizeof(Particle));
		_device->SetFVF(Particle::FVF);
		_device->SetMaterial(&_mtrl);
		_device->SetTexture(0, _tex);		

		// 버텍스 버퍼를 벗어날 경우 처음부터 시작한다.
		if(_vbOffset >= _vbSize)
			_vbOffset = 0;

		Particle* v = 0;

		_vb->Lock(
			_vbOffset * sizeof(Particle),
			_vbBatchSize * sizeof(Particle),
			(void**)&v,
			_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

		DWORD numParticlesInBatch = 0;

		// 모든 파티클이 렌더링될 때까지
		std::list<Attribute>::iterator i;
		for(i = _particles.begin(); i != _particles.end(); i++){
			if(i->_isAlive){
				// 한 단계의 생존한 파티클을 다음 버텍스 버퍼 세그먼트로 복사한다.
				v->_position = i->_position;
				v->_color = (D3DXCOLOR)i->_color;
				v++;	// next element;
				numParticlesInBatch++;	// 단계 카운터를 증가시킨다.
			

				// 현재 단계가 모두 채워져 있는가?
				if(numParticlesInBatch == _vbBatchSize){
					// 버텍스 버퍼로 복사된 마지막 단계의 파티클을 그린다.
					_vb->Unlock();

					_device->DrawPrimitive(
						D3DPT_POINTLIST,
						_vbOffset,
						_vbBatchSize);

					// 단계가 그려지는 동안 다음 단계를 파티클로 채운다.

					// 다음 단계의 처음 오프셋으로 이동한다.
					_vbOffset += _vbBatchSize;

					// 버텍스 버퍼의 경계를 넘는 메모리로 오프셋을 설정하지 않는다.
					// 경계를 넘을 경우 처음부터 시작한다.
					if(_vbOffset >= _vbSize)
						_vbOffset = 0;

					_vb->Lock(
						_vbOffset * sizeof(Particle),
						_vbBatchSize * sizeof(Particle),
						(void**)&v,
						_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

					numParticlesInBatch = 0; // 다음 단계를 위한 리셋
				}//end if
			}//end if
		}//end for
		_vb->Unlock();

		//(numParticlesInBatch == _vbBatchSize) 조건이 만족되지 못하여
		// 마지막 단계가 렌더링되지 않는 경우가 발생할 수 있다. 일부만 채워진 단계는
		// 바로 이곳에서 렌더링된다.

		if(numParticlesInBatch){
			_device->DrawPrimitive(
				D3DPT_POINTLIST,
				_vbOffset,
				numParticlesInBatch);
		}

		// 다음 블록
		_vbOffset += _vbBatchSize;
		postRender();
	} // end if
} // end render()