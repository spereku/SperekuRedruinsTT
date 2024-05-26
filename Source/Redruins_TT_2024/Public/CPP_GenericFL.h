// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CPP_GenericFL.generated.h"

class UProjectileMovementComponent;

UCLASS()
class REDRUINS_TT_2024_API UCPP_GenericFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,Category="Projectile")
	static void ResetProjectileMovement(UProjectileMovementComponent* _projectileMovementComponent, UPrimitiveComponent*_updateComponent,const FVector&_velocity);
};
