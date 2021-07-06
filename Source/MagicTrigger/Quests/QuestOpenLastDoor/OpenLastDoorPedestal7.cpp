// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "OpenLastDoorPedestal7.h"



AOpenLastDoorPedestal7::AOpenLastDoorPedestal7()
{
	CountOfSpheres = 7;
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

	//Visible
	Sphere7->SetVisibility(true);
	Sphere7->SetHiddenInGame(false);
}
