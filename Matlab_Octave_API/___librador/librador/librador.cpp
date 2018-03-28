#include "librador.h"
#include "librador_internal.h"

Librador::Librador()
{
}

int librador_init(){
    if(internal_librador_object != NULL){
        //Object already initialised
        return 1;
    }

    internal_librador_object = new Librador();
    if(internal_librador_object == NULL){
        //Object initialisation failed
        return -1;
    } else {
        //good, fresh initialisation
        return 0;
    }
}

int librador_exit(){
    if(internal_librador_object == NULL){
        //Object not yet initialised
        return 1;
    }

    delete internal_librador_object;
    internal_librador_object = NULL;
    //Object deleted
    return 0;
}
