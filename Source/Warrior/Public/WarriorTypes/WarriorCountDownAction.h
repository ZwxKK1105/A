// BY Zwx

#pragma once

#include"WarriorTypes/WarriorEnumTypes.h"
#include "CoreMinimal.h"

class FWarriorCountDownAction :public FPendingLatentAction
{
public:
	FWarriorCountDownAction(float InTotalCountTime,float InUpdateInterval,float& InOutRemainingTime, 
	EWarriorCountDownActionOutPut& InCountDownOutPut,const FLatentActionInfo& LatentInfo)
	:bNeedToCancel(false),
	TotalCountDownTime(InTotalCountTime),
	UpdateInterval(InUpdateInterval),
	OutRemainingTime(InOutRemainingTime),
	CountDownOutPut(InCountDownOutPut),
	ExecutionFunction(LatentInfo.ExecutionFunction),
	OutputLink(LatentInfo.Linkage),
	CallbackTarget(LatentInfo.CallbackTarget),
	ElapsedInterval(0.f),
	ElapsedTimeSinceStart(0.f)
	{
	
	}

	virtual void UpdateOperation(FLatentResponse& Response) override;

	void CancelAction();



private:
	bool bNeedToCancel;
	float TotalCountDownTime;
	float UpdateInterval;
	float& OutRemainingTime;
	EWarriorCountDownActionOutPut& CountDownOutPut;
	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;
	float ElapsedInterval;
	float ElapsedTimeSinceStart;
};

