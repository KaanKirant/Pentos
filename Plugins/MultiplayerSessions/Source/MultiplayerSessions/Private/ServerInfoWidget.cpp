// Copyright Kaan Kirant.


#include "ServerInfoWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "MultiplayerSessions/Public/Menu.h"

void UServerInfoWidget::OnJoinClicked()
{
	if (Parent)
	{
		Parent->GetSubsystem()->JoinSession(Result);
	}
}

void UServerInfoWidget::Setup(FOnlineSessionSearchResult InResult, int32 InIndex, UMenu* InParent)
{
	Result = InResult;
	Parent = InParent;

	//FString ServerName;
	//Result.Session.SessionSettings.Get(FName("MatchType"), ServerName);
	ServerNameText->SetText(FText::FromString(Result.Session.OwningUserName));

	int32 MaxPlayers = Result.Session.SessionSettings.NumPublicConnections;
	int32 CurrentPlayers = MaxPlayers - Result.Session.NumOpenPublicConnections;

	PlayersText->SetText(FText::FromString(
	FString::Printf(TEXT("%d/%d"), CurrentPlayers, MaxPlayers)));

	PingText->SetText(FText::AsNumber(Result.PingInMs));

	JoinButton->OnClicked.AddDynamic(this, &UServerInfoWidget::OnJoinClicked);
}