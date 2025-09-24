// Copyright Kaan Kirant.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PentosHUD.generated.h"

class UPentosUserWidget;
/**
 * 
 */
UCLASS()
class PENTOS_API APentosHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TObjectPtr<UPentosUserWidget> OverlayWidget;
	void InitOverlay();
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UPentosUserWidget> OverlayWidgetClass;
};
