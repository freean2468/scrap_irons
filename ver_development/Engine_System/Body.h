////////////////////////////////////////////////////////////////////////////////
// 몸체 클래스
// 각종 신체에 대한 정보들의 바탕이 되는 중요한 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _Body_H_
#define _Body_H_

class CBody : public COrgan{
public:
	// 각도 상태
	// 최대라면 true, 최소라면 false
	bool _angleState;

public:
	CBody(int id):COrgan(id){}
	CBody(int id, OWNER p_owner, D3DXVECTOR3 p_vPos, D3DXVECTOR3 p_vSca, D3DXVECTOR3 p_vRot, D3DXVECTOR3 p_vCen);
	virtual	~CBody();

	virtual void Update(){}
	virtual bool HandleMessage(const Telegram& msg){return false;}

	virtual void SettingOrgan(D3DXVECTOR3* p_pChainPos, D3DXVECTOR3* p_pChainSca, D3DXVECTOR3* p_pChainRot, D3DXVECTOR3* p_pChainCen);
	virtual void Render(D3DXVECTOR3* p_vPos, D3DXVECTOR3* p_vSca, D3DXVECTOR3* p_vRot, D3DXVECTOR3* p_vCen);
};

#endif