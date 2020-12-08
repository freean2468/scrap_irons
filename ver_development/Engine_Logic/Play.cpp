#include "../BaseHeader.h"

CPlay::~CPlay(){

}

void CPlay::Update(){  
  m_pStateMachine->Update();
}