// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HosekSky.generated.h"

USTRUCT(BlueprintType)
	struct FHosekParams { 

		GENERATED_BODY()

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

UCLASS()
class TESTHOSEK_API AHosekSky : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHosekSky();


	UFUNCTION(BlueprintCallable, Category = "Atmosphere")
	FHosekParams Compute(float sunTheta, float turbidity, float albedo, float normalizedSunY);

	UFUNCTION(BlueprintCallable, Category = "Atmosphere")
	static float Evaluate(bool notRad, int dataset,int splineStart, int stride, float turbidity, float albedo, float sunTheta);

	
	static float EvaluateSpline(bool notRad, int dataset, int splineStart, int stride, float value);

	UFUNCTION(BlueprintCallable, Category = "Atmosphere")
	static FVector PerezExt(float cos_theta, float gamma, float cos_gamma, FVector A, FVector B, FVector C, FVector D, FVector E, FVector F, FVector G, FVector H, FVector I);

	UFUNCTION(BlueprintCallable, Category = "Math")
	static FVector PowV(FVector base, float expo);

	UFUNCTION(BlueprintCallable, Category = "Math")
	static FVector ExpV(FVector vec);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Atmosphere", meta = (AllowPrivateAccess = "true"))
	FVector Albedo;*/

	
};


