#include "place.h"
#include "house.h"
#include <stdlib.h>
#include "hash.h"

struct Place* newPlace2(char* n,enum depth l){
    struct Place* prt;
    prt=(struct Place*)malloc(sizeof(struct Place));
    prt->name=n;
    prt->level=l;
    prt->father=NULL;
    addVoidTreapNode(&placeTraep,prt,makeHashValue(n));
}

void addPlace(struct Place* prt,void* p){
    addVoidListHead(&(prt->sons),p);
    if(prt->level==community){
        ((struct House*)p)->father=prt;
    }else{
        ((struct Place*)p)->father=prt;
    }
}
