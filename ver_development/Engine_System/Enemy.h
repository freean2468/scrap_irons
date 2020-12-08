////////////////////////////////////////////////////////////////////////////////
// 적 캐릭터 구현 클래스
////////////////////////////////////////////////////////////////////////////////
#ifndef _Enemy_H_
#define _Enemy_H_

class CEnemy : public COrganEntity{
public:
	typedef enum EnemyType{STANDARD = 0} ENEMYTYPE;
	ENEMYTYPE EnemyType;

public:
	CEnemy(int id);
	~CEnemy();

	virtual void Update(){}
	virtual bool HandleMessage(const Telegram& msg){return false;}
	virtual void CalculationOrgan(float timeDelta){}
};

#endif