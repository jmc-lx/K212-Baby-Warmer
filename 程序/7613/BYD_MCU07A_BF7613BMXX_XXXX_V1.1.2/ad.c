#include "Config.h"


uchar xdata adc_NTC_Temp;
uint xdata	ad_result_max,ad_result_min,ad_result_sum;
uint xdata	ad_result,ad_NTC_value,adc_Temp_Step;

code  uint  Temp_tab[]={ 
TEMP0, TEMP1, TEMP2, TEMP3, TEMP4, TEMP5, TEMP6, TEMP7, TEMP8, TEMP9,TEMP10,
TEMP11,TEMP12,TEMP13,TEMP14,TEMP15,TEMP16,TEMP17,TEMP18,TEMP19,TEMP20,
TEMP21,TEMP22,TEMP23,TEMP24,TEMP25,TEMP26,TEMP27,TEMP28,TEMP29,TEMP30,
TEMP31,TEMP32,TEMP33,TEMP34,TEMP35,TEMP36,TEMP37,TEMP38,TEMP39,TEMP40,
TEMP41,TEMP42,TEMP43,TEMP44,TEMP45,TEMP46,TEMP47,TEMP48,TEMP49,TEMP50,
TEMP51,TEMP52,TEMP53,TEMP54,TEMP55,TEMP56,TEMP57,TEMP58,TEMP59,TEMP60,
TEMP61,TEMP62,TEMP63,TEMP64,TEMP65,TEMP66,TEMP67,TEMP68,TEMP69,TEMP70,
TEMP71,TEMP72,TEMP73,TEMP74,TEMP75,TEMP76,TEMP77,TEMP78,TEMP79,TEMP80,
TEMP81,TEMP82,TEMP83,TEMP84,TEMP85,TEMP86,TEMP87,TEMP88,TEMP89,TEMP90,
TEMP91,TEMP92,TEMP93,TEMP94,TEMP95,TEMP96,TEMP97,TEMP98,TEMP99,TEMP100,
TEMP101,TEMP102,TEMP103,TEMP104,TEMP105,TEMP106,TEMP107,TEMP108,TEMP109,TEMP110,TEMP249,TEMP250,
};

uint Temp_Lookup_dichotomy(uint ADchanbufer) {
		 uint   Tempchanbufer;
 if(ADchanbufer>TEMP50){
				Tempchanbufer=0;
			}
			else if(ADchanbufer>TEMP100){
				Tempchanbufer=50;
			}
			else if(ADchanbufer>TEMP150){
				Tempchanbufer=100;
			}
			else if(ADchanbufer>TEMP200){
				Tempchanbufer=150;
			}
			else if(ADchanbufer>TEMP230){
				Tempchanbufer=200; 
			}
			else if(ADchanbufer>TEMP250){
				Tempchanbufer=230; 
			}/**/
			else
				Tempchanbufer=250; 
			while(Temp_tab[Tempchanbufer]>ADchanbufer&&Tempchanbufer<250){
				 Tempchanbufer++;
			}
			return (Tempchanbufer);
			
}





void adc_samp(void)
{
	ad_result=Get_ADC(16)>>2;
	if(adc_Temp_Step == 0){
		ad_result_max = ad_result;
		ad_result_min = ad_result;
	}
	else{
		if(ad_result_max < ad_result)
			ad_result_max = ad_result;
		
		if(ad_result_min > ad_result)
			ad_result_min = ad_result;
		
		
	}
		ad_result_sum = (ad_result_sum + ad_result);	
	adc_Temp_Step++;
	if(adc_Temp_Step>=20){
		adc_Temp_Step=0;

		ad_result_sum = (ad_result_sum - ad_result_min - ad_result_max);
		ad_result_sum = (ad_result_sum / 18);

		ad_NTC_value = ad_result_sum; 
		ad_result_sum=0;

		adc_NTC_Temp=Temp_Lookup_dichotomy(ad_NTC_value);
		}
}







