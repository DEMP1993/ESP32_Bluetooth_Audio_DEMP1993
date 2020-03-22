#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include "esp_log.h"

#include "esp_bt.h"
#include "bt_app_core.h"
#include "bt_app_av.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "esp_a2dp_api.h"
#include "esp_avrc_api.h"
#include "driver/i2s.h"
#include "driver/gpio.h"
#include <driver/can.h>
#include "driver/i2c.h"

int time_d=0;

void id1(void *pvParameter)	//Debug
{
	while (1)
	{
		time_d++;
		vTaskDelay(100 / portTICK_PERIOD_MS);
		printf("CPU1 IDLE in mS: %d \n",time_d);
	}
	
}

void id0(void *pvParameter)	//Debug
{
	while (1)
	{
		time_d++;
		vTaskDelay(100 / portTICK_PERIOD_MS);
		printf("CPU0 IDLE in mS: %d \n",time_d);
	}
	
}

void remote(void *pvParameter)	//Works on the second core (A2DP and main on first one)
{


	//XSMT Pin(DAC) config. (D17)
	gpio_config_t xsmt_conf;
	xsmt_conf.intr_type = GPIO_PIN_INTR_DISABLE;
	xsmt_conf.mode = GPIO_MODE_OUTPUT;
	xsmt_conf.pin_bit_mask = 1<<17;
	gpio_config(&xsmt_conf);
	gpio_set_level(17,1);	//D17 auf High(1)

	//tactile button sw1 (D22)
	gpio_config_t sw1_conf;
	sw1_conf.intr_type = GPIO_PIN_INTR_DISABLE;
	sw1_conf.mode = GPIO_MODE_INPUT;
	sw1_conf.pin_bit_mask = 1<<22;
    sw1_conf.pull_down_en = 0;
    sw1_conf.pull_up_en = 1;
	gpio_config(&sw1_conf);

	//tactile button sw2 (D23)
	gpio_config_t sw2_conf;
	sw2_conf.intr_type = GPIO_PIN_INTR_DISABLE;
	sw2_conf.mode = GPIO_MODE_INPUT;
	sw2_conf.pin_bit_mask = 1<<23;
    sw2_conf.pull_down_en = 0;
    sw2_conf.pull_up_en = 1;
	gpio_config(&sw2_conf);

	int gpio22_time=0;
	int gpio23_time=0;
	int gpio22_level=1;
	int gpio23_level=1;

	//int title_time=0;

	while(1)
	{
	    vTaskDelay(100 / portTICK_PERIOD_MS);

		/*if((title_time+1000000)<esp_timer_get_time())	//request the titel over AVRC every 1s//DBG
		{
			esp_avrc_ct_send_metadata_cmd(2,ESP_AVRC_MD_ATTR_TITLE);
			title_time=esp_timer_get_time();
		}*/

		gpio22_level=gpio_get_level(22);	//get GPIO22 level
		gpio23_level=gpio_get_level(23);	//get GPIO23 level

		//Sends Command over AVRCP if SW1 is pressed
		if(gpio22_level==0 && (gpio22_time+1000000)<esp_timer_get_time())
		{
			esp_err_t e_state=esp_avrc_ct_send_passthrough_cmd(1,ESP_AVRC_PT_CMD_PLAY,ESP_AVRC_PT_CMD_STATE_PRESSED);
			printf("Error State: %s \n",esp_err_to_name(e_state));
			gpio22_time=esp_timer_get_time();
			printf("GPIO22 Triggered!\n");
		}

		//Sends Command over AVRCP if SW2 is pressed
		if(gpio23_level==0 && (gpio23_time+1000000)<esp_timer_get_time())
		{
			esp_err_t e_state=esp_avrc_ct_send_passthrough_cmd(0,ESP_AVRC_PT_CMD_PAUSE,ESP_AVRC_PT_CMD_STATE_PRESSED);
			printf("Error State: %s \n",esp_err_to_name(e_state));
			gpio23_time=esp_timer_get_time();
			printf("GPIO23 Triggered! \n");
		}
	}

}


/* event for handler "bt_av_hdl_stack_up */
enum {
    BT_APP_EVT_STACK_UP = 0,
};

/* handler for bluetooth stack enabled events */
static void bt_av_hdl_stack_evt(uint16_t event, void *p_param);


void app_main()
{
	/* Initialize NVS — it is used to store PHY calibration data */
	    esp_err_t err = nvs_flash_init();
	    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
	        ESP_ERROR_CHECK(nvs_flash_erase());
	        err = nvs_flash_init();
	    }
	    ESP_ERROR_CHECK(err);

	    i2s_config_t i2s_config = {
	        .mode = I2S_MODE_MASTER | I2S_MODE_TX,                                  // Only TX
	        .sample_rate = 44100,
	        .bits_per_sample = 32,
	        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,                           //2-channels
	        .communication_format = I2S_COMM_FORMAT_I2S_MSB,
	        .dma_buf_count = 1024,
	        .dma_buf_len = 32768,
	        .intr_alloc_flags = 0,                                                  //Default interrupt priority
	        .tx_desc_auto_clear = true                                              //Auto clear tx descriptor on underflow
	    };


	    i2s_driver_install(0, &i2s_config, 0, NULL);
	    i2s_pin_config_t pin_config = {
	        .bck_io_num = 19 /*CONFIG_I2S_BCK_PIN 19*/,
	        .ws_io_num = 5/*CONFIG_I2S_LRCK_PIN 5*/,
	        .data_out_num = 18 /*CONFIG_I2S_DATA_PIN 18*/,
	        .data_in_num = -1  //Not used
	    };
	    i2s_set_pin(0, &pin_config);


	    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_BLE));

	    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
	    if ((err = esp_bt_controller_init(&bt_cfg)) != ESP_OK) {
	        ESP_LOGE(BT_AV_TAG, "%s initialize controller failed: %s\n", __func__, esp_err_to_name(err));
	        return;
	    }

	    if ((err = esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT)) != ESP_OK) {
	        ESP_LOGE(BT_AV_TAG, "%s enable controller failed: %s\n", __func__, esp_err_to_name(err));
	        return;
	    }

	    if ((err = esp_bluedroid_init()) != ESP_OK) {
	        ESP_LOGE(BT_AV_TAG, "%s initialize bluedroid failed: %s\n", __func__, esp_err_to_name(err));
	        return;
	    }

	    if ((err = esp_bluedroid_enable()) != ESP_OK) {
	        ESP_LOGE(BT_AV_TAG, "%s enable bluedroid failed: %s\n", __func__, esp_err_to_name(err));
	        return;
	    }

	    /* create application task */
	    bt_app_task_start_up();

	    /* Bluetooth device name, connection mode and profile set up */
	    bt_app_work_dispatch(bt_av_hdl_stack_evt, BT_APP_EVT_STACK_UP, NULL, 0, NULL);

	#if (CONFIG_BT_SSP_ENABLED == true)
	    /* Set default parameters for Secure Simple Pairing */
	    esp_bt_sp_param_t param_type = ESP_BT_SP_IOCAP_MODE;
	    esp_bt_io_cap_t iocap = ESP_BT_IO_CAP_IO;
	    esp_bt_gap_set_security_param(param_type, &iocap, sizeof(uint8_t));
	#endif

	    /*
	     * Set default parameters for Legacy Pairing
	     * Use fixed pin code
	     */
	    esp_bt_pin_type_t pin_type = ESP_BT_PIN_TYPE_FIXED;
	    esp_bt_pin_code_t pin_code;
	    pin_code[0] = '1';
	    pin_code[1] = '2';
	    pin_code[2] = '3';
	    pin_code[3] = '4';
	    esp_bt_gap_set_pin(pin_type, 4, pin_code);

    //Code added to example-----------------------------------------------------------

    xTaskCreatePinnedToCore(&remote, "remote", 8048, NULL, 2, NULL,1);

	//xTaskCreatePinnedToCore(&id1, "id1", 4096, NULL, 0, NULL, 1);	//DEBUG CPU Usage Core1
	//xTaskCreatePinnedToCore(&id0, "id0", 4096, NULL, 0, NULL, 0);	//DEBUG CPU Usage Core0

    //--------------------------------

}

void bt_app_gap_cb(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param)
{
    switch (event) {
    case ESP_BT_GAP_AUTH_CMPL_EVT: {
        if (param->auth_cmpl.stat == ESP_BT_STATUS_SUCCESS) {
            ESP_LOGI(BT_AV_TAG, "authentication success: %s", param->auth_cmpl.device_name);
            esp_log_buffer_hex(BT_AV_TAG, param->auth_cmpl.bda, ESP_BD_ADDR_LEN);
        } else {
            ESP_LOGE(BT_AV_TAG, "authentication failed, status:%d", param->auth_cmpl.stat);
        }
        break;
    }

#if (CONFIG_BT_SSP_ENABLED == true)
    case ESP_BT_GAP_CFM_REQ_EVT:
        ESP_LOGI(BT_AV_TAG, "ESP_BT_GAP_CFM_REQ_EVT Please compare the numeric value: %d", param->cfm_req.num_val);
        esp_bt_gap_ssp_confirm_reply(param->cfm_req.bda, true);
        break;
    case ESP_BT_GAP_KEY_NOTIF_EVT:
        ESP_LOGI(BT_AV_TAG, "ESP_BT_GAP_KEY_NOTIF_EVT passkey:%d", param->key_notif.passkey);
        break;
    case ESP_BT_GAP_KEY_REQ_EVT:
        ESP_LOGI(BT_AV_TAG, "ESP_BT_GAP_KEY_REQ_EVT Please enter passkey!");
        break;
#endif

    default: {
        ESP_LOGI(BT_AV_TAG, "event: %d", event);
        break;
    }
    }
    return;
}
static void bt_av_hdl_stack_evt(uint16_t event, void *p_param)
{
    ESP_LOGD(BT_AV_TAG, "%s evt %d", __func__, event);
    switch (event) {
    case BT_APP_EVT_STACK_UP: {
        /* set up device name */
        char *dev_name = "ESP_SPEAKER";
        esp_bt_dev_set_device_name(dev_name);

        esp_bt_gap_register_callback(bt_app_gap_cb);
        /* initialize A2DP sink */
        esp_a2d_register_callback(&bt_app_a2d_cb);
        esp_a2d_sink_register_data_callback(bt_app_a2d_data_cb);
        esp_a2d_sink_init();

        /* initialize AVRCP controller */
        esp_avrc_ct_init();
        esp_avrc_ct_register_callback(bt_app_rc_ct_cb);

        /* set discoverable and connectable mode, wait to be connected */
        //esp_bt_gap_set_scan_mode(ESP_BT_SCAN_MODE_CONNECTABLE_DISCOVERABLE);
        esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);
        break;
    }
    default:
        ESP_LOGE(BT_AV_TAG, "%s unhandled evt %d", __func__, event);
        break;
    }
}

