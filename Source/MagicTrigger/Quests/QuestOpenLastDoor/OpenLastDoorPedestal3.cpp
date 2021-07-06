// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "OpenLastDoorPedestal3.h"



AOpenLastDoorPedestal3::AOpenLastDoorPedestal3()
{
	CountOfSpheres = 3;
	CurrentEmissive = TotalEmissive / CountOfSpheres;
	MaxEmissive = CurrentEmissive;

	//Visible
	Sphere1->SetVisibility(true);
	Sphere1->SetHiddenInGame(false);

	Sphere2->SetVisibility(false);
	Sphere2->SetHiddenInGame(true);

	Sphere3->SetVisibility(false);
	Sphere3->SetHiddenInGame(true);

	//Visible
	Sphere4->SetVisibility(true);
	Sphere4->SetHiddenInGame(false);

	Sphere5->SetVisibility(false);
	Sphere5->SetHiddenInGame(true);

	Sphere6->SetVisibility(false);
	Sphere6->SetHiddenInGame(true);

	//Visible
	Sphere7->SetVisibility(true);
	Sphere7->SetHiddenInGame(false);
}
