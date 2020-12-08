////////////////////////////////////////////////////////////////////////////////
// 신체조직 외의 유동적인 생명력을 부여하기 위한 부속품 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _Attachment_H_
#define _Attachment_H_

class CAttachment : public COrgan{
private:
	// 각각의 부속물을 구별할 타입
	static bool bIsBeltEnd;

public:
	CAttachment(int id):COrgan(id){}
	CAttachment(int id, OWNER p_owner, D3DXVECTOR3 p_vPos, D3DXVECTOR3 p_vSca, D3DXVECTOR3 p_vRot, D3DXVECTOR3 p_vCen, int p_nAttType);
	~CAttachment();

	virtual void Update(){}
	virtual bool HandleMessage(const Telegram& msg){return false;}

	virtual int GetAttType(){return AttType;}

	// Maps
	void TransformInMainMenu(int p_nAttType, float timeDelta);
	void TransformInStageHome(int p_nAttType, float timeDelta);
	void TransformInStageFurnace(int p_nAttType, float timeDelta);

	// MainMenu 파트 함수
	virtual bool GetbIsBeltEnd(){return bIsBeltEnd;}
	virtual void SetbIsBeltEnd(bool p_bIs){bIsBeltEnd = p_bIs;}
};

#endif