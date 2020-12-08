////////////////////////////////////////////////////
// AI를 담당 관리 클래스
////////////////////////////////////////////////////
#ifndef _AIManager_H_
#define _AIManager_H_

class CAIManager{
public:
	typedef enum CommandType{ATTACK=0, RUNAWAY, DEFENSE, NONE} COMMANDTYPE;
	typedef enum BoundType{ENTITY = 0, DAMAGE, NOTHING} BOUNDTYPE;

private:
	CHero* _hero;
	CFlower* _flower;
	CCart* _cart;

	CDLinkedList<CCharacterEntity*> _OurForceList;

	CDustKid* _dustKid;
	CWorker* _worker;
	CMiniWorker* _miniWorker;
	CGateKeeper* _gateKeeper;
	CDustKing* _dustKing;

	COMMANDTYPE _commandType;	

	d3d::BoundingBox _moveRange;		// 주인공을 중심으로한 우리편 이동 범위 공간
	d3d::BoundingBox _attackRange;		// 주인공을 중심으로한 우리편 공격 범위 공간
	
	CTimer* _commandTime;
	DWORD _commandTimeGap;
	DWORD _attackTimeGap;
	DWORD _avoidTimeGap;
	DWORD _defenseTimeGap;

private:
	CAIManager();
	CAIManager(const CAIManager&);
	CAIManager& operator =(const CAIManager&);

public:
	~CAIManager();
	static CAIManager* Instance(){
		static CAIManager instance;

		return &instance;
	}

	void InsertOurForce(CBluePrint::BLUEPRINTTYPE p_eBluePrintType);

	// command
	void SetCommandType(COMMANDTYPE p_eCommand){_commandType = p_eCommand;}
	COMMANDTYPE GetCommandType(){return _commandType;}

	DWORD GetCommandTimeGap(){return _commandTimeGap;}
	DWORD GetAttackTimeGap(){return _attackTimeGap;}
	DWORD GetDefenseTimeGap(){return _defenseTimeGap;}
	DWORD GetAvoidTimeGap(){return _avoidTimeGap;}
	void SetCommandTimeGap(DWORD p_dwGap){_commandTimeGap = p_dwGap;}
	void SetCommandTime(DWORD p_dwGap){_commandTime = new CTimer(p_dwGap);}
	CTimer* GetCommandTime(){return _commandTime;}

	////////////////////////////////////////
	// AI

	// Main Character Update
	void HeroUpdate();
	void CartUpdate();
	void FlowerUpdate();

	// AI 업데이트
	void AIUpdate();

	// AI 생존여부 확인
	void AIIsLive();

	// 아군 상태 초기화
	void InitOurForce();

	// AI 명령
	void OrderToAI();

	// AI 이동범위 관련
	void CheckMoveRange();
	void CheckMoveRange(CBody* p_pBody);
	d3d::BoundingBox* GetMoveRange(){return &_moveRange;}

	// AI 공격범위 관련
	void CheckAttackRange();
	d3d::BoundingBox* GetAttackRange(){return &_attackRange;}

	// AI 데미지 계산
	int ComputeAverageDamage(float p_fMin, float p_fMax);

	// Buff Character Check
	bool BuffCharacterCheck();

	// AI 살아있는 여부 계산 for Enemy
	bool AILiveCheckToYawoAndKirit();

	///////////////////////////////
	// Enemy
	void CreateDustKid(){_dustKid = new CDustKid(ID_DUSTKID); EntityDB->RegisterEntity(_dustKid);}
	void DustKidUpdate();
	void ResetDustKid(){EntityDB->RemoveEntity(_dustKid); d3d::Delete<CDustKid*>(_dustKid); _dustKid = new CDustKid(ID_DUSTKID); EntityDB->RegisterEntity(_dustKid);}

	void CreateWorker(){_worker = new CWorker(ID_WORKER); EntityDB->RegisterEntity(_worker);}
    void WorkerUpdate();
	void ResetWorker(){EntityDB->RemoveEntity(_worker); d3d::Delete<CWorker*>(_worker);_worker = new CWorker(ID_WORKER); EntityDB->RegisterEntity(_worker);}

	void CreateMiniWorker(){_miniWorker = new CMiniWorker(ID_MINIWORKER); EntityDB->RegisterEntity(_miniWorker);}
    void MiniWorkerUpdate();
	void ResetMiniWorker(){EntityDB->RemoveEntity(_miniWorker); d3d::Delete<CMiniWorker*>(_miniWorker);_miniWorker = new CMiniWorker(ID_MINIWORKER); EntityDB->RegisterEntity(_miniWorker);}

	void CreateGateKeeper(){_gateKeeper = new CGateKeeper(ID_GATEKEEPER); EntityDB->RegisterEntity(_gateKeeper);}
	void GateKeeperUpdate();
	void ResetGateKeeper(){EntityDB->RemoveEntity(_gateKeeper); d3d::Delete<CGateKeeper*>(_gateKeeper);_gateKeeper = new CGateKeeper(ID_GATEKEEPER); EntityDB->RegisterEntity(_gateKeeper);}

	void CreateDustKing(){_dustKing = new CDustKing(ID_DUSTKING); EntityDB->RegisterEntity(_dustKing);}
	void DustKingUpdate();
	void ResetDustKing(){EntityDB->RemoveEntity(_dustKing); d3d::Delete<CDustKing*>(_dustKing); _dustKing = new CDustKing(ID_DUSTKING); EntityDB->RegisterEntity(_dustKing);}

	// Entity Get
	CHero* GetHero(){return _hero;}
	CFlower* GetFlower(){return _flower;}
	CCart* GetCart(){return _cart;}

	CDLinkedList<CCharacterEntity*>* GetOurForceList(){return &_OurForceList;}
	CCharacterEntity* GetOurForceEntityFromOwner(CBaseObject::Owner p_eOwner);
	CCharacterEntity* GetOurForceEntityFromID(int p_nID);

	CDustKid* GetDustKid(){return _dustKid;}
	CWorker* GetWorker(){return _worker;}
	CMiniWorker* GetMiniWorker(){return _miniWorker;}
	CGateKeeper* GetGateKeeper(){return _gateKeeper;}
	CDustKing* GetDustKing(){return _dustKing;}
};

#define AIMgr CAIManager::Instance()

#endif