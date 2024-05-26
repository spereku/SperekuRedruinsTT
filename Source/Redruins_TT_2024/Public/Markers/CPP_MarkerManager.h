// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "CPP_Types.h"
#include "Components/ActorComponent.h"
#include "CPP_MarkerManager.generated.h"


class UCPP_MarkerComponent;

UCLASS(ClassGroup=(Markers), meta=(BlueprintSpawnableComponent))
class REDRUINS_TT_2024_API UCPP_MarkerManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category="Markers")
	FNoParamSignature OnMarkersChanged;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Markers")
	void GetMarkers(TArray<UCPP_MarkerComponent*>& _outMarkers) const { _outMarkers = Markers.Array(); }

	void AddMarker(UCPP_MarkerComponent* _marker);
	void RemoveMarker(UCPP_MarkerComponent* _marker);

private:
	UPROPERTY(Transient)
	TSet<TObjectPtr<UCPP_MarkerComponent>> Markers;
};
