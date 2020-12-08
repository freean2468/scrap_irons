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
	// 카메라의 축이 서로 직각이 되도록 한다.
	D3DXVec3Normalize(&_look, &_look);
	
	D3DXVec3Cross(&_up, &_look, &_right);
	D3DXVec3Normalize(&_up, &_up);

	D3DXVec3Cross(&_right, &_up, &_look);
	D3DXVec3Normalize(&_right, &_right);

	// 뷰 행렬을 구성한다.
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

	// TWODEMENTION라면 카메라 회전 기능을 사용할 수 없다.
	if(_cameraType == TWODEMENTION)
		return;

	D3DXMatrixRotationAxis(&T, &_right, angle);

	// _right를 기준으로 _up과 _look을 회전한다.
	D3DXVec3TransformCoord(&_up, &_up, &T);
	D3DXVec3TransformCoord(&_look, &_look, &T);
}

void CCamera::yaw(float angle){
	D3DXMATRIX T;

	// TWODEMENTION라면 카메라 회전 기능을 사용할 수 없다.
	if(_cameraType == TWODEMENTION)
		return;

	// 지상의 물체에 대해서는 월드 y(0, 1, 0)를 기준으로 회전한다.
	if(_cameraType == LANDOBJECT)
		D3DXMatrixRotationY(&T, angle);

	// 비행 물체에 대해서는 원래의 상향 벡터로 회전한다.
	if(_cameraType == AIRCRAFT)
		D3DXMatrixRotationAxis(&T, &_up, angle);

	// rotate _right and _look around _up or y_axis
	D3DXVec3TransformCoord(&_right, &_right, &T);
	D3DXVec3TransformCoord(&_look, &_look, &T);
}

void CCamera::roll(float angle){
	// TWODEMENTION라면 카메라 회전 기능을 사용할 수 없다.
	if(_cameraType == TWODEMENTION)
		return;

	// 비행 타입일 경우만 회전한다.
	if(_cameraType == AIRCRAFT){
		D3DXMATRIX T;
		D3DXMatrixRotationAxis(&T, &_look, angle);

		// look 벡터 기준으로 위와 오른쪽으로 회전한다.
		D3DXVec3TransformCoord(&_right, &_right, &T);
		D3DXVec3TransformCoord(&_up, &_up, &T);
	}
}

void CCamera::walk(float units){
	// TWODEMENTION라면 깊이 이동을 할 수 없다.
	if(_cameraType == TWODEMENTION)
		return;

	if(units == 0)
		return;
	// 지상의 물체는 xz평면으로 움직임을 제한한다.
	if(_cameraType == LANDOBJECT){
		// 바라보고 있는 방향을 계산한다.
		D3DXVECTOR3 dir;
		D3DXVECTOR3 WORLD_UP(0.0f, 1.0f, 0.0f);

		D3DXVec3Cross(&dir, &_right, &WORLD_UP);
		_pos += D3DXVECTOR3(dir.x, 0.0f, dir.z) * units;
	}

	if(_cameraType == AIRCRAFT)
		_pos += _look*units;
}

void CCamera::strafe(float units){
	// TWODEMENTION 카메라 좌우 이동
	if(_cameraType == TWODEMENTION)
		_pos+=D3DXVECTOR3(_right.x, 0.0f, _right.z) * units;

	// 지상의 물체는 xz 평면으로 움직임을 제한한다.
	if(_cameraType == LANDOBJECT)
		_pos+=D3DXVECTOR3(_right.x, 0.0f, _right.z) * units;

	if(_cameraType == AIRCRAFT)
		_pos += _right * units;
}

void CCamera::fly(float units){
	// TWODEMENTION 카메라 상하 이동, yz명면으로 움직임을 제한한다.
	if(_cameraType == TWODEMENTION)
		_pos+= D3DXVECTOR3(0.0f, _up.y, _up.z) * units;

	if(_cameraType == AIRCRAFT)
		_pos += _up * units;
}

// vPos를 원점으로 되돌린다.
void CCamera::BackPosition(float units){
	// 2차원일 경우
	D3DXVECTOR3 ep(d3d::EPSILON,d3d::EPSILON,0.0f);
	units *= GetVelocity();

	if(_cameraType == TWODEMENTION){
		// _pos가 0이 아닐 경우
		if(_pos > ep || _pos < ep){
			// 움직임이 멈췄을 때
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

// 카메라 Zoom_in, Zoom_out을 부드럽게 조정한다
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