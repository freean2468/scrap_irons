////////////////////////////////////////////////////////////////////////////////
// 신체기관 공통 조상 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _Organ_H_
#define _Organ_H_

class COrgan : public CBaseObject{
protected:
	// 기관 고유의 Transform 정보
	D3DXVECTOR3 _vPrimitivePos;
	D3DXVECTOR3 _vPrimitiveSca;
	D3DXVECTOR3 _vPrimitiveRot;

	// 중점 정보
	D3DXVECTOR3 _vPrimitiveCen;

	// 각도 상태
	// 최대라면 true, 최소라면 false
	bool _angleState;

	// 이동 상태
	// 최대라면 true, 최소라면 false
	bool _moveState;

	// 투명 상태
	// 최대라면 true, 최소라면 false
	bool _alphaState;

	// 스케일 상태
	// 최대라면 true, 최소라면 false
	bool _scaleState;

	// 가속도
	float _velocity;

public:
	COrgan(int id);
	virtual ~COrgan();

	virtual void SettingOrgan(D3DXVECTOR3* p_pChainPos, D3DXVECTOR3* p_pChainSca, D3DXVECTOR3* p_pChainRot, D3DXVECTOR3* p_pChainCen);
	virtual void SettingOrgan(D3DXVECTOR3* p_pChainPos, D3DXVECTOR3* p_pChainCen);
	virtual void SettingJointOrgan(D3DXVECTOR3* p_pChainRot, D3DXVECTOR3* p_pChainCen);

	// Get 함수	
	// 움직이는 건 오른쪽_몸을 기준으로 한다.
	virtual D3DXVECTOR3* GetPriPosRight(){return &_vPrimitivePos;}
	virtual D3DXVECTOR3* GetPriPosLeft(){return &_vPrimitivePos;}
	virtual D3DXVECTOR3* GetPriPos(){return &_vPrimitivePos;}
	virtual D3DXVECTOR3* GetPriSca(){return &_vPrimitiveSca;}
	virtual D3DXVECTOR3* GetPriRot(){return &_vPrimitiveRot;}
	virtual D3DXVECTOR3* GetPriCen(){return &_vPrimitiveCen;}

	virtual float GetVelocity(){return _velocity;}
	virtual void SetVelocity(float p_fVelocity){_velocity = p_fVelocity;}

	virtual float GetWidth(){return _width * _vPrimitiveSca.x;}
	virtual float GetHeight(){return _height * _vPrimitiveSca.y;}
	virtual float GetWidthHalf(){return GetWidth() / 2.0f;}
	virtual float GetHeightHalf(){return GetHeight() / 2.0f ;}

	// Set 함수
	// 움직이는 건 오른쪽_몸을 기준으로 한다.
	virtual void SetPriPosRight(D3DXVECTOR3 p_vPos){_vPrimitivePos.x = p_vPos.x; _vPrimitivePos.y = p_vPos.y; _vPrimitivePos.z = p_vPos.z;}

	// 신체 기관의 Bound영역을 가상함수를 상속받아 변형하여 사용
	virtual float GetLeft();
	virtual float GetRight();
	virtual float GetTop();
	virtual float GetBottom();
	virtual bool GetAngleState(){return _angleState;}
	virtual void SetAngleState(bool p_bool){_angleState = p_bool;}
	virtual bool GetMoveState(){return _moveState;}
	virtual void SetMoveState(bool p_bool){_moveState = p_bool;}
	virtual bool GetAlphaState(){return _alphaState;}
	virtual void SetAlphaState(bool p_bool){_alphaState = p_bool;}
	virtual bool GetScaleState(){return _scaleState;}
	virtual void SetScaleState(bool p_bool){_scaleState = p_bool;}

	virtual void preRender(D3DXVECTOR3* p_vRot);
	virtual void Render(D3DXVECTOR3* p_vPos, D3DXVECTOR3* p_vSca, D3DXVECTOR3* p_vRot, D3DXVECTOR3* p_vCen);
	virtual void RenderApplyScale(D3DXVECTOR3* p_vPos, D3DXVECTOR3* p_vSca, D3DXVECTOR3* p_vCen);
};

#endif