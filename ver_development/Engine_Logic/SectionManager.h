////////////////////////////////////////////////////
// Section 관리 클래스
////////////////////////////////////////////////////
#ifndef _SectionManager_H_
#define _SectionManager_H_

class CSectionManager{
public:
	CBaseGameEntity* _section;

private:
	CSectionManager(){
		_section = new CSection(ID_SECTION);
		EntityDB->RegisterEntity(_section);
	}
	CSectionManager(const CSectionManager&);
	CSectionManager& operator =(const CSectionManager&);

public:
	~CSectionManager(){
		d3d::Delete<CBaseGameEntity*>(_section);
	}
	static CSectionManager* Instance(){
		static CSectionManager instance;

		return &instance;
	}

	CBaseGameEntity* GetSection(){return EntityDB->GetEntityFromID(ID_SECTION);}
};

#define SectionMgr CSectionManager::Instance()

#endif