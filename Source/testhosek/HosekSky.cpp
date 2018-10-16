// Fill out your copyright notice in the Description page of Project Settings.

#include "HosekSky.h"
#include <algorithm>
#include <corecrt_math_defines.h>
#include <iostream>
#define _USE_MATH_DEFINES
//#include "../../Intermediate/ProjectFiles/HosekParams.h"

namespace
{
#include "../../Intermediate/ProjectFiles/hosek_data_rgb.inl"
}





// Sets default values
AHosekSky::AHosekSky()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// << stf;
}

// Called when the game starts or when spawned
void AHosekSky::BeginPlay()
{
	Super::BeginPlay();
	auto stf = datasetsRGB[0] + 1;
}

// Called every frame
void AHosekSky::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto stf = datasetsRGB[0] + 1;
}


FVector AHosekSky::PowV(FVector base, float expo) {
	return FVector{pow(base.X,expo),pow(base.Y,expo),pow(base.Z,expo)};
}

FVector AHosekSky::ExpV(FVector vec) {
	return FVector{exp(vec.X),exp(vec.Y),exp(vec.Z)};
}

//HosekParams AHosekSky::Compute(float sunTheta, float turbidity, float albedo, float normalizedSunY)
//{
//	FVector A, B, C, D, E, F, G, H, I;
//	FVector Z;
//
//	for (int i = 0; i < 3; ++i)
//	{
//
//		A[i] = Evaluate(datasetsRGB[i] + 0, 9, turbidity, albedo, sunTheta);
//		B[i] = Evaluate(datasetsRGB[i] + 1, 9, turbidity, albedo, sunTheta);
//		C[i] = Evaluate(datasetsRGB[i] + 2, 9, turbidity, albedo, sunTheta);
//		D[i] = Evaluate(datasetsRGB[i] + 3, 9, turbidity, albedo, sunTheta);
//		E[i] = Evaluate(datasetsRGB[i] + 4, 9, turbidity, albedo, sunTheta);
//		F[i] = Evaluate(datasetsRGB[i] + 5, 9, turbidity, albedo, sunTheta);
//		G[i] = Evaluate(datasetsRGB[i] + 6, 9, turbidity, albedo, sunTheta);
//
//		// Note: H and I are swapped in the dataset; we use notation from paper
//		H[i] = Evaluate(datasetsRGB[i] + 8, 9, turbidity, albedo, sunTheta);
//		I[i] = Evaluate(datasetsRGB[i] + 7, 9, turbidity, albedo, sunTheta);
//
//		Z[i] = Evaluate(datasetsRGBRad[i], 1, turbidity, albedo, sunTheta);
//	}
//
//	if (normalizedSunY)
//	{
//		FVector S = PerezExt(std::cos(sunTheta), 0, 1.f, A, B, C, D, E, F, G, H, I) * Z;
//
//		Z /= FVector::DotProduct(S,FVector(0.2126, 0.7152, 0.0722));
//		Z *= normalizedSunY;
//		
//	}
//
//	return { A, B, C, D, E, F, G, H, I, Z };
//}

FVector AHosekSky::PerezExt(float cos_theta, float gamma, float cos_gamma, FVector A, FVector B, FVector C, FVector D, FVector E, FVector F, FVector G, FVector H, FVector I)
{
	FVector chi = (1/(1 + cos_gamma * cos_gamma)) * PowV((H * H + 1.f ) - 2.f * cos_gamma * H, 1.5f);

	return (A * ExpV(B / FVector(cos_theta + 0.01f))+ 1.f)*
		(C + D * ExpV(E * gamma) + F * (cos_gamma * cos_gamma) + G * chi + I * sqrt(std::max(0.f, cos_theta)));
}



float AHosekSky::EvaluateSpline(TSharedPtr<float> spline, int stride, float value)
{
	return
		1 * pow(1 - value, 5) *                 spline.Get()[0 * stride] +
		5 * pow(1 - value, 4) * pow(value, 1) * spline.Get()[1 * stride] +
		10 * pow(1 - value, 3) * pow(value, 2) * spline.Get()[2 * stride] +
		10 * pow(1 - value, 2) * pow(value, 3) * spline.Get()[3 * stride] +
		5 * pow(1 - value, 1) * pow(value, 4) * spline.Get()[4 * stride] +
		1 * pow(value, 5) * spline.Get()[5 * stride];
}

float AHosekSky::Evaluate(TSharedPtr<float> dataset,int stride, float turbidity, float albedo, float sunTheta)
{
	// splines are functions of elevation^1/3
	float elevationK = FMath::Pow(std::max(0.f, 1.f - sunTheta / float(M_PI / 2.f)), 1.f / 3.0f);

	// table has values for turbidity 1..10
	int turbidity0 = FMath::Clamp(static_cast<int>(turbidity), 1, 10);
	int turbidity1 = std::min(turbidity0 + 1, 10);
	float turbidityK = FMath::Clamp(turbidity - turbidity0, 0.f, 1.f);

	TSharedPtr<float> datasetA0 = dataset;
	auto datasetA1 = (dataset.Get() + stride * 6 * 10);
	auto stf = dataset.Get() + 1;
	float a0t0 = EvaluateSpline(datasetA0. + stride * 6 * (turbidity0 - 1), stride, elevationK);
	float a1t0 = EvaluateSpline(datasetA1 + stride * 6 * (turbidity0 - 1), stride, elevationK);

	float a0t1 = EvaluateSpline(datasetA0 + stride * 6 * (turbidity1 - 1), stride, elevationK);
	float a1t1 = EvaluateSpline(datasetA1 + stride * 6 * (turbidity1 - 1), stride, elevationK);

	return
		a0t0 * (1 - albedo) * (1 - turbidityK) +
		a1t0 * albedo * (1 - turbidityK) +
		a0t1 * (1 - albedo) * turbidityK +
		a1t1 * albedo * turbidityK;
}
