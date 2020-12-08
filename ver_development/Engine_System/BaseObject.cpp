#include "../BaseHeader.h"

CBaseObject::CBaseObject(int id):CBaseGameEntity(id){
	// 인터페이스 관련 변수
	_pDevice = EngineMgr->GetpDevice();
	_pTexture.Resize(0, 1);	
	_Mtrl.Resize(0, 1);
	for(int i = 0; i < _pTexture.GetHeight();i++)
		for(int j = 0; j < _pTexture.GetWidth();j++)
			_pTexture.Get(i,j) = NULL;

	for(int i = 0; i < _Mtrl.GetHeight();i++)
		for(int j = 0; j < _Mtrl.GetWidth();j++)
			_Mtrl.Get(i,j) = d3d::WHITE_MTRL;
	
	_pQuad = NULL;
	_pIndex = NULL;

	// Object 위치 관련 변수
	D3DXMatrixIdentity(&_matWorld);
	_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 위치 벡터
	_vScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		// 크기 벡터
	_vRotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 회전 벡터

	// Object 데이터 관련 변수
	_width = 0;
	_height = 0;

	// Object 애니메이션 관련 변수
	_dwDelaytime = 0;
	_col = CBaseObject::RIGHT;
	_row = CBaseObject::RIGHT;

	// Object 게임 정보 관련 변수
	_owner = BASE;
}

CBaseObject::~CBaseObject(){
	for(int i = 0; i < _pTexture.GetHeight(); i++){
		for(int j = 0; j < _pTexture.GetWidth(); j++){
			d3d::Release<IDirect3DTexture9*>(_pTexture.Get(i,j));
		}
	}
	d3d::Release<IDirect3DVertexBuffer9*>(_pQuad);
	d3d::Release<IDirect3DIndexBuffer9*>(_pIndex);
}

// 이미지를 불러오며 장치 인터페이스와 스프라이트 인터페이스를 적재한다.
bool CBaseObject::InitObject(IDirect3DDevice9* device, char* texFileName, int width, int height, float fAlpha, int action){
	_pDevice = device;
	_width = (float)width;
	_height = (float)height;
	_widthHalf = width/2.0f;
	_heightHalf = height/2.0f;

	// 재질&텍스처 배열이 꽉찼다면 자리를 만든다.
	_pTexture.FullArray(0, action);
	_Mtrl.FullArray(0, action);

	// 800 : 1 카메라 비율
	// width : x 이미지 비율
	// = width / 800
//	float x;
//	float y;

	// 3D 카메라와 좌표계를 맞추기 위한 비율 연산
//	x = width/((float)SYSTEMHEIGHT-30);
//	y = height/((float)SYSTEMHEIGHT-30);

	float fHalfWidth = width / 2.0f;//x / (float)2;
	float fHalfHeight = height / 2.0f;//y / (float)2;

	// 버텍스 버퍼 생성
	_pDevice->CreateVertexBuffer(
		6 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&_pQuad,
		0);

	// 인덱스 버퍼 생성
	_pDevice->CreateIndexBuffer(
		6 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&_pIndex,
		0);

	// 두 개의 삼각형으로 구성된 사각형,
	// BG의 경우 출력 좌표를 카메라 좌표에서 시작하도록 한다.
	if(this->GetOwner() == BG){
		Vertex* v = 0;

		_pQuad->Lock(0, 0, (void**)&v, 0);

		v[0] = Vertex(-SYSTEMWIDTH/2.0f, -fHalfHeight, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
		v[1] = Vertex(-SYSTEMWIDTH/2.0f,  fHalfHeight, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
		v[2] = Vertex( width - SYSTEMWIDTH/2.0f,  fHalfHeight, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
		v[3] = Vertex(-SYSTEMWIDTH/2.0f, -fHalfHeight, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
		v[4] = Vertex( width - SYSTEMWIDTH/2.0f,  fHalfHeight, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
		v[5] = Vertex( width - SYSTEMWIDTH/2.0f, -fHalfHeight, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
		
		_pQuad->Unlock();	
	}
	else{
		Vertex* v = 0;

		_pQuad->Lock(0, 0, (void**)&v, 0);

		v[0] = Vertex(-fHalfWidth, -fHalfHeight, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
		v[1] = Vertex(-fHalfWidth,  fHalfHeight, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
		v[2] = Vertex( fHalfWidth,  fHalfHeight, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
		v[3] = Vertex(-fHalfWidth, -fHalfHeight, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
		v[4] = Vertex( fHalfWidth,  fHalfHeight, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
		v[5] = Vertex( fHalfWidth, -fHalfHeight, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

		_pQuad->Unlock();	
	}

	// 삼각형 정의
	WORD* indices = 0;
	_pIndex->Lock(0, 0, (void**)&indices, 0);

	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 3; indices[4] = 4; indices[5] = 5;

	_pIndex->Unlock();

	_Mtrl.Get(0, action) = d3d::WHITE_MTRL;
	_Mtrl.Get(0, action).Diffuse.a = fAlpha;
	// 텍스처 데이터를 로드한다
	D3DXCreateTextureFromFileEx(_pDevice, texFileName,
		D3DPOOL_DEFAULT, D3DPOOL_DEFAULT, 1, D3DPOOL_DEFAULT, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT,
		NULL, NULL, NULL, &_pTexture.Get(0, action));
//	D3DXCreateTextureFromFile(_pDevice, texFileName, &_pTexture);

	return true;
}

// 렌더링에 앞서 지정해야 할 초기 렌더 상태를 지정한다.
void CBaseObject::preRender(){
	// ZBuffer 연산 꺼줌
	_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
	_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);

	_pDevice->SetRenderState(D3DRS_LIGHTING, true);

	_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	_pDevice->SetRenderState(D3DRS_SPECULARENABLE, true);

	_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	// 알파채널1 = 난반사 컬러로 알파 지정
	// 알파채널2 = Texture 컬러로 알파 지정
	_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	// 두 알파채널을 곱하여 조정하여 최종 결과물 결정
	_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	

	// 블렌딩 인수를 지정하여 알파 성분이 투명도를 결정하도록 함
	_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
}

// 오브젝트를 그린다.
void CBaseObject::Render(){
	preRender();

	D3DXMATRIXA16 mtMatrix;
	D3DXMatrixIdentity(&mtMatrix);

	D3DXMatrixTranslation(&_pos, _vPos.x, _vPos.y, _vPos.z);

	D3DXMATRIXA16 rX, rY, rZ;
	D3DXMatrixRotationZ(&rX, _vRotate.z);
	D3DXMatrixRotationY(&rY, _vRotate.y);
	D3DXMatrixRotationX(&rZ, _vRotate.x);

	_rotation = rX*rY*rZ;

	D3DXMatrixScaling(&_scale, _vScale.x, _vScale.y, _vScale.z);
	mtMatrix = mtMatrix * _rotation * _scale * _pos;
	_matWorld = mtMatrix;

	_pDevice->SetTransform(D3DTS_WORLD, &mtMatrix);

//	_pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);	// 2차원 텍스처 사용
//	_pDevice->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION );	/// 카메라 좌표계 변환

	_pDevice->SetFVF(Vertex::FVF);
	_pDevice->SetStreamSource(0, _pQuad, 0, sizeof(Vertex));

	// 재질과 텍스처를 활성화한다.
	_pDevice->SetMaterial(&_Mtrl.Get(0, _col));
	_pDevice->SetTexture(0, _pTexture.Get(0, _col));

	// 활성화된 텍스처를 이용해 기본형을 그린다.
	//_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);	
	_pDevice->SetIndices(_pIndex);
	_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 6, 0, 2);

	// 월드 좌표를 원점으로 되돌린다.
	D3DXMatrixIdentity(&mtMatrix);
	_pDevice->SetTransform(D3DTS_WORLD, &mtMatrix);

	postRender();
}

// 특정 클래스가 지정했을 수 있는 렌더 상태를 복구하는 데 이용된다.
void CBaseObject::postRender(){
	// ZBuffer 연산 켜줌
	_pDevice->SetRenderState(D3DRS_ZENABLE,D3DZB_TRUE);
	_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

// 현재는 애니메이션이 필요 없다.
// 현재 필요한 것은 방향에 따른 캐릭터 회전
//// 애니메이션 함수
//void CBaseObject::Animation(){
//	// 딜레이 타임이 0이 아니라면
//	if(_timer.IsValidTimer()){
//		// 딜레이 타임이 다 지났다면
//		if(_timer.IsElapseTimer()){
//			// 다음 프레임으로
//			_col+=1;
//			// 다음 프레임이 없다면 다시 처음으로
//			if(_pTexture.GetSize() <= (_col * _pTexture.GetHeight())){
//				_col = 0;
//			}
//			// 딜레이 타임 다시 초기화
//			_timer.InitTimer(_dwDelaytime);
//		}
//	}
//}

// 이동 함수
void CBaseObject::Move(float x, float y){
	_vPos.x += x;
	_vPos.y += y;
}