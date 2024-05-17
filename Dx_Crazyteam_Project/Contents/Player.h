#pragma once
#include <EngineBase/NetObject.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "ContentsEnum.h"
#include "CAObject.h"
#include "NetInterface.h"

class APlayer;
class PlayerInfo
{
	friend APlayer;

public:
	POINT CurIndex = POINT(0, 0);
	ECharacterType MyType = ECharacterType::Bazzi;
	ETeamType Team = ETeamType::ATeam;
	EPlayerRideType RideType = EPlayerRideType::None;

	int Speed = -1;					// 속도 단계 (1씩 증가시켜주면 속도 계수와 곱해서 적용됨)
	int WBCount = -1;				// 물폭탄 개수	
	int WBPower = -1;				// 물폭탄 파워(물줄기 길이)

	int MaxSpeed = -1;
	int MaxWBCount = -1;
	int MaxWBPower = -1;
};

class APlayer_Shadow;

class APlayer : public ACAObject
{
	GENERATED_BODY(ACAObject)
public:
	APlayer();
	~APlayer();

	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;
	
	void SetCharacterType(ECharacterType _Type);

	void SetWBCount(int _count)
	{
		Info->WBCount = _count;
	}

	void SetTeamType(ETeamType _Team)
	{
		Info->Team = _Team;
	}
	
	void SetSpeed(int _speed)
	{
		Info->Speed = _speed;
	}

	int GetWBCount()
	{
		return Info->WBCount;
	}

	int GetWBPower()
	{
		return Info->WBPower;
	}

	int GetSpeed()
	{
		return Info->Speed;
	}

	PlayerInfo* GetPlayerInfo()
	{
		return Info.get();
	}

	inline bool GetIsSendPacket() const
	{
		return IsSendPacket;
	}

	inline void OffIsSendPacket()
	{
		IsSendPacket = false;
	}

	static int WaterBomb_Token;
	int WaterCourse_Token;

protected:
	std::shared_ptr<PlayerInfo> Info = nullptr;
	UStateManager State;
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	void StateInit();

	void GameOnStart();
	void GameOn(float _DeltaTime);
	void IdleStart();
	void Idle(float _DeltaTime);
	void MoveStart();
	void Move(float _DeltaTime);
	void TrapStart();
	void Trap(float _DeltaTime);
	void RescueStart();
	void Rescue(float _DeltaTime);
	void DieStart();
	void Die(float _DeltaTime);
	void RealDieStart();
	void RealDie(float _DeltaTime);
	void RideIdleStart();
	void RideIdle(float _DeltaTime);
	void RideMoveStart();
	void RideMove(float _DeltaTime);

	float GameOnTime = 1.5f;

	std::string GetAnimationName(std::string_view _StateName);
	void SettingZValue();

	FVector Dir = FVector::Down;
	float AnimationInter = 0.1f;
	float MoveSpeed = 20.f;		// 속도 계수

	float TrapMoveSpeed = 0.4f;
	float TrapMoveTime = 1.f;
	float TrapAnimationTime = 3.f;
	float TrapToDieTime = 5.f;
	FVector TrapDir = FVector::Up;

	bool DieAniTwinkleActive = false;
	float DieAnimationTime = 2.f;
	float DieTwinkleTime = 0.1f;

	std::shared_ptr<APlayer_Shadow> Shadow = nullptr;

	bool IsSendPacket = true;

};


