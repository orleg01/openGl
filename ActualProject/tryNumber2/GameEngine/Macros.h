#ifndef __MACROS__H
#define __MACROS__H

//find the element and remove it
#define REMOVE_FROM_VECTOR_BY_ELEMENT(VEC , VAL) VEC.erase(find(VEC.begin() , VEC.end() , VAL))

#define REMOVE_FROM_VECTOR_BY_INDEX(VEC , INDEX) VEC.erase(VEC.begin() + INDEX)

#endif