#include "wifi_scan.h"
#include "ble_scan.h"
#include "mac_pool.h"
#include <SPI.h>
#include <TFT_eSPI.h>
#include <imagen.h>

#ifndef TFT_DISPOFF
#define TFT_DISPOFF 0x28
#endif

#ifndef TFT_SLPIN
#define TFT_SLPIN   0x10
#endif

#define ADC_EN          14
#define ADC_PIN         34
#define BUTTON_1        35
#define BUTTON_2        0

#define blue_width 129
#define blue_heigh 216

TFT_eSPI tft = TFT_eSPI(135, 240);

MACAddressPool pool(300000); // Age limit: 5 minutes

void setup() 
{
  Serial.begin(115200);
  wifi_scanner_setup();
  ble_scanner_setup(); 
  tft.begin();           //turn on display
  tft.setRotation(1);
  
  tft.fillScreen(TFT_WHITE);                //sets background  
  
 }

void loop() 
{
  while (true)
  {
    wifi_scan();
    ble_scan();
    Serial.print("ble count: ");Serial.println(pool.get_count(BT));
    tft.setCursor(50, 3);
    tft.print("ble:");  
    tft.setCursor(50, 13);
    tft.print(pool.get_count(BT));
    tft.print(" personas");  
    tft.setCursor(50, 23);
    tft.print("wifi:");  
    tft.setCursor(50, 33);
    tft.print(pool.get_count(BT));  
    tft.print(" personas");    
    tft.fillScreen(TFT_BLACK);

    drawArrayJpeg(myBitmap, sizeof(myBitmap), 2, 16); // Draw a jpeg image stored in memory at x,y
   
    //nbiot_transmit_message(pool.get_count(BT), pool.get_count(WIFI));
    pool.Purge();
    pool.Log();
  }
}