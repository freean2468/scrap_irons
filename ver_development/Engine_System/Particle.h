////////////////////////////////////////////////////////////////
// ��ƼŬ Ŭ����
// ������ ��ƼŬ�� ���� ���� �� Ŭ������ ����ؼ� �����.
// ��� ����� ������ ���� �ƴϹǷ� ������� ��ƼŬ�� ���� Ŀ�����ؾ� �� �� ����
// ��å ����
////////////////////////////////////////////////////////////////
#ifndef _Particle_H_
#define _Particle_H_

struct Particle{
	D3DXVECTOR3 _position;
	D3DXCOLOR _color;
	static const DWORD FVF;
};

struct Attribute{
	D3DXVECTOR3 _position;		// ���� �����̽� ���� ��ƼŬ ��ġ
	D3DXVECTOR3 _velocity;		// ��ƼŬ�� �ӵ�, ������ �ʴ� �̵� ������ ����Ѵ�.
	D3DXVECTOR3 _acceleration;	// ��ƼŬ�� ����, ������ �ʴ� �̵� ������ ����Ѵ�.
	float		_lifeTime;		// ��ƼŬ�� �Ҹ��� ������ �����Ǵ� �ð�
	float		_age;			// ��ƼŬ�� ���� ����
	D3DXCOLOR	_color;			// ��ƼŬ�� �÷�
	D3DXCOLOR	_colorFade;		// ��ƼŬ�� �÷��� �ð��� �帧�� ���� ����ϴ� ���
	bool		_isAlive;		// ��ƼŬ�� ������ ��� True, �Ҹ��� ��� False
};

class CParticle{
protected:
	IDirect3DDevice9*		_device;
	D3DXVECTOR3				_origin;		// Ŭ������ ��õ. �ý��� ������ ��ƼŬ�� ���۵Ǵ� ��
	d3d::BoundingBox		_boundingBox;	// ��� ���ڴ� ��ƼŬ�� �̵��� �� �ִ� ���Ǹ� �����ϴ� �� �̿�ȴ�.
	float					_emitRate;		// Ŭ������ ���ο� ��ƼŬ�� �߰��Ǵ� ����. ������ �ʴ� ��ƼŬ ���� ���
	float					_size;			// Ŭ���� �� ��� ��ƼŬ�� ũ��
	IDirect3DTexture9*		_tex;
	IDirect3DVertexBuffer9*	_vb;
	D3DMATERIAL9			_mtrl;
	std::list<Attribute>	_particles;		// �ý��� �� ��ƼŬ �Ӽ��� ����Ʈ (��ƼŬ�� ����� �����ϰ� �����ϴ� �� �� ����Ʈ�� �̿�
	int						_maxParticles;	// �־��� �ð� ���� Ŭ������ ���� �� �ִ� �ִ� ��ƼŬ�� ��

	DWORD _vbSize;			// ���ؽ� ���۰� ������ �� �ִ� ��ƼŬ�� ��. ���� ��ƼŬ Ŭ���� ���� ��ƼŬ ���ʹ� ������
	DWORD _vbOffset;		// ���ؽ� ���ۿ��� ���縦 ������ ��ƼŬ �� ���� �ܰ���ǿ����(��ƼŬ ����)
	DWORD _vbBatchSize;		// �ϳ��� �ܰ迡 ���ǵ� ��ƼŬ�� ��

public:
	CParticle();
	virtual ~CParticle();

	virtual bool init(IDirect3DDevice9* device, char* texFileName);
	virtual void reset();
	virtual void resetParticle(Attribute* attribute) = 0;
	virtual void removeParticles();
	virtual void addParticle();
	virtual void update(float timeDelta) = 0;

	virtual void preRender();
	virtual void render();
	virtual void postRender();

	bool isEmpty();
	bool isDead();

protected:
	virtual void removeDeadParticles();
};

#endif