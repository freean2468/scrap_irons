#include "../BaseHeader.h"

//------------------------- GetEntityFromID -----------------------------------
//-----------------------------------------------------------------------------
CBaseGameEntity* CEntityDataBase::GetEntityFromID(int id)const{
  // Entity를 찾는다
  EntityMap::const_iterator itr = m_EntityMap.find(id);

  //assert that the entity is a member of the map
  assert ( (itr !=  m_EntityMap.end()) && "<CEntityDataBase::GetEntityFromID>: invalid ID");

  return itr->second;
}

//--------------------------- RemoveEntity ------------------------------------
//-----------------------------------------------------------------------------
void CEntityDataBase::RemoveEntity(CBaseGameEntity* pEntity){    
  m_EntityMap.erase(m_EntityMap.find(pEntity->ID()));
} 

//---------------------------- RegisterEntity ---------------------------------
//-----------------------------------------------------------------------------
void CEntityDataBase::RegisterEntity(CBaseGameEntity* NewEntity){
  m_EntityMap.insert(std::make_pair(NewEntity->ID(), NewEntity));
}
