// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "Menu.generated.h"

class UScrollBox;
class UButton;
class UMultiplayerSessionsSubsystem;
/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup(int32 NumberOfPublicConnections = 4, FString TypeOfMatch = FString(TEXT("Coop")), FString LobbyPath = FString(TEXT("/Game/Maps/Lobby")));
	
protected:
	virtual bool Initialize() override;
	virtual void NativeDestruct() override;

	//
	// Callbacks for the custom delegates on the MultiplayerSessionsSubsystem
	//
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
	
	void OnFindSession(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);
	
	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);
	UFUNCTION()
	void OnStartSession(bool bWasSuccessful);

	UPROPERTY(BlueprintReadWrite)
	int32 NumPublicConnections{4};

	TArray<FOnlineSessionSearchResult> MatchingSessionResults;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> ServerInfoWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	FString MatchType{TEXT("Coop")};
	UPROPERTY(BlueprintReadWrite)
	FString PathToLobby{TEXT("")};

private:

	UPROPERTY(meta = (BindWidget))
	UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	UButton* FindButton;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ServerListScrollBox;

	UFUNCTION()
	void HostButtonClicked();

	UFUNCTION()
	void JoinButtonClicked();

	UFUNCTION()
	void FindButtonClicked();

	void MenuTearDown();

	void CreateServerRow(const FOnlineSessionSearchResult& Result, int32 Index);

	//Subsystem designed to handle all online session functionality.
	UMultiplayerSessionsSubsystem* MultiplayerSessionsSubsystem;

public:
	UMultiplayerSessionsSubsystem* GetSubsystem() const {return MultiplayerSessionsSubsystem;}
};
