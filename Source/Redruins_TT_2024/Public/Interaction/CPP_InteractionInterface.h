// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CPP_InteractionInterface.generated.h"

class UCPP_InteractionComponent;

UINTERFACE()
class UCPP_InteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class REDRUINS_TT_2024_API ICPP_InteractionInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category="Interaction")
	bool CanInteract(UCPP_InteractionComponent* _interactionComponent);

	UFUNCTION(BlueprintNativeEvent, Category="Interaction")
	void Interact(UCPP_InteractionComponent* _interactionComponent);

	UFUNCTION(BlueprintNativeEvent, Category="Interaction")
	FVector GetInteractionWidgetOffset(UCPP_InteractionComponent* _interactionComponent);

protected:
	virtual bool CanInteract_Implementation(UCPP_InteractionComponent* _interactionComponent) { return true; }
	virtual void Interact_Implementation(UCPP_InteractionComponent* _interactionComponent) { ; }
	virtual FVector GetInteractionWidgetOffset_Implementation(UCPP_InteractionComponent* _interactionComponent) { return FVector::ZeroVector; }
};
