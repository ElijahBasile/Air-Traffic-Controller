#include "prj2_2018.h"
#include <math.h>
const char *getFlightPattern(enum dir);
const char *getLocation(enum loc location);
//Purpose: to initialize the link list of planes
struct planeData*  list_intialize( unsigned int  num)
{
	//declaration of variables
	int i;
	struct planeData * head;
	struct planeData * newdata;
	struct planeData *temp, *ptr;

	//assigns initial 'box' of data to beginning of link list
	head = (struct planeData *)malloc(sizeof(struct planeData));
	//sets the data inside the link list
	setData(head);
	//assigns a value of NULL to pointer pointing to next item
	//in list. --> assigns the head to be the end
	head->nextPlane = NULL;
	//adds planes to the link list until value entered by user equals
	//number of planes added
	for (i = 1; i < num; i++)
	{
		newdata = (struct planeData *)malloc(sizeof(struct planeData));
		setData(newdata);
		newdata->nextPlane = NULL;

		newdata->nextPlane = head;
		head = newdata;
	}
	//sorts the link list by distance
	head = sortByDist(head);

	ptr = head;
	//performs the check plane function and determines head
	while (ptr != NULL) {
		if (checkPlane(ptr) == 1) {
			temp = ptr->nextPlane;
			head = deletePlane(head, ptr);
			ptr = temp;
		}
		else {
			//if plane collides with another plane, terminate the program
			//and write the plane data in the control log
			if (checkForCollision(head) == 1)
				terminateAndWrite(head);

			ptr = ptr->nextPlane;
		}
	}
	//returns beginning of link list

	return head;
}
//Purpose: to add a plane into the link list
struct planeData*  addPlane (struct planeData* P)
{
	//declaration of variables
	//sets head to initial beginning of link list
	struct planeData *head = P;
	struct planeData *newdata;

	//sets a memory location to the newdata structure
	//uses addplane-code
	newdata = (struct planeData *)malloc(sizeof(struct planeData));
	setData(newdata);
	newdata->nextPlane = NULL;

	newdata->nextPlane = head;
	head = newdata;
	//resorts entire link list based on distance
	head = sortByDist(head);
	//returns the beginning of link list
	return head;
}
//Purpose: to move the planes in the link list based on their
//flightpattern and direction
struct planeData *processPlaneMove (struct planeData *P)
{
	//declaration of variables
	struct planeData *ptr, *temp,*head;
	//sets the head and dynamic pointer to beginning of
	//link list
	head = P;
	ptr = P;
	//while ptr still lies in the link list, move each
	//plane within the list
	while (ptr != NULL) {
		//determines if direction is arriving or departing,
		//if departing, values point away from the origin,
		//if arriving, values point toward the origin

		//departing code
		if (ptr->direction == 'd') {
			switch (ptr->flightPattern) {
			case NE:
			case SE:
			case NW:
			case SW:
				ptr->xCord = ptr->xCord + 1;
				ptr->yCord = ptr->yCord + 2;
				break;
			case EN:
			case ES:
			case WN:
			case WS:
				ptr->xCord = ptr->xCord + 2;
				ptr->yCord = ptr->yCord + 1;
				break;
			}
		}
		//arriving code
		else {
			switch (ptr->flightPattern) {
			case NE:
			case SE:
			case NW:
			case SW:
				ptr->xCord = ptr->xCord - 1;
				ptr->yCord = ptr->yCord - 2;
				break;
			case EN:
			case ES:
			case WN:
			case WS:
				ptr->xCord = ptr->xCord - 2;
				ptr->yCord = ptr->yCord - 1;
				break;
			}
		}
		//recomputes the distance the plane is from the control center
		//based on the x and y Cords
		ptr->distance = sqrt(pow(ptr->xCord, 2) + pow(ptr->yCord, 2));
		//checks Plane (if node needs to be deleted)
		if (checkPlane(ptr) == 1) {
			temp = ptr->nextPlane;
			P = deletePlane(P, ptr);
			ptr = temp;
		}
		else {
			//if plane collides with another plane, terminate the program
			//and write the plane data in the control log
			if (checkForCollision(head) == 1)
				terminateAndWrite(head);

			ptr = ptr->nextPlane;
		}
	}
	//return beginning of link list
	return head;
}
//Purpose: to display the plane data in a list form
void	displayPlaneList (struct planeData *P)
{
	//sets the dynamic pointer to the beginning of the link list
	struct planeData * ptr = P;
	//displays the header for the each element of the plane
	printf("%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n", "Flight Code", "xCoordinate", "yCoordinate", "Distance", "Direction", "Flight Pattern", "Location");
	//while ptr is still in the link list, display the plane data
	while (ptr != NULL)
	{
		printf("%-15hd%-15ld%-15ld%-15.4lf%-15c%-15s%-15s\n", ptr->flightCode, ptr->xCord, ptr->yCord, ptr->distance, ptr->direction, getFlightPattern(ptr->flightPattern), getLocation(ptr->location));

		ptr = ptr->nextPlane;
	}


}
//Purpose: to sort the plane data by the flight code (in descending order)
struct planeData*  sortByCode (struct planeData* P)
{
	//declaration of variables and pointers
	struct planeData *prev, *ptr, *head, *temp1;
	struct planeData *temp;
	int size=0,i,j, pass,x;
	//sets head and ptr to the beginning of the link list
	head = P;

	ptr = P;
	//finds the size of the link list
	while (ptr != NULL) {
		size++;
		ptr = ptr->nextPlane;
	}
	//sets the prev and ptr pointers to beginning of link list
	//and offsets ptr by one
	prev = ptr = P;
	ptr = ptr->nextPlane;
	//uses a form of bubble sort to sort the list by flightcode
	//and ensures that the list is fully sorted
	for (pass = 1; pass < size; pass++) {
		for (i=0;i<size;i++) {
			//the x acts as a form of a temporary flag which monitors if
			//had already been incremented as part of the swap
			x = 0;
			if (prev->flightCode < ptr->flightCode) {
				//if previous is not the head of the function
				if (prev != head) {
					//sets next value of prev to be next value for ptr
					prev->nextPlane = ptr->nextPlane;
					//sets next value of ptr to be prev
					ptr->nextPlane = prev;
					temp1 = head;
					//while temp1's next value isnt prev or ptr, move up by one,
					//this points to the structure before prev or ptr
					while (temp1->nextPlane != prev){
						temp1 = temp1->nextPlane;
					}
					//sets temp1's next value to be the first one that is next
					//after the swap
					if (temp1->nextPlane = prev)
						temp1->nextPlane = ptr;
					else
						temp1->nextPlane = prev;
					//increments both the prev and ptr pointers
					//prev does not change, ptr does
					ptr = ptr->nextPlane;
				}
				else {
					//sets the new head to be ptr
					//and the prev to be the next value
					temp1 = ptr -> nextPlane;
					head = ptr;
					head->nextPlane = prev;
					prev->nextPlane = temp1;
					//prev does not change, ptr does
					ptr = prev->nextPlane;
				}
			}
			//if the swap did not occur, increment normally
			else {
				prev = ptr;
				ptr = ptr->nextPlane;
			}
		}
		//reset the pointer values to the beginning of the link list (which
		//may not be changed due to the swapping)
		prev = ptr = head;
		//offset ptr by one
		ptr = ptr->nextPlane;
	}
	//return head
	return head;
}

//Purpose: to write all of the plane data to planeControlLog.txt
//and close the program
void terminateAndWrite (struct planeData*P)
{
	//declaration of variables
	struct planeData *ptr = P;
	struct planeData *tempptr;
	FILE *fp;
	int ch;

	//opens planeControlLog.txt for writing
	fp = fopen("planeControlLog.txt", "w");

	//while ptr is still in the link list, go through the data
	//in each structure and print is below and also label table created
	fprintf(fp,"%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n", "Flight Code", "xCoordinate", "yCoordinate", "Distance", "Direction", "Flight Pattern", "Location");
	while (ptr != NULL) {
		fprintf(fp,"%-15hd%-15ld%-15ld%-15.4lf%-15c%-15s%-15s\n", ptr->flightCode, ptr->xCord, ptr->yCord, ptr->distance, ptr->direction, getFlightPattern(ptr->flightPattern), getLocation(ptr->location));
		ptr = ptr->nextPlane;
	}
	//closes the file
fclose(fp);
//set ptr back at the beginning of the link list
ptr = P;
//frees each part of memory along link list
while (ptr != NULL) {
	tempptr = ptr->nextPlane;
	free(ptr);
	ptr = tempptr;
}

exit(0);

}

//constants that turn the enum value into name of enum
const char *getLocation(enum loc location) {
	switch (location) {
	case LNE: return "LNE";
	case LNW: return "LNW";
	case LSE: return "LSE";
	case LSW: return "LSW";
	}
	return "";
}

const char *getFlightPattern(enum dir pattern) {
	switch (pattern) {
	case NE: return "NE";
	case EN: return "EN";
	case NW: return "NW";
	case WN: return "WN";
	case SE: return "SE";
	case ES: return "ES";
	case SW: return "SW";
	case WS: return "WS";
	}
	return "";
}

//Purpose: to delete a specified plane given by the flight code
struct planeData* deletePlane(struct planeData* P, struct planeData*to_be_gone)
{
	//declaration of variables
	struct planeData *prev;
	struct planeData *ptr = P;
	struct planeData *head = P;

	//if the plane to be deleted is the head,
	//replaces head with next value and frees previous
	//memory of head
	if (to_be_gone == head) {
		ptr = ptr->nextPlane;
		free(to_be_gone);
		head = ptr;
	}
	else {
		//if the plane is not the head, finds the point in the
		//link list bridges around it, and frees memory
		while (ptr != to_be_gone) {
			prev = ptr;
			ptr = ptr->nextPlane;
		}
		prev->nextPlane = ptr->nextPlane;
		free(to_be_gone);
	}
	return head;
}
//Purpose: to check if there are any planes in the link list with the
//flight code in question
struct planeData* checkForPlane(struct planeData* P, short code)
{
	//decaration of variables
	struct planeData *ptr = P;
	//searches link list for a plane with the code entered
	//if found, returns pointer at plane
	while (ptr != NULL) {
		if (ptr->flightCode == code) {
			return ptr;
		}
		ptr = ptr->nextPlane;
	}
	//if no plane is found, returns a NULL value
	return NULL;
}
//Purpose: to reset the direction structure and flightpattern element in the plane
void resetPlaneDirection(struct planeData* pL)
{
	//sets ptr to pointer at plane to be modified
	struct planeData *ptr = pL;

	//reverses the direction
	if (ptr->direction == 'a') {
		ptr->direction = 'd';
	}
	else {
		ptr->direction = 'a';
	}
	//reverses the flightpattern
	switch (ptr->flightPattern) {
	case NE: 
		ptr->flightPattern = SW; 
		break;
	case EN: 
		ptr->flightPattern = WS; 
		break;
	case NW: 
		ptr->flightPattern = SE; 
		break;
	case WN: 
		ptr->flightPattern = ES; 
		break;
	case SE: 
		ptr->flightPattern = NW; 
		break;
	case ES: 
		ptr->flightPattern = WN; 
		break;
	case SW: 
		ptr->flightPattern = NE; 
		break;
	case WS: 
		ptr->flightPattern = EN; 
		break;
	}

}