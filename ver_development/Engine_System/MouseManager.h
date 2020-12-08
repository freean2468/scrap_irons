////////////////////////////////////////////////////
// Mouse 담당 관리 클래스
////////////////////////////////////////////////////
#ifndef _MouseManager_H_
#define _MouseManager_H_

class CMouseManager{
private:
	CBody* _cursor;

	bool _useCursor;

private:
	CMouseManager();
	CMouseManager(const CMouseManager&);
	CMouseManager& operator =(const CMouseManager&);

public:
	~CMouseManager();
	static CMouseManager* Instance(){
		static CMouseManager instance;

		return &instance;
	}

	// Cursor 업데이트
	void CursorUpdate();

	void SetUseCursor(bool p_bool){_useCursor = p_bool;}
};

#define MouseMgr CMouseManager::Instance()

#endif