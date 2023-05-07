
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>

#define BUF_SIZE 60
#define IP_ADDRESS "192.168.1.59" // internet address of ..
#define FLAG_ZERO 0
#define EQUAL_ZERO 0
#define TRUE 1
#define FALSE 0
#define PORT 7
#define LEN 30
#define SLEEP_TIME 3
#define ERROR -1
#define MAX_SIZE_BUF 256
#define SUCSSES 1
#define UNSUCSSES 255
#define MUX_ITERATIONS 11 

#define ADDRESS_0 0
#define ADDRESS_4 4
#define ADDRESS_5 5
#define ADDRESS_6 6
#define ADDRESS_7 7
#define TEST_SIZE 5

typedef struct send_t
{
        uint32_t Test_ID  ;                             // a number given to the test
        uint8_t Peripheral_tested ;                     // a bitfield for the peripheral being tested: 1 –Timer, 2 – UART, SPI – 4, I2C – 8, ADC – 16
        uint8_t Iterations ;                            // the number of iterations the test should run at the UUT (Unit Under Test) 
        uint8_t Bit_pattern_length  ;                   // the size of the Bit pattern string sent to UUT
        char* Bit_pattern   ;                           // the actual string of characters sent to the UUT
} send_t;

typedef struct resv
{
    uint32_t idTest;                                    // a number given to the test
    uint8_t result;                                     // Holds the result (if the test success is returen 1 eles 256)
} resv_t;

double calculation_time;                      // d hold the 
char buf_to_server[MAX_SIZE_BUF];               // Used for writing from buffer
char buf_from_server[MAX_SIZE_BUF];             // Used for Reading from buffer
time_t start, end;                             // start is started time, end is end of time


int add_test_bying_user();
void connect_to_server(send_t *tests);
void init_tests();