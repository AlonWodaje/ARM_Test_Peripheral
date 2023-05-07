#include "RTG.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SERVER_PORT 7
#define ADDRESS_0 0
#define ADDRESS_4 4
#define ADDRESS_5 5
#define ADDRESS_6 6
#define ADDRESS_7 7

typedef struct resv
{
        uint32_t Test_ID  ;            // a number given to the test
        uint8_t Peripheral_tested ;    // a bitfield for the peripheral being tested: 1 –Timer, 2 – UART, SPI – 4, I2C – 8, ADC – 16
        uint8_t Iterations ;           // the number of iterations the test should run at the UUT (Unit Under Test)
        uint8_t Bit_pattern_length  ;  // the size of the Bit pattern string sent to UUT
        char* Bit_pattern   ;          // the actual string of characters sent to the UUT
} resv;

typedef struct send
{
    uint32_t idTest;                                    // a number given to the test
    uint8_t result;                                     // Holds the result (if the test success is returen 1 eles 256)
} send;

void switch_Peripheral_tested(resv *resv_data, send *Test_Result);

/**
 * redirect printf to uart3
 */
PUTCHAR_PROTOTYPE {
	HAL_UART_Transmit(UART_DEBUG, (uint8_t*) &ch, 1, HAL_MAX_DELAY);
	return ch;
}

extern struct netif gnetif;

void udp_receive_callback(
		void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
	struct pbuf *txBuf = pbuf_alloc(PBUF_TRANSPORT,5, PBUF_RAM);//tX transmit to client back
	send Test_Result;
	resv resv_data;
	resv_data.Test_ID            = *(uint32_t *)(p->payload + ADDRESS_0);
	resv_data.Peripheral_tested  = *(uint8_t *) (p->payload + ADDRESS_4);
	resv_data.Iterations         = *(uint8_t *) (p->payload + ADDRESS_5);
	resv_data.Bit_pattern_length = *(uint8_t *) (p->payload + ADDRESS_6);
    memcpy(resv_data.Bit_pattern, p->payload + ADDRESS_7, resv_data.Bit_pattern_length);

    switch_Peripheral_tested(&resv_data, &Test_Result);

	char buf[5];
	/* copy the data into the buffer  */
    *(uint32_t *)(buf + ADDRESS_0) = Test_Result.idTest;
    *(uint8_t *) (buf + ADDRESS_4) = Test_Result.result;

	pbuf_take(txBuf, buf, 5);

	/* Connect to the remote client */
	udp_connect(upcb, addr, port);

	/* Send a Reply to the Client */
	udp_send(upcb, txBuf);

	/* free the UDP connection, so we can accept new clients */
	udp_disconnect(upcb);

	/* Free the p_tx buffer */
	pbuf_free(txBuf);

	/* Free the p buffer */
	pbuf_free(p);
}

void udpServer_init(void) {
	// UDP Control Block structure
   struct udp_pcb* upcb = udp_new();
   err_t err = udp_bind(upcb, IP_ADDR_ANY, SERVER_PORT);  // 7 is the server UDP port

   /* 3. Set a receive callback for the upcb */
   if (err == ERR_OK) {/// ERR_OK = ** No error, everything OK. */
	   udp_recv(upcb, udp_receive_callback, NULL);
   }
   else {
	   udp_remove(upcb); // free the allocated memory
   }
}

void rtg_main() {

	udpServer_init();
	while (1) {
		 ethernetif_input(&gnetif);
		 sys_check_timeouts();
	}
}

void switch_Peripheral_tested(resv *resv_data, send *Test_Result)
{
	struct pbuf *txBuf = pbuf_alloc(PBUF_TRANSPORT,5, PBUF_RAM);//tX transmit to client back
	int len = strlen(resv_data->Bit_pattern);

	switch(resv_data->Peripheral_tested)
	{
	  case 1://Timer
		  Test_Result->result = timer_main(resv_data->Iterations);
	    break;
	  case 2://UART
		  Test_Result->result = uart_main(resv_data->Iterations, resv_data->Bit_pattern, len);
	    break;
	  case 4://SPI
		  Test_Result->result = spi_main(resv_data->Iterations, resv_data->Bit_pattern, len);
	    break;
	  case 8://I2C
		  Test_Result->result = i2c_main(resv_data->Iterations, resv_data->Bit_pattern, len);
	    break;
	  case 16://ADC
		  Test_Result->result = adc_main(resv_data->Iterations);
	    break;
	  default:
	    // code block
	    break;
	}
}
