/////////////////////////////////////////////////////////
// 카메라 클래스
// 용책 참고
/////////////////////////////////////////////////////////
#ifndef _Camera_H_
#define _Camera_H_

class CCamera{
public:
	enum CameraType {LANDOBJECT, AIRCRAFT, TWODEMENTION};

private:
	CameraType _cameraType;
	D3DXVECTOR3 _right;
	D3DXVECTOR3 _up;
	D3DXVECTOR3 _look;
	D3DXVECTOR3 _pos;

	float _velocity;

	float _fCameraRatio; // 카메라 비율 :: 배경 (float)(Width/Height)
	// 카메라가 이동 상황 식별
	bool _move;
	
	// 카메라 줌인 줌아웃 변수
	float _zoom;

public:
	CCamera();
	CCamera(CameraType cameraType);
	~CCamera();

	void strafe(float units);	// 왼쪽/오른쪽
	void fly(float units);		// 위쪽/아래쪽
	void walk(float units);		// 앞쪽/뒤쪽

	void pitch(float angle);	// 우향 벡터로 회전
	void yaw(float angle);		// 상향 벡터로 회전
	void roll(float angle);		// 전방 벡터로 회전

	void GetViewMatrix(D3DXMATRIX* V);			// 현재 뷰포트 행렬 반환
	void SetCameraType(CameraType cameraType);	// 카메라 타입 지정
	void GetPosition(D3DXVECTOR3* pos);
	void SetPosition(D3DXVECTOR3* pos);
	void GetRight(D3DXVECTOR3* right);
	void GetUp(D3DXVECTOR3* up);
	void GetLook(D3DXVECTOR3* look);
	float GetRatio(){return _fCameraRatio;}
	void SetRatio(float p_fRatio){_fCameraRatio = p_fRatio;}

	float GetVelocity(){return _velocity;}
	void SetVelocity(float p_fVelocity){_velocity = p_fVelocity;}

	// 카메라 좌표를 원점으로 되돌리기 위한 함수
	void CallKeyDown(){_move = true;}
	void CallKeyUp(){_move = false;}
	void BackPosition(float units);

	// Zoom 관련 함수
	float GetZoom(){return _zoom;}
	void SetZoom(float zoom){_zoom = zoom;}
	void Zoom();
};

#endif