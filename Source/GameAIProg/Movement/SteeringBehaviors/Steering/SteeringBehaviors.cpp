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
	// SteeringOutput Steering{};
	// FVector2D TargetVector{Target.Position - Agent.GetPosition()};
	// TargetVector.Normalize();
	// FVector2D ActorRightVector{Agent.GetActorRightVector().X,Agent.GetActorRightVector().Y};
	// ActorRightVector.Normalize();
	//
	// float angularRotation = FVector2D::DotProduct(TargetVector,ActorRightVector);
	//
	// float steering = std::clamp(angularRotation, -1.0f, 1.0f);
	// Steering.AngularVelocity = steering * Agent.GetMaxAngularSpeed();
	// return Steering;
	
	SteeringOutput Steering{};
	Steering.LinearVelocity = Target.Position - Agent.GetPosition();
	
	Agent.SetMaxLinearSpeed(0.f);
	return Steering;
}
