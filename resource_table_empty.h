#pragma once

#include <stddef.h>
#include <rsc_types.h>

struct my_resource_table {
    struct resource_table base;

    uint32_t offset[1]; /* Should match 'num' in actual definition */
};

#pragma DATA_SECTION(".resource_table")
#pragma RETAIN
struct my_resource_table pru_remoteproc_ResourceTable = {
        1,    /* we're the first version that implements this */
        0,    /* number of entries in the table */
        0, 0,    /* reserved, must be zero */
        0,    /* offset[0] */
};
