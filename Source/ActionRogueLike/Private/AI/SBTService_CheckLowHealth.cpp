// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckLowHealth.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SAttributeComponent.h"

void USBTService_CheckLowHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackboardComp))
	{
		AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject("SelfActor"));
		if (TargetActor)
		{
			USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(TargetActor->GetComponentByClass(USAttributeComponent::StaticClass()));
			if (ensure(AttributeComp))
			{
				if (AttributeComp->GetCurrentHealth() < LowHealth)
				{
					BlackboardComp->SetValueAsBool(IsLowOnHealthKey.SelectedKeyName, true);
					return;
				}

				BlackboardComp->SetValueAsBool(IsLowOnHealthKey.SelectedKeyName, false);
			}
		}
	}
}
