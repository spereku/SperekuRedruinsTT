// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPP_CharacterForUObjectReplication.generated.h"

class UCPP_ReplicatedObject;

UCLASS()
class REDRUINS_TT_2024_API ACPP_CharacterForUObjectReplication : public ACharacter
{
	GENERATED_BODY()

	virtual bool ReplicateSubobjects(UActorChannel *Channel, FOutBunch *Bunch, FReplicationFlags *RepFlags) override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const override;
protected:
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "ReplicatedObject")
	TObjectPtr<UCPP_ReplicatedObject> ReplicatedObject;
};
