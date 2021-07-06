// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "OpenLastDoorPedestal5.h"


AOpenLastDoorPedestal5::AOpenLastDoorPedestal5()
{
	CountOfSpheres = 5;
	CurrentEmissive = TotalEmissive / CountOfSpheres;
	MaxEmissive = CurrentEmissive;

	Sphere1->SetVisibility(false);
	Sphere1->SetHiddenInGame(true);

	//Visible
	Sphere2->SetVisibility(true);
	Sphere2->SetHiddenInGame(false);

	//Visible
	Sphere3->SetVisibility(true);
	Sphere3->SetHiddenInGame(false);

	Sphere4->SetVisibility(false);
	Sphere4->SetHiddenInGame(true);

	//Visible
	Sphere5->SetVisibility(true);
	Sphere5->SetHiddenInGame(false);

	//Visible
	Sphere6->SetVisibility(true);
	Sphere6->SetHiddenInGame(false);

	//Visible
	Sphere7->SetVisibility(true);
	Sphere7->SetHiddenInGame(false);
}
