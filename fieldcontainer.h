#ifndef FIELDCONTAINER_H
#define FIELDCONTAINER_H
#include "field.h"

class FieldContainer
{   
public:
    FieldContainer();
    Field* field = nullptr;
    FieldContainer* next = nullptr;
};

#endif // FIELDCONTAINER_H
