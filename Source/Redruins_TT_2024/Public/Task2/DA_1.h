// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_1.generated.h"

class UDA_2;


USTRUCT(BlueprintType)
struct FDA_2Ptr
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	TObjectPtr<UDA_2> DataAsset = nullptr;
};

UCLASS(BlueprintType)
class REDRUINS_TT_2024_API UDA_1 : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings", meta=(ShowOnlyInnerProperties))
	FDA_2Ptr DataAssetStruct;
};
