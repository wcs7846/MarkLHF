/* Includes ------------------------------------------------------------------*/
#include "rtc.h"
/*----------------------------------------------------------------------------*/
extern RTC_HandleTypeDef hrtc;
RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;
RTC_AlarmTypeDef sAlarm;
/*----------------------------------------------------------------------------*/
void RTC_Config(void)
{
		hrtc.Instance = RTC;
		hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
		hrtc.Init.AsynchPrediv = 127;
		hrtc.Init.SynchPrediv = 255;
		hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
		hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
		hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
		HAL_RTC_Init(&hrtc);

		sTime.Hours = 0x02;
		sTime.Minutes = 0x20;
		sTime.Seconds = 0;
		sTime.SubSeconds = 0;
		sTime.TimeFormat = RTC_HOURFORMAT12_AM;
		sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
		sTime.StoreOperation = RTC_STOREOPERATION_RESET;
		HAL_RTC_SetTime(&hrtc, &sTime, FORMAT_BCD);

		sDate.WeekDay = RTC_WEEKDAY_MONDAY;
		sDate.Month = RTC_MONTH_JANUARY;
		sDate.Date = 0x18;
		sDate.Year = 0x14;
		HAL_RTC_SetDate(&hrtc, &sDate, FORMAT_BCD);

		/**Enable the Alarm A 
		*/
		sAlarm.AlarmTime.Hours = 0x02;
		sAlarm.AlarmTime.Minutes = 0x20;
		sAlarm.AlarmTime.Seconds = 0x30;
		sAlarm.AlarmTime.SubSeconds = 0x56;
		sAlarm.AlarmTime.TimeFormat = RTC_HOURFORMAT12_AM;
		sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
		sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
		sAlarm.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY;
		sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_None;
		sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
		sAlarm.AlarmDateWeekDay = RTC_WEEKDAY_MONDAY;
		sAlarm.Alarm = RTC_ALARM_A;
		HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, FORMAT_BCD);
		//对屏幕刷新一次
		OLED_Fill(0xff);
		HAL_Delay(200);
		OLED_Fill(0x00);
		//
		OLED_ShowStr(0,0,"Year:",1);
		OLED_ShowStr(0,1,"Month:",1);
		OLED_ShowStr(0,2,"Day:",1);
		OLED_ShowStr(0,3,"  :  :  ",1);
};

void RTC_TimeShow(uint8_t* Time)
{
	/* Get the RTC current Time */
	HAL_RTC_GetTime(&hrtc, &sTime, FORMAT_BIN);
	/* Display time Format : hh:mm:ss */
	Time[2]=sTime.Hours;
	Time[1]=sTime.Minutes;
	Time[0]=sTime.Seconds;
	if(sTime.Hours<10)
	{
		OLED_ShowNum(0*6,3,0);
		OLED_ShowNum(1*6,3,sTime.Hours);
	}else
	{
		OLED_ShowNum(0*6,3,sTime.Hours/10);
		OLED_ShowNum(1*6,3,sTime.Hours-(sTime.Hours/10)*10);
	}
	if(sTime.Minutes<10)
	{
		OLED_ShowNum(3*6,3,0);
		OLED_ShowNum(4*6,3,sTime.Minutes);
	}else
	{
		OLED_ShowNum(3*6,3,(sTime.Minutes)/10);
		OLED_ShowNum(4*6,3,sTime.Minutes-((sTime.Minutes)/10)*10);
	}
	if(sTime.Seconds<10)
	{
		OLED_ShowNum(6*6,3,0);
		OLED_ShowNum(7*6,3,sTime.Seconds);
	}else
	{
		OLED_ShowNum(6*6,3,(sTime.Seconds)/10);
		OLED_ShowNum(7*6,3,sTime.Seconds-((sTime.Seconds)/10)*10);
	}
};
void RTC_DateShow(uint8_t* Date)
{
	/* Get the RTC current Date */
	HAL_RTC_GetDate(&hrtc, &sDate, FORMAT_BIN);
	/* Display time Format : Year
													 Month
													 Day */
	Date[2]=sDate.Year;
	Date[1]=sDate.Month;
	Date[0]=sDate.Date;
	if(sDate.Year<10)
	{
		OLED_ShowNum(5*6,0,0);
		OLED_ShowNum(6*6,0,sDate.Year);
	}else
	{
		OLED_ShowNum(5*6,0,(sDate.Year)/10);
		OLED_ShowNum(6*6,0,sDate.Year-((sDate.Year)/10)*10);
	}
	if(sDate.Month<10)
	{
		OLED_ShowNum(6*6,1,0);
		OLED_ShowNum(7*6,1,sDate.Month);
	}else
	{
		OLED_ShowNum(6*6,1,(sDate.Month)/10);
		OLED_ShowNum(7*6,1,sDate.Month-((sDate.Month)/10)*10);
	}
	if(sDate.WeekDay)
	{
		OLED_ShowNum(4*6,2,0);
		OLED_ShowNum(5*6,2,sDate.WeekDay);
	}else
	{
		OLED_ShowNum(5*6,2,(sDate.WeekDay)/10);
		OLED_ShowNum(4*6,2,sDate.WeekDay-((sDate.WeekDay)/10)*10);
	}
}
void RTC_AlarmShow(void)
{
	/* Get the RTC Alarm_A Time */
	HAL_RTC_GetAlarm(&hrtc,&sAlarm,RTC_ALARM_A,FORMAT_BIN);
	/* Display time Format : hh:mm:ss */
	OLED_ShowStr(0,4,"The Alarm Clock",1);
	OLED_ShowStr(0,5,"  :  :  ",1);
	if(sAlarm.AlarmTime.Hours<10)
	{
		OLED_ShowNum(0*6,5,0);
		OLED_ShowNum(1*6,5,sAlarm.AlarmTime.Hours);
	}else
	{
		OLED_ShowNum(0*6,5,sAlarm.AlarmTime.Hours/10);
		OLED_ShowNum(1*6,5,sAlarm.AlarmTime.Hours-(sAlarm.AlarmTime.Hours/10)*10);
	}
	if(sAlarm.AlarmTime.Minutes<10)
	{
		OLED_ShowNum(3*6,5,0);
		OLED_ShowNum(4*6,5,sAlarm.AlarmTime.Minutes);
	}else
	{
		OLED_ShowNum(3*6,5,(sAlarm.AlarmTime.Minutes)/10);
		OLED_ShowNum(4*6,5,sAlarm.AlarmTime.Minutes-((sAlarm.AlarmTime.Minutes)/10)*10);
	}
	if(sAlarm.AlarmTime.Seconds<10)
	{
		OLED_ShowNum(6*6,5,0);
		OLED_ShowNum(7*6,5,sAlarm.AlarmTime.Seconds);
	}else
	{
		OLED_ShowNum(6*6,5,(sAlarm.AlarmTime.Seconds)/10);
		OLED_ShowNum(7*6,5,sAlarm.AlarmTime.Seconds-((sAlarm.AlarmTime.Seconds)/10)*10);
	}
};
void RTC_SetTime(uint16_t SetHour,uint16_t SetMinture,uint16_t SetSecond)
{
	sTime.Hours=SetHour;
	sTime.Minutes=SetMinture;
	sTime.Seconds=SetSecond;
	/*--------------------------------------*/
	HAL_RTC_SetTime(&hrtc,&sTime,FORMAT_BIN);
};
//这个现在数值有点问题需要调整一下
void RTC_SetDate(uint16_t SetYear,uint16_t SetMonth,uint16_t SetDay)
{
	sDate.WeekDay=SetDay;
	sDate.Year=SetYear;
	sDate.Month=SetMonth;
	/*--------------------------------------*/
	HAL_RTC_SetDate(&hrtc,&sDate,FORMAT_BIN);
}

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
	OLED_ShowStr(0,6,"THE ALARM IS GET!",1);
	RTC_SetTime(21,20,30);
	RTC_SetDate(14,7,23);
};
