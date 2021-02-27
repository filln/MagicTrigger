/**
 * Макрос для вывода служебного сообщения об ошибках и пр.
 */

#pragma once

#include "Engine/GameEngine.h"

#define CUR_CLASS_FUNC (FString(__FUNCTION__))
#define CUR_LINE  (FString::FromInt(__LINE__))
#define DEBUGMESSAGE(x) UE_LOG(LogTemp, Warning, TEXT("%s <<%s>> ---> %s"), *CUR_CLASS_FUNC, *CUR_LINE, *FString(TEXT(x))); if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, *(CUR_CLASS_FUNC + " <<" + CUR_LINE + ">> " + "---> " + x));}

//#define DEBUGMESSAGE(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, *(CUR_CLASS_FUNC + " <<" + CUR_LINE + ">> " + "---> " + x));}
//#define DEBUGMESSAGE(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT(x));}

 /**
  * #define DEBUGMESSAGE(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT(x), __VA_ARGS__));}
  */

 /*
 https://nerivec.github.io/old-ue4-wiki/pages/logs-printing-class-name-function-name-line-number-of-your-calling-code.html
 https://nerivec.github.io/old-ue4-wiki/pages/logs-printing-messages-to-yourself-during-runtime.html
 https://forums.unrealengine.com/development-discussion/c-gameplay-programming/27976-new-wiki-how-to-get-a-ue4-fstring-of-calling-class-function-and-line-number-rama
 https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros?redirectedfrom=MSDN&view=msvc-160
	Joy String 
		Current Class, File, and Line Number!
			by Rama
			
	PreProcessor commands to get 
		a. Class name
		b. Function Name
		c. Line number 
		d. Function Signature (including parameters)
		
	Gives you a UE4 FString anywhere in your code that these macros are used!
	
	Ex: 
		You can use JOYSTR_CUR_CLASS anywhere to get a UE4 FString back telling you 
		what the current class is where you called this macro!
	
	Ex:
		This macro prints the class and line along with the message of your choosing!
		VSCREENMSG("Have fun today!");
	<3  Rama
*/
/*
#pragma once

//Current Class Name + Function Name where this is called!
#define JOYSTR_CUR_CLASS_FUNC (FString(__FUNCTION__))

//Current Class where this is called!
#define JOYSTR_CUR_CLASS (FString(__FUNCTION__).Left(FString(__FUNCTION__).Find(TEXT(":"))) )

//Current Function Name where this is called!
#define JOYSTR_CUR_FUNC (FString(__FUNCTION__).Right(FString(__FUNCTION__).Len() - FString(__FUNCTION__).Find(TEXT("::")) - 2 ))

//Current Line Number in the code where this is called!
#define JOYSTR_CUR_LINE  (FString::FromInt(__LINE__))

//Current Class and Line Number where this is called!
#define JOYSTR_CUR_CLASS_LINE (JOYSTR_CUR_CLASS + "(" + JOYSTR_CUR_LINE + ")")

//Current Function Signature where this is called!
#define JOYSTR_CUR_FUNCSIG (FString(__FUNCSIG__))


//Victory Screen Message
// 	Gives you the Class name and exact line number where you print a message to yourself!
#define VSCREENMSG(Param1) (GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *(JOYSTR_CUR_CLASS_LINE + ": " + Param1)) )

#define VSCREENMSG2(Param1,Param2) (GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *(JOYSTR_CUR_CLASS_LINE + ": " + Param1 + " " + Param2)) )

#define VSCREENMSGF(Param1,Param2) (GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *(JOYSTR_CUR_CLASS_LINE + ": " + Param1 + " " + FString::SanitizeFloat(Param2))) )

//UE LOG!
#define V_LOG(LogCat, Param1) 		UE_LOG(LogCat,Warning,TEXT("%s: %s"), *JOYSTR_CUR_CLASS_LINE, *FString(Param1))

#define V_LOG2(LogCat, Param1,Param2) 	UE_LOG(LogCat,Warning,TEXT("%s: %s %s"), *JOYSTR_CUR_CLASS_LINE, *FString(Param1),*FString(Param2))

#define V_LOGF(LogCat, Param1,Param2) 	UE_LOG(LogCat,Warning,TEXT("%s: %s %f"), *JOYSTR_CUR_CLASS_LINE, *FString(Param1),Param2)

#define V_LOGM(LogCat, FormatString , ...) UE_LOG(LogCat,Warning,TEXT("%s: %s"), 	*JOYSTR_CUR_CLASS_LINE, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__ ) )

 */