/*
 * The name of this file must not be modified: it is included by the TA dev
 * kit to build the TA header.
 */

#ifndef USER_TA_HEADER_DEFINES_H
#define USER_TA_HEADER_DEFINES_H

/* To get the TA UUID definition */
#include <myta_ta.h>

#define TA_UUID				TA_MYTA_UUID

/* TA properties */
#define TA_FLAGS			0

/* Provisioned stack size */
#define TA_STACK_SIZE			2048

/* Provisioned heap size for TEE_Malloc() and friends */
#define TA_DATA_SIZE			32768

/* The gpd.ta.version property */
#define TA_VERSION			"0.1.0"

/* The gpd.ta.description property */
#define TA_DESCRIPTION			"myta Trusted Application"

#endif /* USER_TA_HEADER_DEFINES_H */
