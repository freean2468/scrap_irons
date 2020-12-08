/////////////////////////////////////////////////////
// CCameraManager클래스는 이 엔진의 시스템을 총괄함
////////////////////////////////////////////////////

#ifndef _CameraManager_H_
#define _CameraManager_H_

class CCameraManager{
public:
	typedef enum CameraMode{MAP, RELAX, COMBAT, EVENT}CAMERAMODE;

private:
	CCamera* _camera;
	D3DXVECTOR3 _vDestination;	// 카메라 목적지
	CAMERAMODE _mode;

	COrgan* _origin;

    // 생성자와 소멸자를 복사하고 할당은 private이어야 한다.
	CCameraManager(const CCameraManager&);
	CCameraManager& operator=(const CCameraManager&);
public:
	CCameraManager();
	~CCameraManager();

	static CCameraManager* Instance(){
		 static CCameraManager instance;

		 return &instance;
	}

	void CameraUpdate();

	///////////////////////////////////////////////////
	// CCameraManager 클래스 제공 함수
	void SetDestinationByMouse();
	void LimitDestination();
	void FaceToDestination();
	void CameraUp(float p_fDownLimit);
	void CameraInit(float p_fx, float p_fy, float p_fz);
	void CameraDefault();
	void CheckKey(float timeDelta, CBaseObject::OWNER Owner);
	void CameraMode();
	void CameraVibration();

	void SetOrigin(COrgan* p_pOrigin){_origin = p_pOrigin;}
	COrgan* GetOrigin(){return _origin;}

	void SetDestination(D3DXVECTOR3* p_pDestination){_vDestination = *(p_pDestination);}
	void SetDestinationX(float p_fPosX){_vDestination.x = p_fPosX;}
	void SetDestinationY(float p_fPosY){_vDestination.y = p_fPosY;}
	void SetDestinationZ(float p_fPosZ){_vDestination.z = p_fPosZ;}

	//Set & Get Function
	D3DXVECTOR3* GetDestination(){return &_vDestination;}
	CCamera* GetCamera(){return _camera;}
	void SetMode(CAMERAMODE p_eMode){_mode = p_eMode;}
	CAMERAMODE GetMode(){return _mode;}
};

// CCameraManager의 인스턴스를 쉽게 접근할 수 있는 방법을 제공한다.
#define CameraMgr CCameraManager::Instance()

#endif