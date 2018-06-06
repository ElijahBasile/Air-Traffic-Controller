
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#ifndef _MY_DEF_
#define _MY_DEF_

enum dir {NE=0, EN, NW,WN,   SE,  ES, SW,WS };
enum loc {LNE=0,  LNW,LSE,LSW};
struct planeData{
	short flightCode;
	long xCord;
	long yCord;
	double distance;
	char direction;
	enum dir flightPattern;
	enum loc location;
	struct planeData *nextPlane;
};

#endif


struct planeData* sortByDist(struct planeData *);
struct planeData * radarPrint(struct planeData*head);
int checkPlane(struct planeData *);
int checkForCollision(struct planeData*);
void  setData(struct planeData *pLane);





