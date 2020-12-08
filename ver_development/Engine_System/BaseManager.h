/////////////////////////////////////////////////////
// CBaseManager클래스는 이 엔진의 시스템을 총괄함
////////////////////////////////////////////////////

#ifndef _BaseManager_H_
#define _BaseManager_H_

class CBaseManager{
private:
	// Application Class app는 어플리케이션을 다루는 클래스이기에 랩 할 수가 없다.

	//////////////////////////////////////////////////////////
	//BM 변수
	//////////////////////////////////////////////////////////
	HWND		_hWnd;		// 응용 프로그램의 메인 윈도우 객체를 가리킨다.

	IDirect3DDevice9* Device;	// 장치 인터페이스 변수

	ID3DXFont*	_pFont;		// 폰트 인터페이스 변수
	ID3DXSprite* _pSprite;	// 스프라이트 인터페이스 변수

	////////////////////////////////////////////////////////////
	//BM 랩 클래스
	////////////////////////////////////////////////////////////
	// 정보 계산 및 출력 담당(Debug용)
	CInformation* Info;

	// 시스템 프레임 담당
	CSystemFrame* Frame;

	// 지형 담당
	CTerrain* Terrain;

	// 파티클(눈) 담당
	CParticle* Snow;
	// 파티클(먼지) 담당
	CParticle* Dirt;
	// 파티클(폭죽) 담당
	CParticle* Firework;
	// 파티클(건) 담당
	CParticle* Gun;
	// 파티클(매연) 담당
	CDLinkedList<CParticle*> ExhaustList;
	// 파티클(불씨) 담당
	CParticle* Kindling;

	// 마우스 상태 1 = Up, 0 = Down->Up, -1 = Down
	int _nLButtonState;

    // 생성자와 소멸자를 복사하고 할당은 private이어야 한다.
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
	// CBaseManager 클래스 제공 함수
	//////////////////////////////////////////////////
	void Initialize();
	void UpdateExhaust();
	void RenderExhaust();
	void DeleteExhaust();
	void Loading();

	//////////////////////////////////////////////////
	// BaseManager wrap 클래스 Set 함수 wrap 함수
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
	// BaseManager 랩 클래스 Set 함수
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
	// BaseManager 랩 클래스 Get 함수
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
	// 변수 Get 함수
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
	// 변수 Set 함수
	///////////////////////////////////////////////////
	void Sethwnd(HWND hWnd){_hWnd = hWnd;}
	void SetpDevice(IDirect3DDevice9* _device){Device = _device;}
	void SetLButtonState(int p_nTemp){_nLButtonState = p_nTemp;}
};

// CBaseManager의 인스턴스를 쉽게 접근할 수 있는 방법을 제공한다.
#define EngineMgr CBaseManager::Instance()

#endif