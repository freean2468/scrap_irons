///////////////////////////////////////////////////////////////////////////////////////
// CSystemFrameŬ������ �� ������ Frame�� ���õ� ��� ��ġ���� �Ѱ���
//////////////////////////////////////////////////////////////////////////////////////

#ifndef _SystemFrame_H_
#define _SystemFrame_H_

class CSystemFrame{
private: 	
	float m_fCurrTimeOfOrigin; // ������ ����� �ð���
	float m_fLastTimeOfOrigin; // �����Ǹ����� �ð���

	float m_fTimeDeltaOfOrigin; // �ٽ� ���ƿ��µ� �ɸ� ������ �ð��� (CurrTime - LastTime)

	float m_fAdjustedCurrTime;	// ������ ����� �ð���
	float m_fAdjustedLastTime;  // �����ȸ����� �ð���
								   
	float m_fAdjustedTimeDelta; // �ٽ� ���ƿ��µ� �ɸ� ������ �ð��� (CurrTime - LastTime)

	float m_fLimitFPS; // �ִ� Frame
	float m_fFPS; // ���� ���� �ʴ� Frame ��

	int m_iFrameCount; // ����� Frame�� ��
	float m_fSecPerFrame; // �ʴ� Frame ��
	
	float m_fTimer; // ��ü �ð� (0���� ������ �ùٸ� Frame, 0���� ũ�� FrameSkip)
	float m_fAcculTime; // ���� �ð�

public:
	CSystemFrame(void);
	virtual ~CSystemFrame(void);

	void CalculationTimeDeltaOfOrigin(); // ������ �ð��� ���
	void CalculationAdjustedTimeDelta(); // ������ �ð��� ���
	void SetFramePerSec(float fFPS);
	bool Update(float timeDelta); // Frame ���
	bool IsFrameSkip(); // FrameSkip (True : Skip, False : NoSkip)

	float GetTimeDeltaOfOrigin(); // ������ TimeDelta �� Return
	float GetAdjustedTimeDelta(); // ������ TimeDelta �� Return
	__inline float GetFPS() const;
	__inline float GetLimitFPS() const;
};

__inline float CSystemFrame::GetFPS() const{
	return m_fFPS;
}
__inline float CSystemFrame::GetLimitFPS() const{
	return m_fLimitFPS;
}

#endif