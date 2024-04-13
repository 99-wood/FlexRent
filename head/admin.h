#ifndef _ADMIN
#define _ADMIN
#include "typedefine.h"
struct Admin{
    char * password;
};
void resetAdmin(struct Admin * admin);
#endif