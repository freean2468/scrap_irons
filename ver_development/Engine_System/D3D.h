///////////////////////////////////////////////////////
// DirectX 관련 사용자정의 함수들의 집함
// 좀더 DIrectX 관련 인터페이스를 쉽게 제공하기 위함
// 용책 참고
///////////////////////////////////////////////////////
#ifndef _D3D_H_
#define _D3D_H_

// Classes and Structures
struct Vertex{
	Vertex(){}
	Vertex(
		float x, float y, float z,
		float nx, float ny, float nz,
		float u, float v)
	{
		_x  = x;  _y  = y;  _z  = z;
		_nx = nx; _ny = ny; _nz = nz;	//	
		_u  = u;  _v  = v;		
	}
	float _x, _y, _z;
	float _nx, _ny, _nz;
	float _u, _v; // texture coordinates
	
	static const DWORD FVF;
};

namespace d3d{
	// COM 인터페이스를 해제하고 null로 지정
	template<class T> void Release(T t){
		if(t){
			t->Release();
			t = 0;
		}
	}

	// 저장고의 객체를 제거하고 포인터를 null로 지정
	template<class T> void Delete(T t){
		if(t){
			delete t;
			t = 0;
		}
	}

	//
	// Colors
	//
	const D3DXCOLOR      WHITE( D3DCOLOR_XRGB(255, 255, 255) );
	const D3DXCOLOR      GRAY( D3DCOLOR_XRGB(127, 127, 127) );
	const D3DXCOLOR      BLACK( D3DCOLOR_XRGB(  0,   0,   0) );
	const D3DXCOLOR        RED( D3DCOLOR_XRGB(255,   0,   0) );
	const D3DXCOLOR      GREEN( D3DCOLOR_XRGB(  0, 255,   0) );
	const D3DXCOLOR       BLUE( D3DCOLOR_XRGB(  0,   0, 255) );
	const D3DXCOLOR     YELLOW( D3DCOLOR_XRGB(255, 255,   0) );
	const D3DXCOLOR       CYAN( D3DCOLOR_XRGB(  0, 255, 255) );
	const D3DXCOLOR    MAGENTA( D3DCOLOR_XRGB(255,   0, 255) );

	const D3DXCOLOR BEACH_SAND( D3DCOLOR_XRGB(255, 249, 157) );
	const D3DXCOLOR DESERT_SAND( D3DCOLOR_XRGB(250, 205, 135) );

	const D3DXCOLOR LIGHTGREEN( D3DCOLOR_XRGB( 60, 184, 120) );
	const D3DXCOLOR  PUREGREEN( D3DCOLOR_XRGB(  0, 166,  81) );
	const D3DXCOLOR  DARKGREEN( D3DCOLOR_XRGB(  0, 114,  54) );

	const D3DXCOLOR LIGHT_YELLOW_GREEN( D3DCOLOR_XRGB(124, 197, 118) );
	const D3DXCOLOR  PURE_YELLOW_GREEN( D3DCOLOR_XRGB( 57, 181,  74) );
	const D3DXCOLOR  DARK_YELLOW_GREEN( D3DCOLOR_XRGB( 25, 123,  48) );

	const D3DXCOLOR LIGHTBROWN(D3DCOLOR_XRGB(198, 156, 109));
	const D3DXCOLOR DARKBROWN( D3DCOLOR_XRGB(115, 100,  87));

	// 재질
	D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p);

	const D3DMATERIAL9 WHITE_MTRL  = InitMtrl(WHITE, WHITE, WHITE, BLACK, 2.0f);
	const D3DMATERIAL9 RED_MTRL    = InitMtrl(RED, RED, RED, BLACK, 2.0f);
	const D3DMATERIAL9 GREEN_MTRL  = InitMtrl(GREEN, GREEN, GREEN, BLACK, 2.0f);
	const D3DMATERIAL9 BLUE_MTRL   = InitMtrl(BLUE, BLUE, BLUE, BLACK, 2.0f);
	const D3DMATERIAL9 YELLOW_MTRL = InitMtrl(YELLOW, YELLOW, YELLOW, BLACK, 2.0f);

	// 조명
	D3DLIGHT9 InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color);
	D3DLIGHT9 InitPointLight(D3DXVECTOR3* position, D3DXCOLOR* color);
	D3DLIGHT9 InitSpotLight(D3DXVECTOR3* position, D3DXVECTOR3* direction, D3DXCOLOR* color);

	// 폰트
	ID3DXFont* IniFont(int wid, int hei, int wei, bool ital, char* style);
    
	const DWORD        NumSubSets = 3;

	void SetupMatrices();
	void RenderTerrain();
	void RenderBG();
	void RenderMirror();
	void RenderShadow();
	void RenderBoundingVolume();
	void RenderParticle();

	const float INFINITY = FLT_MAX;
	const float EPSILON = 0.001f;

	// 경계 박스
	struct BoundingBox{
		BoundingBox();

		bool isPointInside(D3DXVECTOR3& p);
		D3DXVECTOR3 _min;
		D3DXVECTOR3 _max;
	};

	// 경계 구체
	struct BoundingSphere{
		BoundingSphere();

		D3DXVECTOR3 _center;
		float _radius;
	};

	// 광선 클래스
	struct Ray	{
		D3DXVECTOR3 _origin;
		D3DXVECTOR3 _direction;
	};

	bool ComputeBoundingSphere(ID3DXMesh* mesh, d3d::BoundingSphere* sphere);
	bool ComputeBoundingBox(ID3DXMesh* mesh, d3d::BoundingBox* box);

	// 범위 안에 있는 임의의 float를 리턴
	float GetRandomFloat(float lowBound, float highBound);

	// 최소점 min과 최대점 max로 정의된 상자 내의 임의 벡터를 출력
	void GetRandomVector(D3DXVECTOR3* out, D3DXVECTOR3* min, D3DXVECTOR3* max);

	// 1D 선을 따르는 기본 선형 보간
	float Lerp(float a, float b, float t);
	
	// float -> DWORD 형변환
	DWORD FtoDw(float f);

	// 픽킹 관련
	Ray CalcPickingRay(int x, int y);
	void TransformRay(d3d::Ray* ray, D3DXMATRIX* T);
	bool raySphereIntersectionTest(Ray* ray, BoundingSphere* sphere);

	//  
	void SetCameraTerrain();
}

#endif