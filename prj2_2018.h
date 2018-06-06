#include "prj1_2018.h"


struct planeData*  list_intialize( unsigned int);
struct planeData*  addPlane (struct planeData*);
struct planeData *processPlaneMove (struct planeData *);
void	displayPlaneList (struct planeData *);
struct planeData*  sortByCode (struct planeData*);
void terminateAndWrite (struct planeData*);
struct planeData* deletePlane(struct planeData*, struct planeData*);
struct planeData* checkForPlane(struct planeData*, short);
void resetPlaneDirection( struct planeData*);
