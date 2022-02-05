#include "bsp_beep.h"
void beep_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0);
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0x10b0);
    
    GPIO5->GDIR |= (1<<1);/*设置为输出*/
    GPIO5->DR |= (1<<1);/*设置为高电平，关闭蜂鸣器*/

}
void beep_switch(int beep_status)
{
    if(beep_status==ON)
    {
        GPIO5->DR &= ~(1<<1);
    }
    else if(beep_status==OFF)
    {
        GPIO5->DR |= (1<<1);
    }
}
