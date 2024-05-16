#pragma once

enum class ERenderOrder
{
	None,
	Background,
	Map,
	Shadow,
	Item,
	BlockFront,
	Player,
	BlockBack,
	WaterBomb,
	UI,
};

enum class ECollisionOrder
{
	Player,
	Monster,
};

enum class EMapObjectType {
	None,
	Block,   //움직이지도 부서지지도 않는 블록 / 물풍선
	Bush,          //부시
	Water,  //물줄기
	WaterBalloon, // 물풍선
	Item,
};

enum class EItemType
{
	None,
	ItemBubble,	// 개수 + 1 아이템
	ItemFluid,	// 줄기 + 1 아이템
	ItemRoller,	// 속도 + 1 아이템
	ItemOwl,    // 속도 레벨6 아이템
	ItemShoes,  // 물풍선 kick 아이템
	ItemNiddle, // Trap 상태에서 Rescue 만들어주는 아이템
};

enum class EMapObject
{
	Default,
	DummyBlock,
	NormalBlock,
	CampBlock,
	CampMoveBlock,
	WaterBomb,
	Water,
	Item,
};

enum class ECharacterType
{
	None,
	Bazzi,
	Dao,
	Marid,
};

enum class ECADir
{
	None,
	Right,
	Left,
	Up,
	Down,
};

enum class ETeamType
{
	None,
	ATeam,
	BTeam,
};

enum class EPlayerRideType
{
	None,
	Owl,
	Turtle,
};