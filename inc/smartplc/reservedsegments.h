#ifndef _RESERVEDSEGMENTS_H_
#define _RESERVEDSEGMENTS_H_


/* network image */
#define PADT_SEG_NUM_NET_IMG            0

/* process image */
#define PADT_SEG_NUM_PI_IMG             1

/* error log */
#define PADT_SEG_NUM_ERRORLOG           2

/* native code help segment */
#define PADT_SEG_NUM_NCCHELP			3

/* segment with "0" contents */
#define PADT_SEG_NUM_STATIC_NULL        4

/* mapping of OEM varibles */
#define PADT_SEG_NUM_OEM_VAR_INFO		5

/* binary OPC segment */
#define PADT_SEG_NUM_BIN_OPC            6

/* binary DCF segment */
#define PADT_SEG_NUM_BIN_DCF            7

/* segment with "0" contents */
#define PADT_SEG_NUM_VARTAB             8

/* hardware configuration segment */
#define PADT_SEG_NUM_HARDWARE_CONFIG    9

/* mapping table for direct BYREF access */
#define PADT_SEG_NUM_DIRBYREF			10

/* IO Mapping table (OEM-specific) */
#define PADT_SEG_NUM_IOMAP1				11

/* IO Mapping table (OEM-specific) */
#define PADT_SEG_NUM_IOMAP2				12

/* IO (OEM-specific) */
#define PADT_SEG_NUM_IO2				13

/* ======== FROM HERE ON: P0699-specific segment numbers ======== */

/* hardware configuration segment */
#define PADT_SEG_NUM_HWCONFIG			14

/* rack-global shared memory variables segment */
#define PADT_SEG_NUM_SHMVARS			15

/* rack-global shared memory configuration segment (for data consistency) */
#define PADT_SEG_NUM_SHMCONFIG			16

/* -------- FROM HERE ON: segment numbers for data consistency buffers -------- */

/* first and last segment number used for data consistency buffers */
/* IMPORTANT that this matches the other definitions following below! */
/* these definitions are used by the BL code generator to distinguish between regular global variables and data consistency buffer variables! */
#define FIRST_SEG_NUM_DC_BUFFERS		17
#define LAST_SEG_NUM_DC_BUFFERS			29

/* data consistency buffer segments for all tasks (within one CPU) */
#define PADT_SEG_NUM_BUFFER_I1			17
#define PADT_SEG_NUM_BUFFER_I2			18
#define PADT_SEG_NUM_BUFFER_I3			19
#define PADT_SEG_NUM_BUFFER_I4			20
#define PADT_SEG_NUM_BUFFER_I5			21
#define PADT_SEG_NUM_BUFFER_I6			22
#define PADT_SEG_NUM_BUFFER_I7			23
#define PADT_SEG_NUM_BUFFER_I8			24
#define PADT_SEG_NUM_BUFFER_T1			25
#define PADT_SEG_NUM_BUFFER_T2			26
#define PADT_SEG_NUM_BUFFER_T3			27
#define PADT_SEG_NUM_BUFFER_T4			28
#define PADT_SEG_NUM_BUFFER_T5			29

/* first segment number used for data consistency buffers in the shared memory of the CP system */
/* last segment number for this kind of segments is dynamic - maximum is the number of reserved segments in the hardware INI file! */
#define FIRST_SEG_NUM_SHM_DC_BUFFERS	30

/* -------- END segment numbers for data consistency buffers -------- */

/* ======== END P0699-specific segment numbers ======== */

#endif /* _RESERVEDSEGMENTS_H_ */
