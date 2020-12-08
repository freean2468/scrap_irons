//////////////////////////////////////////////////////
// ���� Information ���� & ����� ����ϴ� Ŭ����
//////////////////////////////////////////////////////
#ifndef _Information_H_
#define _Information_H_

class CInformation{
public:
	typedef enum Space {DOWN = 0, UP} SPACE;
	SPACE _space;

private:	
	/////////////////////////////////////
	// FPS ���� ����
	DWORD FrameCntForNon;
	float TimeElapsedForNon;
	DWORD FrameCntForAdjusted;
	float TimeElapsedForAdjusted;
	float FPS;				// Engine�� ���� �������� ���� ���� Frame
	float FPSAdjusted;		// Engine�� ���� ������ Frame
	char _FPSString[30];
	char _FPSAdjustedString[30];
	RECT _rect;

	/////////////////////////////////////
	// ���콺 ���� ����
	char _crdString[60];
	CCoordinates _crdAdjusted;
	CCoordinates _crdAbsoluted;

	/////////////////////////////////////
	// ī�޶� ���� ����
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
	// ���� ���� ��� �Լ�
	void CalcInformation(float timeDelta);
	void FPSCalculation(float timeDelta);						 // ������ FPS ���
	void FPSAdjustedCalculation(float timeDelta);				 // Engine�� ���� ������ FPS�� ���

	// FPS ����
	float GetFPSofOrgin(){return FPS;}
	
	////////////////////////////////////
	// ���콺 ���� �Լ�
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
	// ī�޶� ���� �Լ�
	void SetCameraPos(D3DXVECTOR3* pos){_nowPos = *pos;}
	D3DXVECTOR3* GetCameraPos(){return &_nowPos;}
	void CoordinatesCalculation();	// �������̽� ����

	////////////////////////////////////
	// ���� ���� ��� �Լ�
	void DrawInformation(ID3DXFont* font, ID3DXSprite* sprite);
};

#endif