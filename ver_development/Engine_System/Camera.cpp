#include "../BaseHeader.h"

CCamera::CCamera(){
	_cameraType = AIRCRAFT;

	_pos   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	_up    = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	_look  = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	_move = false;
	_zoom = _pos.z;

	_fCameraRatio = (float)((float)(SYSTEMWIDTH)/(float)(SYSTEMHEIGHT));
}

CCamera::CCamera(CameraType cameraType){
	_cameraType = cameraType;

	if(cameraType == TWODEMENTION)
		_pos   = D3DXVECTOR3(0.0f, 0.0f, -700.0f);
	else
		_pos   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	_up    = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	_look  = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	_move = false;
	_zoom = _pos.z;
}

CCamera::~CCamera(){

}

void CCamera::GetPosition(D3DXVECTOR3* pos){
	*pos = _pos;
}

void CCamera::SetPosition(D3DXVECTOR3* pos){
	_pos = *pos;
}

void CCamera::GetRight(D3DXVECTOR3* right){
	*right = _right;
}

void CCamera::GetUp(D3DXVECTOR3* up){
	*up = _up;
}

void CCamera::GetLook(D3DXVECTOR3* look){
	*look = _look;
}

void CCamera::GetViewMatrix(D3DXMATRIX* V){
	// ī�޶��� ���� ���� ������ �ǵ��� �Ѵ�.
	D3DXVec3Normalize(&_look, &_look);
	
	D3DXVec3Cross(&_up, &_look, &_right);
	D3DXVec3Normalize(&_up, &_up);

	D3DXVec3Cross(&_right, &_up, &_look);
	D3DXVec3Normalize(&_right, &_right);

	// �� ����� �����Ѵ�.
	float x = -D3DXVec3Dot(&_right, &_pos);
	float y = -D3DXVec3Dot(&_up, &_pos);
	float z = -D3DXVec3Dot(&_look, &_pos);

	(*V)(0,0) = _right.x;
	(*V)(0,1) = _up.x;
	(*V)(0,2) = _look.x;
	(*V)(0,3) = 0.0f;

	(*V)(1,0) = _right.y;
	(*V)(1,1) = _up.y;
	(*V)(1,2) = _look.y;
	(*V)(1,3) = 0.0f;

	(*V)(2,0) = _right.z;
	(*V)(2,1) = _up.z;
	(*V)(2,2) = _look.z;
	(*V)(2,3) = 0.0f;

	(*V)(3,0) = x;
	(*V)(3,1) = y;
	(*V)(3,2) = z;
	(*V)(3,3) = 1.0f;
}

void CCamera::pitch(float angle){
	D3DXMATRIX T;

	// TWODEMENTION��� ī�޶� ȸ�� ����� ����� �� ����.
	if(_cameraType == TWODEMENTION)
		return;

	D3DXMatrixRotationAxis(&T, &_right, angle);

	// _right�� �������� _up�� _look�� ȸ���Ѵ�.
	D3DXVec3TransformCoord(&_up, &_up, &T);
	D3DXVec3TransformCoord(&_look, &_look, &T);
}

void CCamera::yaw(float angle){
	D3DXMATRIX T;

	// TWODEMENTION��� ī�޶� ȸ�� ����� ����� �� ����.
	if(_cameraType == TWODEMENTION)
		return;

	// ������ ��ü�� ���ؼ��� ���� y(0, 1, 0)�� �������� ȸ���Ѵ�.
	if(_cameraType == LANDOBJECT)
		D3DXMatrixRotationY(&T, angle);

	// ���� ��ü�� ���ؼ��� ������ ���� ���ͷ� ȸ���Ѵ�.
	if(_cameraType == AIRCRAFT)
		D3DXMatrixRotationAxis(&T, &_up, angle);

	// rotate _right and _look around _up or y_axis
	D3DXVec3TransformCoord(&_right, &_right, &T);
	D3DXVec3TransformCoord(&_look, &_look, &T);
}

void CCamera::roll(float angle){
	// TWODEMENTION��� ī�޶� ȸ�� ����� ����� �� ����.
	if(_cameraType == TWODEMENTION)
		return;

	// ���� Ÿ���� ��츸 ȸ���Ѵ�.
	if(_cameraType == AIRCRAFT){
		D3DXMATRIX T;
		D3DXMatrixRotationAxis(&T, &_look, angle);

		// look ���� �������� ���� ���������� ȸ���Ѵ�.
		D3DXVec3TransformCoord(&_right, &_right, &T);
		D3DXVec3TransformCoord(&_up, &_up, &T);
	}
}

void CCamera::walk(float units){
	// TWODEMENTION��� ���� �̵��� �� �� ����.
	if(_cameraType == TWODEMENTION)
		return;

	if(units == 0)
		return;
	// ������ ��ü�� xz������� �������� �����Ѵ�.
	if(_cameraType == LANDOBJECT){
		// �ٶ󺸰� �ִ� ������ ����Ѵ�.
		D3DXVECTOR3 dir;
		D3DXVECTOR3 WORLD_UP(0.0f, 1.0f, 0.0f);

		D3DXVec3Cross(&dir, &_right, &WORLD_UP);
		_pos += D3DXVECTOR3(dir.x, 0.0f, dir.z) * units;
	}

	if(_cameraType == AIRCRAFT)
		_pos += _look*units;
}

void CCamera::strafe(float units){
	// TWODEMENTION ī�޶� �¿� �̵�
	if(_cameraType == TWODEMENTION)
		_pos+=D3DXVECTOR3(_right.x, 0.0f, _right.z) * units;

	// ������ ��ü�� xz ������� �������� �����Ѵ�.
	if(_cameraType == LANDOBJECT)
		_pos+=D3DXVECTOR3(_right.x, 0.0f, _right.z) * units;

	if(_cameraType == AIRCRAFT)
		_pos += _right * units;
}

void CCamera::fly(float units){
	// TWODEMENTION ī�޶� ���� �̵�, yz������� �������� �����Ѵ�.
	if(_cameraType == TWODEMENTION)
		_pos+= D3DXVECTOR3(0.0f, _up.y, _up.z) * units;

	if(_cameraType == AIRCRAFT)
		_pos += _up * units;
}

// vPos�� �������� �ǵ�����.
void CCamera::BackPosition(float units){
	// 2������ ���
	D3DXVECTOR3 ep(d3d::EPSILON,d3d::EPSILON,0.0f);
	units *= GetVelocity();

	if(_cameraType == TWODEMENTION){
		// _pos�� 0�� �ƴ� ���
		if(_pos > ep || _pos < ep){
			// �������� ������ ��
			if(_move == false){
				if(_pos.x > ep.x){					
					_pos -= D3DXVECTOR3(_right.x, 0.0f, _right.z) * units;
					if(_pos.x < ep.x)
						_pos.x = 0.0f;
				}
				else if(_pos.x < -ep.x){
					_pos += D3DXVECTOR3(_right.x, 0.0f, _right.z) * units;
					if(_pos.x > ep.x)
						_pos.x = 0.0f;
				}

				if(_pos.y > ep.y){
					_pos -= D3DXVECTOR3(0.0f, _up.y, _up.z) * units;
					if(_pos.y < ep.y)
						_pos.y = 0.0f;
				}
				else if(_pos.y < -ep.y){
					_pos +=  D3DXVECTOR3(0.0f, _up.y, _up.z) * units;
					if(_pos.y > ep.y)
						_pos.y = 0.0f;
				}	
			}
		}
	}
}

// ī�޶� Zoom_in, Zoom_out�� �ε巴�� �����Ѵ�
void CCamera::Zoom(){
	if(_pos.z != _zoom){
		if(_pos.z > _zoom){
			_pos.z -= 0.5f;
		}
		else if(_pos.z < _zoom){
			_pos.z += 0.5f;
		}
	}
}