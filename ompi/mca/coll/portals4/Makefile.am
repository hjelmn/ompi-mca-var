#
# Copyright (c) 2013      Sandia National Laboratories. All rights reserved.
# $COPYRIGHT$
# 
# Additional copyrights may follow
# 
# $HEADER$
#

sources = \
        coll_portals4.h \
        coll_portals4_component.c

if MCA_BUILD_ompi_coll_portals4_DSO
component_noinst =
component_install = mca_coll_portals4.la
else
component_noinst = libmca_coll_portals4.la
component_install =
endif

mcacomponentdir = $(pkglibdir)
mcacomponent_LTLIBRARIES = $(component_install)
mca_coll_portals4_la_SOURCES = $(local_sources)
mca_coll_portals4_la_LIBADD = $(coll_portals4_LIBS)
mca_coll_portals4_la_LDFLAGS = -module -avoid-version $(coll_portals4_LDFLAGS)

noinst_LTLIBRARIES = $(component_noinst)
libmca_coll_portals4_la_SOURCES = $(local_sources)
libmca_coll_portals4_la_LIBADD = $(coll_portals4_LIBS)
libmca_coll_portals4_la_LDFLAGS = -module -avoid-version $(coll_portals4_LDFLAGS)
