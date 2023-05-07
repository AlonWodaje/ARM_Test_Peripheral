#include "client_udp.h"

int main(int argc, char *argv[])
{
        printf("*********** Start ******************\n");

        /************************************* Code *****************************************************/

        //add_test_bying_user();
        init_tests();
        return 0;
} 


int add_test_bying_user(){

        send_t test;
        //init_send(test);

        //*********** read Test ID ************** 
        printf("enter Test ID : ");
        scanf("%d", &test.Test_ID);
        if(test.Test_ID <= 0)
        {
                printf("Error input Test ID, EXIT");
                return 0;
                
        }

        //*********** read Peripheral ************** 
        printf("enter Peripheral tested (1 - Timer , 2 - UART, 4 - SPI , 8 - I2C, 16 - ADC) : ");
        scanf("%hhd", &test.Peripheral_tested);
        if ( (test.Peripheral_tested != 1) && (test.Peripheral_tested != 2) && (test.Peripheral_tested != 4) &&(test.Peripheral_tested != 8) && (test.Peripheral_tested != 16) )
        {
                printf("Error input Peripheral, EXIT\n");
                return 0;
        }
        if( (test.Peripheral_tested == 2) || (test.Peripheral_tested == 4) || (test.Peripheral_tested == 8) )
        {
                printf("enter string data : ");
                scanf("%s", test.Bit_pattern);
                test.Bit_pattern_length = strlen(test.Bit_pattern);
        }

        //*********** read iterations ************** 
        printf("enter number of iterations test (maximum iterations 10): ");
        scanf("%hhd", &test.Iterations);
        if(test.Iterations > MUX_ITERATIONS )
        {
                printf("Error input iterations, EXIT\n");
                return 0;
        }

        connect_to_server(&test);
        return 1;

}


void init_tests()
{
        printf("*********** init_tests *************\n");

        send_t tests1[TEST_SIZE] =
        {
                {101, 1,  4, 19, "TIMER TEST ..DATA.."},
                {201, 2,  4, 18, "UART TEST ..DATA.." },
                {301, 4,  4, 17, "SPI TEST ..DATA.."  },
                {401, 8,  4, 17, "I2C TEST ..DATA.."  },
                {501, 16, 4, 17, "ADC TEST ..DATA.."  }
        };
        connect_to_server(tests1);

        
        send_t tests2[TEST_SIZE] =
        {
                {102, 1,  2, 19, "TIMER TEST ..DATA.."},
                {202, 2,  4, 35, "UART TEST ..DATA.." },
                {302, 4,  4, 45, "SPI TEST ..DATA.."  },
                {402, 8,  4, 40, "I2C TEST ..DATA.."  },
                {502, 16, 4, 17, "ADC TEST ..DATA.."  }
        };
        connect_to_server(tests2);

        
        send_t tests3[TEST_SIZE] =
        {
                {103, 1,  4, 19, "TIMER TEST ..DATA.."},
                {203, 2,  4, 10, "UART TEST ..DATA.." },
                {303, 4,  4, 8, "SPI TEST ..DATA.."  },
                {403, 8,  4, 5, "I2C TEST ..DATA.."  },
                {503, 16, 4, 17, "ADC TEST ..DATA.."  }
        };
        connect_to_server(tests3);

        
        send_t tests4[TEST_SIZE] =
        {
                {104, 1,  4, 19, "TIMER TEST ..DATA.."},
                {204, 2,  4, 255, "UART TEST ..DATA.." },
                {304, 4,  4, 255, "SPI TEST ..DATA.."  },
                {404, 8,  4, 255, "I2C TEST ..DATA.."  },
                {504, 16, 4, 17, "ADC TEST ..DATA.."  }
        };
        connect_to_server(tests4);

        
        send_t tests5[TEST_SIZE] =
        {
                {105, 1,  4, 19, "TIMER TEST ..DATA.."},
                {205, 2,  4, 300, "UART TEST ..DATA.." },
                {305, 4,  4, 350, "SPI TEST ..DATA.."  },
                {405, 8,  4, 300, "I2C TEST ..DATA.."  },
                {505, 16, 4, 17, "ADC TEST ..DATA.."  }
        };
        connect_to_server(tests5);

        send_t tests6[TEST_SIZE] =
        {
                {106, 1,  4, 19, "TIMER TEST ..DATA.."},
                {206, 2,  4, -5, "UART TEST ..DATA.." },
                {306, 4,  4, -8, "SPI TEST ..DATA.."  },
                {406, 8,  4, -4, "I2C TEST ..DATA.."  },
                {506, 16, 4, 17, "ADC TEST ..DATA.."  }
        };
        connect_to_server(tests6);

        printf("*********** end all tests **********\n");
}


void connect_to_server(send_t* tests){
        printf("*********** connect_to_server ******\n");

        /*************************************** Vars ***************************************************/
        
        struct sockaddr_in dest;                        // Holds Destination socket (IP+PORT)
        int socket_fd;                                  // Holds socket file descriptor
        unsigned int ssize;                             // Holds size of dest
        struct hostent *hostptr;                        // Holds host information
        int retVal = 0;                                 // Holds return Value for recvfrom() / sendto()
        char *cRetVal = NULL;                           // Holds return Value for fgets()
        resv_t Test_Result;
       
        /************************************* Initialization ******************************************/

        socket_fd = socket(AF_INET, SOCK_DGRAM, FLAG_ZERO); // Create socket
        if (socket_fd == ERROR)
        {
                perror("Create socket");
                exit(TRUE);
        } // Validate the socket

        bzero((char *)&dest, sizeof(dest));             // Clearing the struct
        dest.sin_family = (short)AF_INET;               // Setting IPv4
        dest.sin_port = htons(PORT);                    // Setting port
        dest.sin_addr.s_addr = inet_addr(IP_ADDRESS);   // Setting IP address

        ssize = sizeof(dest); // Get dest size
        int i=0;
        static int index_of_tested = 1;
 
        while (i!=5)
        {
                *(uint32_t *)(buf_to_server + ADDRESS_0) = tests[i].Test_ID;
                *(uint8_t * )(buf_to_server + ADDRESS_4) = tests[i].Peripheral_tested;
                *(uint8_t * )(buf_to_server + ADDRESS_5) = tests[i].Iterations;
                *(uint8_t * )(buf_to_server + ADDRESS_6) = tests[i].Bit_pattern_length;
                memcpy(buf_to_server + ADDRESS_7, tests[i].Bit_pattern, tests[i].Bit_pattern_length);
                i++;

                retVal = sendto(socket_fd, buf_to_server, LEN, FLAG_ZERO, (struct sockaddr *)&dest, ssize);              // Send Ping
                if (retVal < 0)
                        break;
                else
                {
                        retVal = recvfrom(socket_fd, buf_from_server, LEN, FLAG_ZERO, (struct sockaddr *)&dest, &ssize); // Get answer
                                                         // calculation time between start end end
                        if (retVal < 0)
                                break;
                        Test_Result.idTest = *(uint32_t *)(buf_from_server + ADDRESS_0);                                          // fill the struct from server for test id
                        Test_Result.result = *(uint8_t * )(buf_from_server + ADDRESS_4);                                          // fill the struct from server for result
                        printf("Test id : %d\n", (int)Test_Result.idTest);
                        if(Test_Result.result == SUCSSES)
                                printf("test success\n");
                        else if(Test_Result.result == UNSUCSSES)
                                printf("test unsuccess\n");
                        else
                                printf("fail test, input data are error\n");
                        
                }       
        }
        close(socket_fd); // Closing socket
        printf("*********** end test %d *************\n", index_of_tested);
        index_of_tested++;
        sleep(SLEEP_TIME);
     
}
