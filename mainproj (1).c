#include <stdio.h>
#include<ctype.h>
#include <stdlib.h>

#include <string.h>


#include "prj2_2018.h"
#include "prj1_2018.h"
struct planeData * zzradarPrint(struct planeData*head);
void print_main_menu();

int main()

{	
	char X='Q';
	int list_size;
	char buffer[100];
	struct planeData *listptr,  *pL;
	short flight_to_be_gone, code;
	
	printf("Enter a seed to the random number generator (i.e. an integer >0)\n");
	gets(buffer);

	srand(atoi(buffer));

	printf("\n\n>>>>> Enter a value >0\n");
	gets(buffer);
	list_size=atoi(buffer);
	if(list_size <=0)
		return printf("terminating ..........\n");

  
	listptr= list_intialize( list_size);

    while((X!='T') && (listptr!=NULL ))
	{
		
		print_main_menu();
		printf(">>>>> Enter a command ");

	
		X=getchar();
		fflush(stdin);
		X=toupper(X);
	
		switch(X)
	
		{
	

	
		case 'A':
//		Add Plane to list
			listptr=addPlane (listptr);
			break;

	
		case 'D':
//		Delete Plane from list
			
			displayPlaneList (listptr);
			printf(">>>>> Choose an Flight Code\n");
			flight_to_be_gone= (short) atoi(gets(buffer));
			pL= checkForPlane(listptr, flight_to_be_gone);
			if(pL!=NULL)
				listptr=deletePlane(listptr,pL);
			else
				printf("there is no plane with flight code %hd\n",code);
			break;

		case 'M':
//		Process Plane movement
			listptr=processPlaneMove (listptr);
			break;

	
		case 'P':
//		Display list
			displayPlaneList (listptr);
			break;

		case 'Q':
//		Re-sort by distance
//completed by BK
			listptr=sortByDist(listptr);
			break;

		case 'R':
//		Radar display by distance
//completed by BK
			listptr=radarPrint(listptr);
			//struct planeData * xxradarPrint(struct planeData*head)
			break;

		case 'S':
//		Sort by flight code
			listptr=sortByCode (listptr);
			break;

	
		case 'T':
//		Terminate
			terminateAndWrite (listptr);
		
			break;

		case 'V':
//		Reset Direction
			
			displayPlaneList(listptr);
			printf(">>>>> Choose a Flight Code \n");
			code= (short) atoi(gets(buffer));
			pL= checkForPlane(listptr,code);
			if(pL!=NULL)
				resetPlaneDirection( pL);
			else
				printf("there is no plane with flight code $hd\n",code);


			break;

	
	
		}
    
	}


	return 1;

}


void print_main_menu()
{
	printf("*******************************************************\n");
	printf("*******************************************************\n");
	printf("                Main Menu\n");
	printf("*******************************************************\n");
	printf("\tA\t\tadd Plane to list\n");
	printf("\tD\t\tdelete Plane from list\n");
	printf("\tM\t\tMove  planes in list\n");
	printf("\tP\t\tdisplay Plane List\n");
	printf("\tQ\t\tsort list by Distance\n");
	printf("\tR\t\tPrint the radar representation of the plane list\n");
	printf("\tS\t\tsort list By flight Code\n");
	printf("\tT\t\tterminate.. Write data to file and free list \n");
	printf("\tV\t\treset a Plane’s flight pattern\n");
	printf("*******************************************************\n");
	printf("*******************************************************\n");

}


