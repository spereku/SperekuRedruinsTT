// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_2.generated.h"

UENUM(BlueprintType)
enum class EDA_1Display : uint8
{
	value_true,
	value_false,
	value_n
};

class UDA_1;

UCLASS(BlueprintType)
class REDRUINS_TT_2024_API UDA_2 : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	EDA_1Display DA_1Display;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings", meta=(EditCondition="DA_1Display==EDA_1Display::value_true",EditConditionHides))
	TObjectPtr<UDA_1> DataAsset;
};
