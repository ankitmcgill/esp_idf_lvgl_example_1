// DEFINES -TYPES
// SEPTEMBER 9, 2025

#ifndef _DEFINES_COMMON_DATA_TYPES_
#define _DEFINES_COMMON_DATA_TYPES_

#define BIT_VALUE(x)    (1 << x)

typedef enum
{
    COMPONENT_TYPE_NON_TASK = 0,
    COMPONENT_TYPE_TASK
}component_type_t;

#endif