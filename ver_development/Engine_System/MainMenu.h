////////////////////////////////////////////////////////////////////////////////
// 유동적인 메인메뉴 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _MainMenu_H_
#define _MainMenu_H_

class CMainMenu : public COrganEntity{
public:
	typedef enum MenuAttType {START = 0, INTRO, EXIT, TITLE, LEFT, RIGHT, ENTER, LIGHT} MENUATTTYPE;

public:
	CMainMenu(int id);
	~CMainMenu();

	virtual void TransformOrgan(float timeDelta);

	virtual void Update(){this->CalculationOrgan(EngineMgr->GetTimeDelta());}
	virtual bool HandleMessage(const Telegram& msg){return false;}

	virtual void CalculationOrgan(float timeDelta);
};

#endif