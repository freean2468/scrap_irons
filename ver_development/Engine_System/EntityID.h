////////////////////////////////////////////////////
// ID
////////////////////////////////////////////////////
#ifndef _EntityID_H_
#define _EntityID_H_

enum {
	// Engine Logic Manage Entity
	ID_SECTION,
	ID_EVENTSTAGE,
	ID_EVENTWORLDMAP,

	// UserInterface Entity
	ID_PRODUCTION,
	ID_PRODUCING,
	ID_INTERACT,
	ID_INVENTORY,
	ID_BLUEPRINTLIST,
	ID_BLUEPRINTSCROLL,
	ID_AREA,
	ID_COMMANDER,
	ID_SMALLINFO,

	// Logic Owned Entity
	ID_LOGO,
	ID_WORLDMAP,
	ID_MAINMENU,
	ID_STAGEHOME,
	ID_STAGEMOUNTAIN,
	ID_STAGEFURNACE,
	ID_STAGECHIMNEY,
	ID_STAGEDUSTBRIDGE,
	ID_STAGEGOODHOPE,

	// Character Entity
	ID_HERO,
	ID_CART,
	ID_FLOWER,
	ID_ASSISTANT,
	ID_ENEMY,

	ID_WAGOO,
	ID_WOOWO,
	ID_YAWO,
	ID_KIRIT,
	ID_TINKLE,

	ID_WORKER,
	ID_DUSTKID,
	ID_MINIWORKER,
	ID_GATEKEEPER,
	ID_DUSTKING,

	// Item Entity
	ID_ITEM,
	/*ID_BLUEPRINT,
	ID_WIRE,
	ID_BULB,
	ID_REBAR,
	ID_PLYWOOD,*/

	// Effect Entity
	ID_BGEFFECT,
	ID_EFFECT,

	// Special Entity
	ID_EVENTENTITY,

	// Character Owned Entity (Organ Entity)
	ID_BODY,
	ID_MESSAGE,
	ID_ATTACHMENT,

	// Intro
	ID_INTRO
};

#endif