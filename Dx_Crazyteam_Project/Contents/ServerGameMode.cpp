#include "PreCompile.h"
#include "ServerGameMode.h"

#include <EngineCore/Image.h>
#include <EngineCore/Camera.h>
#include <EngineBase/EngineSerializer.h>
#include <EngineCore/BlurEffect.h>
#include <EngineCore/EngineEditorGUI.h>

#include "ServerPlayer.h"
#include "Game_Core.h"
#include "Packets.h"
#include "OtherPlayer.h"

AServerGameMode::AServerGameMode() 
{
}

AServerGameMode::~AServerGameMode() 
{
	if (nullptr != UGame_Core::Net)
	{
		UGame_Core::Net->End();
		UGame_Core::Net = nullptr;
	}
}

void AServerGameMode::BeginPlay() 
{
	Super::BeginPlay();
	// TestThread.Start();
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));

	MainPlayer = GetWorld()->SpawnActor<AServerPlayer>("Player");
}

void AServerGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void AServerGameMode::LevelStart(ULevel* _DeltaTime)
{
	if (nullptr == NetWindow)
	{
		NetWindow = UEngineEditorGUI::CreateEditorWindow<UEngineNetWindow>("NetWindow");

		NetWindow->SetServerOpenFunction([&]()
			{
				UGame_Core::Net = std::make_shared<UEngineServer>();
				UGame_Core::Net->ServerOpen(30000, 512);

				// ���⿡�� ���� �÷��̾����� ��ȣ�� �ϳ� �̴ٰϴ�.

				MainPlayer->SetObjectToken(UNetObject::GetNewObjectToken());

				ServerPacketInit(UGame_Core::Net->Dispatcher);
			});

		NetWindow->SetClientConnectFunction([&](std::string IP, short PORT)
			{
				UGame_Core::Net = std::make_shared<UEngineClient>();
				UGame_Core::Net->Connect(IP, PORT);

				UGame_Core::Net->SetTokenPacketFunction([=](USessionTokenPacket* _Token)
					{
						MainPlayer->SetObjectToken(_Token->GetObjectToken());

					});

				// � ��Ű�� ������ ��� ó���Ұ����� ���ϴ� �� �ؾ��Ѵ�.
				ClientPacketInit(UGame_Core::Net->Dispatcher);
			});
	}
	NetWindow->On();
}

void AServerGameMode::ServerPacketInit(UEngineDispatcher& Dis)
{
	Dis.AddHandler<UActorUpdatePacket>([=](std::shared_ptr<UActorUpdatePacket> _Packet)
		{
			// �ٸ� ��������� �� ������Ʈ�� ���ؼ� �˸���
		    UGame_Core::Net->Send(_Packet);

			GetWorld()->PushFunction([=]()
				{
					AOtherPlayer* OtherPlayer = UNetObject::GetNetObject<AOtherPlayer>(_Packet->GetObjectToken());
					if (nullptr == OtherPlayer)
					{
						OtherPlayer = this->GetWorld()->SpawnActor<AOtherPlayer>("OtherPlayer", 0).get();
						OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
					}
					OtherPlayer->SetActorLocation(_Packet->Pos);
				});


		});
}

void AServerGameMode::ClientPacketInit(UEngineDispatcher& Dis)
{
	Dis.AddHandler<UActorUpdatePacket>([=](std::shared_ptr<UActorUpdatePacket> _Packet)
		{
			GetWorld()->PushFunction([=]()
				{
					AOtherPlayer* OtherPlayer = UNetObject::GetNetObject<AOtherPlayer>(_Packet->GetObjectToken());
					if (nullptr == OtherPlayer)
					{
						OtherPlayer = this->GetWorld()->SpawnActor<AOtherPlayer>("OtherPlayer", 0).get();
						OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
					}
					OtherPlayer->SetActorLocation(_Packet->Pos);
				});
		});
}

void AServerGameMode::LevelEnd(ULevel* _DeltaTime)
{
	NetWindow->Off();
}