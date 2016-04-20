#ifndef __ESP_HEADER__
#define __ESP_HEADER__

void esp_init();

void esp_send_cmd(char data[]);
void esp_write(char data[], unsigned short size);

void esp_rst();

// wifi layer
typedef enum
{
	ESP_MODE_STA = 0,
	ESP_MODE_AP,
	ESP_MODE_STA_AP
} ESP_MODE;
void esp_set_mode(ESP_MODE mode);
unsigned char esp_connect_ap(char ssid[], char pw[]);		// warning, be careful to special car, protect with backslash
unsigned char esp_disconnect_ap();

// tcp/ip layer
unsigned char esp_open_tcp_socket(char ip_domain[], unsigned short port);
unsigned char esp_open_udp_socket(char ip_domain[], unsigned short port, unsigned short localPort, unsigned char mode);
void esp_close_socket(unsigned char sock);
void esp_write_socket(unsigned char sock, char data[], unsigned short size);
void esp_write_socket_string(unsigned char sock, char str[]);

typedef enum 
{
	FSM_UNKNOW = 0,
	FSM_WAITING_VALIDATE,
	FSM_START,
	
	FSM_OK_O,
	FSM_OK_K,
	
	FSM_SENDOK_S,
	FSM_SENDOK_E,
	FSM_SENDOK_N,
	FSM_SENDOK_D,
	FSM_SENDOK_Sp,
	FSM_SENDOK_O,
	FSM_SENDOK_K,
	
	FSM_ERROR_E,
	FSM_ERROR_R1,
	FSM_ERROR_R2,
	FSM_ERROR_O,
	FSM_ERROR_R3,
	
	FSM_PLUS,
	
	FSM_IPD_I,
	FSM_IPD_P,
	FSM_IPD_D,
	FSM_IPD_COMMA_1,
	FSM_IPD_SOCKET_DIGIT,
	FSM_IPD_COMMA_2,
	FSM_IPD_SIZE_DIGITS,
	FSM_PACKET_RX,
	FSM_RX_COMPLETE	
	
} WIFIstatus;

typedef enum
{
	WIFI_STATE_NONE = 0,
	WIFI_STATE_OK,
	WIFI_STATE_ERROR,
	WIFI_STATE_RECEIVE_DATA,
	WIFI_STATE_SEND_DATA,
	WIFI_STATE_SEND_OK
	
} WIFI_STATE;

void wait_ok();
unsigned char getRec();
WIFI_STATE get_state();
unsigned char getRecSocket();

char *getRecData();
unsigned short getRecSize();

#endif   //__ESP_HEADER__