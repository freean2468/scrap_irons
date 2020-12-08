//////////////////////////////////////////////////////
// 각종 오브젝트들의 공통 부분을 담고 있는 조상 클래스
//////////////////////////////////////////////////////
#ifndef _BaseObject_H_
#define _BaseObject_H_

class CBaseObject : public CBaseGameEntity{
public:
	typedef enum Direction {RIGHT = 0, LEFT} DIRECTION;				// 방향
	typedef enum Owner {SMALLINFO = -12, COMMANDER, AREA, PRODUCING, BLUEPRINTSCROLL, BLUEPRINTLIST, INVENTORY, INTERACT, PRODUCTION, EVENT, BGEFFECT, ITEM, 
		BASE=0, BG, LOGO, MAINMENU, WORLDMAP, STAGEHOME,STAGEMOUNTAIN, STAGEFURNACE, STAGECHIMNEY, STAGEDUSTBRIDGE, STAGEGOODHOPE, INTRO,
		HERO = 20, CART, FLOWER, 
		WAGOO=30, WOOWO, YAWO, KIRIT, TINKLE,
		ENEMY = 50, WORKER, DUSTKID, MINIWORKER, GATEKEEPER, DUSTKING} OWNER;	// 소유자

protected:
	// 인터페이스 관련 변수
	IDirect3DDevice9* _pDevice;				// 장치 인터페이스 포인터
	CArray2D<IDirect3DTexture9*> _pTexture;	// 오브젝트 텍스처(이미지) 포인터
	CArray2D<D3DMATERIAL9> _Mtrl;			// 오브젝트 재질 포인터
	IDirect3DVertexBuffer9* _pQuad;			// 버텍스 버퍼
	IDirect3DIndexBuffer9* _pIndex;			// 인덱스 버퍼

	// Object 위치 관련 변수
	D3DXMATRIX _matWorld;	// 월드 행렬

	D3DXVECTOR3 _vPos;			// 위치 벡터
	D3DXMATRIXA16 _pos;			// 위치 변환 행렬
	D3DXVECTOR3 _vScale;		// 크기 벡터
	D3DXMATRIXA16 _scale;		// 크기 변환 행렬
	D3DXMATRIXA16 _rotation;	// 회전 변환 행렬
	D3DXVECTOR3 _vRotate;		// 회전 벡터

	// Object 데이터 관련 변수
	RECT _TextureRect;				// 텍스처 사각영역	
	float _width, _height;
	float _widthHalf, _heightHalf;

	// Object 애니메이션 관련 변수
	int _col;				// (열)가로,행동 인덱스
	int _row;				// (행)세로,방향 인덱스
	DWORD _dwDelaytime;		// 프레임간격
	CTimer _timer;			// 시간 클래스

	// Object 게임 정보 관련 변수
	OWNER _owner;
	int AttType;

public:
	CBaseObject(int id);
	virtual ~CBaseObject();

	////////////////////////////////////////////////
	// 기본 공통 함수
	virtual bool InitObject(IDirect3DDevice9* device, char* texFileName, int width, int height, float fAlpha, int action);
	virtual void Render();
	virtual void preRender();
	virtual void postRender();
//	virtual void Animation();

	virtual void Move(float x, float y);

	////////////////////////////////////////////////
	// Set함수
	virtual void SetRow(DIRECTION dir){_row = dir;}
	virtual void SetCol(int width){_col = width;}
	virtual void SetPos(D3DXVECTOR3 _vec){_vPos = _vec;}
	virtual void SetOwner(OWNER p_owner){_owner = p_owner;}

	////////////////////////////////////////////////
	// Get함수
	virtual int GetRow(){return _row;}
	virtual int GetCol(){return _col;}
	virtual CArray2D<D3DMATERIAL9>* GetMtrlArray(){return &_Mtrl;}
	virtual D3DXVECTOR3 GetPos(){return _vPos;}
	virtual D3DXMATRIX GetMatWorld(){return _matWorld;}
	virtual OWNER GetOwner(){return _owner;}
	virtual IDirect3DDevice9* GetpDevice(){return _pDevice;}
	virtual float GetWidth(){return _width;}
	virtual float GetHeight(){return _height;}
	virtual float GetWidthHalf(){return _widthHalf;}
	virtual float GetHeightHalf(){return _heightHalf;}
};

#endif