#include "PreCompile.h"
#include "Player.h"
#include "BaseMap.h"
#include "CAGameMode.h"
#include "Player_Shadow.h"
#include "WaterBomb.h"
#include "Packets.h"
#include "SendPacketManager.h"
#include <EngineCore/EngineDebugMsgWindow.h>
#include "OtherPlayer.h"
#include <EngineCore/Image.h>

void APlayer::StateInit()
{
	InputOn();

	// CreateAnimation
	// 레드 배찌 애니메이션
	Renderer->CreateAnimation("Red_Bazzi_Idle_Up",		"bazzi_1_red.png", AnimationInter,		false,	12,	12);
	Renderer->CreateAnimation("Red_Bazzi_Idle_Down",	"bazzi_1_red.png", AnimationInter,		false,	20,	20);
	Renderer->CreateAnimation("Red_Bazzi_Idle_Right",	"bazzi_1_red.png", AnimationInter,	false,	6,	6);
	Renderer->CreateAnimation("Red_Bazzi_Idle_Left",	"bazzi_1_red.png", AnimationInter,		false,	0,	0);
	Renderer->CreateAnimation("Red_Bazzi_Move_Left",	"bazzi_1_red.png", AnimationInter,		true,	0,	5);
	Renderer->CreateAnimation("Red_Bazzi_Move_Right",	"bazzi_1_red.png", AnimationInter,	true,	6,	11);
	Renderer->CreateAnimation("Red_Bazzi_Move_Up",		"bazzi_1_red.png", AnimationInter,		true,	12,	19);
	Renderer->CreateAnimation("Red_Bazzi_Move_Down",	"bazzi_1_red.png", AnimationInter,		true,	20,	27);
	Renderer->CreateAnimation("Red_Bazzi_Trap", "bazzi_trap_long.png", AnimationInter,		false,	6, 31);
	Renderer->CreateAnimation("Red_Bazzi_Rescue", "bazzi_rescue.png", 0.1f, false, 0, 2);
	Renderer->CreateAnimation("Red_Bazzi_Die", "bazzi_die.png", 0.1f, false, 0, 5);
	Renderer->CreateAnimation("Red_Bazzi_GameOn1", "bazzi_1_red.png", AnimationInter * 0.5f, true, 45, 48);
	Renderer->CreateAnimation("Red_Bazzi_GameOn2", "bazzi_1_red.png", { 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f }, { 49, 50, 51, 52, 53, 52, 49, 49, 50, 50 }, false);
	
	Renderer->CreateAnimation("Red_Bazzi_Win", "bazzi_1_red.png", { 0.2f, 0.2f }, { 20, 33 }, true);

	// 블루 배찌 애니메이션
	Renderer->CreateAnimation("Blue_Bazzi_Idle_Up", "Bazzi_1_blue.png", AnimationInter,		false,	12,	12);
	Renderer->CreateAnimation("Blue_Bazzi_Idle_Down", "Bazzi_1_blue.png", AnimationInter,	false,	20,	20);
	Renderer->CreateAnimation("Blue_Bazzi_Idle_Right", "Bazzi_1_blue.png", AnimationInter,	false,	6,	6);
	Renderer->CreateAnimation("Blue_Bazzi_Idle_Left", "Bazzi_1_blue.png", AnimationInter,	false,	0,	0);
	Renderer->CreateAnimation("Blue_Bazzi_Move_Left", "Bazzi_1_blue.png", AnimationInter,	true,	0,	5);
	Renderer->CreateAnimation("Blue_Bazzi_Move_Right", "Bazzi_1_blue.png", AnimationInter,	true,	6,	11);
	Renderer->CreateAnimation("Blue_Bazzi_Move_Up", "Bazzi_1_blue.png", AnimationInter,		true,	12,	19);
	Renderer->CreateAnimation("Blue_Bazzi_Move_Down", "Bazzi_1_blue.png", AnimationInter,	true,	20,	27);
	Renderer->CreateAnimation("Blue_Bazzi_Trap", "Bazzi_4_blue.png", AnimationInter,		false,	6,	31);
	Renderer->CreateAnimation("Blue_Bazzi_Rescue", "Bazzi_2_blue.png", 0.1f, false, 6, 9);
	Renderer->CreateAnimation("Blue_Bazzi_Die", "Bazzi_2_blue.png", 0.1f, false, 0, 5);
	Renderer->CreateAnimation("Blue_Bazzi_GameOn1", "Bazzi_1_blue.png", AnimationInter * 0.5f, true, 45, 48);
	Renderer->CreateAnimation("Blue_Bazzi_GameOn2", "Bazzi_1_blue.png", { 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f}, { 49, 50, 51, 52, 53, 52, 49, 49, 50, 50 }, false);

	Renderer->CreateAnimation("Blue_Bazzi_Win", "Bazzi_1_blue.png", { 0.2f, 0.2f }, { 20, 33 }, true);

	// 배찌 Ride 애니메이션
	Renderer->CreateAnimation("Red_Bazzi_Owl_Idle_Up",			"bazzi_3_red.png", AnimationInter, false, 4, 4);
	Renderer->CreateAnimation("Red_Bazzi_Owl_Idle_Down",		"bazzi_3_red.png", AnimationInter, false, 6, 6);
	Renderer->CreateAnimation("Red_Bazzi_Owl_Idle_Right",		"bazzi_3_red.png", AnimationInter, false, 2, 2);
	Renderer->CreateAnimation("Red_Bazzi_Owl_Idle_Left",		"bazzi_3_red.png", AnimationInter, false, 0, 0);
	Renderer->CreateAnimation("Red_Bazzi_Owl_Move_Left",		"bazzi_3_red.png", AnimationInter, true, 0, 1);
	Renderer->CreateAnimation("Red_Bazzi_Owl_Move_Right",		"bazzi_3_red.png", AnimationInter, true, 2, 3);
	Renderer->CreateAnimation("Red_Bazzi_Owl_Move_Up",			"bazzi_3_red.png", AnimationInter, true, 4, 5);
	Renderer->CreateAnimation("Red_Bazzi_Owl_Move_Down",		"bazzi_3_red.png", AnimationInter, true, 6, 7);
	Renderer->CreateAnimation("Red_Bazzi_Turtle_Idle_Up",		"bazzi_3_red.png", AnimationInter, false, 12, 12);
	Renderer->CreateAnimation("Red_Bazzi_Turtle_Idle_Down",		"bazzi_3_red.png", AnimationInter, false, 14, 14);
	Renderer->CreateAnimation("Red_Bazzi_Turtle_Idle_Right",	"bazzi_3_red.png", AnimationInter, false, 10, 10);
	Renderer->CreateAnimation("Red_Bazzi_Turtle_Idle_Left",		"bazzi_3_red.png", AnimationInter, false, 8, 8);
	Renderer->CreateAnimation("Red_Bazzi_Turtle_Move_Left",		"bazzi_3_red.png", AnimationInter, true, 8, 9);
	Renderer->CreateAnimation("Red_Bazzi_Turtle_Move_Right",	"bazzi_3_red.png", AnimationInter, true, 10, 11);
	Renderer->CreateAnimation("Red_Bazzi_Turtle_Move_Up",		"bazzi_3_red.png", AnimationInter, true, 12, 13);
	Renderer->CreateAnimation("Red_Bazzi_Turtle_Move_Down",		"bazzi_3_red.png", AnimationInter, true, 14, 15);

	Renderer->CreateAnimation("Blue_Bazzi_Owl_Idle_Up", "Bazzi_3_blue.png", AnimationInter, false, 4, 4);
	Renderer->CreateAnimation("Blue_Bazzi_Owl_Idle_Down", "Bazzi_3_blue.png", AnimationInter, false, 6, 6);
	Renderer->CreateAnimation("Blue_Bazzi_Owl_Idle_Right", "Bazzi_3_blue.png", AnimationInter, false, 2, 2);
	Renderer->CreateAnimation("Blue_Bazzi_Owl_Idle_Left", "Bazzi_3_blue.png", AnimationInter, false, 0, 0);
	Renderer->CreateAnimation("Blue_Bazzi_Owl_Move_Left", "Bazzi_3_blue.png", AnimationInter, true, 0, 1);
	Renderer->CreateAnimation("Blue_Bazzi_Owl_Move_Right", "Bazzi_3_blue.png", AnimationInter, true, 2, 3);
	Renderer->CreateAnimation("Blue_Bazzi_Owl_Move_Up", "Bazzi_3_blue.png", AnimationInter, true, 4, 5);
	Renderer->CreateAnimation("Blue_Bazzi_Owl_Move_Down", "Bazzi_3_blue.png", AnimationInter, true, 6, 7);
	Renderer->CreateAnimation("Blue_Bazzi_Turtle_Idle_Up", "Bazzi_3_blue.png", AnimationInter, false, 12, 12);
	Renderer->CreateAnimation("Blue_Bazzi_Turtle_Idle_Down", "Bazzi_3_blue.png", AnimationInter, false, 14, 14);
	Renderer->CreateAnimation("Blue_Bazzi_Turtle_Idle_Right", "Bazzi_3_blue.png", AnimationInter, false, 10, 10);
	Renderer->CreateAnimation("Blue_Bazzi_Turtle_Idle_Left", "Bazzi_3_blue.png", AnimationInter, false, 8, 8);
	Renderer->CreateAnimation("Blue_Bazzi_Turtle_Move_Left", "Bazzi_3_blue.png", AnimationInter, true, 8, 9);
	Renderer->CreateAnimation("Blue_Bazzi_Turtle_Move_Right", "Bazzi_3_blue.png", AnimationInter, true, 10, 11);
	Renderer->CreateAnimation("Blue_Bazzi_Turtle_Move_Up", "Bazzi_3_blue.png", AnimationInter, true, 12, 13);
	Renderer->CreateAnimation("Blue_Bazzi_Turtle_Move_Down", "Bazzi_3_blue.png", AnimationInter, true, 14, 15);

	
	// 레드 다오 애니메이션
	Renderer->CreateAnimation("Red_Dao_Idle_Up", "Dao_4_red.png", AnimationInter, false, 2, 2);
	Renderer->CreateAnimation("Red_Dao_Idle_Down", "Dao_4_red.png", AnimationInter, false, 0, 0);
	Renderer->CreateAnimation("Red_Dao_Idle_Right", "Dao_4_red.png", AnimationInter, false, 1, 1);
	Renderer->CreateAnimation("Red_Dao_Idle_Left", "Dao_4_red.png", AnimationInter, false, 3, 3);
	Renderer->CreateAnimation("Red_Dao_Move_Left", "Dao_1_red.png", AnimationInter, true, 6, 11);
	Renderer->CreateAnimation("Red_Dao_Move_Right", "Dao_1_red.png", AnimationInter, true, 0, 5);
	Renderer->CreateAnimation("Red_Dao_Move_Up", "Dao_1_red.png", AnimationInter, true, 12, 17);
	Renderer->CreateAnimation("Red_Dao_Move_Down", "Dao_1_red.png", AnimationInter, true, 18, 23);
	Renderer->CreateAnimation("Red_Dao_Trap", "Dao_5_red.png", AnimationInter, false, 0, 25);
	Renderer->CreateAnimation("Red_Dao_Rescue", "Dao_2_red.png", 0.1f, false, 6, 9);
	Renderer->CreateAnimation("Red_Dao_Die", "Dao_2_red.png", 0.1f, false, 0, 5);
	Renderer->CreateAnimation("Red_Dao_GameOn1", "Dao_1_red.png", AnimationInter * 0.5f, true, 24, 27);
	Renderer->CreateAnimation("Red_Dao_GameOn2", "Dao_1_red.png", AnimationInter, false, 28, 37);
	Renderer->CreateAnimation("Red_Dao_Win", "Dao_6_red.png", AnimationInter * 2, true, 0, 1);

	// 블루 다오 애니메이션
	Renderer->CreateAnimation("Blue_Dao_Idle_Up",	"dao_4_blue.png", AnimationInter, false, 2, 2);
	Renderer->CreateAnimation("Blue_Dao_Idle_Down", "dao_4_blue.png", AnimationInter, false, 0, 0);
	Renderer->CreateAnimation("Blue_Dao_Idle_Right","dao_4_blue.png", AnimationInter, false, 1, 1);
	Renderer->CreateAnimation("Blue_Dao_Idle_Left", "dao_4_blue.png", AnimationInter, false, 3, 3);
	Renderer->CreateAnimation("Blue_Dao_Move_Left", "dao_1_blue.png", AnimationInter, true, 6, 11);
	Renderer->CreateAnimation("Blue_Dao_Move_Right","dao_1_blue.png", AnimationInter, true, 0, 5);
	Renderer->CreateAnimation("Blue_Dao_Move_Up",	"dao_1_blue.png", AnimationInter, true, 12, 17);
	Renderer->CreateAnimation("Blue_Dao_Move_Down", "dao_1_blue.png", AnimationInter, true, 18, 23);
	Renderer->CreateAnimation("Blue_Dao_Trap",			"dao_trap_long.png", AnimationInter, false, 0, 25);
	Renderer->CreateAnimation("Blue_Dao_Rescue",		"dao_rescue.png", 0.1f, false, 0, 2);
	Renderer->CreateAnimation("Blue_Dao_Die",			"dao_die.png", 0.1f, false, 0, 5);
	Renderer->CreateAnimation("Blue_Dao_GameOn1",		"dao_1_blue.png", AnimationInter * 0.5f, true, 24, 27);
	Renderer->CreateAnimation("Blue_Dao_GameOn2",		"dao_1_blue.png", AnimationInter, false, 28, 37);
	Renderer->CreateAnimation("Blue_Dao_Win", "dao_6_blue.png", AnimationInter * 2, true, 0, 1);

	// 다오 Ride 애니메이션
	Renderer->CreateAnimation("Red_Dao_Owl_Idle_Up", "Dao_3_red.png", AnimationInter, false, 4, 4);
	Renderer->CreateAnimation("Red_Dao_Owl_Idle_Down", "Dao_3_red.png", AnimationInter, false, 6, 6);
	Renderer->CreateAnimation("Red_Dao_Owl_Idle_Right", "Dao_3_red.png", AnimationInter, false, 2, 2);
	Renderer->CreateAnimation("Red_Dao_Owl_Idle_Left", "Dao_3_red.png", AnimationInter, false, 0, 0);
	Renderer->CreateAnimation("Red_Dao_Owl_Move_Left", "Dao_3_red.png", AnimationInter, true, 0, 1);
	Renderer->CreateAnimation("Red_Dao_Owl_Move_Right", "Dao_3_red.png", AnimationInter, true, 2, 3);
	Renderer->CreateAnimation("Red_Dao_Owl_Move_Up", "Dao_3_red.png", AnimationInter, true, 4, 5);
	Renderer->CreateAnimation("Red_Dao_Owl_Move_Down", "Dao_3_red.png", AnimationInter, true, 6, 7);
	Renderer->CreateAnimation("Red_Dao_Turtle_Idle_Up", "Dao_3_red.png", AnimationInter, false, 12, 12);
	Renderer->CreateAnimation("Red_Dao_Turtle_Idle_Down", "Dao_3_red.png", AnimationInter, false, 14, 14);
	Renderer->CreateAnimation("Red_Dao_Turtle_Idle_Right", "Dao_3_red.png", AnimationInter, false, 10, 10);
	Renderer->CreateAnimation("Red_Dao_Turtle_Idle_Left", "Dao_3_red.png", AnimationInter, false, 8, 8);
	Renderer->CreateAnimation("Red_Dao_Turtle_Move_Left", "Dao_3_red.png", AnimationInter, true, 8, 9);
	Renderer->CreateAnimation("Red_Dao_Turtle_Move_Right", "Dao_3_red.png", AnimationInter, true, 10, 11);
	Renderer->CreateAnimation("Red_Dao_Turtle_Move_Up", "Dao_3_red.png", AnimationInter, true, 12, 13);
	Renderer->CreateAnimation("Red_Dao_Turtle_Move_Down", "Dao_3_red.png", AnimationInter, true, 14, 15);
	
	Renderer->CreateAnimation("Blue_Dao_Owl_Idle_Up",		"dao_3_blue.png", AnimationInter, false, 4, 4);
	Renderer->CreateAnimation("Blue_Dao_Owl_Idle_Down",		"dao_3_blue.png", AnimationInter, false, 6, 6);
	Renderer->CreateAnimation("Blue_Dao_Owl_Idle_Right",	"dao_3_blue.png", AnimationInter, false, 2, 2);
	Renderer->CreateAnimation("Blue_Dao_Owl_Idle_Left",		"dao_3_blue.png", AnimationInter, false, 0, 0);
	Renderer->CreateAnimation("Blue_Dao_Owl_Move_Left",		"dao_3_blue.png", AnimationInter, true, 0, 1);
	Renderer->CreateAnimation("Blue_Dao_Owl_Move_Right",	"dao_3_blue.png", AnimationInter, true, 2, 3);
	Renderer->CreateAnimation("Blue_Dao_Owl_Move_Up",		"dao_3_blue.png", AnimationInter, true, 4, 5);
	Renderer->CreateAnimation("Blue_Dao_Owl_Move_Down",		"dao_3_blue.png", AnimationInter, true, 6, 7);
	Renderer->CreateAnimation("Blue_Dao_Turtle_Idle_Up",	"dao_3_blue.png", AnimationInter, false, 12, 12);
	Renderer->CreateAnimation("Blue_Dao_Turtle_Idle_Down",	"dao_3_blue.png", AnimationInter, false, 14, 14);
	Renderer->CreateAnimation("Blue_Dao_Turtle_Idle_Right", "dao_3_blue.png", AnimationInter, false, 10, 10);
	Renderer->CreateAnimation("Blue_Dao_Turtle_Idle_Left",	"dao_3_blue.png", AnimationInter, false, 8, 8);
	Renderer->CreateAnimation("Blue_Dao_Turtle_Move_Left",	"dao_3_blue.png", AnimationInter, true, 8, 9);
	Renderer->CreateAnimation("Blue_Dao_Turtle_Move_Right", "dao_3_blue.png", AnimationInter, true, 10, 11);
	Renderer->CreateAnimation("Blue_Dao_Turtle_Move_Up",	"dao_3_blue.png", AnimationInter, true, 12, 13);
	Renderer->CreateAnimation("Blue_Dao_Turtle_Move_Down",	"dao_3_blue.png", AnimationInter, true, 14, 15);

	// 레드 마리드 애니메이션
	Renderer->CreateAnimation("Red_Marid_Idle_Up", "luxMarid_1.png", AnimationInter, false, 12, 12);
	Renderer->CreateAnimation("Red_Marid_Idle_Down", "luxMarid_1.png", AnimationInter, false, 18, 18);
	Renderer->CreateAnimation("Red_Marid_Idle_Right", "luxMarid_1.png", AnimationInter, false, 0, 0);
	Renderer->CreateAnimation("Red_Marid_Idle_Left", "luxMarid_1.png", AnimationInter, false, 6, 6);
	Renderer->CreateAnimation("Red_Marid_Move_Left", "luxMarid_1.png", AnimationInter, true, 6, 11);
	Renderer->CreateAnimation("Red_Marid_Move_Right", "luxMarid_1.png", AnimationInter, true, 0, 5);
	Renderer->CreateAnimation("Red_Marid_Move_Up", "luxMarid_1.png", AnimationInter, true, 12, 17);
	Renderer->CreateAnimation("Red_Marid_Move_Down", "luxMarid_1.png", AnimationInter, true, 18, 23);
	Renderer->CreateAnimation("Red_Marid_Trap", "luxMarid_5.png", AnimationInter, false, 0, 25);
	Renderer->CreateAnimation("Red_Marid_Rescue", "luxMarid_2.png", 0.1f, false, 6, 9);
	Renderer->CreateAnimation("Red_Marid_Die", "luxMarid_2.png", 0.1f, false, 0, 5);
	Renderer->CreateAnimation("Red_Marid_GameOn1", "luxMarid_1.png", AnimationInter * 0.5f, true, 24, 27);
	Renderer->CreateAnimation("Red_Marid_GameOn2", "luxMarid_1.png", AnimationInter, false, 28, 37);
	Renderer->CreateAnimation("Red_Marid_Win", "luxMarid_6.png", AnimationInter * 2, true, 0, 1);
	 
	// 블루 마리드 애니메이션
	Renderer->CreateAnimation("Blue_Marid_Idle_Up",		"luxMarid_4_blue.png", AnimationInter, false, 2, 2);
	Renderer->CreateAnimation("Blue_Marid_Idle_Down",	"luxMarid_4_blue.png", AnimationInter, false, 0, 0);
	Renderer->CreateAnimation("Blue_Marid_Idle_Right",	"luxMarid_4_blue.png", AnimationInter, false, 1, 1);
	Renderer->CreateAnimation("Blue_Marid_Idle_Left",	"luxMarid_4_blue.png", AnimationInter, false, 3, 3);
	Renderer->CreateAnimation("Blue_Marid_Move_Left",	"luxMarid_1_blue.png", AnimationInter, true, 6, 11);
	Renderer->CreateAnimation("Blue_Marid_Move_Right",	"luxMarid_1_blue.png", AnimationInter, true, 0, 5);
	Renderer->CreateAnimation("Blue_Marid_Move_Up",		"luxMarid_1_blue.png", AnimationInter, true, 12, 17);
	Renderer->CreateAnimation("Blue_Marid_Move_Down",	"luxMarid_1_blue.png", AnimationInter, true, 18, 23);
	Renderer->CreateAnimation("Blue_Marid_Trap", "luxMarid_5_blue.png", AnimationInter, false, 0, 25);
	Renderer->CreateAnimation("Blue_Marid_Rescue", "luxMarid_2_blue.png", 0.1f, false, 6, 9);
	Renderer->CreateAnimation("Blue_Marid_Die", "luxMarid_2_blue.png", 0.1f, false, 0, 5);
	Renderer->CreateAnimation("Blue_Marid_GameOn1", "luxMarid_1_blue.png", AnimationInter * 0.5f, true, 24, 27);
	Renderer->CreateAnimation("Blue_Marid_GameOn2", "luxMarid_1_blue.png", AnimationInter, false, 28, 37);
	Renderer->CreateAnimation("Blue_Marid_Win", "luxMarid_6_blue.png", AnimationInter * 2, true, 0, 1);

	//Ride 애니메이션
	Renderer->CreateAnimation("Red_Marid_Owl_Idle_Up", "luxMarid_3.png", AnimationInter, false, 4, 4);
	Renderer->CreateAnimation("Red_Marid_Owl_Idle_Down", "luxMarid_3.png", AnimationInter, false, 6, 6);
	Renderer->CreateAnimation("Red_Marid_Owl_Idle_Right", "luxMarid_3.png", AnimationInter, false, 2, 2);
	Renderer->CreateAnimation("Red_Marid_Owl_Idle_Left", "luxMarid_3.png", AnimationInter, false, 0, 0);
	Renderer->CreateAnimation("Red_Marid_Owl_Move_Left", "luxMarid_3.png", AnimationInter, true, 0, 1);
	Renderer->CreateAnimation("Red_Marid_Owl_Move_Right", "luxMarid_3.png", AnimationInter, true, 2, 3);
	Renderer->CreateAnimation("Red_Marid_Owl_Move_Up", "luxMarid_3.png", AnimationInter, true, 4, 5);
	Renderer->CreateAnimation("Red_Marid_Owl_Move_Down", "luxMarid_3.png", AnimationInter, true, 6, 7);
	Renderer->CreateAnimation("Red_Marid_Turtle_Idle_Up", "luxMarid_3.png", AnimationInter, false, 14, 14);
	Renderer->CreateAnimation("Red_Marid_Turtle_Idle_Down", "luxMarid_3.png", AnimationInter, false, 12, 12);
	Renderer->CreateAnimation("Red_Marid_Turtle_Idle_Right", "luxMarid_3.png", AnimationInter, false, 10, 10);
	Renderer->CreateAnimation("Red_Marid_Turtle_Idle_Left", "luxMarid_3.png", AnimationInter, false, 8, 8);
	Renderer->CreateAnimation("Red_Marid_Turtle_Move_Left", "luxMarid_3.png", AnimationInter, true, 8, 9);
	Renderer->CreateAnimation("Red_Marid_Turtle_Move_Right", "luxMarid_3.png", AnimationInter, true, 10, 11);
	Renderer->CreateAnimation("Red_Marid_Turtle_Move_Up", "luxMarid_3.png", AnimationInter, true, 14, 15);
	Renderer->CreateAnimation("Red_Marid_Turtle_Move_Down", "luxMarid_3.png", AnimationInter, true, 12, 13);

	Renderer->CreateAnimation("Blue_Marid_Owl_Idle_Up", "luxMarid_3_blue.png", AnimationInter, false, 4, 4);
	Renderer->CreateAnimation("Blue_Marid_Owl_Idle_Down", "luxMarid_3_blue.png", AnimationInter, false, 6, 6);
	Renderer->CreateAnimation("Blue_Marid_Owl_Idle_Right", "luxMarid_3_blue.png", AnimationInter, false, 2, 2);
	Renderer->CreateAnimation("Blue_Marid_Owl_Idle_Left", "luxMarid_3_blue.png", AnimationInter, false, 0, 0);
	Renderer->CreateAnimation("Blue_Marid_Owl_Move_Left", "luxMarid_3_blue.png", AnimationInter, true, 0, 1);
	Renderer->CreateAnimation("Blue_Marid_Owl_Move_Right", "luxMarid_3_blue.png", AnimationInter, true, 2, 3);
	Renderer->CreateAnimation("Blue_Marid_Owl_Move_Up", "luxMarid_3_blue.png", AnimationInter, true, 4, 5);
	Renderer->CreateAnimation("Blue_Marid_Owl_Move_Down", "luxMarid_3_blue.png", AnimationInter, true, 6, 7);
	Renderer->CreateAnimation("Blue_Marid_Turtle_Idle_Up", "luxMarid_3_blue.png", AnimationInter, false, 14, 14);
	Renderer->CreateAnimation("Blue_Marid_Turtle_Idle_Down", "luxMarid_3_blue.png", AnimationInter, false, 12, 12);
	Renderer->CreateAnimation("Blue_Marid_Turtle_Idle_Right", "luxMarid_3_blue.png", AnimationInter, false, 10, 10);
	Renderer->CreateAnimation("Blue_Marid_Turtle_Idle_Left", "luxMarid_3_blue.png", AnimationInter, false, 8, 8);
	Renderer->CreateAnimation("Blue_Marid_Turtle_Move_Left", "luxMarid_3_blue.png", AnimationInter, true, 8, 9);
	Renderer->CreateAnimation("Blue_Marid_Turtle_Move_Right", "luxMarid_3_blue.png", AnimationInter, true, 10, 11);
	Renderer->CreateAnimation("Blue_Marid_Turtle_Move_Up", "luxMarid_3_blue.png", AnimationInter, true, 14, 15);
	Renderer->CreateAnimation("Blue_Marid_Turtle_Move_Down", "luxMarid_3_blue.png", AnimationInter, true, 12, 13);


	// CreateState
	State.CreateState("GameOn");
	State.CreateState("Idle");
	State.CreateState("Move");
	State.CreateState("Trap");
	State.CreateState("Rescue");
	State.CreateState("Die");
	State.CreateState("RealDie");
	State.CreateState("RideIdle");
	State.CreateState("RideMove");
	State.CreateState("RideOff");
	State.CreateState("Win");
	State.CreateState("Lose");


	// StartFunction
	State.SetStartFunction("GameOn", std::bind(&APlayer::GameOnStart, this));
	State.SetStartFunction("Idle", std::bind(&APlayer::IdleStart, this));
	State.SetStartFunction("Move", std::bind(&APlayer::MoveStart, this));
	State.SetStartFunction("Trap", std::bind(&APlayer::TrapStart, this));
	State.SetStartFunction("Rescue", std::bind(&APlayer::RescueStart, this));
	State.SetStartFunction("Die", std::bind(&APlayer::DieStart, this));
	State.SetStartFunction("RealDie", std::bind(&APlayer::RealDieStart, this));
	State.SetStartFunction("RideIdle", std::bind(&APlayer::RideIdleStart, this));
	State.SetStartFunction("RideMove", std::bind(&APlayer::RideMoveStart, this));
	State.SetStartFunction("RideOff", std::bind(&APlayer::RideOffStart, this));
	State.SetStartFunction("Win", std::bind(&APlayer::WinStart, this));
	State.SetStartFunction("Lose", std::bind(&APlayer::LoseStart, this));

	// UpdateFunction
	State.SetUpdateFunction("GameOn", std::bind(&APlayer::GameOn, this, std::placeholders::_1));
	State.SetUpdateFunction("Idle", std::bind(&APlayer::Idle, this, std::placeholders::_1));
	State.SetUpdateFunction("Move", std::bind(&APlayer::Move, this, std::placeholders::_1));
	State.SetUpdateFunction("Trap", std::bind(&APlayer::Trap, this, std::placeholders::_1));
	State.SetUpdateFunction("Rescue", std::bind(&APlayer::Rescue, this, std::placeholders::_1));
	State.SetUpdateFunction("Die", std::bind(&APlayer::Die, this, std::placeholders::_1));
	State.SetUpdateFunction("RealDie", std::bind(&APlayer::RealDie, this, std::placeholders::_1));
	State.SetUpdateFunction("RideIdle", std::bind(&APlayer::RideIdle, this, std::placeholders::_1));
	State.SetUpdateFunction("RideMove", std::bind(&APlayer::RideMove, this, std::placeholders::_1));
	State.SetUpdateFunction("RideOff", std::bind(&APlayer::RideOff, this, std::placeholders::_1));
	State.SetUpdateFunction("Win", std::bind(&APlayer::Win, this, std::placeholders::_1));
	State.SetUpdateFunction("Lose", std::bind(&APlayer::Lose, this, std::placeholders::_1));

	// Init
	State.ChangeState("GameOn");
}

void APlayer::GameOnStart()
{
	InputOff();
	GameOnTime = 1.5f;
	Renderer->ChangeAnimation((GetAnimationName("GameOn1")));
}

void APlayer::GameOn(float _DeltaTime)
{
	// 게임 시작 시 플레이어 input off 하고 애니메이션 자동생성

	GameOnTime -= _DeltaTime;

	if (0.0f >= GameOnTime)
	{
		Renderer->ChangeAnimation((GetAnimationName("GameOn2")));

		if (true == Renderer->IsCurAnimationEnd())
		{
			InputOn();
			State.ChangeState("Idle");
			return;
		}

	}

}

void APlayer::IdleStart()
{
	Renderer->ChangeAnimation(GetAnimationName("Idle"));
	Renderer->SetPosition(FVector::Zero);
}

void  APlayer::Idle(float _DeltaTime)
{
	if (true == IsPress(VK_UP) || true == IsPress(VK_DOWN) || true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT))
	{
		State.ChangeState("Move");
		return;
	}

	// 물줄기에 맞았을 때
	if (true == GetGameMode()->GetCurMap()->IsOnWater(GetActorLocation()))
	{
		State.ChangeState("Trap");
		return;
	}

	WaterBombUpdate();
}

void APlayer::MoveStart()
{
	//Dir = FVector::Zero;
}

void APlayer::Move(float _DeltaTime)
{
	if (true == IsFree(VK_UP) && true == IsFree(VK_DOWN) && true == IsFree(VK_RIGHT) && true == IsFree(VK_LEFT))
	{
		State.ChangeState("Idle");
		return;
	}

	// 물줄기에 맞았을 때
	if (true == GetGameMode()->GetCurMap()->IsOnWater(GetActorLocation()))
	{
		if (Info->RideType != EPlayerRideType::None)
		{
			// 탈 것에 타있었다면 내리기 (SetRideType 내에서 State변경까지 함)
			SetRideType(EPlayerRideType::None);
			return;
		}
		State.ChangeState("Trap");
		return;
	}

	WaterBombUpdate();
	MoveUpdate(_DeltaTime);

}

void APlayer::TrapStart()
{
	Renderer->ChangeAnimation(GetAnimationName("Trap"));
	TrapDir = FVector::Up;
	TrapMoveTime = 1.f;
	TrapToDieTime = 5.f;

	UEngineSound::SoundPlay("Damaged.wav");
}

void APlayer::Trap(float _DeltaTime)
{
#ifdef _DEBUG
	// 치트키 : F2키 누르면 Rescue 상태로 변경
	if (true == IsDown(VK_F2))
	{
		Renderer->SetPosition(FVector::Zero);
		State.ChangeState("Rescue");
		return;
	}
#endif

	IsPlayerTrap = true;

	// Trap 상태에서 바늘 아이템 사용 시 Rescue 상태로 변경, 바늘 아이템 소거
	if (true == IsDown(VK_CONTROL) && CtrlItem == EItemType::ItemNiddle)
	{
		CtrlItem = EItemType::None;

		Renderer->SetPosition(FVector::Zero);
		State.ChangeState("Rescue");
		return;
	}

	TrapMoveTime -= _DeltaTime;
	//TrapAnimationTime -= _DeltaTime;
	TrapToDieTime -= _DeltaTime;

	// Renderer 상하로 움직이도록 Dir을 변경
	if (TrapMoveTime < 0.f)
	{
		TrapDir *= -1.f;
		TrapMoveTime = 1.f;
	}
	Renderer->AddPosition(TrapDir * TrapMoveSpeed * _DeltaTime);

	AOtherPlayer* Other = IsOtherPlayer();
	if (nullptr != Other)
	{
		if (Other->GetTeamType() == Info->Team)	// 같은 팀
		{
			State.ChangeState("Rescue");
			return;
		}
		else									// 다른 팀
		{
			State.ChangeState("Die");
			return;
		}
	}

	// Trap 이후 DieTime 초과 시 Die 상태로 변경
	if (TrapToDieTime < 0.f)
	{
		Renderer->SetPosition(FVector::Zero);
		State.ChangeState("Die");
		return;
	}

	//트랩상태 이동기능
	FVector MovePos = FVector::Zero;
	FVector NextPos1 = FVector::Zero;	// Center
	FVector NextPos2 = FVector::Zero;	// 추가 체크포인트
	FVector NextPos3 = FVector::Zero;	// 추가 체크포인트


	if (true == IsPress(VK_UP))
	{
		Dir = FVector::Up;
		NextPos1 = GetActorLocation() + MovePos + Dir * 20.f;
		NextPos2 = NextPos1 + FVector(-15, 0, 0);
		NextPos3 = NextPos1 + FVector(15, 0, 0);
		MovePos = FVector::Up * TrapBubbleMoveSpeed * _DeltaTime;
	}
	if (true == IsPress(VK_DOWN))
	{
		Dir = FVector::Down;
		NextPos1 = GetActorLocation() + MovePos + Dir * 5.f;
		NextPos2 = NextPos1 + FVector(-15, 0, 0);
		NextPos3 = NextPos1 + FVector(15, 0, 0);
		MovePos = FVector::Down * TrapBubbleMoveSpeed * _DeltaTime;
	}
	if (true == IsPress(VK_RIGHT))
	{
		Dir = FVector::Right;
		NextPos1 = GetActorLocation() + MovePos + Dir * 20.f;
		NextPos2 = NextPos1 + FVector(0, 10, 0);
		NextPos3 = NextPos1 + FVector(0, 0, 0);
		MovePos = FVector::Right * TrapBubbleMoveSpeed * _DeltaTime;
	}
	if (true == IsPress(VK_LEFT))
	{
		Dir = FVector::Left;
		NextPos1 = GetActorLocation() + MovePos + Dir * 20.f;
		NextPos2 = NextPos1 + FVector(0, 10, 0);
		NextPos3 = NextPos1 + FVector(0, 0, 0);
		MovePos = FVector::Left * TrapBubbleMoveSpeed * _DeltaTime;
	}
	if (true == GetGameMode()->GetCurMap()->IsMove(NextPos1) && true == GetGameMode()->GetCurMap()->IsMove(NextPos2) && true == GetGameMode()->GetCurMap()->IsMove(NextPos3))
	{
		AddActorLocation(MovePos);
		SettingZValue();
		return;
	}

}

void APlayer::RescueStart()
{
	Renderer->ChangeAnimation(GetAnimationName("Rescue"));
	UEngineSound::SoundPlay("Revival.mp3");
}

void APlayer::Rescue(float _DeltaTime)
{
	IsPlayerTrap = false;

	if (true == Renderer->IsCurAnimationEnd())
	{
		Dir = FVector::Down;
		State.ChangeState("Idle");
		return;
	}
}

void APlayer::DieStart()
{
	Renderer->ChangeAnimation(GetAnimationName("Die"));
	Shadow->ShadowRenderOff();

	UEngineSound::SoundPlay("Die.mp3");

	DieAniTwinkleActive = 0;
	DieTwinkleTime = 0.1f;
	DieAnimationTime = 2.f;
}

void APlayer::Die(float _DeltaTime)
{
	if (5 == Renderer->GetCurAnimationFrame())
	{
		DieAnimationTime -= _DeltaTime;
		DieTwinkleTime -= _DeltaTime;

		if (DieTwinkleTime < 0.f)
		{
			Renderer->SetAlpha(static_cast<float>(DieAniTwinkleActive));
			DieAniTwinkleActive = static_cast<int>(!(static_cast<bool>(DieAniTwinkleActive)));
			DieTwinkleTime = 0.1f;
		}

		if (DieAnimationTime < 0.f)
		{
			State.ChangeState("RealDie");
			return;
		}
	}
}

void APlayer::RealDieStart()
{
	// 진짜 죽음 처리
	ConstValue::MainPlayerIsDie = true;
	Renderer->SetActive(false);
	SoloArrowRenderer->SetActive(false);

	SetActorLocation(FVector(0.0f, 10000.0f));

	PlayerListUI->ChangeAnimation(GetUIAnimationName("Cry"));
}

void APlayer::RealDie(float _DeltaTime)
{

}

void APlayer::RideIdleStart()
{
	// 임시로 Idle 사용 (RideIdle 만들면 바꿔야 함)
  	Renderer->ChangeAnimation(GetAnimationName("Idle"));	
	SoloArrowRenderer->SetPosition(FVector(0, 5, 0));
	RideTwinkleTime = 0.1f;
}

void APlayer::RideIdle(float _DeltaTime)
{
	RideGodModeTime -= _DeltaTime;
	RideTwinkleTime -= _DeltaTime;
	if (RideGodModeTime > 0.f)
	{
		if(RideTwinkleTime < 0.f)
		{
			Renderer->SetAlpha(static_cast<float>(RideAniTwinkleActive));
			RideAniTwinkleActive = static_cast<int>(!static_cast<bool>(RideAniTwinkleActive));
			RideTwinkleTime = 0.1f;
		}
		return;
	}

	Renderer->SetAlpha(1.f);

	if (true == IsPress(VK_UP) || true == IsPress(VK_DOWN) || true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT))
	{
		State.ChangeState("RideMove");
		return;
	}

	// 물줄기에 맞았을 때
	if (true == GetGameMode()->GetCurMap()->IsOnWater(GetActorLocation()))
	{
		// 탈것에서 내리기 (SetRideType 내에서 State변경까지 함)
		SetRideType(EPlayerRideType::None);
		return;
	}

	WaterBombUpdate();
}

void APlayer::RideMoveStart()
{

}

void APlayer::RideMove(float _DeltaTime)
{
	if (true == IsFree(VK_UP) && true == IsFree(VK_DOWN) && true == IsFree(VK_RIGHT) && true == IsFree(VK_LEFT))
	{
		State.ChangeState("RideIdle");
		return;
	}

	// 물줄기에 맞았을 때
	if (true == GetGameMode()->GetCurMap()->IsOnWater(GetActorLocation()))
	{
		// 탈것에서 내리기 (SetRideType 내에서 State변경까지 함)
		SetRideType(EPlayerRideType::None);
		return;
	}

	WaterBombUpdate();
	MoveUpdate(_DeltaTime);
	
}

void APlayer::RideOffStart()
{
	// 처음 몇초간 무적
	RideGodModeTime = 2.f;
	RideTwinkleTime = 0.1f;
}

void APlayer::RideOff(float _DeltaTime)
{
	RideGodModeTime -= _DeltaTime;
	RideTwinkleTime -= _DeltaTime;
	if (RideGodModeTime > 0.f)
	{
		if (RideTwinkleTime < 0.f)
		{
			Renderer->SetAlpha(static_cast<float>(RideAniTwinkleActive));
			RideAniTwinkleActive = static_cast<int>(!static_cast<bool>(RideAniTwinkleActive));
			RideTwinkleTime = 0.1f;
		}
		return;
	}

	if (RideGodModeTime < 0.f)
	{
		SoloArrowRenderer->SetPosition(FVector(0, 4, 0));
		State.ChangeState("Idle");
		return;
	}
}

void APlayer::WinStart()
{
	InputOff();
	Renderer->ChangeAnimation(GetAnimationName("Win"));
}

void APlayer::Win(float _DeltaTime)
{

}

void APlayer::LoseStart()
{
	InputOff();
	//우선 State Idle로 변경 후 , Dir_Down 으로만 보게..
	Dir = FVector::Down;
	Renderer->ChangeAnimation(GetAnimationName("Idle"));
}

void APlayer::Lose(float _DeltaTime)
{

}


// 물풍선 놓는 함수
void APlayer::WaterBombUpdate()
{
	if (true == IsDown(VK_SPACE))
	{
		int CurCount = Info->WBCount;

		if (CurCount <= 0)
		{
			return;
		}

		POINT PlayerPoint = GetGameMode()->GetCurMap()->PosToPoint(GetActorLocation());
		if (GetGameMode()->GetCurMap()->GetMapObject(PlayerPoint.y, PlayerPoint.x) != nullptr &&
			GetGameMode()->GetCurMap()->GetMapObject(PlayerPoint.y, PlayerPoint.x)->GetType() == EMapObjectType::Block)
		{
			return;
		}
		
		// Player가 있는 위치에 물풍선이 없을 때.
		if (true != GetGameMode()->GetCurMap()->IsOnWaterBomb(GetActorLocation()))
		{
			--Info->WBCount;
			POINT BombPoint = GetGameMode()->GetCurMap()->PosToPoint(GetActorLocation());
	
			std::shared_ptr<AMapObject> WaterBomb = GetGameMode()->GetCurMap()->SpawnWaterBomb(BombPoint.y, BombPoint.x, Info->WBPower, GetObjectToken());
			WaterBomb->SetObjectToken(WaterBomb_Token++);
			USendPacketManager::SendWaterBombSpawnPacket(WaterBomb, { BombPoint.y, BombPoint.x }, EMapObject::WaterBomb, Info->WBPower);

			UEngineSound::SoundPlay("SetBallon.wav");
		}
	}
}

void APlayer::MoveUpdate(float _DeltaTime)
{
	FVector MovePos = FVector::Zero;
	FVector NextPos1 = GetActorLocation();	// Center
	FVector NextPos2 = NextPos1;	// 추가 체크포인트
	FVector NextPos3 = NextPos1;	// 추가 체크포인트

	float Speed = static_cast<float>(Info->Speed);

	if (true == IsPress(VK_UP))
	{
		Dir = FVector::Up;
		NextPos1 = GetActorLocation() + MovePos + Dir * 20.f;
		NextPos2 = NextPos1 + FVector(-15, 0, 0);
		NextPos3 = NextPos1 + FVector(15, 0, 0);
		MovePos = FVector::Up * Speed * MoveSpeed * _DeltaTime;
	}
	if (true == IsPress(VK_DOWN))
	{
		Dir = FVector::Down;
		NextPos1 = GetActorLocation() + MovePos + Dir * 5.f;
		NextPos2 = NextPos1 + FVector(-15, 0, 0);
		NextPos3 = NextPos1 + FVector(15, 0, 0);
		MovePos = FVector::Down * Speed * MoveSpeed * _DeltaTime;
	}
	if (true == IsPress(VK_RIGHT))
	{
		Dir = FVector::Right;
		NextPos1 = GetActorLocation() + MovePos + Dir * 20.f;
		NextPos2 = NextPos1 + FVector(0, 10, 0);
		NextPos3 = NextPos1 + FVector(0, 0, 0);
		MovePos = FVector::Right * Speed * MoveSpeed * _DeltaTime;
	}
	if (true == IsPress(VK_LEFT))
	{
		Dir = FVector::Left;
		NextPos1 = GetActorLocation() + MovePos + Dir * 20.f;
		NextPos2 = NextPos1 + FVector(0, 10, 0);
		NextPos3 = NextPos1 + FVector(0, 0, 0);
		MovePos = FVector::Left * Speed * MoveSpeed * _DeltaTime;
	}

	Renderer->ChangeAnimation(GetAnimationName("Move"));
	if (true == GetGameMode()->GetCurMap()->IsMove(NextPos1) && true == GetGameMode()->GetCurMap()->IsMove(NextPos2) && true == GetGameMode()->GetCurMap()->IsMove(NextPos3))
	{
		AddActorLocation(MovePos);
		//SettingZValue();
		return;
	}

}

void APlayer::DebugFunction(float _DeltaTime)
{
	std::string PlayerSpeed = std::format("Player Speed : {}\n", Info->Speed);
	std::string WaterCount = std::format("Water Count : {}\n", Info->WBCount);
	std::string WaterPower= std::format("Water Power : {}\n", Info->WBPower);

	UEngineDebugMsgWindow::PushMsg(PlayerSpeed);
	UEngineDebugMsgWindow::PushMsg(WaterCount);
	UEngineDebugMsgWindow::PushMsg(WaterPower);
}