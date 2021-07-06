// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "OpenLastDoorPedestal2.h"


AOpenLastDoorPedestal2::AOpenLastDoorPedestal2()
{
	CountOfSpheres = 2;
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

	Sphere7->SetVisibility(false);
	Sphere7->SetHiddenInGame(true);

}
