#include <tee_internal_api.h>
#include <tee_internal_api_extensions.h>

#include <myta_ta.h>

/* Called when the instance of the TA is created, first call in the TA */
TEE_Result TA_CreateEntryPoint(void)
{
	return TEE_SUCCESS;
}

/* Called when the instance of the TA is destroyed, last call in the TA */
void TA_DestroyEntryPoint(void)
{
}

/*
 * Called when a new session is opened to the TA. *sess_ctx can be set to
 * identify this session in the subsequent calls.
 */
TEE_Result TA_OpenSessionEntryPoint(uint32_t __unused param_types,
				    TEE_Param __unused params[4],
				    void __unused **sess_ctx)
{
	IMSG("Hello from myta!");

	/* If return value != TEE_SUCCESS the session will not be created. */
	return TEE_SUCCESS;
}

/* Called when a session is closed */
void TA_CloseSessionEntryPoint(void __unused *sess_ctx)
{
	IMSG("Goodbye from myta!");
}

static TEE_Result inc_value(uint32_t param_types, TEE_Param params[4])
{
	uint32_t exp_param_types = TEE_PARAM_TYPES(TEE_PARAM_TYPE_VALUE_INOUT,
						   TEE_PARAM_TYPE_NONE,
						   TEE_PARAM_TYPE_NONE,
						   TEE_PARAM_TYPE_NONE);

	if (param_types != exp_param_types)
		return TEE_ERROR_BAD_PARAMETERS;

	IMSG("Got value: %u from NW", params[0].value.a);
	params[0].value.a++;
	IMSG("Increase value to: %u", params[0].value.a);

	return TEE_SUCCESS;
}

/*
 * Called when a TA is invoked. The command ID and the parameters come from
 * the normal world.
 */
TEE_Result TA_InvokeCommandEntryPoint(void __unused *sess_ctx,
				      uint32_t cmd_id, uint32_t param_types,
				      TEE_Param params[4])
{
	switch (cmd_id) {
	case TA_MYTA_CMD_INC_VALUE:
		return inc_value(param_types, params);
	default:
		return TEE_ERROR_BAD_PARAMETERS;
	}
}
