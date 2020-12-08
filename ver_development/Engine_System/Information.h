//////////////////////////////////////////////////////
// 각종 Information 관리 & 출력을 담당하는 클래스
//////////////////////////////////////////////////////
#ifndef _Information_H_
#define _Information_H_

class CInformation{
public:
	typedef enum Space {DOWN = 0, UP} SPACE;
	SPACE _space;

private:	
	/////////////////////////////////////
	// FPS 관련 변수
	DWORD FrameCntForNon;
	float TimeElapsedForNon;
	DWORD FrameCntForAdjusted;
	float TimeElapsedForAdjusted;
	float FPS;				// Engine에 의해 조정되지 않은 실제 Frame
	float FPSAdjusted;		// Engine에 의해 조정된 Frame
	char _FPSString[30];
	char _FPSAdjustedString[30];
	RECT _rect;

	/////////////////////////////////////
	// 마우스 관련 변수
	char _crdString[60];
	CCoordinates _crdAdjusted;
	CCoordinates _crdAbsoluted;

	/////////////////////////////////////
	// 카메라 관련 변수
	char _cameraString[60];
	D3DXVECTOR3 _nowPos;
	
	char _distanceString[30];
	D3DXVECTOR3 _disPos;
	D3DXVECTOR3 _firstPos;
	D3DXVECTOR3 _lastPos;

public:
	CInformation();
	~CInformation();

	////////////////////////////////////
	// 각종 정보 계산 함수
	void CalcInformation(float timeDelta);
	void FPSCalculation(float timeDelta);						 // 본래의 FPS 계산
	void FPSAdjustedCalculation(float timeDelta);				 // Engine에 의해 조정된 FPS를 계산

	// FPS 관련
	float GetFPSofOrgin(){return FPS;}
	
	////////////////////////////////////
	// 마우스 관련 함수
	CCoordinates GetCrdAdjusted(){return _crdAdjusted;}
	void SetAdjustedX(float _x){_crdAdjusted.SetX(_x);}
	void SetAdjustedY(float _y){_crdAdjusted.SetY(_y);}
	float GetAdjustedX(){return _crdAdjusted.GetX();}
	float GetAdjustedY(){return _crdAdjusted.GetY();}
	void SetAbsolutedX(float _x){_crdAbsoluted.SetX(_x);}
	void SetAbsolutedY(float _y){_crdAbsoluted.SetY(_y);}
	float GetAbsolutedX(){return _crdAbsoluted.GetX();}
	float GetAbsolutedY(){return _crdAbsoluted.GetY();}

	////////////////////////////////////
	// 카메라 관련 함수
	void SetCameraPos(D3DXVECTOR3* pos){_nowPos = *pos;}
	D3DXVECTOR3* GetCameraPos(){return &_nowPos;}
	void CoordinatesCalculation();	// 인터페이스 제공

	////////////////////////////////////
	// 각종 정보 출력 함수
	void DrawInformation(ID3DXFont* font, ID3DXSprite* sprite);
};

#endif