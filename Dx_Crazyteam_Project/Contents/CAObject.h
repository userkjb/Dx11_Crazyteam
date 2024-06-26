#pragma once
#include "NetInterface.h"

// ���� :
class ACAGameMode;
class ACAObject : public UNetInterface
{
	GENERATED_BODY(UNetInterface)
public:
	// constructor destructor
	ACAObject();
	~ACAObject();

	// delete Function
	ACAObject(const ACAObject& _Other) = delete;
	ACAObject(ACAObject&& _Other) noexcept = delete;
	ACAObject& operator=(const ACAObject& _Other) = delete;
	ACAObject& operator=(ACAObject&& _Other) noexcept = delete;

	void SetCurGameMode(ACAGameMode* _GameMode)
	{
		CurGameMode = _GameMode;
	}

	ACAGameMode* GetGameMode()
	{
		return CurGameMode;
	}


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	ACAGameMode* CurGameMode = nullptr;
private:

};

