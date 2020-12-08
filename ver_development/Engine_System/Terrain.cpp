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
	// 이 메서드는 텍스처의 최상위 표면을 절차적인 방식으로 채우며,
	// 표면에 조명을 추가한다. 이어 D3DXFilterTexture 함수를 이용해
	// 최상위 표면 데이터를 기반으로 다른 밉맵을 채운다.

	HRESULT hr = 0;

	// 각각의 사각형 셀을 위한 텍셀
	int texWidth = _numCellsPerRow;
	int texHeight = _numCellsPerCol;

	// 빈 텍스처를 만든다.
	hr = D3DXCreateTexture(
		_device,
		texWidth, texHeight, // 크기
		0, // 완전한 밉맵 체인을 만든다.
		0, // 이용 - 없음
		D3DFMT_X8R8G8B8, // 32-비트 XRGB 포맷
		D3DPOOL_MANAGED, // 메모리 풀
		&_tex);

	if(FAILED(hr))
		return false;

	D3DSURFACE_DESC textureDesc;
	_tex->GetLevelDesc(0 /*레벨*/, &textureDesc);

	// 이 코드는 직접 32-비트 픽셀을 이용해 텍스처를 채우므로
	// 올바른 포맷인지를 먼저 확인한다.
	if(textureDesc.Format != D3DFMT_X8R8G8B8)
		return false;

	D3DLOCKED_RECT lockedRect;
	_tex->LockRect(0/*최상위 레벨을 잠근다.*/, &lockedRect, 0 /*lock entire tex*/, 0 /*플래그*/);

	// 텍스처를 채운다.
	DWORD* imageData = (DWORD*)lockedRect.pBits;
	for(int i = 0; i < texHeight; i++){
		for(int j = 0; j < texWidth; j++){
			D3DXCOLOR c;

			// 사각형의 우측 상단 높이를 구한다.
			float height = (float) GetHeightmapEntry(i, j)/_heightScale;

			// 대응되는 사각형의 높이에 따라
			// 텍셀의 컬러를 지정한다.
			if((height) <42.5f) c = d3d::BEACH_SAND;
			else if((height) <85.0f) c = d3d::LIGHT_YELLOW_GREEN;
			else if((height) < 127.5f) c = d3d::PUREGREEN;
			else if((height) < 170.0f) c = d3d::DARK_YELLOW_GREEN;
			else if((height) < 212.5f) c = d3d::DARKBROWN;
			else c = d3d::WHITE;

			// 잠금 데이터를 채운다. 피치로 4로 나누었음을 확인
			// 피치는 바이트로 주어지며 DWORD는 4바이트로 이루어져 있다.
			imageData[i*lockedRect.Pitch / 4 + j] = (D3DCOLOR)c;
		}
	}

	_tex->UnlockRect(0);

	// 지형을 밝힌다.
	if(!lightTerrain(directionToLight)){
		OutputDebugString("lightTerrain() - FAILED");
		return false;
	}

	// 밉맵을 채운다.
	hr = D3DXFilterTexture(
		_tex,	// 밉맵 레벨을 채울 텍스처
		0,		// 디폴트 팔레트
		0,		// 하위 레벨의 원본으로 최상위 레벨을 이용한다.
		D3DX_DEFAULT);	// 디폴트 필터

	if(FAILED(hr)){
		OutputDebugString("D3DXFilterTexture() - FAILED");
		return false;
	}

	return true;
}

float CTerrain::computeShade(int cellRow, int cellCol, D3DXVECTOR3* directionToLight){
	// 사각형의 세 버텍스 높이를 얻는다.
	float heightA = (float)GetHeightmapEntry(cellRow, cellCol);
	float heightB = (float)GetHeightmapEntry(cellRow, cellCol+1);
	float heightC = (float)GetHeightmapEntry(cellRow+1, cellCol);

	// 사각형의 두 벡터를 구성한다.
	D3DXVECTOR3 u((float)_cellSpacing, heightB - heightA, 0.0f);
	D3DXVECTOR3 v(0.0f, heightC - heightA, -(float)_cellSpacing);

	// 사각형의 두 벡터 외적을 이용해
	// 법선을 찾아낸다.
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

			// 셀의 현재 컬러를 얻는다.
			// get current color of quad
			D3DXCOLOR c( imageData[index] );

			// shade current quad
			// 셀에 음영을 적용한다
			c *= computeShade(i, j, directionToLight);;

			// save shaded color
			// 음영을 입힌 컬러를 저장한다.
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

	// 버텍스 생성을 시작할 좌표
	int startX = -_width / 2;
	int startZ = _depth / 2;

	// 버텍스 생성을 마칠 좌표
	int endX = _width / 2;
	int endZ = -_depth / 2;

	// 하나의 버텍스에서 다음 버텍스로 증가할 텍스처 좌표의 크기를 계산한다.
	float uCoordIncrementSize = 1.0f / (float)_numCellsPerRow;
	float vCoordIncrementSize = 1.0f / (float)_numCellsPerCol;

	TerrainVertex* v = 0;
	_vb->Lock(0, 0, (void**)&v, 0);

	int i = 0;
	for(int z = startZ; z >= endZ; z -= _cellSpacing){
		int j = 0;
		for(int x = startX; x <= endX; x += _cellSpacing){
			// 중첩된 루프 내의 위치에 따라
			// 버텍스 버퍼와 높이맵으로의 올바른 인덱스를 계산한다.
			int index = i * _numVertsPerRow + j;
			v[index] = TerrainVertex(
				(float)x,
				(float)_heightmap[index],
				(float)z,
				(float)j * uCoordIncrementSize,
				(float)i * vCoordIncrementSize);

			j++; // 다음 열
		}
		i++;	// 다음 행
	}

	_vb->Unlock();

	return true;
}

bool CTerrain::computeIndices(){
	HRESULT hr = 0;

	hr = _device->CreateIndexBuffer(
		_numTriangles * 3 * sizeof(WORD),	// 삼각형 당 3개의 인덱스
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&_ib,
		0);

	if(FAILED(hr))
		return false;

	WORD* indices = 0;
	_ib->Lock(0, 0, (void**)&indices, 0);

	// 하나의 사각형을 구성하는 두 개의 삼각형을 나타내기 위한
	// 6개의 인덱스 그룹의 시작점
	int baseIndex = 0;

	// 각 사각형의 삼각형을 계산하는 루프
	for(int i = 0; i < _numCellsPerCol;i++){
		for(int j = 0; j < _numCellsPerRow; j++){
			indices[baseIndex] = i * _numVertsPerRow + j;
			indices[baseIndex + 1] = i * _numVertsPerRow + j + 1;
			indices[baseIndex + 2] = (i+1) * _numVertsPerRow + j;
			indices[baseIndex + 3] = (i+1) * _numVertsPerRow + j;
			indices[baseIndex + 4] = i * _numVertsPerRow + j + 1;
			indices[baseIndex + 5] = (i+1) * _numVertsPerRow + j + 1;

			// 다음 사각형
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
	// 각 벡터를 위한 높이
	std::vector<BYTE> in(_numVertices);

	ifstream inFile(fileName.c_str(), std::ios_base::binary);

	if(inFile == 0) return false;

	inFile.read(
		(char*)&in[0],	// 버퍼
		in.size());		// 버퍼로 읽어 들일 바이트 수
	
	inFile.close();

	// BYTE벡터를 int 벡터로 복사한다.
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
	// 지형의 시작점을 원점으로 이동하는 변환으로
	// xz-평면 상에서 이동한다
	x = ((float)_width / 2.0f) + x;
	z = ((float)_depth / 2.0f) - z;

	// 셀 간격을 1로 만드는 변환으로
	// 변환의 배율을 낮춘다.
	// Cellspacing * 1 / cellspacing = 1이므로,
	// 1 / cellspacing을 이용한다.
	x /= (float)_cellSpacing;
	z /= (float)_cellSpacing;

	// 현재 셀의 행과 열을 알아낼 수 있다.
	// x의 정수부분은 열과 같으며, z의 정수 부분은 행과 같다.
	// floor(t)함수로 가장 큰 정수 <= t를 얻을 수 있다.
	float col = ::floorf(x);
	float row = ::floorf(z);

	// 이제 현재 위치의 셀을 찾을 수 있으므로 셀을 구성하는 네 버텍스의 높이를 구할 수 있다.

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
	if(dz < 1.0f - dx){		// 위쪽 삼각형 ABC
		float uy = B - A; // A->B
		float vy = C - A; // A->C
		height = A + d3d::Lerp(0.0f, uy, dx) + d3d::Lerp(0.0f, vy, dz);
	}
	else{		// 아래쪽 삼각형 DCB
		float uy = C - D;	// D->C
		float vy = B - D;	// D->B
		height = D + d3d::Lerp(0.0f, uy, 1.0f - dx) + d3d::Lerp(0.0f, vy, 1.0f - dz);
	}
	return height;
}