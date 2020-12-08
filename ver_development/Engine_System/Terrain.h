////////////////////////////////////////////////////////////////////////////////
// ������ ���� ��� ���� ����ϴ� Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Terrain_H_
#define _Terrain_H_

class CTerrain{
public:
	CTerrain(){}
	CTerrain(
		IDirect3DDevice9* device,
		std::string heightmapFileName, 
		int numVertsPerRow,  
		int numVertsPerCol, 
		int cellSpacing,    // space between cells �� ���� ����
		float heightScale); // ���� ������ �����ϴ� ��

	~CTerrain();

	int  GetHeightmapEntry(int row, int col);
	void SetHeightmapEntry(int row, int col, int value);

	float GetHeight(float x, float z);

	bool  loadTexture(std::string fileName);
	bool  genTexture(D3DXVECTOR3* directionToLight);
	bool  draw(D3DXMATRIX* world, bool drawTris);
	bool  lightTerrain(D3DXVECTOR3* directionToLight);

private:
	IDirect3DDevice9*       _device;
	IDirect3DTexture9*      _tex;
	IDirect3DVertexBuffer9* _vb;
	IDirect3DIndexBuffer9*  _ib;

	int _numVertsPerRow;
	int _numVertsPerCol;
	int _cellSpacing;

	int _numCellsPerRow;
	int _numCellsPerCol;
	int _width;
	int _depth;
	int _numVertices;
	int _numTriangles;

	float _heightScale;

	std::vector<int> _heightmap;

	// helper methods
	bool  readRawFile(std::string fileName);
	bool  computeVertices();
	bool  computeIndices();
	float computeShade(int cellRow, int cellCol, D3DXVECTOR3* directionToLight);

	struct TerrainVertex{
		TerrainVertex(){}
		TerrainVertex(float x, float y, float z, float u, float v){
			_x = x; _y = y; _z = z; _u = u; _v = v;
		}
		float _x, _y, _z;
		float _u, _v;

		static const DWORD FVF;
	};
};

#endif