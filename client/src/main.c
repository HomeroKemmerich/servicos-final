// HTTP Client - FreeRTOS ESP IDF - GET

#include <stdio.h>
#include <time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_http_client.h"
#include "constants/connection.h"

#define BASE_URL "http://192.168.242.203:8000"
#define SHORT_DELAY 1000
#define LONG_DELAY 5000

//#region WiFi
static void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    switch (event_id)
    {
    case WIFI_EVENT_STA_START:
        printf("WiFi connecting ... \n");
        break;
    case WIFI_EVENT_STA_CONNECTED:
        printf("WiFi connected ... \n");
        break;
    case WIFI_EVENT_STA_DISCONNECTED:
        printf("WiFi lost connection ... \n");
        break;
    case IP_EVENT_STA_GOT_IP:
        printf("WiFi got IP ... \n\n");
        break;
    default:
        break;
    }
}

void wifi_connection()
{
    // 1 - Wi-Fi/LwIP Init Phase
    esp_netif_init();                    // TCP/IP initiation 					s1.1
    esp_event_loop_create_default();     // event loop 			                s1.2
    esp_netif_create_default_wifi_sta(); // WiFi station 	                    s1.3
    wifi_init_config_t wifi_initiation = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&wifi_initiation); // 					                    s1.4
    // 2 - Wi-Fi Configuration Phase
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler, NULL);
    wifi_config_t wifi_configuration = {
        .sta = {
            .ssid = SSID,
            .password = PASS}};
    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_configuration);
    // 3 - Wi-Fi Start Phase
    esp_wifi_start();
    // 4- Wi-Fi Connect Phase
    esp_wifi_connect();
}
//#endregion

//#region Métodos HTTP
esp_err_t client_event_get_handler(esp_http_client_event_handle_t evt)
{
    switch (evt->event_id)
    {
    case HTTP_EVENT_ON_DATA:
        printf("HTTP_EVENT_ON_DATA: %.*s\n", evt->data_len, (char *)evt->data);
        break;

    default:
        break;
    }
    return ESP_OK;
}

static void rest_get(char* path)
{
    char url[100];
    sprintf(url, "%s%s", BASE_URL, path);
    strcpy(url, BASE_URL);
    strcat(url, path);

    esp_http_client_config_t config_get = {
        .url = url,
        .method = HTTP_METHOD_GET,
        .cert_pem = NULL,
        .event_handler = client_event_get_handler
    };
        
    esp_http_client_handle_t client = esp_http_client_init(&config_get);
    esp_http_client_perform(client);
    esp_http_client_cleanup(client);
}

esp_err_t client_event_post_handler(esp_http_client_event_handle_t evt)
{
    switch (evt->event_id)
    {
    case HTTP_EVENT_ON_DATA:
        printf("HTTP_EVENT_ON_DATA: %.*s\n", evt->data_len, (char *)evt->data);
        break;

    default:
        break;
    }
    return ESP_OK;
}

static void rest_post(char* path, char* data)
{
    char url[100];
    sprintf(url, "%s%s", BASE_URL, path);
    strcpy(url, BASE_URL);
    strcat(url, path);

    esp_http_client_config_t config_post = {
        .url = url,
        .method = HTTP_METHOD_POST,
        .cert_pem = NULL,
        .event_handler = client_event_post_handler
    };
        
    esp_http_client_handle_t client = esp_http_client_init(&config_post);

    char  *post_data = ("{\"id\": 2,\"name\": \"Homero\",\"latitude\": 0.0,\"longitude\": 0.0,\"status\": \"working\",\"last_updated\": \"2023-10-19T00:00:00\",\"created\": \"2023-10-19T00:00:00\"}");
    esp_http_client_set_post_field(client, post_data, strlen(post_data));
    esp_http_client_set_header(client, "Content-Type", "application/json");

    esp_http_client_perform(client);
    esp_http_client_cleanup(client);
}

void rest_put(char *path, char *data)
{
    char url[100];
    sprintf(url, "%s%s", BASE_URL, path);
    strcpy(url, BASE_URL);
    strcat(url, path);

    esp_http_client_config_t config_put = {
        .url = url,
        .method = HTTP_METHOD_PUT,
        .cert_pem = NULL,
        .event_handler = client_event_post_handler
    };
        
    esp_http_client_handle_t client = esp_http_client_init(&config_put);

    char  *post_data = "{\"id\": 2,\"name\": \"Homero\",\"latitude\": 0.0,\"longitude\": 0.0,\"status\": \"working\",\"last_updated\": \"2023-10-19T11:11:11\",\"created\": \"2023-10-19T00:00:00\"}";
    esp_http_client_set_post_field(client, post_data, strlen(post_data));
    esp_http_client_set_header(client, "Content-Type", "application/json");

    esp_http_client_perform(client);
    esp_http_client_cleanup(client);
}

void rest_delete(char *path)
{
    char url[100];
    sprintf(url, "%s%s", BASE_URL, path);
    strcpy(url, BASE_URL);
    strcat(url, path);

    esp_http_client_config_t config_delete = {
        .url = url,
        .method = HTTP_METHOD_DELETE,
        .cert_pem = NULL,
        .event_handler = client_event_post_handler
    };
        
    esp_http_client_handle_t client = esp_http_client_init(&config_delete);

    esp_http_client_perform(client);
    esp_http_client_cleanup(client);
}
//#endregion

void app_main(void)
{
    nvs_flash_init();
    wifi_connection();

    vTaskDelay(2000 / portTICK_PERIOD_MS);
    printf("WIFI was initiated ...........\n\n");

    /*
        Sequência de ações:
            - [x] Acessa o recurso raiz
            - [x] Cria um novo recurso
            - [x] Acessa o recurso criado
            - [x] Cria um novo recurso
            - [x] Lista todos os recursos
            - [x] Altera o segundo recurso
            - [x] Exclui o primeiro recurso
            - [x] Lista todos os recursos
    */
    int machine_id = 0;
    while(1){        
        char machine_path[100] = "/machines/", machine_path_id[100];
        sprintf(machine_path_id, "/machines/%d", machine_id);
        


        printf("GET /         ...........\n\n");
        rest_get("/");
        sys_delay_ms(SHORT_DELAY);
        
        printf("POST /machines ...........\n\n");
        rest_post(machine_path, "");
        sys_delay_ms(SHORT_DELAY);

        printf("GET %s ...........\n\n", machine_path);
        rest_get(machine_path_id);
        sys_delay_ms(SHORT_DELAY);

        sprintf(machine_path_id, "/machines/%d", machine_id+1);
        printf("POST /machines ...........\n\n");
        rest_post(machine_path_id, "");
        sys_delay_ms(SHORT_DELAY);

        printf("GET /machines ...........\n\n");
        rest_get(machine_path);
        sys_delay_ms(SHORT_DELAY);

        printf("PUT %s ...........\n\n", machine_path_id);
        rest_put(machine_path_id, "");
        sys_delay_ms(SHORT_DELAY);

        printf("DELETE %s ...........\n\n", machine_path);
        rest_delete(machine_path_id);
        sys_delay_ms(SHORT_DELAY);

        printf("GET /machines ...........\n\n");
        rest_get("/machines/");
        sys_delay_ms(SHORT_DELAY);

        machine_id++;
        sys_delay_ms(LONG_DELAY);
    }
}