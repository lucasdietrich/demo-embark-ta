#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <myta.h>

int main(int argc, char *argv[])
{
	myta_t *handle = NULL;
	uint32_t value = 42;
	myta_result_t res;

	if (argc > 1) {
		value = (uint32_t)strtoul(argv[1], NULL, 0);
	}

	res = myta_open(&handle);
	if (res != MYTA_SUCCESS) {
		fprintf(stderr, "myta_open failed with code 0x%x\n", res);
		return 1;
	}

	printf("Invoking TA to increment %u\n", value);
	res = myta_inc_value(handle, &value);
	if (res == MYTA_SUCCESS) {
		printf("TA incremented value to %u\n", value);
	} else {
		fprintf(stderr, "TA command failed with code 0x%x\n", res);
	}

	myta_close(handle);

	return res == MYTA_SUCCESS ? 0 : 1;
}
