/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) 2012-2013 Los Alamos National Security, LLC. All rights
 *                         reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 */

#include "ompi/mpi/tool/mpit-internal.h"

opal_mutex_t mpit_big_lock;

volatile uint32_t mpit_init_count = 0;
volatile int32_t initted = 0;

void mpit_lock (void)
{
    if (initted) {
        opal_mutex_lock (&mpit_big_lock);
    }
}

void mpit_unlock (void)
{
    if (initted) {
        opal_mutex_unlock (&mpit_big_lock);
    }
}

int ompit_var_type_to_datatype (mca_base_var_type_t type, MPI_Datatype *datatype)
{
    switch (type) {
    case MCA_BASE_VAR_TYPE_INT:
        *datatype = MPI_INT;
        break;
    case MCA_BASE_VAR_TYPE_UNSIGNED_INT:
        *datatype = MPI_UNSIGNED;
        break;
    case MCA_BASE_VAR_TYPE_UNSIGNED_LONG:
        *datatype = MPI_UNSIGNED_LONG;
        break;
    case MCA_BASE_VAR_TYPE_UNSIGNED_LONG_LONG:
        *datatype = MPI_UNSIGNED_LONG_LONG;
        break;
    case MCA_BASE_VAR_TYPE_SIZE_T:
        if (sizeof (size_t) == sizeof (unsigned)) {
            *datatype = MPI_UNSIGNED;
        } else if (sizeof (size_t) == sizeof (unsigned long)) {
            *datatype = MPI_UNSIGNED_LONG;
        } else if (sizeof (size_t) == sizeof (unsigned long long)) {
            *datatype = MPI_UNSIGNED_LONG_LONG;
        } else {
            /* not supported -- fixme */
            assert (0);
        }

        break;
    case MCA_BASE_VAR_TYPE_STRING:
        *datatype = MPI_CHAR;
        break;
    case MCA_BASE_VAR_TYPE_BOOL:
        if (sizeof (bool) == sizeof (char)) {
            *datatype = MPI_CHAR;
        } else if (sizeof (bool) == sizeof (int)) {
            *datatype = MPI_INT;
        } else {
            /* not supported -- fixme */
            assert (0);
        }
        break;
    case MCA_BASE_VAR_TYPE_DOUBLE:
        *datatype = MPI_DOUBLE;
        break;
    default:
        /* not supported -- fixme */
        assert (0);
        break;
    }

    return OMPI_SUCCESS;
}
