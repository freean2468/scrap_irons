#include "../BaseHeader.h"

// 생성자에서는 초기화만을 담당한다.
CBaseManager::CBaseManager(){
	Device = 0;

	_pFont = 0;
	_pSprite = 0;

	Info = 0;
	Frame = 0;
	Terrain = 0;
	Snow = 0;
	Firework = 0;
	Dirt = 0;
	Gun = 0;

	_nLButtonState = -1;
}

CBaseManager::~CBaseManager(){
	// Device는 어플리케이션에서 해제한다.
	// 해제 순서는 생성 순서의 반대로(스택)
	d3d::Delete<CParticle*>( Gun );
	d3d::Delete<CParticle*>( Firework );
	d3d::Delete<CParticle*>( Snow );
	
	d3d::Delete<CTerrain*>( Terrain );
	d3d::Delete<CSystemFrame*>( Frame );
	//  해제를 하려 하면 오류가 뜬다.
//	d3d::Delete<CInformation*>( Info );

	d3d::Release<ID3DXSprite*>(GetpSprite());
	d3d::Release<ID3DXFont*>(GetpFont());
}

void CBaseManager::Loading(){
	d3d::SetupMatrices();

	AppMgr->PreRendering();

	GetpSprite()->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE); // 3D 공간상에 텍스트 출력

	D3DXMATRIXA16 _rotation;	// 회전 변환 행렬
	D3DXVECTOR3 _vRotate;		// 회전 벡터

	D3DXMATRIXA16 mtMatrix;
	D3DXMatrixIdentity(&mtMatrix);

	D3DXMATRIXA16 rX;
	D3DXMatrixIdentity(&rX);
	D3DXMatrixRotationX(&rX, D3DX_PI);
	_rotation = rX;

	mtMatrix *= _rotation;

	GetpSprite()->SetTransform(&mtMatrix);

	RECT rect;

	rect.right = SYSTEMWIDTH/2 - 70;
	rect.left = -SYSTEMWIDTH/2;
	rect.top = -SYSTEMHEIGHT/2;
	rect.bottom = SYSTEMHEIGHT/2 - 50;

	// Text 출력     
	_pFont->DrawText(GetpSprite(), "Loading...", -1, &rect, DT_RIGHT | DT_BOTTOM , 0xff000000);

	GetpSprite()->End();

	// 월드 좌표를 원점으로 되돌린다.
	D3DXMatrixIdentity(&mtMatrix);
	GetpSprite()->SetTransform(&mtMatrix);

	AppMgr->PostRendering();
}

// 초기화&셋팅 함수
void CBaseManager::Initialize(){
	// 폰트 설정
	_pFont = d3d::IniFont(17, 10, 500, false, "Times New Roman");

	// 스프라이트 생성
	D3DXCreateSprite(GetpDevice(), GetppSprite() );

	Loading();

	// SetInformation
	SetInfo();

	// SetSystemFrame
	SetFrame();
	
	// SetTerrain
//	SetTerrain();

	// SetParticle(Snow)
//	SetSnow();

	// SetParticle(Firework)
//	SetFireWork();

	// SetParticle(ParticleGun)
//	SetParticleGun();
}

void CBaseManager::SetInfo(){
	this->SetCInformation(new CInformation());
}

void CBaseManager::SetFrame(){
	this->SetCSystemFrame(new CSystemFrame());

	this->GetpSystemFrame()->SetFramePerSec(60.0f);
}

void CBaseManager::SetTerrain(){
	D3DXVECTOR3 lightDirection(0.0f, 1.0f, 0.0f);

	this->SetCTerrain(new CTerrain(GetpDevice(), "./Image/coastMountain64.raw", 64, 64, 10, 1.0f));
	this->GetpTerrain()->genTexture(&lightDirection);
}

void CBaseManager::SetSnow(){
	d3d::BoundingBox boundingBox;
	boundingBox._min = D3DXVECTOR3(-500.0f, -400.0f, -100.0f);
	boundingBox._max = D3DXVECTOR3( 2500.0,  400.0f,  -50.0f);

	this->SetCSnow(new CSnow(&boundingBox, 50));
	this->GetpSnow()->init(GetpDevice(), "./Image/Particle/snowflake.dds");
}

void CBaseManager::SetDirt(float fMinX, float fMinY, float fMinZ, float fMaxX, float fMaxY, float fMaxZ, int numParticles){
	d3d::BoundingBox boundingBox;
	boundingBox._min = D3DXVECTOR3(fMinX, fMinY, fMinZ);
	boundingBox._max = D3DXVECTOR3(fMaxX, fMaxY, fMaxZ);

	SetCDirt(new CDirt(&boundingBox, numParticles));	
}

void CBaseManager::SetKindling(float fMinX, float fMinY, float fMinZ, float fMaxX, float fMaxY, float fMaxZ, int numParticles){
	d3d::BoundingBox boundingBox;
	boundingBox._min = D3DXVECTOR3(fMinX, fMinY, fMinZ);
	boundingBox._max = D3DXVECTOR3(fMaxX, fMaxY, fMaxZ);

	SetCKindling(new CKindling(&boundingBox, numParticles));	
}

void CBaseManager::SetExhaust(D3DXVECTOR3 origin, float fMinX, float fMinY, float fMinZ, float fMaxX, float fMaxY, float fMaxZ, int numParticles){
	d3d::BoundingBox boundingBox;
	boundingBox._min = D3DXVECTOR3(fMinX, fMinY, fMinZ);
	boundingBox._max = D3DXVECTOR3(fMaxX, fMaxY, fMaxZ);

	ExhaustList.Append(new CExhaust(&boundingBox, &origin, numParticles));
}

void CBaseManager::UpdateExhaust(){
	// 반복자 생성
	CDListIterator<CParticle*> itr;
	
	// ExhaustList로부터 반복자 초기화
	itr = ExhaustList.GetIterator();
	
	// ExhaustList를 훑으며
	for(itr.Start(); itr.Valid(); itr.Forth()){
		itr.Item()->update(EngineMgr->GetTimeDelta());
	}
}

void CBaseManager::RenderExhaust(){
	// 반복자 생성
	CDListIterator<CParticle*> itr;
	
	// ExhaustList로부터 반복자 초기화
	itr = ExhaustList.GetIterator();
	
	// ExhaustList를 훑으며
	for(itr.Start(); itr.Valid(); itr.Forth()){
		itr.Item()->render();
	}
}

void CBaseManager::DeleteExhaust(){
	// 반복자 생성
	CDListIterator<CParticle*> itr;
	
	// ExhaustList로부터 반복자 초기화
	itr = ExhaustList.GetIterator();
	
	// ExhaustList를 훑으며
	for(itr.Start(); itr.Valid();){
		d3d::Delete<CParticle*>(itr.Item());
		ExhaustList.Remove(itr);
	}
}

void CBaseManager::SetFireWork(){
	D3DXVECTOR3 origin(float(rand()%10), float(rand()%10), float(rand()%20+50));

	this->SetCFireWork(new CFirework(&origin, 3000));
	this->GetpFirework()->init(GetpDevice(), "./Image/flare.bmp");
}

void CBaseManager::SetParticleGun(){
	this->SetCParticleGun(new CParticleGun( CameraMgr->GetCamera() ));
	this->GetpGun()->init(GetpDevice(), "./Image/flare_alpha.dds");
}