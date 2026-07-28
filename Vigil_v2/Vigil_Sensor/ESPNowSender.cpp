#include <esp_wifi.h>
#include "ESPNowSender.h"


ESPNowSender::ESPNowSender()
{
    uint8_t mac[] =
    {
        0x28,
        0x84,
        0x85,
        0x51,
        0xCE,
        0x6C
    };

    memcpy(receiverMAC, mac, 6);
}

bool ESPNowSender::begin()
{
    WiFi.mode(WIFI_STA);

    esp_wifi_set_channel(
        11,
        WIFI_SECOND_CHAN_NONE
    );

    if(esp_now_init() != ESP_OK)
        return false;

    esp_now_peer_info_t peerInfo = {};

    memcpy(
        peerInfo.peer_addr,
        receiverMAC,
        6
    );

    peerInfo.channel = 0;

    peerInfo.encrypt = false;

    if(
        esp_now_add_peer(&peerInfo)
        != ESP_OK
    )
    {
        return false;
    }

    return true;
}

void ESPNowSender::send(
    OccupancyData data
)
{
    esp_now_send(
        receiverMAC,
        (uint8_t*)&data,
        sizeof(data)
    );
}