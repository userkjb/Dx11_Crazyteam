#include "PreCompile.h"
#include "Block.h"

ABlock::ABlock() 
{
}

ABlock::~ABlock() 
{
}

void ABlock::BeginPlay()
{
	Super::BeginPlay();

	SetType(EMapObjectType::Block);
}

void ABlock::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

