// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HosekSky.generated.h"
struct HosekParams;

UCLASS()
class TESTHOSEK_API AHosekSky : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHosekSky();


	UFUNCTION(BlueprintCallable, Category = "Atmosphere")
	HosekParams Compute(float sunTheta, float turbidity, float albedo, float normalizedSunY);

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
