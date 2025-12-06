// Copyright Kaan Kirant.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MultiplayerSessionsSubsystem.h"
#include "ServerInfoWidget.generated.h"

class UMenu;
class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UServerInfoWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* ServerNameText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* PlayersText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* PingText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* JoinButton;

	UFUNCTION()
	void OnJoinClicked();

	void Setup(FOnlineSessionSearchResult InResult, int32 InIndex, UMenu* InParent);

	UPROPERTY()
	UMenu* Parent;
	
	FOnlineSessionSearchResult Result;
};
