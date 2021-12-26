#ifndef _LIGHTCONTROL_H
#define _LIGHTCONTROL_H

#define Light_Port 	PORTD
#define Light_DDR   DDRD
#define Dimmer_port PORT
#define Dimmer_DDR  DDR
#define Light1 		PD7	
#define Light2 		PD6
#define Light3 		PD5
#define Light4 		PD4
#define Light5 		PD3
#define Light6 		PD2
#define Dimmer1		B
#define Dimmer2		A
#define Dimmer3		C
#define D1_1_pos	PB0
#define D1_2_pos	PB1
#define D1_3_pos	PB2
#define D2_1_pos	PA0
#define D2_2_pos	PA1
#define D2_3_pos	PA2
#define D3_1_pos	PA3
#define D3_2_pos	PC0
#define D3_3_pos	PC1
#define D4_1_pos	PC2
#define D4_2_pos	PC3
#define D4_3_pos	PC4
#define Dimmer1port PORT(Dimmer1)
#define Dimmer2port PORT(Dimmer2)
#define Dimmer3port PORT(Dimmer3)


#define Dimmer1_DDR	DDR(Dimmer1)
#define Dimmer2_DDR	DDR(Dimmer2)
#define Dimmer3_DDR	DDR(Dimmer3)

void LightControlint(void)
{
	//SET IO PORT FOR LIGHT
	Light_DDR=0xFC;
	Light_Port=0xFC;

	//SET IO PORT FOR DIMMER
	Dimmer1_DDR|=(1<<D1_1_pos);
	Dimmer1port|=(1<<D1_1_pos);
	Dimmer1_DDR|=(1<<D1_2_pos);
	Dimmer1port|=(1<<D1_2_pos);
	Dimmer1_DDR|=(1<<D1_3_pos);
	Dimmer1port|=(1<<D1_3_pos);
	
	Dimmer2_DDR|=(1<<D2_1_pos);
	Dimmer2port|=(1<<D2_1_pos);
	Dimmer2_DDR|=(1<<D2_2_pos);
	Dimmer2port|=(1<<D2_2_pos);
	Dimmer2_DDR|=(1<<D2_3_pos);
	Dimmer2port|=(1<<D2_3_pos);
	
	Dimmer2_DDR|=(1<<D3_1_pos);
	Dimmer2port|=(1<<D3_1_pos);
	Dimmer3_DDR|=(1<<D3_2_pos);
	Dimmer3port|=(1<<D3_2_pos);
	Dimmer3_DDR|=(1<<D3_3_pos);
	Dimmer3port|=(1<<D3_3_pos);	
	
	Dimmer3_DDR|=(1<<D4_1_pos);
	Dimmer3port|=(1<<D4_1_pos);
	Dimmer3_DDR|=(1<<D4_2_pos);
	Dimmer3port|=(1<<D4_2_pos);
	Dimmer3_DDR|=(1<<D4_3_pos);
	Dimmer3port|=(1<<D4_3_pos);
}
uint8_t ControlLight(char *input,int8_t *i)
{
		
	if (strcmp(input,"01")==0)
     	Light_Port ^= _BV(Light1);
		
		else if(strcmp(input,"02")==0)
		Light_Port ^= _BV(Light2);
		
		else if(strcmp(input,"03")==0)
     	Light_Port ^= _BV(Light3);
		
		else if(strcmp(input,"04")==0)
		Light_Port ^= _BV(Light4);
		
		else if(strcmp(input,"05")==0)
		Light_Port ^= _BV(Light5);
		
		else if(strcmp(input,"06")==0)
     	Light_Port ^= _BV(Light6);
		
		else if(strcmp(input,"00")==0)
		{
			if(i==0)
			{
			Light_Port=0x00;
			i=1;
			}
			else
			{
			Light_Port=0xFF;
			i=0;
			}
		}
		
		return i;
}

void ControlDimmer(char *dim,char *input)
{
	if(strcmp(dim,"32")==0)
	{
		if(strcmp(input,"AA")==0){
			Dimmer1port&=(~(1<<D1_1_pos));
			Dimmer1port|=(1<<D1_2_pos);
			Dimmer1port|=(1<<D1_3_pos);
		}
		else if(strcmp(input,"AB")==0){
			Dimmer1port|=(1<<D1_1_pos);
			Dimmer1port&=(~(1<<D1_2_pos));
			Dimmer1port|=(1<<D1_3_pos);
		}
		else if(strcmp(input,"BB")==0){
			Dimmer1port&=(~(1<<D1_1_pos));
			Dimmer1port&=(~(1<<D1_2_pos));
			Dimmer1port|=(1<<D1_3_pos);
		}
		else if(strcmp(input,"BC")==0){
			Dimmer1port|=(1<<D1_1_pos);
			Dimmer1port|=(1<<D1_2_pos);
			Dimmer1port&=(~(1<<D1_3_pos));
		}
		else if(strcmp(input,"CC")==0){
			Dimmer1port&=(~(1<<D1_1_pos));
			Dimmer1port|=(1<<D1_2_pos);
			Dimmer1port&=(~(1<<D1_3_pos));
		}
		else if(strcmp(input,"CD")==0){
			Dimmer1port|=(1<<D1_1_pos);
			Dimmer1port&=(~(1<<D1_2_pos));
			Dimmer1port&=(~(1<<D1_3_pos));
		}
		else if(strcmp(input,"DD")==0){			
			Dimmer1port&=(~(1<<D1_1_pos));
			Dimmer1port&=(~(1<<D1_2_pos));
			Dimmer1port&=(~(1<<D1_3_pos));
		}
		else{
			Dimmer1port|=(1<<D1_1_pos);
			Dimmer1port|=(1<<D1_2_pos);
			Dimmer1port|=(1<<D1_3_pos);
		}
					
	}
	
	else if(strcmp(dim,"34")==0)
	{
		if(strcmp(input,"AA")==0){
			Dimmer2port&=(~(1<<D2_1_pos));
			Dimmer2port|=(1<<D2_2_pos);
			Dimmer2port|=(1<<D2_3_pos);
		}
		else if(strcmp(input,"AB")==0){
			Dimmer2port|=(1<<D2_1_pos);
			Dimmer2port&=(~(1<<D2_2_pos));
			Dimmer2port|=(1<<D2_3_pos);
		}
		else if(strcmp(input,"BB")==0){
			Dimmer2port&=(~(1<<D2_1_pos));
			Dimmer2port&=(~(1<<D2_2_pos));
			Dimmer2port|=(1<<D2_3_pos);
		}
		else if(strcmp(input,"BC")==0){
			Dimmer2port|=(1<<D2_1_pos);
			Dimmer2port|=(1<<D2_2_pos);
			Dimmer2port&=(~(1<<D2_3_pos));
		}
		else if(strcmp(input,"CC")==0){
			Dimmer2port&=(~(1<<D2_1_pos));
			Dimmer2port|=(1<<D2_2_pos);
			Dimmer2port&=(~(1<<D2_3_pos));
		}
		else if(strcmp(input,"CD")==0){
			Dimmer2port|=(1<<D2_1_pos);
			Dimmer2port&=(~(1<<D2_2_pos));
			Dimmer2port&=(~(1<<D2_3_pos));
		}
		else if(strcmp(input,"DD")==0){			
			Dimmer2port&=(~(1<<D2_1_pos));
			Dimmer2port&=(~(1<<D2_2_pos));
			Dimmer2port&=(~(1<<D2_3_pos));
		}
		else{
			Dimmer2port|=(1<<D2_1_pos);
			Dimmer2port|=(1<<D2_2_pos);
			Dimmer2port|=(1<<D2_3_pos);
		}
	}
	else if(strcmp(dim,"07")==0)
	{
		if(strcmp(input,"AA")==0){
			Dimmer2port&=(~(1<<D3_1_pos));
			Dimmer3port|=(1<<D3_2_pos);
			Dimmer3port|=(1<<D3_3_pos);
		}
		else if(strcmp(input,"AB")==0){
			Dimmer2port|=(1<<D3_1_pos);
			Dimmer3port&=(~(1<<D3_2_pos));
			Dimmer3port|=(1<<D3_3_pos);
		}
		else if(strcmp(input,"BB")==0){
			Dimmer2port&=(~(1<<D3_1_pos));
			Dimmer3port&=(~(1<<D3_2_pos));
			Dimmer3port|=(1<<D3_3_pos);
		}
		else if(strcmp(input,"BC")==0){
			Dimmer2port|=(1<<D3_1_pos);
			Dimmer3port|=(1<<D3_2_pos);
			Dimmer3port&=(~(1<<D3_3_pos));
		}
		else if(strcmp(input,"CC")==0){
			Dimmer2port&=(~(1<<D3_1_pos));
			Dimmer3port|=(1<<D3_2_pos);
			Dimmer3port&=(~(1<<D3_3_pos));
		}
		else if(strcmp(input,"CD")==0){
			Dimmer2port|=(1<<D3_1_pos);
			Dimmer3port&=(~(1<<D3_2_pos));
			Dimmer3port&=(~(1<<D3_3_pos));
		}
		else if(strcmp(input,"DD")==0){			
			Dimmer2port&=(~(1<<D3_1_pos));
			Dimmer3port&=(~(1<<D3_2_pos));
			Dimmer3port&=(~(1<<D3_3_pos));
		}
		else{
			Dimmer2port|=(1<<D3_1_pos);
			Dimmer3port|=(1<<D3_2_pos);
			Dimmer3port|=(1<<D3_3_pos);
		}
	}
	else if(strcmp(dim,"ID")==0)
	{
		if(strcmp(input,"AA")==0){
			Dimmer3port&=(~(1<<D4_1_pos));
			Dimmer3port|=(1<<D4_2_pos);
			Dimmer3port|=(1<<D4_3_pos);
		}
		else if(strcmp(input,"AB")==0){
			Dimmer3port|=(1<<D4_1_pos);
			Dimmer3port&=(~(1<<D4_2_pos));
			Dimmer3port|=(1<<D4_3_pos);
		}
		else if(strcmp(input,"BB")==0){
			Dimmer3port&=(~(1<<D4_1_pos));
			Dimmer3port&=(~(1<<D4_2_pos));
			Dimmer3port|=(1<<D4_3_pos);
		}
		else if(strcmp(input,"BC")==0){
			Dimmer3port|=(1<<D4_1_pos);
			Dimmer3port|=(1<<D4_2_pos);
			Dimmer3port&=(~(1<<D1_3_pos));
		}
		else if(strcmp(input,"CC")==0){
			Dimmer3port&=(~(1<<D4_1_pos));
			Dimmer3port|=(1<<D4_2_pos);
			Dimmer3port&=(~(1<<D4_3_pos));
		}
		else if(strcmp(input,"CD")==0){
			Dimmer3port|=(1<<D4_1_pos);
			Dimmer3port&=(~(1<<D4_2_pos));
			Dimmer3port&=(~(1<<D4_3_pos));
		}
		else if(strcmp(input,"DD")==0){			
			Dimmer3port&=(~(1<<D4_1_pos));
			Dimmer3port&=(~(1<<D4_2_pos));
			Dimmer3port&=(~(1<<D4_3_pos));
		}
		else{
			Dimmer3port|=(1<<D4_1_pos);
			Dimmer3port|=(1<<D4_2_pos);
			Dimmer3port|=(1<<D4_3_pos);
		}
		
	}

}


/*_________________________________________________________________________________________*/
#endif

