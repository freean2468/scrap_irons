////////////////////////////////////////////////////////////////////////////////
// 메세지 클래스
// 오브젝트의 Event Text 렌더링을 담당하는 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _Message_H_
#define _Message_H_

class CMessage : public COrgan{
private:
	COrgan* _origin;
	char* line;
	bool bUse;	// true면 출력, false 면 비출력
	ID3DXFont*	_pFont;		// 폰트 인터페이스 변수
	RECT rect;

public:
	CMessage(int id):COrgan(id){}
	CMessage(COrgan* p_pOrgan, int id, OWNER p_owner, D3DXVECTOR3 p_vPos, D3DXVECTOR3 p_vSca, D3DXVECTOR3 p_vRot, D3DXVECTOR3 p_vCen);
	virtual	~CMessage();

	virtual void Update(){}
	virtual bool HandleMessage(const Telegram& msg){return false;}

	void ReadLine(char* p_pStr);
	void RenderLine(ID3DXFont* p_pFont = 0);

	void SetUse(bool p_bool){bUse = p_bool;}
	bool GetUse(){return bUse;}

	void SetLine(char* p_pStr){line = p_pStr;}
};

#endif