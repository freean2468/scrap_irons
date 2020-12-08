////////////////////////////////////////////////////////////////////////////////
// ��ü ����� ������ Entity ���� Ŭ���� 
////////////////////////////////////////////////////////////////////////////////
#ifndef _OrganEntity_H_
#define _OrganEntity_H_

// ������ Entity���� ������ ������ ���� �� �ֵ��� ����.

class COrganEntity : public CBaseObject{
//public:
//	typedef enum ORGANIZING {BODY = 0, LEGLEFT, LEGRIGHT, FOOTLEFT, FOOTRIGHT, ARMLEFT, ARMRIGHT,
//								BRAIN, THROAT, EYELEFT, EYERIGHT, PUPILLEFT, PUPILRIGHT};
protected:
	CBody* _body;
	CMessage* _message;

	// ���� �ʿ��� ���� ������ ��ü �����
	CArray<CAttachment*> _attachment;

private:
	// ��ü ��� ��ġ ���� ���� ����
	D3DXVECTOR3 _vChainPos; // ��ġ
	D3DXVECTOR3 _vChainSca;	// ������
	D3DXVECTOR3 _vChainRot;	// ȸ��
	D3DXVECTOR3 _vChainCen;	// ����

public:
	COrganEntity(int id);
	virtual ~COrganEntity();

	// ���� ���� �Լ�
	virtual void Render(D3DXVECTOR3* p_vPos, D3DXVECTOR3* p_vSca, D3DXVECTOR3* p_vRot, D3DXVECTOR3* p_vCen){};
	virtual void CalculationOrgan(float timeDelta) = 0;
	virtual void RenderOrgan();

	// ��ũ��Ʈ�κ��� EntityData Load�Լ�
	virtual void LoadEntityData(char* name, COrganEntity* p_pEntity);

	// ü�� ���� �ʱ�ȭ �Լ�
	virtual InitChainVector(){_vChainPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);_vChainSca = D3DXVECTOR3(1.0f, 1.0f, 1.0f);_vChainRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);_vChainCen = D3DXVECTOR3(0.0f, 0.0f, 0.0f);}

	// ü�� ���� �ٵ� ���� �Լ�
	virtual void BodySetting(){_body->SettingOrgan(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());	}
	virtual void BodyOnlyPosSetting(){_body->SettingOrgan(GetChainPos(), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f)); }

	// ü�� ���� Get�Լ�
	virtual D3DXVECTOR3* GetChainPos(){return &_vChainPos;}
	virtual D3DXVECTOR3* GetChainSca(){return &_vChainSca;}
	virtual D3DXVECTOR3* GetChainRot(){return &_vChainRot;}
	virtual D3DXVECTOR3* GetChainCen(){return &_vChainCen;}
	
	// �� Ŭ���� Set�Լ�
	virtual	void SetBody(CBody* body){_body = body;}
	virtual	void SetMessage(CMessage* message){_message = message;}
	virtual void SetAttachment(CAttachment* Attachment, int index){_attachment.Insert(Attachment, index); _attachment.IncreseCount();}
	
	// �� Ŭ���� Get�Լ�
	virtual	CBody* GetBody(){return _body;}
	virtual	CMessage* GetMessage(){return _message;}
	virtual CArray<CAttachment*>* GetAttachmentArray();
	virtual CAttachment* GetAttachment(int index);
	virtual CAttachment* GetAttachmentFromType(int p_nType);
	virtual int GetAttachmentIndex(int p_nType);

	// ��ü ��� ���� �Լ�
	virtual void TransformOrgan(float timeDelta){}
	virtual void RotationZOrgan(D3DXVECTOR3* p_vRot, float p_fScalar);
	virtual void RotationYOrgan(D3DXVECTOR3* p_vRot, float p_fScalar);
	virtual void RotationXOrgan(D3DXVECTOR3* p_vRot, float p_fScalar);
	virtual void TranslationXOrgan(D3DXVECTOR3* p_vPos, float p_fScalar);
	virtual void TranslationYOrgan(D3DXVECTOR3* p_vPos, float p_fScalar);
	virtual void TranslationZOrgan(D3DXVECTOR3* p_vPos, float p_fScalar);
	virtual void TranslationCenXOrgan(D3DXVECTOR3* p_vCen, float p_fScalar);
	virtual void TranslationCenYOrgan(D3DXVECTOR3* p_vCen, float p_fScalar);
	virtual void TranslationCenZOrgan(D3DXVECTOR3* p_vCen, float p_fScalar);
};

#endif