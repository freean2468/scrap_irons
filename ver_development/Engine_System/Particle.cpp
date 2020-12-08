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

// ����Ʈ ��������Ʈ�� �����ϱ� ���� ���ؽ� ���۸� ����� �ؽ�ó�� ����� ����
// DIrect3D�� ��ġ �������� �ʱ�ȭ �۾��� ó���Ѵ�.
bool CParticle::init(IDirect3DDevice9* device, char* texFileName){
	// vertex buffer's size does not equal the number of particles in our system.  We
	// use the vertex buffer to draw a portion of our particles at a time.  The arbitrary
	// size we choose for the vertex buffer is specified by the _vbSize variable.

	_device = device; // save a ptr to the device

	HRESULT hr = 0;

	// ���� ���ؽ� ���� �̿�
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

// �� �޼���� �ý��� ���� ��� ��ƼŬ �Ӽ��� �����Ѵ�.
void CParticle::reset(){
	std::list<Attribute>::iterator i;
	for(i = _particles.begin(); i != _particles.end(); i++){
		resetParticle(&(*i));
	}
}

// Ŭ������ ��ƼŬ�� �߰��Ѵ�. ����Ʈ�� �߰����� ���� ��ƼŬ�� �ʱ�ȭ
void CParticle::addParticle(){
	Attribute attribute;

	resetParticle(&attribute);

	_particles.push_back(attribute);
}

// �������� �ռ� �����ؾ� �� �ʱ� ���� ���¸� �����Ѵ�.
void CParticle::preRender(){
	// ZBuffer ���� ����
	_device->SetRenderState(D3DRS_ZENABLE,FALSE);
	_device->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);

	_device->SetRenderState(D3DRS_LIGHTING, true);

	_device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	_device->SetRenderState(D3DRS_SPECULARENABLE, true);

	_device->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	_device->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	_device->SetRenderState(D3DRS_POINTSIZE, d3d::FtoDw(_size));
	_device->SetRenderState(D3DRS_POINTSIZE_MIN, d3d::FtoDw(0.0f));

	// ����ä��1 = ���ݻ� �÷��� ���� ����
	// ����ä��2 = Texture �÷��� ���� ����
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	
	// �� ����ä���� ���Ͽ� �����Ͽ� ���� ����� ����
	_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	

	// �Ÿ��� ���� ��ƼŬ�� ũ�⸦ �����Ѵ�.
	_device->SetRenderState(D3DRS_POINTSCALE_A, d3d::FtoDw(0.0f));
	_device->SetRenderState(D3DRS_POINTSCALE_B, d3d::FtoDw(0.0f));
	_device->SetRenderState(D3DRS_POINTSCALE_C, d3d::FtoDw(1.0f));

	// ���� �μ��� �����Ͽ� ���� ������ ������ �����ϵ��� ��
	_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
}

// Ư�� ��ƼŬ Ŭ������ �������� �� �ִ� ���� ���¸� �����ϴ� �� �̿�ȴ�.
void CParticle::postRender(){
	_device->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	_device->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

	// ZBuffer ���� ����
	_device->SetRenderState(D3DRS_ZENABLE,D3DZB_TRUE);
	_device->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	_device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

// ���� Ŭ������ ��ƼŬ�� ���� ��� True�� ����
bool CParticle::isEmpty(){
	return _particles.empty();
}

// Ŭ���� ���� ��ƼŬ�� ��� ���� ��� True�� ����
// ���� ���´� ��ƼŬ�� ���������� ���� ������ ǥ�õ� ���¸� �ǹ�
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

// �Ӽ� ����Ʈ _particle�� �˻��Ͽ� ���� ��ƼŬ�� ����Ʈ���� �����Ѵ�.
void CParticle::removeDeadParticles(){
	std::list<Attribute>::iterator i;

	i = _particles.begin();

	while(i != _particles.end()){
		if(i->_isAlive == false){
			// erase�� ���� �ݺ��ڸ� �����ϹǷ� �츮�� �ݺ��ڸ� ������ų �ʿ䰡 ����.
			i = _particles.erase(i);
		}
		else{
			i++;	// next in list
		}
	}
}

// ��� ��ƼŬ�� ����
void CParticle::removeParticles(){
	std::list<Attribute>::iterator i;

	i = _particles.begin();

	while(i != _particles.end()){		
		i = _particles.erase(i);
	}
}

void CParticle::render(){
	if(!_particles.empty()){
		// ���� ���¸� �����Ѵ�.
		preRender();

		_device->SetStreamSource(0, _vb, 0, sizeof(Particle));
		_device->SetFVF(Particle::FVF);
		_device->SetMaterial(&_mtrl);
		_device->SetTexture(0, _tex);		

		// ���ؽ� ���۸� ��� ��� ó������ �����Ѵ�.
		if(_vbOffset >= _vbSize)
			_vbOffset = 0;

		Particle* v = 0;

		_vb->Lock(
			_vbOffset * sizeof(Particle),
			_vbBatchSize * sizeof(Particle),
			(void**)&v,
			_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

		DWORD numParticlesInBatch = 0;

		// ��� ��ƼŬ�� �������� ������
		std::list<Attribute>::iterator i;
		for(i = _particles.begin(); i != _particles.end(); i++){
			if(i->_isAlive){
				// �� �ܰ��� ������ ��ƼŬ�� ���� ���ؽ� ���� ���׸�Ʈ�� �����Ѵ�.
				v->_position = i->_position;
				v->_color = (D3DXCOLOR)i->_color;
				v++;	// next element;
				numParticlesInBatch++;	// �ܰ� ī���͸� ������Ų��.
			

				// ���� �ܰ谡 ��� ä���� �ִ°�?
				if(numParticlesInBatch == _vbBatchSize){
					// ���ؽ� ���۷� ����� ������ �ܰ��� ��ƼŬ�� �׸���.
					_vb->Unlock();

					_device->DrawPrimitive(
						D3DPT_POINTLIST,
						_vbOffset,
						_vbBatchSize);

					// �ܰ谡 �׷����� ���� ���� �ܰ踦 ��ƼŬ�� ä���.

					// ���� �ܰ��� ó�� ���������� �̵��Ѵ�.
					_vbOffset += _vbBatchSize;

					// ���ؽ� ������ ��踦 �Ѵ� �޸𸮷� �������� �������� �ʴ´�.
					// ��踦 ���� ��� ó������ �����Ѵ�.
					if(_vbOffset >= _vbSize)
						_vbOffset = 0;

					_vb->Lock(
						_vbOffset * sizeof(Particle),
						_vbBatchSize * sizeof(Particle),
						(void**)&v,
						_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

					numParticlesInBatch = 0; // ���� �ܰ踦 ���� ����
				}//end if
			}//end if
		}//end for
		_vb->Unlock();

		//(numParticlesInBatch == _vbBatchSize) ������ �������� ���Ͽ�
		// ������ �ܰ谡 ���������� �ʴ� ��찡 �߻��� �� �ִ�. �Ϻθ� ä���� �ܰ��
		// �ٷ� �̰����� �������ȴ�.

		if(numParticlesInBatch){
			_device->DrawPrimitive(
				D3DPT_POINTLIST,
				_vbOffset,
				numParticlesInBatch);
		}

		// ���� ���
		_vbOffset += _vbBatchSize;
		postRender();
	} // end if
} // end render()