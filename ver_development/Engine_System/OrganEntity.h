////////////////////////////////////////////////////////////////////////////////
// 신체 기관을 소유한 Entity 구현 클래스 
////////////////////////////////////////////////////////////////////////////////
#ifndef _OrganEntity_H_
#define _OrganEntity_H_

// 각각의 Entity마다 관절의 구조를 정할 수 있도록 하자.

class COrganEntity : public CBaseObject{
//public:
//	typedef enum ORGANIZING {BODY = 0, LEGLEFT, LEGRIGHT, FOOTLEFT, FOOTRIGHT, ARMLEFT, ARMRIGHT,
//								BRAIN, THROAT, EYELEFT, EYERIGHT, PUPILLEFT, PUPILRIGHT};
protected:
	CBody* _body;
	CMessage* _message;

	// 따로 필요한 몸을 구성한 신체 기관들
	CArray<CAttachment*> _attachment;

private:
	// 신체 기관 위치 설정 벡터 변수
	D3DXVECTOR3 _vChainPos; // 위치
	D3DXVECTOR3 _vChainSca;	// 스케일
	D3DXVECTOR3 _vChainRot;	// 회전
	D3DXVECTOR3 _vChainCen;	// 중점

public:
	COrganEntity(int id);
	virtual ~COrganEntity();

	// 렌더 관련 함수
	virtual void Render(D3DXVECTOR3* p_vPos, D3DXVECTOR3* p_vSca, D3DXVECTOR3* p_vRot, D3DXVECTOR3* p_vCen){};
	virtual void CalculationOrgan(float timeDelta) = 0;
	virtual void RenderOrgan();

	// 스크립트로부터 EntityData Load함수
	virtual void LoadEntityData(char* name, COrganEntity* p_pEntity);

	// 체인 벡터 초기화 함수
	virtual InitChainVector(){_vChainPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);_vChainSca = D3DXVECTOR3(1.0f, 1.0f, 1.0f);_vChainRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);_vChainCen = D3DXVECTOR3(0.0f, 0.0f, 0.0f);}

	// 체인 벡터 바디 셋팅 함수
	virtual void BodySetting(){_body->SettingOrgan(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());	}
	virtual void BodyOnlyPosSetting(){_body->SettingOrgan(GetChainPos(), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f)); }

	// 체인 벡터 Get함수
	virtual D3DXVECTOR3* GetChainPos(){return &_vChainPos;}
	virtual D3DXVECTOR3* GetChainSca(){return &_vChainSca;}
	virtual D3DXVECTOR3* GetChainRot(){return &_vChainRot;}
	virtual D3DXVECTOR3* GetChainCen(){return &_vChainCen;}
	
	// 랩 클래스 Set함수
	virtual	void SetBody(CBody* body){_body = body;}
	virtual	void SetMessage(CMessage* message){_message = message;}
	virtual void SetAttachment(CAttachment* Attachment, int index){_attachment.Insert(Attachment, index); _attachment.IncreseCount();}
	
	// 랩 클래스 Get함수
	virtual	CBody* GetBody(){return _body;}
	virtual	CMessage* GetMessage(){return _message;}
	virtual CArray<CAttachment*>* GetAttachmentArray();
	virtual CAttachment* GetAttachment(int index);
	virtual CAttachment* GetAttachmentFromType(int p_nType);
	virtual int GetAttachmentIndex(int p_nType);

	// 신체 기관 변형 함수
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