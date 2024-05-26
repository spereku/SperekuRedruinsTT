// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CPP_MarkerComponent.generated.h"


class UCPP_MarkerManager;

UCLASS(ClassGroup=(Markers), meta=(BlueprintSpawnableComponent))
class REDRUINS_TT_2024_API UCPP_MarkerComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	//Function from https://forums.unrealengine.com/t/easy-offscreen-indicator-blueprint-node/21342/52 with small modifications
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Markers")
	void GetScreenLocationForMarker(APlayerController* _playerController, const float _edgePercent, const FVector2D _viewportCenterLoc, FVector2D& _outScreenPosition,
	                                float& _outRotationAngleDegrees, bool& _bIsOnScreen);

protected:
	virtual void Activate(bool bReset) override;
	virtual void Deactivate() override;

private:
	UPROPERTY(Transient)
	TObjectPtr<UCPP_MarkerManager> MarkerManager;
};
