/////////////////////////////////////////////////////////
// ī�޶� Ŭ����
// ��å ����
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

	float _fCameraRatio; // ī�޶� ���� :: ��� (float)(Width/Height)
	// ī�޶� �̵� ��Ȳ �ĺ�
	bool _move;
	
	// ī�޶� ���� �ܾƿ� ����
	float _zoom;

public:
	CCamera();
	CCamera(CameraType cameraType);
	~CCamera();

	void strafe(float units);	// ����/������
	void fly(float units);		// ����/�Ʒ���
	void walk(float units);		// ����/����

	void pitch(float angle);	// ���� ���ͷ� ȸ��
	void yaw(float angle);		// ���� ���ͷ� ȸ��
	void roll(float angle);		// ���� ���ͷ� ȸ��

	void GetViewMatrix(D3DXMATRIX* V);			// ���� ����Ʈ ��� ��ȯ
	void SetCameraType(CameraType cameraType);	// ī�޶� Ÿ�� ����
	void GetPosition(D3DXVECTOR3* pos);
	void SetPosition(D3DXVECTOR3* pos);
	void GetRight(D3DXVECTOR3* right);
	void GetUp(D3DXVECTOR3* up);
	void GetLook(D3DXVECTOR3* look);
	float GetRatio(){return _fCameraRatio;}
	void SetRatio(float p_fRatio){_fCameraRatio = p_fRatio;}

	float GetVelocity(){return _velocity;}
	void SetVelocity(float p_fVelocity){_velocity = p_fVelocity;}

	// ī�޶� ��ǥ�� �������� �ǵ����� ���� �Լ�
	void CallKeyDown(){_move = true;}
	void CallKeyUp(){_move = false;}
	void BackPosition(float units);

	// Zoom ���� �Լ�
	float GetZoom(){return _zoom;}
	void SetZoom(float zoom){_zoom = zoom;}
	void Zoom();
};

#endif