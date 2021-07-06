// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "OpenLastDoorPedestal6.h"



AOpenLastDoorPedestal6::AOpenLastDoorPedestal6()
{
	CountOfSpheres = 6;
	CurrentEmissive = TotalEmissive / CountOfSpheres;
	MaxEmissive = CurrentEmissive;

	//Visible
	Sphere1->SetVisibility(true);
	Sphere1->SetHiddenInGame(false);

	//Visible
	Sphere2->SetVisibility(true);
	Sphere2->SetHiddenInGame(false);

	//Visible
	Sphere3->SetVisibility(true);
	Sphere3->SetHiddenInGame(false);
	
	//Visible
	Sphere4->SetVisibility(true);
	Sphere4->SetHiddenInGame(false);

	//Visible
	Sphere5->SetVisibility(true);
	Sphere5->SetHiddenInGame(false);

	//Visible
	Sphere6->SetVisibility(true);
	Sphere6->SetHiddenInGame(false);

	Sphere7->SetVisibility(false);
	Sphere7->SetHiddenInGame(true);
}
