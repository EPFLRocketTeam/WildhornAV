/*  Title		: Messenger
 *  Filename	: messenger.c
 *	Author		: iacopo sprenger
 *	Date		: 30.01.2021
 *	Version		: 0.1
 *	Description	: messenger to communicate with linux kernel on CA7
 */

/**********************
 *	INCLUDES
 **********************/

#include <openamp.h>

#include "linuxcomm/messenger.h"

/**********************
 *	CONSTANTS
 **********************/

#define MAX_BUFFER_SIZE RPMSG_BUFFER_SIZE
#define RPMSG_SERVICE_NAME              "rpmsg-netlink"


/**********************
 *	MACROS
 **********************/


/**********************
 *	TYPEDEFS
 **********************/

/*
enum { PREAMBLE=0xABCD, };
#pragma pack(1)
struct packet {
  uint16_t preamble;
  uint16_t length;
  uint16_t crc16;
};

struct virt_dev_buffer {
  FlagStatus rx_status;
  uint8_t *rx_buffer;
  uint16_t rx_size;
};
*/

/**********************
 *	VARIABLES
 **********************/

/*
uint8_t rx_buffer[MAX_BUFFER_SIZE];
struct virt_dev_buffer rx_dev = {
  .rx_status = RESET,
  .rx_buffer = rx_buffer,
  .rx_size = 0,
};
uint16_t rpmsg_expected_nbytes = 0;
*/

/**********************
 *	PROTOTYPES
 **********************/

static int rx_callback(struct rpmsg_endpoint *rp_chnl, void *data, size_t len, uint32_t src, void *priv);

/**********************
 *	DECLARATIONS
 **********************/

/* END */
