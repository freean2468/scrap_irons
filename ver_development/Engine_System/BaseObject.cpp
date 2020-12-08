#include "../BaseHeader.h"

CBaseObject::CBaseObject(int id):CBaseGameEntity(id){
	// �������̽� ���� ����
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

	// Object ��ġ ���� ����
	D3DXMatrixIdentity(&_matWorld);
	_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ��ġ ����
	_vScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		// ũ�� ����
	_vRotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ȸ�� ����

	// Object ������ ���� ����
	_width = 0;
	_height = 0;

	// Object �ִϸ��̼� ���� ����
	_dwDelaytime = 0;
	_col = CBaseObject::RIGHT;
	_row = CBaseObject::RIGHT;

	// Object ���� ���� ���� ����
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

// �̹����� �ҷ����� ��ġ �������̽��� ��������Ʈ �������̽��� �����Ѵ�.
bool CBaseObject::InitObject(IDirect3DDevice9* device, char* texFileName, int width, int height, float fAlpha, int action){
	_pDevice = device;
	_width = (float)width;
	_height = (float)height;
	_widthHalf = width/2.0f;
	_heightHalf = height/2.0f;

	// ����&�ؽ�ó �迭�� ��á�ٸ� �ڸ��� �����.
	_pTexture.FullArray(0, action);
	_Mtrl.FullArray(0, action);

	// 800 : 1 ī�޶� ����
	// width : x �̹��� ����
	// = width / 800
//	float x;
//	float y;

	// 3D ī�޶�� ��ǥ�踦 ���߱� ���� ���� ����
//	x = width/((float)SYSTEMHEIGHT-30);
//	y = height/((float)SYSTEMHEIGHT-30);

	float fHalfWidth = width / 2.0f;//x / (float)2;
	float fHalfHeight = height / 2.0f;//y / (float)2;

	// ���ؽ� ���� ����
	_pDevice->CreateVertexBuffer(
		6 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&_pQuad,
		0);

	// �ε��� ���� ����
	_pDevice->CreateIndexBuffer(
		6 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&_pIndex,
		0);

	// �� ���� �ﰢ������ ������ �簢��,
	// BG�� ��� ��� ��ǥ�� ī�޶� ��ǥ���� �����ϵ��� �Ѵ�.
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

	// �ﰢ�� ����
	WORD* indices = 0;
	_pIndex->Lock(0, 0, (void**)&indices, 0);

	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 3; indices[4] = 4; indices[5] = 5;

	_pIndex->Unlock();

	_Mtrl.Get(0, action) = d3d::WHITE_MTRL;
	_Mtrl.Get(0, action).Diffuse.a = fAlpha;
	// �ؽ�ó �����͸� �ε��Ѵ�
	D3DXCreateTextureFromFileEx(_pDevice, texFileName,
		D3DPOOL_DEFAULT, D3DPOOL_DEFAULT, 1, D3DPOOL_DEFAULT, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT,
		NULL, NULL, NULL, &_pTexture.Get(0, action));
//	D3DXCreateTextureFromFile(_pDevice, texFileName, &_pTexture);

	return true;
}

// �������� �ռ� �����ؾ� �� �ʱ� ���� ���¸� �����Ѵ�.
void CBaseObject::preRender(){
	// ZBuffer ���� ����
	_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
	_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);

	_pDevice->SetRenderState(D3DRS_LIGHTING, true);

	_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	_pDevice->SetRenderState(D3DRS_SPECULARENABLE, true);

	_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	// ����ä��1 = ���ݻ� �÷��� ���� ����
	// ����ä��2 = Texture �÷��� ���� ����
	_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	// �� ����ä���� ���Ͽ� �����Ͽ� ���� ����� ����
	_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	

	// ���� �μ��� �����Ͽ� ���� ������ ������ �����ϵ��� ��
	_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
}

// ������Ʈ�� �׸���.
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

//	_pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);	// 2���� �ؽ�ó ���
//	_pDevice->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION );	/// ī�޶� ��ǥ�� ��ȯ

	_pDevice->SetFVF(Vertex::FVF);
	_pDevice->SetStreamSource(0, _pQuad, 0, sizeof(Vertex));

	// ������ �ؽ�ó�� Ȱ��ȭ�Ѵ�.
	_pDevice->SetMaterial(&_Mtrl.Get(0, _col));
	_pDevice->SetTexture(0, _pTexture.Get(0, _col));

	// Ȱ��ȭ�� �ؽ�ó�� �̿��� �⺻���� �׸���.
	//_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);	
	_pDevice->SetIndices(_pIndex);
	_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 6, 0, 2);

	// ���� ��ǥ�� �������� �ǵ�����.
	D3DXMatrixIdentity(&mtMatrix);
	_pDevice->SetTransform(D3DTS_WORLD, &mtMatrix);

	postRender();
}

// Ư�� Ŭ������ �������� �� �ִ� ���� ���¸� �����ϴ� �� �̿�ȴ�.
void CBaseObject::postRender(){
	// ZBuffer ���� ����
	_pDevice->SetRenderState(D3DRS_ZENABLE,D3DZB_TRUE);
	_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

// ����� �ִϸ��̼��� �ʿ� ����.
// ���� �ʿ��� ���� ���⿡ ���� ĳ���� ȸ��
//// �ִϸ��̼� �Լ�
//void CBaseObject::Animation(){
//	// ������ Ÿ���� 0�� �ƴ϶��
//	if(_timer.IsValidTimer()){
//		// ������ Ÿ���� �� �����ٸ�
//		if(_timer.IsElapseTimer()){
//			// ���� ����������
//			_col+=1;
//			// ���� �������� ���ٸ� �ٽ� ó������
//			if(_pTexture.GetSize() <= (_col * _pTexture.GetHeight())){
//				_col = 0;
//			}
//			// ������ Ÿ�� �ٽ� �ʱ�ȭ
//			_timer.InitTimer(_dwDelaytime);
//		}
//	}
//}

// �̵� �Լ�
void CBaseObject::Move(float x, float y){
	_vPos.x += x;
	_vPos.y += y;
}