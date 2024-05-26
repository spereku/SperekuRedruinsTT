// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CPP_ReplicatedObject.generated.h"

//Code from https://jambax.co.uk/replicating-uobjects/
UCLASS(BlueprintType,Blueprintable)
class REDRUINS_TT_2024_API UCPP_ReplicatedObject : public UObject
{
	GENERATED_BODY()
public:
	
	virtual UWorld* GetWorld() const override;
	AActor* GetOwningActor() const{return GetTypedOuter<AActor>();}
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual bool IsSupportedForNetworking() const override{return true;}
	
	virtual int32 GetFunctionCallspace(UFunction* Function, FFrame* Stack) override;

	virtual bool CallRemoteFunction(UFunction* Function, void* Parms, struct FOutParmRec* OutParms, FFrame* Stack) override;
};
