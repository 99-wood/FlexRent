#include "head.h"
#include "core.h"
int main(){
    initSystem();
    addPlace("liaonin", "root");
    addPlace("beijing", "root");
    addPlace("shenyang", "liaonin");
    addPlace("hunnan", "shenyang");
    addPlace("11", "niumo");
    printPlaceTree(&placeRoot, 0);
    struct House* house = addHouse("fw", "123", "hunnan", "No195", 100, 2);
    delHouse(house);
    // printHouse(house);

}