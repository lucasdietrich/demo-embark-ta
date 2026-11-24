#ifndef MYTA_H
#define MYTA_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Client library of the myta Trusted Application: wraps the
 * OP-TEE client API (libteec) to talk to the TA.
 */

/* MYTA_SUCCESS on success, otherwise a TEEC_Result error code */
typedef uint32_t myta_result_t;
#define MYTA_SUCCESS 0u

/* Connection to the TA */
typedef struct myta myta_t;

/* Connect to the TEE and open a session on the TA */
myta_result_t myta_open(myta_t **handle);

/* Close the session and the connection, `handle` can be NULL */
void myta_close(myta_t *handle);

/* Ask the TA to increment `*value` */
myta_result_t myta_inc_value(myta_t *handle, uint32_t *value);

#ifdef __cplusplus
}
#endif

#endif /* MYTA_H */
