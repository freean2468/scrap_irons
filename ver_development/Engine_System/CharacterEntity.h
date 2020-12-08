////////////////////////////////////////////////////////////////////////////////
// Character�� Ư���� ���� Entity���� Base class
////////////////////////////////////////////////////////////////////////////////
#ifndef _CharacterEntity_H_
#define _CharacterEntity_H_

class CCharacterEntity : public COrganEntity{
public:
	typedef enum TribeType{NOTHING, IRON, DUST} TRIBETYPE;
	typedef enum HealthyState{NONE, HEALTHFUL, NORMAL, WEAK} HEALTHSTATE;
	typedef enum DamagedType{PAT, SPRINGUP, SHOCK} DAMAGEDTYPE;

private:
	// ����
	TRIBETYPE _tribeType;

	// �ּ� �ִ� ������
	float _minDamage;
	float _maxDamage;
	
	// ����
	float _def;
	// ü�� & �ǰ�����
	int _maxHealthy;
	int _nowHealthy;
	HEALTHSTATE _healthState;

	// ���� ����
	bool _live;

	// �������� ��
	float _force;
	
	// ������ ����
	D3DXVECTOR3 _destination;

	// �� ��� ����
	bool _bIsForce;

	// ����, �̵� ���� ����
	bool _canAttack;
	bool _canMove;

	// ��� ����
	d3d::BoundingBox _attackBound;
	d3d::BoundingBox _entityBound;

	ID3DXFont* _boundFont;

	// ������ �Ÿ�
	float _distance;

	// ���� ���� �ִ���
	bool _lookEnemy;

	int _attackTimeGap;

	CTimer* _attackTime;		// ���� ���ݱ��� �ɸ��� �ð�
	CTimer* _applyTime;			// ���� ������ ���� ������ �ɸ��� �ð�

public:
	CCharacterEntity(int id);
	virtual ~CCharacterEntity();

	// Bound Update & RenderForTest
	virtual void BoundUpdate() = 0;
	virtual void BoundRender();

	virtual void InitHealthy(int p_nHealthy){_nowHealthy = _maxHealthy = p_nHealthy;}
	virtual void Damaged(float p_fX, float p_fY, int p_nDamage);
	virtual void ApplyDamageWithEffect(float p_fX, float p_fY, int p_nDamage);
	virtual void ApplyDamageEnemyToOurForce(DAMAGEDTYPE p_eType = PAT, DWORD p_dwApply = 0);
	virtual void ApplyDamageEnemyToOurForceByEntity(COrgan* p_pEntity, DAMAGEDTYPE p_eType = PAT, DWORD p_dwApply = 0);
	virtual void ApplyDamageOurForceToEnemy();
	virtual void ComputeEntityBound();
	virtual bool ComputeEntityBound(CCharacterEntity* p_pEntity);
	virtual void ComputeDamageBound();
	virtual bool EntityMove(float* op_pDeltaDistance = NULL);
	virtual bool EntityAttackToEnemy();
	virtual bool EntityAttackToOurForce();
	virtual void CheckHealthState();

	// SetGet �Լ���
	virtual void SetTribeType(TRIBETYPE p_eTribe){_tribeType = p_eTribe;}
	virtual TRIBETYPE GetTribeType(){return _tribeType;}
	virtual void SetEntityBound(D3DXVECTOR3* p_pMin, D3DXVECTOR3* p_pMax){
		_entityBound._min.x = p_pMin->x; _entityBound._min.y = p_pMin->y; _entityBound._min.z = p_pMin->z;
		_entityBound._max.x = p_pMax->x; _entityBound._max.y = p_pMax->y; _entityBound._max.z = p_pMax->z;
	}
	virtual void SetAttackBound(D3DXVECTOR3* p_pMin, D3DXVECTOR3* p_pMax){
		_attackBound._min.x = p_pMin->x; _attackBound._min.y = p_pMin->y; _attackBound._min.z = p_pMin->z;
		_attackBound._max.x = p_pMax->x; _attackBound._max.y = p_pMax->y; _attackBound._max.z = p_pMax->z;
	}

    virtual d3d::BoundingBox* GetAttackBound(){return &_attackBound;}
	virtual d3d::BoundingBox* GetEntityBound(){return &_entityBound;}

	virtual void SetMinDamage(float p_fMin){_minDamage = p_fMin;}
	virtual void SetMaxDamage(float p_fMax){_maxDamage = p_fMax;}
	virtual float GetMinDamage(){return _minDamage;}
	virtual float GetMaxDamage(){return _maxDamage;}

	virtual void SetDef(float p_fDef){_def = p_fDef;}
	virtual float GetDef(){return _def;}
	virtual void SetHealthy(int p_nHealthy){_nowHealthy = p_nHealthy;}
	virtual float GetNowHealthy(){return (float)_nowHealthy;}
	virtual float GetMaxHealthy(){return (float)_maxHealthy;}
	virtual void SetHealthState(HEALTHSTATE p_eState){_healthState = p_eState;}
	virtual HEALTHSTATE GetHealthState(){return _healthState;} 

	virtual void SetLive(bool p_bool){_live = p_bool;}
	virtual bool GetLive(){return _live;}

	virtual void SetForce(float p_fForce){_force = p_fForce;}
	virtual float GetForce(){return _force;}
	virtual void SetForceOnOff(bool p_bool){_bIsForce;}
	virtual bool GetForceOnOff(){return _bIsForce;}

	virtual void SetDestinationX(float p_fDestinationX){_destination.x = p_fDestinationX;}
	virtual void SetDestination(D3DXVECTOR3* p_pPos){_destination = *p_pPos;}
	virtual D3DXVECTOR3* GetDestination(){return &_destination;}

	virtual void FaceToDestination();

	virtual void SetCanAttack(bool p_bool){_canAttack = p_bool;}
	virtual void SetCanMove(bool p_bool){_canMove = p_bool;}
	virtual bool GetCanAttack(){return _canAttack;}
	virtual bool GetCanMove(){return _canMove;}

	virtual ID3DXFont* GetBoundFont(){return _boundFont;}

	virtual void SetDistance(float t_fDis){_distance = t_fDis;}
	virtual float GetDistance(){return _distance;}

	virtual void SetLookEnemy(bool p_bool){_lookEnemy = p_bool;}
	virtual bool GetLookEnemy(){return _lookEnemy;}

	virtual CTimer* GetAttackTime(){return _attackTime;}
	virtual void SetAttackTime(int p_nGap){_attackTime = new CTimer(p_nGap);}
	virtual void SetAttackTimeGap(int p_nGap){_attackTimeGap = p_nGap;}
	virtual int GetAttackTimeGap(){return _attackTimeGap;}

	virtual void SetApplyTime(DWORD p_dwApply){_applyTime = new CTimer(p_dwApply);}
	virtual CTimer* GetApplyTime(){return _applyTime;}
};

#endif