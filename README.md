# raspberry_spi  
SPI user interface for raspberrypi (based on ioctl)  
GPIO user interface for raspberrypi (based on ioctl)  

Test environment is Raspberry Pi Zero W with Raspbian GNU/Linux 9 (stretch)  
ZJY_M270_ZK3V3(128x64) OLED with GT30L32S4W & SSD1325  

###   Interface with OLED
| NAME    |  BCM  |   PHY | FUNCTION  |
| :------ | ----: | ----: | ---------:|
| MOSI    | ----  |     19|        SDA|
| MISO    | ----  |     21|        FS0|
| SCLK    | ----  |     23|        SCL|
| CE0     | ----  |     24|        CS1|
| CE1     | ----  |     26|        CS2|
| GPIO.0  |     17|     11|         DC|
| GPIO.1  |     18|     12|        RES|
