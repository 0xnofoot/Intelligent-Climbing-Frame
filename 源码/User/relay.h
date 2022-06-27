#ifndef __RELAY_H
#define __RELAY_H

#include "main.h"

/*设置继电器相关FLASH 保存地址(必须为4的倍数，且所在扇区,要大于本代码所占用到的扇区.
	否则,写操作的时候,可能会导致擦除整个扇区,从而引起部分程序丢失.引起死机.
*/
#define FLASH_VALUE_RELAY1  0X08030000 	//Relay1 flash地址
										
#define FLASH_VALUE_RELAY2  0X08040000 	//Relay2 flash地址
							
							
void Relay_Init(void);
void Relay1_Open(void);
void Relay1_Close(void);
void Relay2_Open(void);
void Relay2_Close(void);

#endif /*__RELAY_H*/

