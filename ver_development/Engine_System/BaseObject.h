//////////////////////////////////////////////////////
// ���� ������Ʈ���� ���� �κ��� ��� �ִ� ���� Ŭ����
//////////////////////////////////////////////////////
#ifndef _BaseObject_H_
#define _BaseObject_H_

class CBaseObject : public CBaseGameEntity{
public:
	typedef enum Direction {RIGHT = 0, LEFT} DIRECTION;				// ����
	typedef enum Owner {SMALLINFO = -12, COMMANDER, AREA, PRODUCING, BLUEPRINTSCROLL, BLUEPRINTLIST, INVENTORY, INTERACT, PRODUCTION, EVENT, BGEFFECT, ITEM, 
		BASE=0, BG, LOGO, MAINMENU, WORLDMAP, STAGEHOME,STAGEMOUNTAIN, STAGEFURNACE, STAGECHIMNEY, STAGEDUSTBRIDGE, STAGEGOODHOPE, INTRO,
		HERO = 20, CART, FLOWER, 
		WAGOO=30, WOOWO, YAWO, KIRIT, TINKLE,
		ENEMY = 50, WORKER, DUSTKID, MINIWORKER, GATEKEEPER, DUSTKING} OWNER;	// ������

protected:
	// �������̽� ���� ����
	IDirect3DDevice9* _pDevice;				// ��ġ �������̽� ������
	CArray2D<IDirect3DTexture9*> _pTexture;	// ������Ʈ �ؽ�ó(�̹���) ������
	CArray2D<D3DMATERIAL9> _Mtrl;			// ������Ʈ ���� ������
	IDirect3DVertexBuffer9* _pQuad;			// ���ؽ� ����
	IDirect3DIndexBuffer9* _pIndex;			// �ε��� ����

	// Object ��ġ ���� ����
	D3DXMATRIX _matWorld;	// ���� ���

	D3DXVECTOR3 _vPos;			// ��ġ ����
	D3DXMATRIXA16 _pos;			// ��ġ ��ȯ ���
	D3DXVECTOR3 _vScale;		// ũ�� ����
	D3DXMATRIXA16 _scale;		// ũ�� ��ȯ ���
	D3DXMATRIXA16 _rotation;	// ȸ�� ��ȯ ���
	D3DXVECTOR3 _vRotate;		// ȸ�� ����

	// Object ������ ���� ����
	RECT _TextureRect;				// �ؽ�ó �簢����	
	float _width, _height;
	float _widthHalf, _heightHalf;

	// Object �ִϸ��̼� ���� ����
	int _col;				// (��)����,�ൿ �ε���
	int _row;				// (��)����,���� �ε���
	DWORD _dwDelaytime;		// �����Ӱ���
	CTimer _timer;			// �ð� Ŭ����

	// Object ���� ���� ���� ����
	OWNER _owner;
	int AttType;

public:
	CBaseObject(int id);
	virtual ~CBaseObject();

	////////////////////////////////////////////////
	// �⺻ ���� �Լ�
	virtual bool InitObject(IDirect3DDevice9* device, char* texFileName, int width, int height, float fAlpha, int action);
	virtual void Render();
	virtual void preRender();
	virtual void postRender();
//	virtual void Animation();

	virtual void Move(float x, float y);

	////////////////////////////////////////////////
	// Set�Լ�
	virtual void SetRow(DIRECTION dir){_row = dir;}
	virtual void SetCol(int width){_col = width;}
	virtual void SetPos(D3DXVECTOR3 _vec){_vPos = _vec;}
	virtual void SetOwner(OWNER p_owner){_owner = p_owner;}

	////////////////////////////////////////////////
	// Get�Լ�
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