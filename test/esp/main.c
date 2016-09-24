#include <stdio.h>

#include "../../include/sys/buffer.h"
#include "../../include/driver/esp8266.h"

int main()
{
    puts("test\n");
    esp_init();
    
    esp_set_mode(ESP_MODE_STA);
    esp_connect_ap("wifi1", "pwd");
    esp_disconnect_ap();
    
    esp_close_socket(3);
    esp_write_socket_string(3, "cmd");
    
    return 0;
}