#pragma once
#include "CoreMinimal.h"

USTRUCT(BlueprintType)
	struct FHosekParams { 
	public:
		GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Parameters")
		FVector A;
		UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Parameters")
		FVector B;
		UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Parameters")
		FVector c;
		UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Parameters")
		FVector D;
		UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Parameters")
		FVector E;
		UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Parameters")
		FVector F;
		UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Parameters")
		FVector G;
		UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Parameters") 
		FVector H;
		UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Parameters")
		FVector I;
		UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Parameters")
		FVector Z;

	};
//
