#include "SteeringBehaviors.h"

#include "HLSLMathAliases.h"
#include "GameAIProg/Movement/SteeringBehaviors/SteeringAgent.h"

//SEEK
//*******
// TODO: Do the Week01 assignment :^)
SteeringOutput Seek::CalculateSteering(float DeltaT, ASteeringAgent& Agent)
{
	SteeringOutput Steering{};
	Steering.LinearVelocity = Target.Position - Agent.GetPosition();
	
	//normalize not needed
	//Steering.LinearVelocity.Normalize();
	
	
	return Steering;
}

SteeringOutput Flee::CalculateSteering(float DeltaT, ASteeringAgent& Agent)
{
	SteeringOutput Steering{};
	Steering.LinearVelocity = Agent.GetPosition() - Target.Position;
	
	return Steering;
}

Arrive::Arrive(float AgentMaxSpeed)
	:m_MaxSpeed(AgentMaxSpeed)
{
}




SteeringOutput Arrive::CalculateSteering(float DeltaT, ASteeringAgent& Agent)
{
	const float breakRadius = 800.f;
	const float stopRadius = 300.f;
	SteeringOutput Steering{};
	Steering.LinearVelocity = Target.Position - Agent.GetPosition();
	
	float targetDistance =Steering.LinearVelocity.Length();
	float speed = 0.f;
	if (targetDistance>stopRadius)
	{
		speed = std::clamp(targetDistance,0.f,breakRadius)/breakRadius * m_MaxSpeed;
	}
	Agent.SetMaxLinearSpeed(speed);
	
	return Steering;
}

SteeringOutput Face::CalculateSteering(float DeltaT, ASteeringAgent& Agent)
{
	constexpr float stopAngleDegrees = 0.5f;
	constexpr float stopAngleRadiance = FMath::DegreesToRadians(stopAngleDegrees);
	SteeringOutput Steering{};
	Steering.AngularVelocity = 0.f;
	
	FVector2D targetVector{Target.Position - Agent.GetPosition()};
	
	float desiredRotation = FMath::Atan2(targetVector.Y, targetVector.X);
	float currentRotation = FMath::DegreesToRadians(Agent.GetActorRotation().Yaw);
	
	float deltaRotation = FMath::FindDeltaAngleRadians(currentRotation, desiredRotation);
	
	if (FMath::Abs(deltaRotation)<stopAngleRadiance) return Steering;

	Steering.AngularVelocity = std::clamp(deltaRotation, -Agent.GetMaxAngularSpeed(), Agent.GetMaxAngularSpeed());

	return Steering;
	
	
	// SteeringOutput Steering{};
	// Steering.LinearVelocity = Target.Position - Agent.GetPosition();
	//
	// Agent.SetMaxLinearSpeed(0.f);
	// return Steering;
}

SteeringOutput Pursuit::CalculateSteering(float DeltaT, ASteeringAgent& Agent)
{
	SteeringOutput Steering{};
	
	FVector2D targetPosition = Target.Position;
	FVector2D targetLinearVelocity = Target.LinearVelocity;
	
	FVector2D targetPositionPredict = Target.Position + Target.LinearVelocity * DeltaT;
	
	Steering.LinearVelocity = targetPositionPredict - Agent.GetPosition();
	
	
	return Steering;
}

SteeringOutput Evade::CalculateSteering(float DeltaT, ASteeringAgent& Agent)
{
	SteeringOutput Steering{};
	
	FVector2D targetPosition = Target.Position;
	FVector2D targetLinearVelocity = Target.LinearVelocity;
	
	FVector2D targetPositionPredict = Target.Position + Target.LinearVelocity * DeltaT;
	
	Steering.LinearVelocity = Agent.GetPosition() - targetPositionPredict;
	
	
	return Steering;
}
