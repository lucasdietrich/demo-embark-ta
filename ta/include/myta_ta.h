#ifndef TA_MYTA_H
#define TA_MYTA_H

/*
 * UUID of the Trusted Application, shared by the TA and its clients.
 * It must match the BINARY UUID of ta/Makefile, which names the signed
 * binary (c081257b-243b-581e-8cc2-a3895ee16564.ta).
 */
#define TA_MYTA_UUID \
	{ 0xc081257b, 0x243b, 0x581e, { 0x8c, 0xc2, 0xa3, 0x89, 0x5e, 0xe1, 0x65, 0x64 } }

/* Command of the TA: increment params[0].value.a */
#define TA_MYTA_CMD_INC_VALUE		0

#endif /* TA_MYTA_H */
