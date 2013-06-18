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

static const char FUNC_NAME[] = "MPI_T_cvar_get_info";

int MPI_T_cvar_get_info(int cvar_index, char *name, int *name_len, int *verbosity,
			MPI_Datatype *datatype, MPI_T_enum *enumtype, char *desc,
			int *desc_len, int *bind, int *scope)
{
    const mca_base_var_t *var;
    int rc = MPI_SUCCESS;

    if (!mpit_is_initialized ()) {
        return MPI_T_ERR_NOT_INITIALIZED;
    }

    mpit_lock ();

    do {
        rc = mca_base_var_get (cvar_index, &var);
        if (OPAL_SUCCESS != rc) {
            rc = (OPAL_ERR_VALUE_OUT_OF_BOUNDS == rc) ? MPI_T_ERR_INVALID_INDEX :
                MPI_ERR_OTHER;
            break;
        }

        mpit_copy_string (name, name_len, var->mbv_full_name);
        mpit_copy_string (desc, desc_len, var->mbv_description);

        /* find the corresponding mpi type for an mca type */
        rc = ompit_var_type_to_datatype (var->mbv_type, datatype);
        if (OMPI_SUCCESS != rc) {
            break;
        }

        if (NULL != enumtype) {
            *enumtype = var->mbv_enumerator ? (MPI_T_enum) var->mbv_enumerator : MPI_T_ENUM_NULL;
        }

        if (NULL != scope) {
            *scope = var->mbv_scope;
        }

        /* XXX -- TODO -- All bindings are currently 0. Add support for variable binding. */
        if (NULL != bind) {
            *bind = var->mbv_bind;
        }
    } while (0);

    mpit_unlock ();

    return rc;
}
