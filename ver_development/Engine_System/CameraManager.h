/////////////////////////////////////////////////////
// CCameraManagerŬ������ �� ������ �ý����� �Ѱ���
////////////////////////////////////////////////////

#ifndef _CameraManager_H_
#define _CameraManager_H_

class CCameraManager{
public:
	typedef enum CameraMode{MAP, RELAX, COMBAT, EVENT}CAMERAMODE;

private:
	CCamera* _camera;
	D3DXVECTOR3 _vDestination;	// ī�޶� ������
	CAMERAMODE _mode;

	COrgan* _origin;

    // �����ڿ� �Ҹ��ڸ� �����ϰ� �Ҵ��� private�̾�� �Ѵ�.
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
	// CCameraManager Ŭ���� ���� �Լ�
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

// CCameraManager�� �ν��Ͻ��� ���� ������ �� �ִ� ����� �����Ѵ�.
#define CameraMgr CCameraManager::Instance()

#endif