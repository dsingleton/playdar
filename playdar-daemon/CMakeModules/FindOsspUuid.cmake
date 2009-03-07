# Created by Max Howell

FIND_LIBRARY (OSSPUUID_LIBRARIES NAMES ossp-uuid uuid)
FIND_PATH (OSSPUUID_INCLUDE_DIR NAMES ossp/uuid.h uuid.h)

# the source install doesn't prefix with an ossp folder, everyone with sense, does.
FIND_FILE (HAS_OSSP_NAMESPACE_FOLDER ossp/uuid.h)
IF (HAS_OSSP_NAMESPACE_FOLDER)
    ADD_DEFINITIONS( -DHAS_OSSP_UUID_H )
ENDIF (HAS_OSSP_NAMESPACE_FOLDER)

INCLUDE (FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(OsspUuid DEFAULT_MSG OSSPUUID_LIBRARIES OSSPUUID_INCLUDE_DIR)

IF (OSSPUUID_FOUND)
   INCLUDE (CheckLibraryExists)
   CHECK_LIBRARY_EXISTS (${OSSPUUID_LIBRARIES} uuid_create "" OSSPUUID_NEED_PREFIX)
ENDIF (OSSPUUID_FOUND)

MARK_AS_ADVANCED (OSSPUUID_INCLUDE_DIR OSSPUUID_LIBRARIES)
