#include "PreCompile.h"
#include "LobbyMainMode.h"
#include "PlayLobby.h"
#include "FontActor.h"
#include "Game_Core.h"
#include "OtherLobbyPlayer.h"
#include "Packets.h"
#include <EngineCore/Image.h>


ALobbyMainMode::ALobbyMainMode()
{
}

ALobbyMainMode::~ALobbyMainMode()
{
}

void ALobbyMainMode::BeginPlay()
{
	Super::BeginPlay();

	PlayLobby = GetWorld()->SpawnActor<APlayLobby>("Lobby");
	GetWorld()->SpawnActor<AFontActor>("FontActor");
}


void ALobbyMainMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}

void ALobbyMainMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
	GEngine->DestroyLevel("LobbyMainMode");
}

void ALobbyMainMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	PlayLobby->SetMySessionToken(UGame_Core::Net->GetSessionToken());

	if (0 == UGame_Core::Net->GetSessionToken())
	{
		ServerPacketInit(UGame_Core::Net->Dispatcher);
	}
	else if (1 <= UGame_Core::Net->GetSessionToken())
	{
		ClientPacketInit(UGame_Core::Net->Dispatcher);
	}
}

void ALobbyMainMode::ServerPacketInit(UEngineDispatcher& Dis)
{
	Dis.AddHandler<ULobbyPlayerUpdatePacket>([=](std::shared_ptr<ULobbyPlayerUpdatePacket> _Packet)
		{
			//UGame_Core::Net->Send(_Packet);
			PlayLobby->SetMySessionToken(_Packet->GetSessionToken());
	
			AOtherLobbyPlayer* OtherPlayer = UNetObject::GetNetObject<AOtherLobbyPlayer>(_Packet->GetObjectToken());
			if (nullptr == OtherPlayer)
			{
				OtherPlayer = this->GetWorld()->SpawnActor<AOtherLobbyPlayer>("OtherLobbyPlayer", 0).get();
				OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
				OtherPlayer->MySessionToken = _Packet->GetObjectToken() - 110000;
			}
			OtherPlayer->PushProtocol(_Packet);
			
		});
}

void ALobbyMainMode::ClientPacketInit(UEngineDispatcher& Dis)
{
	Dis.AddHandler<ULobbyPlayerUpdatePacket>([=](std::shared_ptr<ULobbyPlayerUpdatePacket> _Packet)
		{
			UNetObject* OtherPlayer = UNetObject::GetNetObject<UNetObject>(_Packet->GetObjectToken());
			if (nullptr == OtherPlayer)
			{
				if (PlayLobby->LobbyPlayer[_Packet->Token] == nullptr)
				{
					UImage* Sprite = CreateWidget<UImage>(GetWorld(), "LobbyPlayer");
					PlayLobby->LobbyPlayer[_Packet->Token] = Sprite;
					Sprite->SetActive(false);
					OtherPlayer = this->GetWorld()->SpawnActor<AOtherLobbyPlayer>("OtherLobbyPlayer", 0).get();
				}
			}
			OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
			OtherPlayer->PushProtocol(_Packet);
		});
}