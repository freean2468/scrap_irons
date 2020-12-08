#include "../BaseHeader.h"

const DWORD CTerrain::TerrainVertex::FVF = D3DFVF_XYZ | D3DFVF_TEX1;

CTerrain::CTerrain(IDirect3DDevice9* device,
				 std::string heightmapFileName,
				 int numVertsPerRow,
				 int numVertsPerCol,
				 int cellSpacing,
				 float heightScale)
{
	_device         = device;
	_numVertsPerRow = numVertsPerRow;
	_numVertsPerCol = numVertsPerCol;
	_cellSpacing    = cellSpacing;

	_numCellsPerRow = _numVertsPerRow - 1;
	_numCellsPerCol = _numVertsPerCol - 1;

	_width = _numCellsPerRow * _cellSpacing;
	_depth = _numCellsPerCol * _cellSpacing;

	_numVertices  = _numVertsPerRow * _numVertsPerCol;
	_numTriangles = _numCellsPerRow * _numCellsPerCol * 2;

	_heightScale = heightScale;
	_tex = 0;

	// load heightmap
	if( !readRawFile(heightmapFileName) )
	{
		OutputDebugString("readRawFile - FAILED");
		::PostQuitMessage(0);
	}

	// scale heights
	for(int i = 0; i < _heightmap.size(); i++)
		_heightmap[i] *= heightScale;

	// compute the vertices
	if( !computeVertices() )
	{
		OutputDebugString("computeVertices - FAILED");
		::PostQuitMessage(0);
	}

	// compute the indices
	if( !computeIndices() )
	{
		OutputDebugString("computeIndices - FAILED");
		::PostQuitMessage(0);
	}
}

CTerrain::~CTerrain()
{
	d3d::Release<IDirect3DTexture9*>(_tex);
}


bool CTerrain::draw(D3DXMATRIX* world, bool drawTris)
{
	HRESULT hr = 0;

	if( _device )
	{
		_device->SetTransform(D3DTS_WORLD, world);

		_device->SetStreamSource(0, _vb, 0, sizeof(TerrainVertex));
		_device->SetFVF(TerrainVertex::FVF);
		_device->SetIndices(_ib);
		
		_device->SetTexture(0, _tex);

		// turn off lighting since we're lighting it ourselves
		_device->SetRenderState(D3DRS_LIGHTING, true);

		hr =_device->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST,
			0,
			0,
			_numVertices,
			0,
			_numTriangles);

		_device->SetRenderState(D3DRS_LIGHTING, false);

		if( drawTris )
		{
			hr =_device->DrawIndexedPrimitive(
				D3DPT_TRIANGLELIST,
				0,
				0,
				_numVertices,
				0,
				_numTriangles);

			_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}

		if(FAILED(hr))
			return false;
	}

	return true;
}

bool CTerrain::genTexture(D3DXVECTOR3* directionToLight){
	// �� �޼���� �ؽ�ó�� �ֻ��� ǥ���� �������� ������� ä���,
	// ǥ�鿡 ������ �߰��Ѵ�. �̾� D3DXFilterTexture �Լ��� �̿���
	// �ֻ��� ǥ�� �����͸� ������� �ٸ� �Ӹ��� ä���.

	HRESULT hr = 0;

	// ������ �簢�� ���� ���� �ؼ�
	int texWidth = _numCellsPerRow;
	int texHeight = _numCellsPerCol;

	// �� �ؽ�ó�� �����.
	hr = D3DXCreateTexture(
		_device,
		texWidth, texHeight, // ũ��
		0, // ������ �Ӹ� ü���� �����.
		0, // �̿� - ����
		D3DFMT_X8R8G8B8, // 32-��Ʈ XRGB ����
		D3DPOOL_MANAGED, // �޸� Ǯ
		&_tex);

	if(FAILED(hr))
		return false;

	D3DSURFACE_DESC textureDesc;
	_tex->GetLevelDesc(0 /*����*/, &textureDesc);

	// �� �ڵ�� ���� 32-��Ʈ �ȼ��� �̿��� �ؽ�ó�� ä��Ƿ�
	// �ùٸ� ���������� ���� Ȯ���Ѵ�.
	if(textureDesc.Format != D3DFMT_X8R8G8B8)
		return false;

	D3DLOCKED_RECT lockedRect;
	_tex->LockRect(0/*�ֻ��� ������ ��ٴ�.*/, &lockedRect, 0 /*lock entire tex*/, 0 /*�÷���*/);

	// �ؽ�ó�� ä���.
	DWORD* imageData = (DWORD*)lockedRect.pBits;
	for(int i = 0; i < texHeight; i++){
		for(int j = 0; j < texWidth; j++){
			D3DXCOLOR c;

			// �簢���� ���� ��� ���̸� ���Ѵ�.
			float height = (float) GetHeightmapEntry(i, j)/_heightScale;

			// �����Ǵ� �簢���� ���̿� ����
			// �ؼ��� �÷��� �����Ѵ�.
			if((height) <42.5f) c = d3d::BEACH_SAND;
			else if((height) <85.0f) c = d3d::LIGHT_YELLOW_GREEN;
			else if((height) < 127.5f) c = d3d::PUREGREEN;
			else if((height) < 170.0f) c = d3d::DARK_YELLOW_GREEN;
			else if((height) < 212.5f) c = d3d::DARKBROWN;
			else c = d3d::WHITE;

			// ��� �����͸� ä���. ��ġ�� 4�� ���������� Ȯ��
			// ��ġ�� ����Ʈ�� �־����� DWORD�� 4����Ʈ�� �̷���� �ִ�.
			imageData[i*lockedRect.Pitch / 4 + j] = (D3DCOLOR)c;
		}
	}

	_tex->UnlockRect(0);

	// ������ ������.
	if(!lightTerrain(directionToLight)){
		OutputDebugString("lightTerrain() - FAILED");
		return false;
	}

	// �Ӹ��� ä���.
	hr = D3DXFilterTexture(
		_tex,	// �Ӹ� ������ ä�� �ؽ�ó
		0,		// ����Ʈ �ȷ�Ʈ
		0,		// ���� ������ �������� �ֻ��� ������ �̿��Ѵ�.
		D3DX_DEFAULT);	// ����Ʈ ����

	if(FAILED(hr)){
		OutputDebugString("D3DXFilterTexture() - FAILED");
		return false;
	}

	return true;
}

float CTerrain::computeShade(int cellRow, int cellCol, D3DXVECTOR3* directionToLight){
	// �簢���� �� ���ؽ� ���̸� ��´�.
	float heightA = (float)GetHeightmapEntry(cellRow, cellCol);
	float heightB = (float)GetHeightmapEntry(cellRow, cellCol+1);
	float heightC = (float)GetHeightmapEntry(cellRow+1, cellCol);

	// �簢���� �� ���͸� �����Ѵ�.
	D3DXVECTOR3 u((float)_cellSpacing, heightB - heightA, 0.0f);
	D3DXVECTOR3 v(0.0f, heightC - heightA, -(float)_cellSpacing);

	// �簢���� �� ���� ������ �̿���
	// ������ ã�Ƴ���.
	D3DXVECTOR3 n;
	D3DXVec3Cross(&n, &u, &v);
	D3DXVec3Normalize(&n, &n);

	float cosine = D3DXVec3Dot(&n, directionToLight);

	if(cosine < 0.0f)
		cosine = 0.0f;

	return cosine;
}

bool CTerrain::lightTerrain(D3DXVECTOR3* directionToLight)
{
	HRESULT hr = 0;

	D3DSURFACE_DESC textureDesc; 
	_tex->GetLevelDesc(0 /*level*/, &textureDesc);

	// make sure we got the requested format because our code that fills the
	// texture is hard coded to a 32 bit pixel depth.
	if( textureDesc.Format != D3DFMT_X8R8G8B8 )
		return false;
		
	D3DLOCKED_RECT lockedRect;
	_tex->LockRect(
		0,          // lock top surface level in mipmap chain
		&lockedRect,// pointer to receive locked data
		0,          // lock entire texture image
		0);         // no lock flags specified

	DWORD* imageData = (DWORD*)lockedRect.pBits;
	for(int i = 0; i < textureDesc.Height; i++)
	{
		for(int j = 0; j < textureDesc.Width; j++)
		{
			// index into texture, note we use the pitch and divide by 
			// four since the pitch is given in bytes and there are 
			// 4 bytes per DWORD.
			int index = i * lockedRect.Pitch / 4 + j;

			// ���� ���� �÷��� ��´�.
			// get current color of quad
			D3DXCOLOR c( imageData[index] );

			// shade current quad
			// ���� ������ �����Ѵ�
			c *= computeShade(i, j, directionToLight);;

			// save shaded color
			// ������ ���� �÷��� �����Ѵ�.
			imageData[index] = (D3DCOLOR)c;
		}
	}

	_tex->UnlockRect(0);

	return true;
}

bool CTerrain::computeVertices(){
	HRESULT hr = 0;

	hr = _device->CreateVertexBuffer(
		_numVertices * sizeof(TerrainVertex),
		D3DUSAGE_WRITEONLY,
		TerrainVertex::FVF,
		D3DPOOL_MANAGED,
		&_vb,
		0);

	if(FAILED(hr))
		return false;

	// ���ؽ� ������ ������ ��ǥ
	int startX = -_width / 2;
	int startZ = _depth / 2;

	// ���ؽ� ������ ��ĥ ��ǥ
	int endX = _width / 2;
	int endZ = -_depth / 2;

	// �ϳ��� ���ؽ����� ���� ���ؽ��� ������ �ؽ�ó ��ǥ�� ũ�⸦ ����Ѵ�.
	float uCoordIncrementSize = 1.0f / (float)_numCellsPerRow;
	float vCoordIncrementSize = 1.0f / (float)_numCellsPerCol;

	TerrainVertex* v = 0;
	_vb->Lock(0, 0, (void**)&v, 0);

	int i = 0;
	for(int z = startZ; z >= endZ; z -= _cellSpacing){
		int j = 0;
		for(int x = startX; x <= endX; x += _cellSpacing){
			// ��ø�� ���� ���� ��ġ�� ����
			// ���ؽ� ���ۿ� ���̸������� �ùٸ� �ε����� ����Ѵ�.
			int index = i * _numVertsPerRow + j;
			v[index] = TerrainVertex(
				(float)x,
				(float)_heightmap[index],
				(float)z,
				(float)j * uCoordIncrementSize,
				(float)i * vCoordIncrementSize);

			j++; // ���� ��
		}
		i++;	// ���� ��
	}

	_vb->Unlock();

	return true;
}

bool CTerrain::computeIndices(){
	HRESULT hr = 0;

	hr = _device->CreateIndexBuffer(
		_numTriangles * 3 * sizeof(WORD),	// �ﰢ�� �� 3���� �ε���
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&_ib,
		0);

	if(FAILED(hr))
		return false;

	WORD* indices = 0;
	_ib->Lock(0, 0, (void**)&indices, 0);

	// �ϳ��� �簢���� �����ϴ� �� ���� �ﰢ���� ��Ÿ���� ����
	// 6���� �ε��� �׷��� ������
	int baseIndex = 0;

	// �� �簢���� �ﰢ���� ����ϴ� ����
	for(int i = 0; i < _numCellsPerCol;i++){
		for(int j = 0; j < _numCellsPerRow; j++){
			indices[baseIndex] = i * _numVertsPerRow + j;
			indices[baseIndex + 1] = i * _numVertsPerRow + j + 1;
			indices[baseIndex + 2] = (i+1) * _numVertsPerRow + j;
			indices[baseIndex + 3] = (i+1) * _numVertsPerRow + j;
			indices[baseIndex + 4] = i * _numVertsPerRow + j + 1;
			indices[baseIndex + 5] = (i+1) * _numVertsPerRow + j + 1;

			// ���� �簢��
			baseIndex += 6;
		}
	}

	_ib->Unlock();

	return true;
}

bool CTerrain::loadTexture(std::string fileName){
	HRESULT hr = 0;
	hr = D3DXCreateTextureFromFile(
		_device,
		fileName.c_str(),
		&_tex);

	if(FAILED(hr))
		return false;

	return true;
}

bool CTerrain::readRawFile(std::string fileName){
	// �� ���͸� ���� ����
	std::vector<BYTE> in(_numVertices);

	ifstream inFile(fileName.c_str(), std::ios_base::binary);

	if(inFile == 0) return false;

	inFile.read(
		(char*)&in[0],	// ����
		in.size());		// ���۷� �о� ���� ����Ʈ ��
	
	inFile.close();

	// BYTE���͸� int ���ͷ� �����Ѵ�.
	_heightmap.resize(_numVertices);
	for(int i = 0; i < in.size(); i++)
		_heightmap[i] = in[i];

	return true;
}

int CTerrain::GetHeightmapEntry(int row, int col){
	return _heightmap[row * _numVertsPerRow + col];
}

void CTerrain::SetHeightmapEntry(int row, int col, int value){
	_heightmap[row * _numVertsPerRow + col] = value;
}

float CTerrain::GetHeight(float x, float z){
	// ������ �������� �������� �̵��ϴ� ��ȯ����
	// xz-��� �󿡼� �̵��Ѵ�
	x = ((float)_width / 2.0f) + x;
	z = ((float)_depth / 2.0f) - z;

	// �� ������ 1�� ����� ��ȯ����
	// ��ȯ�� ������ �����.
	// Cellspacing * 1 / cellspacing = 1�̹Ƿ�,
	// 1 / cellspacing�� �̿��Ѵ�.
	x /= (float)_cellSpacing;
	z /= (float)_cellSpacing;

	// ���� ���� ��� ���� �˾Ƴ� �� �ִ�.
	// x�� �����κ��� ���� ������, z�� ���� �κ��� ��� ����.
	// floor(t)�Լ��� ���� ū ���� <= t�� ���� �� �ִ�.
	float col = ::floorf(x);
	float row = ::floorf(z);

	// ���� ���� ��ġ�� ���� ã�� �� �����Ƿ� ���� �����ϴ� �� ���ؽ��� ���̸� ���� �� �ִ�.

	// get the heights of the quad we're in:
	// 
    //  A   B
    //  *---*
    //  | / |
    //  *---*  
    //  C   D

	float A = (float)(GetHeightmapEntry((int)row, (int)col));
	float B = (float)(GetHeightmapEntry((int)row, (int)col+1));
	float C = (float)(GetHeightmapEntry((int)row+1, (int)col));
	float D = (float)(GetHeightmapEntry((int)row+1, (int)col+1));

	float dx = x - col;
	float dz = z - row;

	float height = 0.0f;
	if(dz < 1.0f - dx){		// ���� �ﰢ�� ABC
		float uy = B - A; // A->B
		float vy = C - A; // A->C
		height = A + d3d::Lerp(0.0f, uy, dx) + d3d::Lerp(0.0f, vy, dz);
	}
	else{		// �Ʒ��� �ﰢ�� DCB
		float uy = C - D;	// D->C
		float vy = B - D;	// D->B
		height = D + d3d::Lerp(0.0f, uy, 1.0f - dx) + d3d::Lerp(0.0f, vy, 1.0f - dz);
	}
	return height;
}