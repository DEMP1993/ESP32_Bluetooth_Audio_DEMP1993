deps_config := \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\app_trace\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\aws_iot\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\bt\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\driver\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\efuse\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\esp32\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\esp_adc_cal\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\esp_event\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\esp_http_client\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\esp_http_server\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\esp_https_ota\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\espcoredump\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\ethernet\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\fatfs\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\freemodbus\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\freertos\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\heap\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\libsodium\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\log\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\lwip\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\mbedtls\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\mdns\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\mqtt\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\nvs_flash\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\openssl\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\pthread\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\spi_flash\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\spiffs\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\tcpip_adapter\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\unity\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\vfs\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\wear_levelling\Kconfig \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\app_update\Kconfig.projbuild \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\bootloader\Kconfig.projbuild \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\esptool_py\Kconfig.projbuild \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\a2dp_sink\main\Kconfig.projbuild \
	C:\Users\forst\Desktop\esp32\home\MP1993\esp\esp-idf\components\partition_table\Kconfig.projbuild \
	/home/MP1993/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)

ifneq "$(IDF_TARGET)" "esp32"
include/config/auto.conf: FORCE
endif
ifneq "$(IDF_CMAKE)" "n"
include/config/auto.conf: FORCE
endif

$(deps_config): ;
