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

#include "ompi/mpit/mpit-internal.h"

static const char FUNC_NAME[] = "MPI_T_pvar_handle_free";

int MPI_T_pvar_handle_free(MPI_T_pvar_session session, MPI_T_pvar_handle *handle)
{
    int ret = MPI_SUCCESS;

    if (!mpit_is_initialized ()) {
        return MPI_T_ERR_NOT_INITIALIZED;
    }

    mpit_lock ();

    do {
        /* Check that this is a valid handle */
        if (MPI_T_PVAR_HANDLE_NULL == *handle ||
            MPI_T_PVAR_ALL_HANDLES == *handle) {
            /* As of MPI 3.0 MPI_T_PVAR_ALL_HANDLES is not a valid handle for
               MPI_T_pvar_handle_free */
            ret = MPI_T_ERR_INVALID_HANDLE;
            break;
        }

        ret = mca_base_pvar_handle_free (*handle);
        if (OPAL_SUCCESS != ret) {
            ret = MPI_ERR_UNKNOWN;
        }

        *handle = MPI_T_PVAR_HANDLE_NULL;
    } while (0);

    mpit_unlock ();

    return ret;
}
