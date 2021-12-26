#ifndef _LIGHTCONTROL_H
#define _LIGHTCONTROL_H


#define Dimmer_port PORT
#define Dimmer_DDR  DDR
#define Dimmer1		A
#define Dimmer2		B
#define Dimmer3		C

#define D3_1_pos	PC6
#define D3_2_pos	PC7
#define D3_3_pos	PB2
#define D2_1_pos	PB3
#define D2_2_pos	PA0
#define D2_3_pos	PA1
#define D1_1_pos	PA2
#define D1_2_pos	PA3
#define D1_3_pos	PA4
#define D0_1_pos	PA5
#define D0_2_pos	PA6
#define D0_3_pos	PA7

#define Dimmer1port PORT(Dimmer1)
#define Dimmer2port PORT(Dimmer2)
#define Dimmer3port PORT(Dimmer3)
#define Dimmer1_DDR	DDR(Dimmer1)
#define Dimmer2_DDR	DDR(Dimmer2)
#define Dimmer3_DDR	DDR(Dimmer3)

/*void LightControlint(void)
{
	//SET IO PORT FOR LIGHT
	LIGHT_DDR = 0XFF;
	LIGHT_PORT=0XFF; 

	//SET IO PORT FOR DIMMER
	Dimmer1_DDR|=(1<<D0_1_pos);
	Dimmer1port|=(1<<D0_1_pos);
	Dimmer1_DDR|=(1<<D0_2_pos);
	Dimmer1port|=(1<<D0_2_pos);
	Dimmer1_DDR|=(1<<D0_3_pos);
	Dimmer1port|=(1<<D0_3_pos);
	
	Dimmer1_DDR|=(1<<D1_1_pos);
	Dimmer1port|=(1<<D1_1_pos);
	Dimmer1_DDR|=(1<<D1_2_pos);
	Dimmer1port|=(1<<D1_2_pos);
	Dimmer1_DDR|=(1<<D1_3_pos);
	Dimmer1port|=(1<<D1_3_pos);
	
	Dimmer2_DDR|=(1<<D2_1_pos);
	Dimmer2port|=(1<<D2_1_pos);
	Dimmer1_DDR|=(1<<D2_2_pos);
	Dimmer1port|=(1<<D2_2_pos);
	Dimmer1_DDR|=(1<<D2_3_pos);
	Dimmer1port|=(1<<D2_3_pos);	
	
	Dimmer3_DDR|=(1<<D3_1_pos);
	Dimmer3port|=(1<<D3_1_pos);
	Dimmer3_DDR|=(1<<D3_2_pos);
	Dimmer3port|=(1<<D3_2_pos);
	Dimmer2_DDR|=(1<<D3_3_pos);
	Dimmer2port|=(1<<D3_3_pos);
}*/ 


#endif

