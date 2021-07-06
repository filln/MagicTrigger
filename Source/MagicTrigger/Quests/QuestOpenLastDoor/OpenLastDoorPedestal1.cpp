// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "OpenLastDoorPedestal1.h"

AOpenLastDoorPedestal1::AOpenLastDoorPedestal1()
{
	CountOfSpheres = 1;
	CurrentEmissive = TotalEmissive / CountOfSpheres;
	MaxEmissive = CurrentEmissive;

	Sphere1->SetVisibility(false);
	Sphere1->SetHiddenInGame(true);

	Sphere2->SetVisibility(false);
	Sphere2->SetHiddenInGame(true);

	Sphere3->SetVisibility(false);
	Sphere3->SetHiddenInGame(true);

	Sphere4->SetVisibility(false);
	Sphere4->SetHiddenInGame(true);

	Sphere5->SetVisibility(false);
	Sphere5->SetHiddenInGame(true);

	Sphere6->SetVisibility(false);
	Sphere6->SetHiddenInGame(true);

	//Visible
	Sphere7->SetVisibility(true);
	Sphere7->SetHiddenInGame(false);
}
