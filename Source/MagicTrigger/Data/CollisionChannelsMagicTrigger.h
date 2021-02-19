// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Определение внутренних названий каналов коллизий.
 */

 /**
  *  +DefaultChannelResponses=(Channel=ECC_GameTraceChannel1,DefaultResponse=ECR_Overlap,bTraceType=False,bStaticObject=False,Name="ThrowableObject")
	 +DefaultChannelResponses=(Channel=ECC_GameTraceChannel2,DefaultResponse=ECR_Ignore,bTraceType=True,bStaticObject=False,Name="Attack")
	 +DefaultChannelResponses=(Channel=ECC_GameTraceChannel3,DefaultResponse=ECR_Overlap,bTraceType=False,bStaticObject=False,Name="AttackAbility")
	 +DefaultChannelResponses=(Channel=ECC_GameTraceChannel4,DefaultResponse=ECR_Ignore,bTraceType=False,bStaticObject=False,Name="Observe")
	 +DefaultChannelResponses=(Channel=ECC_GameTraceChannel5,DefaultResponse=ECR_Overlap,bTraceType=False,bStaticObject=False,Name="InteractNPC")
	 +DefaultChannelResponses=(Channel=ECC_GameTraceChannel6,DefaultResponse=ECR_Overlap,bTraceType=False,bStaticObject=False,Name="InteractPlayerCharacter")
  */

#pragma once

//Trace channel
#define ECC_Attack ECC_GameTraceChannel2

//Collision channel
#define ECC_ThrowableObject             ECC_GameTraceChannel1

//Collision channel
#define ECC_AttackAbility               ECC_GameTraceChannel3

//Collision channel
#define ECC_Observe                     ECC_GameTraceChannel4

//Collision channel
#define ECC_InteractNPC                 ECC_GameTraceChannel5

//Collision channel
#define ECC_InteractPlayerCharacter     ECC_GameTraceChannel6