////////////////////////////////////////////////////////////////////////////////
// ��ü���� ���� �������� ������� �ο��ϱ� ���� �μ�ǰ Ŭ����
////////////////////////////////////////////////////////////////////////////////
#ifndef _Attachment_H_
#define _Attachment_H_

class CAttachment : public COrgan{
private:
	// ������ �μӹ��� ������ Ÿ��
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

	// MainMenu ��Ʈ �Լ�
	virtual bool GetbIsBeltEnd(){return bIsBeltEnd;}
	virtual void SetbIsBeltEnd(bool p_bIs){bIsBeltEnd = p_bIs;}
};

#endif