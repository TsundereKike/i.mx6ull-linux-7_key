#include "bsp_key.h"
void key_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18,0);

    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18,0xf080);

    GPIO1->GDIR &= ~(1<<18);
}
int read_key(void)
{
    int ret = 0;
    ret = ((GPIO1->DR) >> 18) & 0x01;
    return ret;
}
int get_key_value(void)
{
    int ret = 0;
    static unsigned char key_release = 1;/*按键释放状态，默认释放*/
    if((key_release==1) && (read_key()==0))/*按键按下*/
    {
        delay_ms(10);
        key_release = 0;
        if(read_key()==0)/*延时10ms后，GPIO引脚依然被拉低*/
        {
            ret =  KEY0_VALUE;/*按键0被有效按下*/
        }
    }
    else if(read_key()==1)
    {
        key_release = 1;
        ret = KEY_NONE;
    }
    return ret;
}