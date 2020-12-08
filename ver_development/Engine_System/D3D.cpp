#include "../BaseHeader.h"

const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

void d3d::SetupMatrices(){
	// ���� ���
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	EngineMgr->GetpDevice()->SetTransform(D3DTS_WORLD, &matWorld);

	// �� ��� ����
	D3DXMATRIX matView;
	if(EngineMgr->GetpTerrain()){
		d3d::SetCameraTerrain();
	}
	else{
		CameraMgr->GetCamera()->GetViewMatrix(&matView);
		EngineMgr->GetpDevice()->SetTransform(D3DTS_VIEW, &matView);
	}

	// �������� ��� ����
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

// ��ƼŬ �׸���
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

// ���� �׸���
void d3d::RenderTerrain(){
	D3DXMATRIX I;
	D3DXMatrixIdentity(&I);

	if(EngineMgr->GetpTerrain())
		EngineMgr->GetpTerrain()->draw(&I, true);
}

// ������ ���� ī�޶� ��ġ ����
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

// ��� ��ü �浹 ���
bool d3d::ComputeBoundingSphere(ID3DXMesh* mesh,			// ��� ��ü �浹�� ����� �޽��� ��� ��ü
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

// ��� ���� �浹 ���
bool d3d::ComputeBoundingBox(ID3DXMesh* mesh,   // ��� ���� �浹�� ����� �޽��� ��� ����
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


// ���� �ʱ�ȭ
D3DMATERIAL9 d3d::InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p){
	D3DMATERIAL9 mtrl;
	mtrl.Ambient = a;
	mtrl.Diffuse = d;
	mtrl.Specular = s;
	mtrl.Emissive = e;
	mtrl.Power = p;
	return mtrl;
}


// ���⼺ ���� �ʱ�ȭ
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

// �� ���� �ʱ�ȭ
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

// ����Ʈ ���� �ʱ�ȭ
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

// ��Ʈ �ʱ�ȭ
ID3DXFont* d3d::IniFont(int wid, int hei, int wei, bool ital, char* style){	
	D3DXFONT_DESC lf;

	ZeroMemory(&lf, sizeof(D3DXFONT_DESC));
	lf.Height			= wid;		// ���� ����
	lf.Width			= hei;		// ���� ����
	lf.Weight			= wei;		// ������ ����, ���� 0(����) - 1000(�β���)
	lf.Italic			= ital;
	lf.CharSet			= DEFAULT_CHARSET;
	strcpy(lf.FaceName, style);	// �۲� ��Ÿ��
	
	ID3DXFont* font;
	if(FAILED(D3DXCreateFontIndirect(EngineMgr->GetpDevice(), &lf, &font))){
		OutputDebugString("D3DXCreateFontIndirect() - FAILED");
		::PostQuitMessage(0);
	}
	return font;
}

d3d::BoundingBox::BoundingBox(){
	// ���Ѵ��� ���� ��� ����
	_min.x = d3d::INFINITY;
	_min.y = d3d::INFINITY;
	_min.z = d3d::INFINITY;
	_max.x = -d3d::INFINITY;
	_max.y = -d3d::INFINITY;
	_max.z = -d3d::INFINITY;
}

bool d3d::BoundingBox::isPointInside(D3DXVECTOR3& p){
	//������ ����Ʈ�� ��� ���� ���� �ִ°�?
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

// ���� float�� ����
float d3d::GetRandomFloat(float lowBound, float highBound){
	if(lowBound >= highBound)	// �߸��� �Է�
		return lowBound;

	//[0,1] ������ ���� float�� ��´�.
	float f = (rand() % 10000) * 0.0001f;

	// [lowBound, highBound] ������ float�� �����Ѵ�.
	return (f * (highBound - lowBound)) + lowBound;
}

// ���� Vector�� ����
void d3d::GetRandomVector(D3DXVECTOR3* out, D3DXVECTOR3* min, D3DXVECTOR3* max){
	out->x = GetRandomFloat(min->x, max->x);
	out->y = GetRandomFloat(min->y, max->y);
	out->z = GetRandomFloat(min->z, max->z);
}

// float�� dword�� ����ȯ
DWORD d3d::FtoDw(float f){
	return *((DWORD*)&f);
}

// ���콺 ��ũ�� ��ǥ�� 3D �������� ��ȯ
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

// ��ũ�� ������ ������ ���� �����̽� or ���� �����̽��� ��ȯ
void d3d::TransformRay(d3d::Ray* ray, D3DXMATRIX* T){
	// ������ ������ ��ȯ�Ѵ�. w = 1
	D3DXVec3TransformCoord(
		&ray->_origin,
		&ray->_origin,
		T);

	// ������ ������ ��ȯ�Ѵ�. w = 0
	D3DXVec3TransformNormal(
		&ray->_direction,
		&ray->_direction,
		T);

	// ������ ����ȭ�Ѵ�.
	D3DXVec3Normalize(&ray->_direction, &ray->_direction);
}

// ��豸ü�� ���콺 ������ ���� Ȯ�� �Լ�
bool d3d::raySphereIntersectionTest(d3d::Ray* ray, d3d::BoundingSphere* sphere){
	if(sphere == 0)
		return false;

	D3DXVECTOR3 v = ray->_origin - sphere->_center;

	float b = 2.0f * D3DXVec3Dot(&ray->_direction, &v);
	float c = D3DXVec3Dot(&v, &v) - (sphere->_radius * sphere->_radius);

	// �Ǻ���
	float discriminant = (b*b) - (4.0f * c);

	// ������ ���� ���� �׽�Ʈ
	if(discriminant<0.0f)
		return false;

	discriminant = sqrtf(discriminant);

	float s0 = (-b + discriminant) / 2.0f;
	float s1 = (-b - discriminant) / 2.0f;

	// �ذ� >= 0�� ��� ��ü�� �����ϴ� ���̴�.
	if(s0 >= 0.0f || s1 >= 0.0f)
		return true;

	return false;
}