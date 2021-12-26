#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "ip_arp_udp_tcp.h"
#include "enc28j60.h"
#include "timeout.h"
#include "avr_compat.h"
#include "net.h"

// mac and ip have to be unique
// in your local area network. You can not have the same numbers in
// two devices:

static uint8_t mymac[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
//how did I get the mac addr? Translate the first 3 numbers into ascii is: TUX
static uint8_t myip[4] = {192,168,1,177};
//listen port for tcp/www (max range 1-254)
#define MYWWWPORT 1234
//listen port for udp
#define MYUDPPORT 1200
#define BUFFER_SIZE 900
static uint8_t buf[BUFFER_SIZE+20];
int8_t analyse_get_url(char *str)
{       // check the first char, garbage after this is ignored (including a slash)
		//str++;
        if (*str < 0x3a && *str > 0x2f){
                // is a ASCII number, return it
//for 1
				if((*str-0x30)==0){
					str++;
					if((*str-0x30)==1)
					return(01);
					else if((*str-0x30)==0)
					return(00);
				}
//for 2
				if((*str-0x30)==1){
					str++;
					if((*str-0x30)==1)
					return(11);
					else if((*str-0x30)==0)
					return(10);
				} 
//for 3
				if((*str-0x30)==2){
					str++;
					if((*str-0x30)==1)
					return(21);
					else if((*str-0x30)==0)
					return(20);
				}
//for 4
				if((*str-0x30)==3){
					str++;
					if((*str-0x30)==1)
					return(31);
					else if((*str-0x30)==0)
					return(30);
				}
//for 5
				if((*str-0x30)==4){
					str++;
					if((*str-0x30)==1)
					return(41);
					else if((*str-0x30)==0)
					return(40);
				}
//for 6
				if((*str-0x30)==5){
					str++;
					if((*str-0x30)==1)
					return(51);
					else if((*str-0x30)==0)
					return(50);
				}
//for D1 & D2
				if((*str-0x30)==6){
					str++;
					if((*str-0x30)==1)
					return(61);
					else if((*str-0x30)==0)
					return(60);
				}
				 
//for D3 & D4				
				if((*str-0x30)==7){
					str++;
					if((*str-0x30)==1)
					return(71);
					else if((*str-0x30)==0)
					return(70);
				}
//for [+]&[-]
				if((*str-0x30)==8){
					str++;
					if((*str-0x30)==1)
					return(81);
					else if((*str-0x30)==0)
					return(80);
				}
        }
        return(-2);
}  

// prepare the webpage by writing the data to the tcp send buffer
uint16_t print_webpage(uint8_t *buf,uint8_t on_off1,uint8_t on_off2,uint8_t on_off3,uint8_t on_off4,uint8_t on_off5,uint8_t on_off6)
{
        uint16_t plen;
        plen=fill_tcp_data_p(buf,0,PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n"));
		plen=fill_tcp_data_p(buf,plen,PSTR("<p><font size=\"12\"font face=\"Swis721 BlkOul BT\" font color=\"Blue\">LIGHT CONTROL SYSTEM :</font></p> "));
		plen=fill_tcp_data_p(buf,plen,PSTR("<title>Ethernet Light Control System</title> <br />"));
       
        if (on_off1){
                plen=fill_tcp_data_p(buf,plen,PSTR("<a href=\"./00\">LIGHT 1 OFF  </a><br />"));
        }else{
                plen=fill_tcp_data_p(buf,plen,PSTR("<a href=\"./01\">LIGHT 1  ON  </a><br />"));
        }
		if (on_off2){
                plen=fill_tcp_data_p(buf,plen,PSTR("<a href=\"./10\">LIGHT 2 OFF  </a><br />"));
        }else{
                plen=fill_tcp_data_p(buf,plen,PSTR("<a href=\"./11\">LIGHT 2  ON  </a><br />"));
        }
		if (on_off3){
                plen=fill_tcp_data_p(buf,plen,PSTR("<a href=\"./20\">LIGHT 3 OFF </a><br />"));
        }else{
                plen=fill_tcp_data_p(buf,plen,PSTR("<a href=\"./21\">LIGHT 3  ON  </a><br />"));
        }
		if (on_off4){
                plen=fill_tcp_data_p(buf,plen,PSTR("<a href=\"./30\">LIGHT 4 OFF  </a><br />"));
        }else{
                plen=fill_tcp_data_p(buf,plen,PSTR("<a href=\"./31\">LIGHT 4  ON  </a><br />"));
        }
		if (on_off5){
                plen=fill_tcp_data_p(buf,plen,PSTR("<a href=\"./40\">LIGHT 5 OFF  </a><br />"));
        }else{
                plen=fill_tcp_data_p(buf,plen,PSTR("<a href=\"./41\">LIGHT 5  ON  </a><br />"));
        }
		if (on_off6){
                plen=fill_tcp_data_p(buf,plen,PSTR("<a href=\"./50\">LIGHT 6 OFF  </a><br />"));
        }else{
                plen=fill_tcp_data_p(buf,plen,PSTR("<a href=\"./51\">LIGHT 6  ON  </a><br />"));
        }
		        
        plen=fill_tcp_data_p(buf,plen,PSTR("<a href=\"./60\">Dimmer1  </a><a href=\"./61\">Dimmer2  </a>"));
        plen=fill_tcp_data_p(buf,plen,PSTR("<a href=\"./70\">Dimmer3  </a><a href=\"./71\">Dimmer4  </a><br />"));
        plen=fill_tcp_data_p(buf,plen,PSTR("<a href=\"./80\">[-] </a><a href=\"./81\">[+] </a><br />"));
		plen=fill_tcp_data_p(buf,plen,PSTR("<hr><br>version 1.0,<a href=\"http://www.ambimat.com\">AMBIMAT ELECTRONICS</a>\n"));
 		return(plen);
}


int main(void){

        
        uint16_t plen;
        uint16_t dat_p;
        uint8_t i=0,count=0,count1=0,count2=0,count3=0;
	   	int8_t cmd,temp_cmd=0;
    
        
        /* enable PD2/INT0, as input */
        INT0_INPUT_DDR &= ~(1<<INT0_INPUT_DDD2);

        /*initialize enc28j60*/
        enc28j60Init(mymac);
    
        delay_ms(10);
        
        // LED
        /* enable PB1, LED as output */
        LED_DDR |= (1<<STATUS_LED_DD);

        /* set output to Vcc, LED off */
        LED_PORT |= (1<<STATUS_LED);

        // the Light on PD7
        LIGHT_DDR |= (1<<LIGHT1_DD);
        LIGHT_PORT &= ~(1<<LIGHT1);// Light1 off
		
		LIGHT_DDR |= (1<<LIGHT1_DD);
        LIGHT_PORT &= ~(1<<LIGHT1);// Light2 off
		
		LIGHT_DDR |= (1<<LIGHT1_DD);
        LIGHT_PORT &= ~(1<<LIGHT1);// Light3 off
		
		LIGHT_DDR |= (1<<LIGHT1_DD);
        LIGHT_PORT &= ~(1<<LIGHT1);// Light4 off
		
		LIGHT_DDR |= (1<<LIGHT1_DD);
        LIGHT_PORT &= ~(1<<LIGHT1);// Light5 off
		
		LIGHT_DDR |= (1<<LIGHT1_DD);
        LIGHT_PORT &= ~(1<<LIGHT1);// Light6 off

		//DIMMER1 INITIALIZATION PA5,PA6,PA7
		DIMMER1_DDR |= (1<<DIMMER1_0_DD);
        DIMMER1_PORT &= ~(1<<DIMMER1_0);
		
		DIMMER1_DDR |= (1<<DIMMER1_1_DD);
        DIMMER1_PORT &= ~(1<<DIMMER1_1);
		
		DIMMER1_DDR |= (1<<DIMMER1_2_DD);
        DIMMER1_PORT &= ~(1<<DIMMER1_2);

		//DIMMER2 INITIALIZATION PA2,PA3,PA4
		DIMMER1_DDR |= (1<<DIMMER2_0_DD);
        DIMMER1_PORT &= ~(1<<DIMMER2_0);
		
		DIMMER1_DDR |= (1<<DIMMER2_1_DD);
        DIMMER1_PORT &= ~(1<<DIMMER2_1);
		
		DIMMER1_DDR |= (1<<DIMMER2_2_DD);
        DIMMER1_PORT &= ~(1<<DIMMER2_2);

		//DIMMER3 INITIALIZATION PB3,PA0,PA1
		DIMMER2_DDR |= (1<<DIMMER3_0_DD);
        DIMMER2_PORT &= ~(1<<DIMMER3_0);
		
		DIMMER1_DDR |= (1<<DIMMER3_1_DD);
        DIMMER1_PORT &= ~(1<<DIMMER3_1);
		
		DIMMER1_DDR |= (1<<DIMMER3_2_DD);
        DIMMER1_PORT &= ~(1<<DIMMER3_2);

		//DIMMER4 INITIALIZATION PC6,PC7,PB2
		DIMMER3_DDR |= (1<<DIMMER4_0_DD);
        DIMMER3_PORT &= ~(1<<DIMMER4_0);
		
		DIMMER3_DDR |= (1<<DIMMER4_1_DD);
        DIMMER3_PORT &= ~(1<<DIMMER4_1);
		
		DIMMER2_DDR |= (1<<DIMMER4_2_DD);
        DIMMER2_PORT &= ~(1<<DIMMER4_2);
		        

        /* Magjack leds configuration, see enc28j60 datasheet, page 11 */
        // LEDB=yellow LEDA=green
        //
        // 0x476 is PHLCON LEDA=links status, LEDB=receive/transmit
        // enc28j60PhyWrite(PHLCON,0b0000 0100 0111 01 10);
        enc28j60PhyWrite(PHLCON,0x476);
        delay_ms(20);
        
        /* set output to GND, red LED on */
        LED_PORT &= ~(1<<STATUS_LED);

        i=1;

        //init the ethernet/ip layer:
        init_ip_arp_udp_tcp(mymac,myip,MYWWWPORT);

        while(1){
                // get the next new packet:
                plen = enc28j60PacketReceive(BUFFER_SIZE, buf);

                /*plen will be unequal to zero if there is a valid 
                 * packet (without crc error) */
                if(plen==0){
                        continue;
                }
                        
                // arp is broadcast if unknown but a host may also
                // verify the mac address by sending it to 
                // a unicast address.
                if(eth_type_is_arp_and_my_ip(buf,plen)){
                        make_arp_answer_from_request(buf);
                        continue;
                }

                // check if ip packets are for us:
                if(eth_type_is_ip_and_my_ip(buf,plen)==0){
                        continue;
                }
                // led----------
                if (i){
                        /* set output to Vcc, LED off */
                        LED_PORT |= (1<<STATUS_LED);
                        i=0;
                }else{
                        /* set output to GND, LED on */
                        LED_PORT &= ~(1<<STATUS_LED);
                        i=1;
                }
                
                if(buf[IP_PROTO_P]==IP_PROTO_ICMP_V && buf[ICMP_TYPE_P]==ICMP_TYPE_ECHOREQUEST_V){
                        // a ping packet, let's send pong
                        make_echo_reply_from_request(buf,plen);
                        continue;
                }
                // tcp port www start, compare only the lower byte
                if (buf[IP_PROTO_P]==IP_PROTO_TCP_V&&buf[TCP_DST_PORT_H_P]==0&&buf[TCP_DST_PORT_L_P]==MYWWWPORT){
                        if (buf[TCP_FLAGS_P] & TCP_FLAGS_SYN_V){
                                make_tcp_synack_from_syn(buf);
                                // make_tcp_synack_from_syn does already send the syn,ack
                                continue;
                        }
                        if (buf[TCP_FLAGS_P] & TCP_FLAGS_ACK_V){
                                init_len_info(buf); // init some data structures
                                // we can possibly have no data, just ack:
                                dat_p=get_tcp_data_pointer();
                                if (dat_p==0){
                                        if (buf[TCP_FLAGS_P] & TCP_FLAGS_FIN_V){
                                                // finack, answer with ack
                                                make_tcp_ack_from_any(buf);
                                        }
                                        // just an ack with no data, wait for next packet
                                        continue;
                                }
                                if (strncmp("GET ",(char *)&(buf[dat_p]),4)!=0){
                                        // head, post and other methods:
                                        //
                                        // for possible status codes see:
                                        // http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html
                                        plen=fill_tcp_data_p(buf,0,PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n<h1>200 OK</h1>"));
                                        goto SENDTCP;
                                }
                             
                                cmd=analyse_get_url((char *)&(buf[dat_p+5]));
                              // for possible status codes see:
                              // http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html
                              /*  if (cmd==-1){
                                        plen=fill_tcp_data_p(buf,0,PSTR("HTTP/1.0 401 Unauthorized\r\nContent-Type: text/html\r\n\r\n<h1>401 Unauthorized</h1>"));
                                        goto SENDTCP;
                                }*/
                                if (cmd==01) LIGHT_PORT|= (1<<LIGHT1);					//Light1 on
                                if (cmd==00) LIGHT_PORT &= ~(1<<LIGHT1);					//Light1 off
								
								if (cmd==11) LIGHT_PORT|= (1<<LIGHT2);					//Light2 on
                                if (cmd==10) LIGHT_PORT &= ~(1<<LIGHT2);					//Light2 off
                                
								if (cmd==21) LIGHT_PORT|= (1<<LIGHT3);					//Light3 on
                                if (cmd==20) LIGHT_PORT &= ~(1<<LIGHT3);					//Light3 off
                                
								if (cmd==31) LIGHT_PORT|= (1<<LIGHT4);					//Light4 on
                                if (cmd==30) LIGHT_PORT &= ~(1<<LIGHT4);					//Light4 off
                                
								if (cmd==41) LIGHT_PORT|= (1<<LIGHT5);					//Light5 on
                                if (cmd==40) LIGHT_PORT &= ~(1<<LIGHT5);					//Light5 off
                                
								if (cmd==51) LIGHT_PORT|= (1<<LIGHT6);					//Light6 on
                                if (cmd==50) LIGHT_PORT &= ~(1<<LIGHT6);					//Light6 off 
								
								if (cmd==60 || cmd==61 || cmd==70 || cmd==71)
								{
									temp_cmd=cmd;	//Dimmer selection
									count=0;                               
                              	}
								
								if (temp_cmd==60){
									if(cmd==80){
										count++;
									}else if(cmd==81){
									count--;
									}
									switch(count){
									case 0:
											DIMMER1_PORT &= ~(1<<DIMMER1_0);
											DIMMER1_PORT &= ~(1<<DIMMER1_1);
											DIMMER1_PORT &= ~(1<<DIMMER1_2);
									case 1:
											DIMMER1_PORT |= (1<<DIMMER1_0);
											DIMMER1_PORT &= ~(1<<DIMMER1_1);
											DIMMER1_PORT &= ~(1<<DIMMER1_2);
									case 2:
											DIMMER1_PORT &= ~(1<<DIMMER1_0);
											DIMMER1_PORT |= (1<<DIMMER1_1);
											DIMMER1_PORT &= ~(1<<DIMMER1_2);
									case 3:
											DIMMER1_PORT |= (1<<DIMMER1_0);
											DIMMER1_PORT |= (1<<DIMMER1_1);
											DIMMER1_PORT &= ~(1<<DIMMER1_2);
									case 4:
											DIMMER1_PORT &= ~(1<<DIMMER1_0);
											DIMMER1_PORT &= ~(1<<DIMMER1_1);
											DIMMER1_PORT |= (1<<DIMMER1_2);
									case 5:
											DIMMER1_PORT |= (1<<DIMMER1_0);
											DIMMER1_PORT &= ~(1<<DIMMER1_1);
											DIMMER1_PORT |= (1<<DIMMER1_2);
									case 6:
											DIMMER1_PORT &= ~(1<<DIMMER1_0);
											DIMMER1_PORT |= (1<<DIMMER1_1);
											DIMMER1_PORT |= (1<<DIMMER1_2);	
									case 7:
											DIMMER1_PORT |= (1<<DIMMER1_0);
											DIMMER1_PORT |= (1<<DIMMER1_1);
											DIMMER1_PORT |= (1<<DIMMER1_2);						
									}
									if(count>=7)count=0;
									else if(count<=0)count=7;
								}
								
								if (temp_cmd==61){
									if(cmd==80){
										count1++;
									}else if(cmd==81){
									count1--;
									}
									switch(count1){
									case 0:
											DIMMER1_PORT &= ~(1<<DIMMER2_0);
											DIMMER1_PORT &= ~(1<<DIMMER2_1);
											DIMMER1_PORT &= ~(1<<DIMMER2_2);
									case 1:
											DIMMER1_PORT |= (1<<DIMMER2_0);
											DIMMER1_PORT &= ~(1<<DIMMER2_1);
											DIMMER1_PORT &= ~(1<<DIMMER2_2);
									case 2:
											DIMMER1_PORT &= ~(1<<DIMMER2_0);
											DIMMER1_PORT |= (1<<DIMMER2_1);
											DIMMER1_PORT &= ~(1<<DIMMER2_2);
									case 3:
											DIMMER1_PORT |= (1<<DIMMER2_0);
											DIMMER1_PORT |= (1<<DIMMER2_1);
											DIMMER1_PORT &= ~(1<<DIMMER2_2);
									case 4:
											DIMMER1_PORT &= ~(1<<DIMMER2_0);
											DIMMER1_PORT &= ~(1<<DIMMER2_1);
											DIMMER1_PORT |= (1<<DIMMER2_2);
									case 5:
											DIMMER1_PORT |= (1<<DIMMER2_0);
											DIMMER1_PORT &= ~(1<<DIMMER2_1);
											DIMMER1_PORT |= (1<<DIMMER2_2);
									case 6:
											DIMMER1_PORT &= ~(1<<DIMMER2_0);
											DIMMER1_PORT |= (1<<DIMMER2_1);
											DIMMER1_PORT |= (1<<DIMMER2_2);	
									case 7:
											DIMMER1_PORT |= (1<<DIMMER2_0);
											DIMMER1_PORT |= (1<<DIMMER2_1);
											DIMMER1_PORT |= (1<<DIMMER2_2);
									}
									if(count1>=7)count1=0;
									else if(count1<=0)count1=7;
								}
								
								if (temp_cmd==70){
									if(cmd==80)count2++;
									else if(cmd==81)count2--;
									switch(count2){
									case 0:
											DIMMER2_PORT &= ~(1<<DIMMER3_0);
											DIMMER1_PORT &= ~(1<<DIMMER3_1);
											DIMMER1_PORT &= ~(1<<DIMMER3_2);
									case 1:
											DIMMER2_PORT |= (1<<DIMMER3_0);
											DIMMER1_PORT &= ~(1<<DIMMER3_1);
											DIMMER1_PORT &= ~(1<<DIMMER3_2);
									case 2:
											DIMMER2_PORT &= ~(1<<DIMMER3_0);
											DIMMER1_PORT |= (1<<DIMMER3_1);
											DIMMER1_PORT &= ~(1<<DIMMER3_2);
									case 3:
											DIMMER2_PORT |= (1<<DIMMER3_0);
											DIMMER1_PORT |= (1<<DIMMER3_1);
											DIMMER1_PORT &= ~(1<<DIMMER3_2);
									case 4:
											DIMMER2_PORT &= ~(1<<DIMMER3_0);
											DIMMER1_PORT &= ~(1<<DIMMER3_1);
											DIMMER1_PORT |= (1<<DIMMER3_2);
									case 5:
											DIMMER2_PORT |= (1<<DIMMER3_0);
											DIMMER1_PORT &= ~(1<<DIMMER3_1);
											DIMMER1_PORT |= (1<<DIMMER3_2);
									case 6:
											DIMMER2_PORT &= ~(1<<DIMMER3_0);
											DIMMER1_PORT |= (1<<DIMMER3_1);
											DIMMER1_PORT |= (1<<DIMMER3_2);	
									case 7:
											DIMMER2_PORT |= (1<<DIMMER1_0);
											DIMMER1_PORT |= (1<<DIMMER1_1);
											DIMMER1_PORT |= (1<<DIMMER1_2);
									}
									if(count2>=7)count2=0;
									else if(count2<=0)count2=7;
								}
								
								if (temp_cmd==71){
									if(cmd==80)count3++;
									else if(cmd==81)count3--;
									switch(count3){
									case 0:
											DIMMER3_PORT &= ~(1<<DIMMER4_0);
											DIMMER3_PORT &= ~(1<<DIMMER4_1);
											DIMMER2_PORT &= ~(1<<DIMMER4_2);
									case 1:
											DIMMER3_PORT |= (1<<DIMMER4_0);
											DIMMER3_PORT &= ~(1<<DIMMER4_1);
											DIMMER2_PORT &= ~(1<<DIMMER4_2);
									case 2:
											DIMMER3_PORT &= ~(1<<DIMMER4_0);
											DIMMER3_PORT |= (1<<DIMMER4_1);
											DIMMER2_PORT &= ~(1<<DIMMER4_2);
									case 3:
											DIMMER3_PORT |= (1<<DIMMER4_0);
											DIMMER3_PORT |= (1<<DIMMER4_1);
											DIMMER2_PORT &= ~(1<<DIMMER4_2);
									case 4:
											DIMMER3_PORT &= ~(1<<DIMMER4_0);
											DIMMER3_PORT &= ~(1<<DIMMER4_1);
											DIMMER2_PORT |= (1<<DIMMER4_2);
									case 5:
											DIMMER3_PORT |= (1<<DIMMER4_0);
											DIMMER3_PORT &= ~(1<<DIMMER4_1);
											DIMMER2_PORT |= (1<<DIMMER4_2);
									case 6:
											DIMMER3_PORT &= ~(1<<DIMMER4_0);
											DIMMER3_PORT |= (1<<DIMMER4_1);
											DIMMER2_PORT |= (1<<DIMMER4_2);	
									case 7:
											DIMMER3_PORT |= (1<<DIMMER4_0);
											DIMMER3_PORT |= (1<<DIMMER4_1);
											DIMMER2_PORT |= (1<<DIMMER4_2);
									}
									if(count3>=7)count3=0;
									else if(count3<=0)count3=7;
								}
							
                                // if (cmd==-2) or any other value
                                // just display the status:
			plen=print_webpage(buf,(LIGHT_PORT & (1<<LIGHT1)),(LIGHT_PORT & (1<<LIGHT2)),(LIGHT_PORT & (1<<LIGHT3)),
								   (LIGHT_PORT & (1<<LIGHT4)),(LIGHT_PORT & (1<<LIGHT5)),(LIGHT_PORT & (1<<LIGHT6)));
                                //
SENDTCP:
                                make_tcp_ack_from_any(buf); 								// send ack for http get
                                make_tcp_ack_with_data(buf,plen); 							// send data
                                continue;
                        }

                }
                // tcp port www end
             
        }
        return (0);
}
