#include "../BaseHeader.h"

const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

void d3d::SetupMatrices(){
	// 월드 행렬
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	EngineMgr->GetpDevice()->SetTransform(D3DTS_WORLD, &matWorld);

	// 뷰 행렬 설정
	D3DXMATRIX matView;
	if(EngineMgr->GetpTerrain()){
		d3d::SetCameraTerrain();
	}
	else{
		CameraMgr->GetCamera()->GetViewMatrix(&matView);
		EngineMgr->GetpDevice()->SetTransform(D3DTS_VIEW, &matView);
	}

	// 프로젝션 행렬 설정
	D3DXMATRIX Proj;
	D3DXMatrixPerspectiveFovLH(
			&Proj,
			D3DX_PI / 4.0f, // 45 - degree
			(float)(SYSTEMWIDTH)/(float)(SYSTEMHEIGHT),
			1.0f,
			1000.0f);
	EngineMgr->GetpDevice()->SetTransform(D3DTS_PROJECTION, &Proj);
}

void d3d::RenderBG(){

}	

void d3d::RenderMirror(){
	
}

void d3d::RenderShadow(){
	
}

void d3d::RenderBoundingVolume(){
	////
	//// Draw bounding volume in blue and at 10% opacity
	//D3DMATERIAL9 blue = d3d::BLUE_MTRL;
	//blue.Diffuse.a = 0.10f; // 10% opacity

	//AppMgr->GetpDevice()->SetMaterial(&blue);
	//AppMgr->GetpDevice()->SetTexture(0, 0); // disable texture

	//AppMgr->GetpDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//AppMgr->GetpDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//AppMgr->GetpDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//if( AppMgr->RenderBoundingSphere )
	//	AppMgr->SphereMesh->DrawSubset(0);
	//else
	//	AppMgr->BoxMesh->DrawSubset(0);

	//AppMgr->GetpDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

// 파티클 그리기
void d3d::RenderParticle(){
	if(EngineMgr->GetpFirework())
		EngineMgr->GetpFirework()->render();
	if(EngineMgr->GetpSnow())
		EngineMgr->GetpSnow()->render();
	if(EngineMgr->GetpDirt())
		EngineMgr->GetpDirt()->render();
	if(EngineMgr->GetpGun())
		EngineMgr->GetpGun()->render();
}

// 지형 그리기
void d3d::RenderTerrain(){
	D3DXMATRIX I;
	D3DXMatrixIdentity(&I);

	if(EngineMgr->GetpTerrain())
		EngineMgr->GetpTerrain()->draw(&I, true);
}

// 지형에 따른 카메라 위치 조정
void d3d::SetCameraTerrain(){
	D3DXVECTOR3 pos;
	CameraMgr->GetCamera()->GetPosition(&pos);
	float height = EngineMgr->GetpTerrain()->GetHeight( pos.x, pos.z );
	pos.y = height + 5.0f; // add height because we're standing up
	CameraMgr->GetCamera()->SetPosition(&pos);

	D3DXMATRIX V;
	CameraMgr->GetCamera()->GetViewMatrix(&V);
	EngineMgr->GetpDevice()->SetTransform(D3DTS_VIEW, &V);
}

// 경계 구체 충돌 계산
bool d3d::ComputeBoundingSphere(ID3DXMesh* mesh,			// 경계 구체 충돌을 계산할 메쉬와 경계 구체
						   d3d::BoundingSphere* sphere){	
	HRESULT hr = 0;
							   
	BYTE* v = 0;
	mesh->LockVertexBuffer(0, (void**)&v);

	hr = D3DXComputeBoundingSphere(
		(D3DXVECTOR3*)v,
		mesh->GetNumVertices(),
		D3DXGetFVFVertexSize(mesh->GetFVF()),
		&sphere->_center,
		&sphere->_radius);

	mesh->UnlockVertexBuffer();

	if(FAILED(hr))
		return false;
	return true;
}

// 경계 상자 충돌 계산
bool d3d::ComputeBoundingBox(ID3DXMesh* mesh,   // 경계 상자 충돌을 계산할 메쉬와 경계 상자
						d3d::BoundingBox* box){
	HRESULT hr = 0;

	BYTE* v = 0;
	mesh->LockVertexBuffer(0, (void**)&v);

	hr = D3DXComputeBoundingBox(
		(D3DXVECTOR3*)v,
		mesh->GetNumVertices(),
		D3DXGetFVFVertexSize(mesh->GetFVF()),
		&box->_min,
		&box->_max);

	mesh->UnlockVertexBuffer();

	if(FAILED(hr))
		return false;

	return true;
}


// 재질 초기화
D3DMATERIAL9 d3d::InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p){
	D3DMATERIAL9 mtrl;
	mtrl.Ambient = a;
	mtrl.Diffuse = d;
	mtrl.Specular = s;
	mtrl.Emissive = e;
	mtrl.Power = p;
	return mtrl;
}


// 방향성 광원 초기화
D3DLIGHT9 d3d::InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color){
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Ambient = *color * 0.4f;
	light.Diffuse = *color;
	light.Specular = *color * 0.6f;
	light.Direction = *direction;

	return light;
}

// 점 광원 초기화
D3DLIGHT9 d3d::InitPointLight(D3DXVECTOR3* position, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type      = D3DLIGHT_POINT;
	light.Ambient   = *color * 0.6f;
	light.Diffuse   = *color;
	light.Specular  = *color * 0.6f;
	light.Position  = *position;
	light.Range        = 1000.0f;
	light.Falloff      = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;

	return light;
}

// 스포트 광원 초기화
D3DLIGHT9 d3d::InitSpotLight(D3DXVECTOR3* position, D3DXVECTOR3* direction, D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type      = D3DLIGHT_SPOT;
	light.Ambient   = *color * 0.0f;
	light.Diffuse   = *color;
	light.Specular  = *color * 0.6f;
	light.Position  = *position;
	light.Direction = *direction;
	light.Range        = 1000.0f;
	light.Falloff      = 1.0f;
	light.Attenuation0 = 1.0f;
	light.Attenuation1 = 0.0f;
	light.Attenuation2 = 0.0f;
	light.Theta        = 0.4f;
	light.Phi          = 0.9f;

	return light;
}

// 폰트 초기화
ID3DXFont* d3d::IniFont(int wid, int hei, int wei, bool ital, char* style){	
	D3DXFONT_DESC lf;

	ZeroMemory(&lf, sizeof(D3DXFONT_DESC));
	lf.Height			= wid;		// 논리적 단위
	lf.Width			= hei;		// 논리적 단위
	lf.Weight			= wei;		// 굵기의 단위, 범위 0(얇음) - 1000(두꺼움)
	lf.Italic			= ital;
	lf.CharSet			= DEFAULT_CHARSET;
	strcpy(lf.FaceName, style);	// 글꼴 스타일
	
	ID3DXFont* font;
	if(FAILED(D3DXCreateFontIndirect(EngineMgr->GetpDevice(), &lf, &font))){
		OutputDebugString("D3DXCreateFontIndirect() - FAILED");
		::PostQuitMessage(0);
	}
	return font;
}

d3d::BoundingBox::BoundingBox(){
	// 무한대의 작은 경계 상자
	_min.x = d3d::INFINITY;
	_min.y = d3d::INFINITY;
	_min.z = d3d::INFINITY;
	_max.x = -d3d::INFINITY;
	_max.y = -d3d::INFINITY;
	_max.z = -d3d::INFINITY;
}

bool d3d::BoundingBox::isPointInside(D3DXVECTOR3& p){
	//지정된 포인트가 경계 상자 내에 있는가?
	if(p.x >= _min.x && p.y >= _min.y && p.z >= _min.z &&
		p.x <= _max.x && p.y <= _max.y && p.z <= _max.z){
		return true;		
	}
	else{
		return false;
	}
}

d3d::BoundingSphere::BoundingSphere(){
	_radius = 0.0f;
}

float d3d::Lerp(float a, float b, float t){
	return a - (a*t) + (b*t);
}

// 랜덤 float를 생성
float d3d::GetRandomFloat(float lowBound, float highBound){
	if(lowBound >= highBound)	// 잘못된 입력
		return lowBound;

	//[0,1] 범위의 임의 float를 얻는다.
	float f = (rand() % 10000) * 0.0001f;

	// [lowBound, highBound] 범위의 float을 리턴한다.
	return (f * (highBound - lowBound)) + lowBound;
}

// 랜덤 Vector를 생성
void d3d::GetRandomVector(D3DXVECTOR3* out, D3DXVECTOR3* min, D3DXVECTOR3* max){
	out->x = GetRandomFloat(min->x, max->x);
	out->y = GetRandomFloat(min->y, max->y);
	out->z = GetRandomFloat(min->z, max->z);
}

// float를 dword로 형변환
DWORD d3d::FtoDw(float f){
	return *((DWORD*)&f);
}

// 마우스 스크린 좌표를 3D 광선으로 변환
d3d::Ray d3d::CalcPickingRay(int x, int y){
	float px = 0.0f;
	float py = 0.0f;

	D3DVIEWPORT9 vp;
	EngineMgr->GetpDevice()->GetViewport(&vp);

	D3DXMATRIX proj;
	EngineMgr->GetpDevice()->GetTransform(D3DTS_PROJECTION, &proj);

	px = (((2.0f*x) / vp.Width) - 1.0f) / proj(0, 0);
	py = (((-2.0f*y) / vp.Height) + 1.0f) / proj(1, 1);

	d3d::Ray ray;
	ray._origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	ray._direction = D3DXVECTOR3(px, py, 1.0f);

	return ray;
}

// 스크린 포인터 광선을 로컬 스페이스 or 월드 스페이스로 변환
void d3d::TransformRay(d3d::Ray* ray, D3DXMATRIX* T){
	// 광선의 원점을 변환한다. w = 1
	D3DXVec3TransformCoord(
		&ray->_origin,
		&ray->_origin,
		T);

	// 광선의 방향을 변환한다. w = 0
	D3DXVec3TransformNormal(
		&ray->_direction,
		&ray->_direction,
		T);

	// 방향을 정규화한다.
	D3DXVec3Normalize(&ray->_direction, &ray->_direction);
}

// 경계구체와 마우스 광선의 교차 확인 함수
bool d3d::raySphereIntersectionTest(d3d::Ray* ray, d3d::BoundingSphere* sphere){
	if(sphere == 0)
		return false;

	D3DXVECTOR3 v = ray->_origin - sphere->_center;

	float b = 2.0f * D3DXVec3Dot(&ray->_direction, &v);
	float c = D3DXVec3Dot(&v, &v) - (sphere->_radius * sphere->_radius);

	// 판별식
	float discriminant = (b*b) - (4.0f * c);

	// 가상의 수에 대한 테스트
	if(discriminant<0.0f)
		return false;

	discriminant = sqrtf(discriminant);

	float s0 = (-b + discriminant) / 2.0f;
	float s1 = (-b - discriminant) / 2.0f;

	// 해가 >= 0일 경우 구체를 교차하는 것이다.
	if(s0 >= 0.0f || s1 >= 0.0f)
		return true;

	return false;
}