/////////////////////////////////////////////////////
// CBaseManagerŬ������ �� ������ �ý����� �Ѱ���
////////////////////////////////////////////////////

#ifndef _BaseManager_H_
#define _BaseManager_H_

class CBaseManager{
private:
	// Application Class app�� ���ø����̼��� �ٷ�� Ŭ�����̱⿡ �� �� ���� ����.

	//////////////////////////////////////////////////////////
	//BM ����
	//////////////////////////////////////////////////////////
	HWND		_hWnd;		// ���� ���α׷��� ���� ������ ��ü�� ����Ų��.

	IDirect3DDevice9* Device;	// ��ġ �������̽� ����

	ID3DXFont*	_pFont;		// ��Ʈ �������̽� ����
	ID3DXSprite* _pSprite;	// ��������Ʈ �������̽� ����

	////////////////////////////////////////////////////////////
	//BM �� Ŭ����
	////////////////////////////////////////////////////////////
	// ���� ��� �� ��� ���(Debug��)
	CInformation* Info;

	// �ý��� ������ ���
	CSystemFrame* Frame;

	// ���� ���
	CTerrain* Terrain;

	// ��ƼŬ(��) ���
	CParticle* Snow;
	// ��ƼŬ(����) ���
	CParticle* Dirt;
	// ��ƼŬ(����) ���
	CParticle* Firework;
	// ��ƼŬ(��) ���
	CParticle* Gun;
	// ��ƼŬ(�ſ�) ���
	CDLinkedList<CParticle*> ExhaustList;
	// ��ƼŬ(�Ҿ�) ���
	CParticle* Kindling;

	// ���콺 ���� 1 = Up, 0 = Down->Up, -1 = Down
	int _nLButtonState;

    // �����ڿ� �Ҹ��ڸ� �����ϰ� �Ҵ��� private�̾�� �Ѵ�.
	CBaseManager(const CBaseManager&);
	CBaseManager& operator=(const CBaseManager&);
public:
	CBaseManager();
	~CBaseManager();

	static CBaseManager* Instance(){
		 static CBaseManager instance;

		 return &instance;
	}

	///////////////////////////////////////////////////
	// CBaseManager Ŭ���� ���� �Լ�
	//////////////////////////////////////////////////
	void Initialize();
	void UpdateExhaust();
	void RenderExhaust();
	void DeleteExhaust();
	void Loading();

	//////////////////////////////////////////////////
	// BaseManager wrap Ŭ���� Set �Լ� wrap �Լ�
	//////////////////////////////////////////////////
	void SetInfo();
	void SetFrame();
	void SetTerrain();
	void SetSnow();
	void SetDirt(float fMinX, float fMinY, float fMinZ, float fMaxX, float fMaxY, float fMaxZ, int numParticles);
	void SetKindling(float fMinX, float fMinY, float fMinZ, float fMaxX, float fMaxY, float fMaxZ, int numParticles);
	void SetExhaust(D3DXVECTOR3 origin, float fMinX, float fMinY, float fMinZ, float fMaxX, float fMaxY, float fMaxZ, int numParticles);
	void SetFireWork();
	void SetParticleGun();
	void SetSound();

	///////////////////////////////////////////////////
	// BaseManager �� Ŭ���� Set �Լ�
	///////////////////////////////////////////////////
	void SetCInformation(CInformation* _info){Info = _info;}
	void SetCSystemFrame(CSystemFrame* _frame){Frame = _frame;}
	void SetCTerrain(CTerrain* _terrain){Terrain = _terrain;}
	void SetCSnow(CParticle* _snow){Snow = _snow;}
	void SetCDirt(CParticle* _dirt){Dirt = _dirt;}
	void SetCKindling(CParticle* _kindling){Kindling = _kindling;}
	void SetCFireWork(CParticle* _fire){Firework = _fire;}
	void SetCParticleGun(CParticle* _gun){Gun = _gun;};

	///////////////////////////////////////////////////
	// BaseManager �� Ŭ���� Get �Լ�
	///////////////////////////////////////////////////
	CInformation* GetpInformation(){return Info;}
	CSystemFrame* GetpSystemFrame(){return Frame;}
	CTerrain* GetpTerrain(){return Terrain;}
	CParticle* GetpSnow(){return Snow;}
	CParticle* GetpDirt(){return Dirt;}
	CParticle* GetpKindling(){return Kindling;}
	CDLinkedList<CParticle*> GetpExhaust(){return ExhaustList;}
	CParticle* GetpFirework(){return Firework;}
	CParticle* GetpGun(){return Gun;}

	///////////////////////////////////////////////////
	// ���� Get �Լ�
	///////////////////////////////////////////////////
	IDirect3DDevice9*	GetpDevice(){return Device;}	
	IDirect3DDevice9**	GetppDevice(){return &Device;}
	ID3DXFont* GetpFont(){return _pFont;}
	ID3DXSprite* GetpSprite(){return _pSprite;}
	ID3DXSprite** GetppSprite(){return &_pSprite;}
	HWND	Gethwnd(){return _hWnd;}
	float GetTimeDelta(){return Frame->GetTimeDeltaOfOrigin();}
	float GetAdjustedTimeDelta(){return Frame->GetAdjustedTimeDelta();}
	int GetLButtonState(){return _nLButtonState;}

	///////////////////////////////////////////////////
	// ���� Set �Լ�
	///////////////////////////////////////////////////
	void Sethwnd(HWND hWnd){_hWnd = hWnd;}
	void SetpDevice(IDirect3DDevice9* _device){Device = _device;}
	void SetLButtonState(int p_nTemp){_nLButtonState = p_nTemp;}
};

// CBaseManager�� �ν��Ͻ��� ���� ������ �� �ִ� ����� �����Ѵ�.
#define EngineMgr CBaseManager::Instance()

#endif