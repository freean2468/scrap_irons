#include "../BaseHeader.h"

//------------------------- GetEntityFromID -----------------------------------
//-----------------------------------------------------------------------------
CItem* CItemDataBase::GetItemFromID(int id)const{
  // Entity를 찾는다
  ItemMap::const_iterator itr = m_ItemMap.find(id);

  //assert that the entity is a member of the map
  assert ( (itr !=  m_ItemMap.end()) && "<CItemDataBase::GetItemFromID>: invalid ID");

  return itr->second;
}

//--------------------------- RemoveEntity ------------------------------------
//-----------------------------------------------------------------------------
void CItemDataBase::RemoveItem(CItem* pItem){    
  m_ItemMap.erase(m_ItemMap.find(pItem->ID()));
} 

//---------------------------- RegisterEntity ---------------------------------
//-----------------------------------------------------------------------------
void CItemDataBase::RegisterItem(CItem* NewItem){
  m_ItemMap.insert(std::make_pair(NewItem->ID(), NewItem));
}
