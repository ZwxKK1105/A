// BY Zwx


#include "WarriorTypes/WarriorCountDownAction.h"

void FWarriorCountDownAction::UpdateOperation(FLatentResponse& Response)
{
	if (bNeedToCancel)
	{
		CountDownOutPut = EWarriorCountDownActionOutPut::Cancelled;
		Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
		return;
	}
	
	if (ElapsedTimeSinceStart>=TotalCountDownTime)
	{
		CountDownOutPut = EWarriorCountDownActionOutPut::Completed;
		Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
		return;
	}
	
	if (ElapsedInterval < UpdateInterval)
	{
		ElapsedInterval += Response.ElapsedTime();
		
	}
	else
	{
		ElapsedTimeSinceStart += UpdateInterval > 0.f ? UpdateInterval : Response.ElapsedTime();

		OutRemainingTime = TotalCountDownTime - ElapsedTimeSinceStart;

		CountDownOutPut = EWarriorCountDownActionOutPut::Updated;

		Response.TriggerLink(ExecutionFunction, OutputLink, CallbackTarget);

		ElapsedInterval = 0.f;
	}


}

void FWarriorCountDownAction::CancelAction()
{
	bNeedToCancel = true;
}
