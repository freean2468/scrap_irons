#ifndef _MathManager_H_
////////////////////////////////////////////
// ���� �Լ� ���� ���
////////////////////////////////////////////
#define _MathManager_H_

class CMathManager{
private:
	CMathManager();
	CMathManager(const CMathManager&);
	CMathManager& operator =(const CMathManager&);

public:
	~CMathManager();
	static CMathManager* Instance(){
		static CMathManager instance;

		return &instance;
	}

	// ���� ������ //
	void swap(float* A, float* B);
	void VLine(float x, float y1, float y2);
	void HLine(float x1, float x2, float y);
	void Line(float x1, float y1, float x2, float y2);
	void LinearMove(COrgan* p_pOrgan, float mx, float my, float vx, float vy); // mx, my �����̰��� �ϴ� ��ǥ, vx, vy�� ������ �Ÿ�
};

#define MathMgr CMathManager::Instance()

#endif