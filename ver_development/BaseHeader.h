////////////////////////////////////////////////////
// Engine에서 제공하는 모든 헤더파일 선언
////////////////////////////////////////////////////
#ifndef _BaseHeader_H_
#define _BaseHeader_H_

// 모든 etc 부분
#include "./Engine_System/Singleton.h"
#include "./Engine_System/String.h"
#include "./Engine_System/SystemDefines.h"
#include "./Engine_System/Coordinates.h"
#include "./Engine_System/Timer.h"
#include "./Engine_System/CrudeTimer.h"

// Resource 부분
#include "./Engine_Resource/resource.h"

// Math&Physics 부분


// Data Structures 부분
#include "./Engine_Data Structures/Array.h"
#include "./Engine_Data Structures/Array2D.h"
#include "./Engine_Data Structures/Array3D.h"
#include "./Engine_Data Structures/Bitvector.h"
#include "./Engine_Data Structures/SListNode.h"
#include "./Engine_Data Structures/SLinkedList.h"
#include "./Engine_Data Structures/SListIterator.h"
#include "./Engine_Data Structures/DListNode.h"
#include "./Engine_Data Structures/DLinkedList.h"
#include "./Engine_Data Structures/DListIterator.h"
#include "./Engine_Data Structures/AStack.h"
#include "./Engine_Data Structures/LStack.h"
#include "./Engine_Data Structures/AQueue.h"
#include "./Engine_Data Structures/LQueue.h"
#include "./Engine_Data Structures/HashEntry.h"
#include "./Engine_Data Structures/HashFuntion.h"
#include "./Engine_Data Structures/Tree.h"
#include "./Engine_Data Structures/TreeIterator.h"
#include "./Engine_Data Structures/BinaryTree.h"
#include "./Engine_Data Structures/BinarySearchTree.h"
#include "./Engine_Data Structures/Heap.h"
#include "./Engine_Data Structures/GraphArc.h"
#include "./Engine_Data Structures/GraphNode.h"
#include "./Engine_Data Structures/Graph.h"

// Data Structures 부분 종료

// Engine System 부분
#include "./Engine_System/D3D.h"
#include "./Engine_System/dsutil.h"
#include "./Engine_System/dxutil.h"

#include "./Engine_System/SystemFrame.h"
#include "./Engine_System/Information.h"
#include "./Engine_System/Camera.h"
#include "./Engine_System/Terrain.h"
#include "./Engine_System/Particle.h"
#include "./Engine_System/Snow.h"
#include "./Engine_System/Firework.h"
#include "./Engine_System/ParticleGun.h"
#include "./Engine_System/Dirt.h"
#include "./Engine_System/Exhaust.h"
#include "./Engine_System/Kindling.h"
#include "./Engine_System/Script.h"
#include "./Engine_System/Telegram.h"
#include "./Engine_System/EntityID.h"
#include "./Engine_System/BaseGameEntity.h"
#include "./Engine_System/State.h"
#include "./Engine_System/StateMachine.h"
#include "./Engine_System/BaseMessageDispatcher.h"
#include "./Engine_System/EntityDB.h"
#include "./Engine_System/ItemDB.h"
#include "./Engine_System/MessageTypes.h"
#include "./Engine_System/EffectType.h"

// 오브젝트
#include "./Engine_System/BaseObject.h"
#include "./Engine_System/Organ.h"
#include "./Engine_System/Body.h"
#include "./Engine_System/Attachment.h"
#include "./Engine_System/Message.h"

#include "./Engine_System/OrganEntity.h"
#include "./Engine_System/CharacterEntity.h"

// Item
#include "./Engine_System/ItemOwnedStates.h"
#include "./Engine_System/Item.h"
#include "./Engine_System/BluePrint.h"

// UI
#include "./Engine_System/Logo.h"
#include "./Engine_System/IntroOwnedStates.h"
#include "./Engine_System/Intro.h"
#include "./Engine_System/MainMenu.h"
#include "./Engine_System/ProductionOwnedStates.h"
#include "./Engine_System/Production.h"
#include "./Engine_System/InteractOwnedStates.h"
#include "./Engine_System/Interact.h"
#include "./Engine_System/InventoryOwnedStates.h"
#include "./Engine_System/Inventory.h"
#include "./Engine_System/BluePrintListOwnedStates.h"
#include "./Engine_System/BluePrintList.h"
#include "./Engine_System/BluePrintScrollOwnedStates.h"
#include "./Engine_System/BluePrintScroll.h"
#include "./Engine_System/ProducingOwnedStates.h"
#include "./Engine_System/Producing.h"
#include "./Engine_System/AreaOwnedStates.h"
#include "./Engine_System/Area.h"
#include "./Engine_System/CommanderOwnedStates.h"
#include "./Engine_System/Commander.h"
#include "./Engine_System/SmallInfoOwnedStates.h"
#include "./Engine_System/SmallInfo.h"

// Map
#include "./Engine_System/WorldMapOwnedStates.h"
#include "./Engine_System/WorldMap.h"
#include "./Engine_System/StageChimneyOwnedStates.h"
#include "./Engine_System/StageChimney.h"
#include "./Engine_System/StageDustBridgeOwnedStates.h"
#include "./Engine_System/StageDustBridge.h"
#include "./Engine_System/StageHome.h"
#include "./Engine_System/StageMountainOwnedStates.h"
#include "./Engine_System/StageMountain.h"
#include "./Engine_System/StageFurnace.h"
#include "./Engine_System/StageGoodHopeOwnedStates.h"
#include "./Engine_System/StageGoodHope.h"

// Effect
#include "./Engine_System/BaseEffect.h"
#include "./Engine_System/QuestionMarkOwnedStates.h"
#include "./Engine_System/QuestionMark.h"
#include "./Engine_System/DamageEffectOwnedStates.h"
#include "./Engine_System/DamageEffect.h"
#include "./Engine_System/SparksEffectOwnedStates.h"
#include "./Engine_System/SparksEffect.h"
#include "./Engine_System/RayEffectOwnedStates.h"
#include "./Engine_System/RayEffect.h"
#include "./Engine_System/DiggyEffectOwnedStates.h"
#include "./Engine_System/DiggyEffect.h"
#include "./Engine_System/LightEffectOwnedStates.h"
#include "./Engine_System/LightEffect.h"
#include "./Engine_System/DustEffectOwnedStates.h"
#include "./Engine_System/DustEffect.h"
#include "./Engine_System/BoldDustEffectOwnedStates.h"
#include "./Engine_System/BoldDustEffect.h"

// Character
#include "./Engine_System/HeroOwnedStates.h"
#include "./Engine_System/Hero.h"
#include "./Engine_System/FlowerOwnedStates.h"
#include "./Engine_System/Flower.h"
#include "./Engine_System/CartOwnedStates.h"
#include "./Engine_System/Cart.h"

// OurForce
#include "./Engine_System/WagooOwnedStates.h"
#include "./Engine_System/Wagoo.h"
#include "./Engine_System/WoowoOwnedStates.h"
#include "./Engine_System/Woowo.h"
#include "./Engine_System/YawoOwnedStates.h"
#include "./Engine_System/Yawo.h"
#include "./Engine_System/KiritOwnedStates.h"
#include "./Engine_System/Kirit.h"
#include "./Engine_System/TinkleOwnedStates.h"
#include "./Engine_System/Tinkle.h"

// Enemy
#include "./Engine_System/WorkerOwnedStates.h"
#include "./Engine_System/Worker.h"
#include "./Engine_System/MiniWorkerOwnedStates.h"
#include "./Engine_System/MiniWorker.h"
#include "./Engine_System/DustKidOwnedStates.h"
#include "./Engine_System/DustKid.h"
#include "./Engine_System/GateKeeperOwnedStates.h"
#include "./Engine_System/GateKeeper.h"
#include "./Engine_System/DustKingOwnedStates.h"
#include "./Engine_System/DustKing.h"

// 어플리케이션
#include "./Engine_System/Stdafx.h"
#include "./Engine_System/Object.h"
#include "./Engine_System/Wnd.h"
#include "./Engine_System/App.h"
#include "./Engine_System/View.h"

// Engine System 부분 종료

// Logic

// 섹션
#include "./Engine_Logic/SectionOwnedStates.h"
#include "./Engine_Logic/Section.h"

// 이벤트
#include "./Engine_Logic/EventWorldMapOwnedStates.h"
#include "./Engine_Logic/EventWorldMap.h"
#include "./Engine_Logic/EventStageOwnedStates.h"
#include "./Engine_Logic/EventStage.h"

// Logic 종료

// 모든 관리자
#include "./Engine_System/BaseManager.h"
#include "./Engine_System/ObjectManager.h"
#include "./Engine_Logic/StageManager.h"
#include "./Engine_Math&Physics/MathManager.h"
#include "./Engine_Logic/UIManager.h"
#include "./Engine_Logic/SectionManager.h"
#include "./Engine_Logic/EventManager.h"
#include "./Engine_Logic/AIManager.h"
#include "./Engine_System/EffectManager.h"
#include "./Engine_System/CameraManager.h"
#include "./Engine_System/MusicManager.h"
#include "./Engine_System/MouseManager.h"

#endif