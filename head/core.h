#ifndef _CORE
#define _CORE
#include "typedefine.h"
#include "head.h"
/*init*/
void initSystem(){
    initVoidTreap(&rentHouseMsg);
    initVoidTreap(&viewHouseMsg);
    initVoidTreap(&users);
    initVoidTreap(&middiums);
}
/*Admin*/
char* getAdminPassword(){
    return admin.password;
}
void setAdminPassword(char newPassword[]){
    free(admin.password);
    int len = strlen(newPassword);
    admin.password = (char*)malloc(sizeof(char) * (len + 1));
    for(int i = 0; i <= len; ++i){
        admin.password[i] = newPassword[i];
    }
    return;
}

/*place*/

int addPlace(char name[], char fatherName[]){
    Place *place, *father;
    father = 
}
#endif