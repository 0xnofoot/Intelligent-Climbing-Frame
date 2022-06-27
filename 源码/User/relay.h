#ifndef __RELAY_H
#define __RELAY_H

#include "main.h"

/*���ü̵������FLASH �����ַ(����Ϊ4�ı���������������,Ҫ���ڱ�������ռ�õ�������.
	����,д������ʱ��,���ܻᵼ�²�����������,�Ӷ����𲿷ֳ���ʧ.��������.
*/
#define FLASH_VALUE_RELAY1  0X08030000 	//Relay1 flash��ַ
										
#define FLASH_VALUE_RELAY2  0X08040000 	//Relay2 flash��ַ
							
							
void Relay_Init(void);
void Relay1_Open(void);
void Relay1_Close(void);
void Relay2_Open(void);
void Relay2_Close(void);

#endif /*__RELAY_H*/

