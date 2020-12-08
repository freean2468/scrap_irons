////////////////////////////////////////////////////////////////
// 파티클 클래스
// 임의의 파티클을 만들 때는 이 클래스를 상속해서 만든다.
// 모든 기능이 갖춰진 것이 아니므로 만들려는 파티클에 따라 커스텀해야 할 수 있음
// 용책 참고
////////////////////////////////////////////////////////////////
#ifndef _Particle_H_
#define _Particle_H_

struct Particle{
	D3DXVECTOR3 _position;
	D3DXCOLOR _color;
	static const DWORD FVF;
};

struct Attribute{
	D3DXVECTOR3 _position;		// 월드 스페이스 내의 파티클 위치
	D3DXVECTOR3 _velocity;		// 파티클의 속도, 보통은 초당 이동 단위로 기록한다.
	D3DXVECTOR3 _acceleration;	// 파티클의 가속, 보통은 초당 이동 단위로 기록한다.
	float		_lifeTime;		// 파티클이 소멸할 때까지 유지되는 시간
	float		_age;			// 파티클의 현재 나이
	D3DXCOLOR	_color;			// 파티클의 컬러
	D3DXCOLOR	_colorFade;		// 파티클의 컬러가 시간의 흐름에 따라 퇴색하는 방법
	bool		_isAlive;		// 파티클이 생존한 경우 True, 소멸한 경우 False
};

class CParticle{
protected:
	IDirect3DDevice9*		_device;
	D3DXVECTOR3				_origin;		// 클래스의 원천. 시스템 내에서 파티클이 시작되는 것
	d3d::BoundingBox		_boundingBox;	// 경계 상자는 파티클이 이동할 수 있는 부피를 제한하는 데 이용된다.
	float					_emitRate;		// 클래스에 새로운 파티클이 추가되는 비율. 보통은 초당 파티클 수로 기록
	float					_size;			// 클래스 내 모든 파티클의 크기
	IDirect3DTexture9*		_tex;
	IDirect3DVertexBuffer9*	_vb;
	D3DMATERIAL9			_mtrl;
	std::list<Attribute>	_particles;		// 시스템 내 파티클 속성의 리스트 (파티클을 만들고 제거하고 갱신하는 데 이 리스트를 이용
	int						_maxParticles;	// 주어진 시간 동안 클래스가 가질 수 있는 최대 파티클의 수

	DWORD _vbSize;			// 버텍스 버퍼가 보관할 수 있는 파티클의 수. 실제 파티클 클래스 내의 파티클 수와는 독립적
	DWORD _vbOffset;		// 버텍스 버퍼에서 복사를 시작할 파티클 내 다음 단계로의오브셋(파티클 단위)
	DWORD _vbBatchSize;		// 하나의 단계에 정의된 파티클의 수

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