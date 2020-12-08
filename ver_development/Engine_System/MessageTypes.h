#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

enum message_type
{
  // Characters
  Msg_Event,
  Msg_Usual,
  Msg_Ready,
  Msg_NotRender,
  Msg_Shock,
  Msg_SpringUp,
  
  Msg_Healthful,
  Msg_Normal,
  Msg_Weak,
  Msg_Die,

  // MAP
  Msg_Selection,
  Msg_Area1,
  Msg_Area2,
  Msg_Area3,

  // WORLDMAP
  Msg_ScrapMountainClear,
  Msg_FurnaceClear,
  Msg_ChimneyClear,
  Msg_DustBridgeClear,

  // Cart
  Msg_Pull,
  Msg_Put,

  // Event
  Msg_Senario,
  Msg_SenarioEnd,
  Msg_Ending,

  // UI
  Msg_Activate,
  Msg_Close,
  Msg_InProduction,

  // AI Command
  Msg_Attack,
  Msg_RunAway,
  Msg_Defense,
};

#endif