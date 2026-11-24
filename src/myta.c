#include <stdlib.h>
#include <string.h>

#include <myta.h>

/* OP-TEE TEE client API (libteec) */
#include <tee_client_api.h>

/* For the UUID and the commands of the TA */
#include <myta_ta.h>

struct myta {
    TEEC_Context ctx;
    TEEC_Session sess;
};

myta_result_t myta_open(myta_t **handle)
{
    TEEC_UUID uuid = TA_MYTA_UUID;
    uint32_t err_origin;
    myta_t *h;
    TEEC_Result res;

    if (handle == NULL) {
        return TEEC_ERROR_BAD_PARAMETERS;
    }

    h = calloc(1, sizeof(*h));
    if (h == NULL) {
        return TEEC_ERROR_OUT_OF_MEMORY;
    }

    res = TEEC_InitializeContext(NULL, &h->ctx);
    if (res != TEEC_SUCCESS) {
        free(h);
        return res;
    }

    res = TEEC_OpenSession(
        &h->ctx, &h->sess, &uuid, TEEC_LOGIN_PUBLIC, NULL, NULL, &err_origin);
    if (res != TEEC_SUCCESS) {
        TEEC_FinalizeContext(&h->ctx);
        free(h);
        return res;
    }

    *handle = h;
    return MYTA_SUCCESS;
}

void myta_close(myta_t *handle)
{
    if (handle == NULL) {
        return;
    }

    TEEC_CloseSession(&handle->sess);
    TEEC_FinalizeContext(&handle->ctx);
    free(handle);
}

myta_result_t myta_inc_value(myta_t *handle, uint32_t *value)
{
    TEEC_Operation op;
    uint32_t err_origin;
    TEEC_Result res;

    if (handle == NULL || value == NULL) {
        return TEEC_ERROR_BAD_PARAMETERS;
    }

    memset(&op, 0, sizeof(op));
    op.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);
    op.params[0].value.a = *value;

    res = TEEC_InvokeCommand(&handle->sess, TA_MYTA_CMD_INC_VALUE, &op, &err_origin);
    if (res == TEEC_SUCCESS) {
        *value = op.params[0].value.a;
    }

    return res;
}
