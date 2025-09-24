// Copyright Kaan Kirant.


#include "UI/HUD/PentosHUD.h"
#include "UI/Widget/PentosUserWidget.h"

void APentosHUD::InitOverlay()
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_PentosHUD."));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UPentosUserWidget>(Widget);
	Widget->AddToViewport();
}
