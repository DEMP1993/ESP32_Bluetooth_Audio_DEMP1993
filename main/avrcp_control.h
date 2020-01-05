/*
 * avrcp_control.h
 *
 *  Created on: 14.03.2019
 *      Author: MP1993
 */
#include <stdio.h>
#include <esp_avrc_api.h>
#include <esp_timer.h>

int avrcp_play=0;
int64_t avrcp_play_starttime=0;
int avrcp_stop=0;
int64_t avrcp_stop_starttime=0;
int avrcp_next=0;
int64_t avrcp_next_starttime=0;
int avrcp_previous=0;
int64_t avrcp_previous_starttime=0;

#ifndef MAIN_AVRCP_CONTROL_H_
#define MAIN_AVRCP_CONTROL_H_

void avrcp_stop_send_activate()
{
	avrcp_stop=1;
}

void avrcp_play_send_activate()
{
	avrcp_play=1;
	//printf("%d \n",avrcp_play);
}

void avrcp_next_send_activate()
{
	avrcp_next=1;
}

void avrcp_previous_send_activate()
{
	avrcp_previous=1;
}

void avrcp_send_commands()
{

	//AVRCP STOP
	if(avrcp_stop==1 && avrcp_stop_starttime==0)//AVRCP Stop senden
	{
		esp_avrc_ct_send_passthrough_cmd(0,ESP_AVRC_PT_CMD_STOP,ESP_AVRC_PT_CMD_STATE_PRESSED);
		avrcp_stop_starttime=esp_timer_get_time();
		printf("Send AVRCP Stop!\n");
	}
	if((esp_timer_get_time()>avrcp_stop_starttime+10) &&(avrcp_stop==1)&& (avrcp_stop_starttime !=0))//AVRCP Stop beenden
	{
		esp_avrc_ct_send_passthrough_cmd(0,ESP_AVRC_PT_CMD_STOP,ESP_AVRC_PT_CMD_STATE_RELEASED);
		avrcp_stop=0;
		avrcp_stop_starttime=0;
		printf("Send AVRCP Stop!\n");
	}

	//AVRCP PLAY
	if(avrcp_play==1 && avrcp_play_starttime==0)//AVRCP Play senden
	{
		//AVRCP Play senden
		esp_avrc_ct_send_passthrough_cmd(1,ESP_AVRC_PT_CMD_PLAY,ESP_AVRC_PT_CMD_STATE_PRESSED);
		avrcp_play_starttime=esp_timer_get_time();
		printf("Send AVRCP Play!\n");
	}
	if((esp_timer_get_time()>avrcp_play_starttime+10) &&(avrcp_play==1)&& (avrcp_play_starttime !=0))//AVRCP Play beenden
	{
		esp_avrc_ct_send_passthrough_cmd(0,ESP_AVRC_PT_CMD_PLAY,ESP_AVRC_PT_CMD_STATE_RELEASED);
		avrcp_play=0;
		avrcp_play_starttime=0;
		printf("Send AVRCP Play!\n");
	}

	//AVRCP NEXT
	if(avrcp_next==1 && avrcp_next_starttime==0)//AVRCP naechstes Lied senden
	{
		esp_avrc_ct_send_passthrough_cmd(1,ESP_AVRC_PT_CMD_FORWARD,ESP_AVRC_PT_CMD_STATE_PRESSED);
		avrcp_next_starttime=esp_timer_get_time();
		printf("Send AVRCP Next!\n");
	}
	if((esp_timer_get_time()>avrcp_next_starttime+10) &&(avrcp_next==1)&& (avrcp_next_starttime !=0))//AVRCP naechstes Lied beenden
	{
		esp_avrc_ct_send_passthrough_cmd(0,ESP_AVRC_PT_CMD_FORWARD,ESP_AVRC_PT_CMD_STATE_RELEASED);
		avrcp_next=0;
		avrcp_next_starttime=0;
		printf("Send AVRCP Next!\n");
	}

	//AVRCP PREVIOUS
	if(avrcp_previous==1 && avrcp_previous_starttime==0)//AVRCP vorheriges Lied senden
	{
		esp_avrc_ct_send_passthrough_cmd(1,ESP_AVRC_PT_CMD_BACKWARD,ESP_AVRC_PT_CMD_STATE_PRESSED);
		avrcp_previous_starttime=esp_timer_get_time();
		printf("Send AVRCP PREVIOUS!\n");

	}
	if((esp_timer_get_time()>avrcp_previous_starttime+10) &&(avrcp_previous==1)&& (avrcp_previous_starttime !=0))//AVRCP vorheriges Lied beenden
	{
		esp_avrc_ct_send_passthrough_cmd(0,ESP_AVRC_PT_CMD_BACKWARD,ESP_AVRC_PT_CMD_STATE_RELEASED);
		avrcp_previous=0;
		avrcp_previous_starttime=0;
		printf("Send AVRCP PREVIOUS!\n");
	}
}






#endif /* MAIN_AVRCP_CONTROL_H_ */
