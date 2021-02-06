/**
 * https://gitlab.com/district0/unreal-engine-4-snippets/snippets/1832992 
 Interface implementation check for Unreal Engine 4 (UE4)
In UE4 checking that object implement interface are complicated.

So we developed clear and fast way to check them.
 */

#pragma once

#include "UObject/Interface.h"

 /**
 * Fast and full checking of interface implementation including nullptr check, C++ cast check and blueprint check
 * @param TIInterfaceType is interface IClass (not UClass)
 * @param object          is pointer to check
 * @return                true if object implements TIInterfaceType, false if nullptr or doesn't implement
 */
template<typename TIInterfaceType>
FORCEINLINE bool IsInterfaceImplementedBy(const UObject* const object)
{
	return
		// Nullptr is invalid
		object &&
		// C++-style cast much faster
		(Cast<TIInterfaceType>(object) ||
			// But blueprint implementation pass only this check
			object->GetClass()->ImplementsInterface(TIInterfaceType::UClassType::StaticClass()));
}
