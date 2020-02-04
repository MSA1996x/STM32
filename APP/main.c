#include "APP/APP_H/main.h"


#define _EXTI_IMR_MR0 	BITBAND_PERI(EXTI_BASE + 0x00, 0)
#define _EXTI_RTSR_TR0 	BITBAND_PERI(EXTI_BASE + 0x08, 0)
#define _EXTI_EMR_MR0 	BITBAND_PERI(EXTI_BASE + 0x04, 0)


char Str[50];

/*
static RTOS_thread_t thread1;
static RTOS_stack_t thread1stack;
static RTOS_thread_t thread2;
static RTOS_stack_t thread2stack;
static RTOS_thread_t thread3;
static RTOS_stack_t thread3stack;

static RTOS_mutex_t mutex1;
static RTOS_semaphore_t semaphore1;
static RTOS_mailbox_t mailbox1;
static uint32_t mailbox1buffer[2];

void thread1function(void)
{
	while(1)
	{
		uint16_t ID = 0;
		char* Data;

		if(digitalRead(GPIOB, 12)){
			ID = 25;
			Data = "Node 1\0";
		}
		else{
			ID = 150;
			Data = "Node 2\0";
		}

		CAN1_Transmit(ID, ID_MODE_STANDARD, FRAME_MODE_DATA, MAILBOX_0, Data);

		PC13 ^= 1;
		RTOS_SVC_threadDelay(1000);
	}
}

void thread2function(void)
{

	while(1)
	{
		char Data[20];
		uint8_t DLC = 0;
		uint8_t FilterIndex = 0;

		if(CAN1_Receive(FIFO_NUM_0, Data, &DLC, &FilterIndex) == REC_SUCCESS){

			USART1_Send_Str("FI:");
			itoa(FilterIndex, Str, 10);
			USART1_Send_Str(Str);
			USART1_Send_Str(", ");

			USART1_Send_Str("DLC: ");
			itoa(DLC, Str, 10);
			USART1_Send_Str(Str);
			USART1_Send_Str(", ");

			USART1_Send_Str("Data: ");
			USART1_Send_Str(Data);
			USART1_Send_Ln();

		}

		RTOS_SVC_threadDelay(10);
	}
}


void thread3function(void)
{

  while(1)
  {

  }

}
*/






void SYS_BL_Jump(void){

	/*Disable Interrupts*/
	__disable_irq();

	/*Reset All Peripherals Are Used By The BL*/
	/*
	 * GPIO, DMA, USART
	 */


    /* Reset USART1 */
    RCC->APB2RSTR = RCC_APB2RSTR_USART1RST;

    /* Release reset */
    RCC->APB2RSTR = 0;

    /* Reset RCC */
    /* Set HSION bit to the reset value */
    RCC->CR |= RCC_CR_HSION;


    /* Reset CFGR register */
        RCC->CFGR = 0;

	/* Clear HSEON, HSEBYP and CSSON bits */
		RCC->CR &= ~(RCC_CR_HSEON | RCC_CR_HSEBYP | RCC_CR_CSSON);

   /* Clear PLLON bit */
	RCC->CR &= ~RCC_CR_PLLON;

    /* Reset SysTick */
    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL = 0;


	 /* Get jump address */
	  uint32_t address = 0x1FFFF000;



	  /* Vector Table Relocation in Internal FLASH */
	  __DMB();/*Wail For Data Move From Cache To Memory*/
	  SCB->VTOR = address;
	  __DSB();/*All Memory Operations Were Done*/


	/* Set jump to the reset handler */
	void (*jump_address)(void) = (void *)(*((uint32_t *)(address + 4)));

	/* Set stack pointer */
	__set_MSP(address);

	/* Jump */
	jump_address();



	/*
	 * SP -> RESET HANDLER
	 * X  -> X + 4
	 */

}

void ITM_Printf(char *Str);
void ITM_SendChar_Port(uint8_t Port, uint8_t Ch);
void ITM_Printf_Port(uint8_t Port, char *Str);


void ITM_Printf(char *Str){
	while(*Str != '\0')
		ITM_SendChar(*(Str++));
	ITM_SendChar('\r');
	ITM_SendChar('\n');
}

void ITM_Printf_Port(uint8_t Port, char *Str){
	while(*Str != '\0')
		ITM_SendChar_Port(Port, *(Str++));
	ITM_SendChar_Port(Port, '\r');
	ITM_SendChar_Port(Port, '\n');
}

void ITM_SendChar_Port(uint8_t Port, uint8_t Ch){
	/* ITM enabled */ /* ITM Port #0 enabled */
	if ((ITM->TCR & ITM_TCR_ITMENA_Msk) && (ITM->TER & (1UL << Port)))
	{
		while (ITM->PORT[0].u32 == 0);
		ITM->PORT[Port].u8 = Ch;
	}
}

/*Bit Filed */
typedef union Flags_Union{
	char Flags_Reg;
	struct{
		char Flag0 : 1;
		char Flag1 : 1;
		char Flag2 : 1;
		char Flag3 : 1;
		char Flag4 : 1;
		char Flag5 : 1;
		char Flag6 : 1;
		char Flag7 : 1;
	};
} Flags;

float Distance;
int Current = 0;

int main(void)
{

	/*
	Flags LEDs;
	LEDs.Flags_Reg = 50;
	LEDs.Flag0 = 1;
	 */


	delay_init();


	GPIO_Config(GPIOC, 13, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_GP_OPEN_DRAIN);

	GPIO_Config(GPIOB, 12, MODE_INPUT, CONFIG_INPUT_PULL_UP);

	GPIO_Config(GPIOC, 14, MODE_INPUT, CONFIG_INPUT_PULL_DOWN);


	//GPIO_Config(GPIOB, 3, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_AF_OPEN_DRAIN);


	USART1_Init_Adv(115200, 5, U_TX_EN, U_LINEN_SET, U_RX_EN, U_LBDL_11_BIT, U_RX_INT_EN);

	USART3_Init_Adv(115200, 5, U_TX_EN, U_LINEN_SET, U_RX_EN, U_LBDL_11_BIT, U_RX_INT_EN);



	for(int i = 0;i < 20; i++){
		PC13 ^= 1;
		delay_ms(30);
	}



	if(digitalRead(GPIOB, 12))
		USART1_Send_Str("MASTER");
	else
		USART1_Send_Str("SLAVE");

	USART1_Send_Ln();



	/*
	CAN1_Init();
	CAN1_Filter(0, FLTR_MODE_MASK, FLTR_SCALE_SINGLE, FLTR_FIFO_0, 25<<21, 0xFFFFFFFF);

	RTOS_init();

	RTOS_SVC_threadCreate(&thread1, &thread1stack, 1, thread1function);
	RTOS_SVC_threadCreate(&thread2, &thread2stack, 1, thread2function);
	RTOS_SVC_threadCreate(&thread3, &thread3stack, 2, thread3function);

	RTOS_SVC_mutexCreate(&mutex1, 1);
	RTOS_SVC_semaphoreCreate(&semaphore1, 1);
	RTOS_SVC_mailboxCreate(&mailbox1, mailbox1buffer, 2, 4);

	RTOS_SVC_schedulerStart();
*/
/*
	RCC_CSR_LSION_BIT = 1;

	while(!RCC_CSR_LSIRDY_BIT);

	IWDG_Init(3, 10, 1);

	IWDG_Start();
*/




	TS_Init();


	//WWDG_Init(0x50, 0x53, 3, 1);

	//WWDG_Start();

	UltraSonic US1;
	US1.GPIO = GPIOB;
	US1.Triger_Pin = 1;
	US1.Echo_Pin = 0;

	UltraSonic_Init(US1);


	PDFPlayer_Init();
	delay_ms(3000);

	PDFPlayer_Set_Vol(15);


	while(1)
	{




		TS_Point CurrentPoint = TS_Get_Point();

		/*
		if(WWDG_Get_Counter() > 0x40 && WWDG_Get_Counter() < 0x50)
			WWDG_Refresh();
		 */

/*
		Distance = UltraSonic_Get_Distance(US1);
		gcvt (Distance, 10, Str);
		USART1_Send_Str("Distance : ");
		USART1_Send_Str(Str);
		USART1_Send_Ln();
*/
		if(CurrentPoint.Valid && CurrentPoint.Z < 800){
			itoa(CurrentPoint.X, Str, 10);
			USART1_Send_Str("X : ");
			USART1_Send_Str(Str);
			itoa(CurrentPoint.Y, Str, 10);
			USART1_Send_Str("   Y : ");
			USART1_Send_Str(Str);
			itoa(CurrentPoint.Z, Str, 10);
			USART1_Send_Str("   Z : ");
			USART1_Send_Str(Str);
			USART1_Send_Ln();

			if(CurrentPoint.Y > 300){

				PDFPlayer_Play(1, ++Current);

			}
			else{
				PDFPlayer_Play(1, --Current);
			}
			delay_ms(500);
		}


		if(digitalRead(GPIOC, 14)){
			for(int i = 0;i < 30; i++){
				PC13 ^= 1;
				delay_us(20000);
			}
			SYS_BL_Jump();
		}

		//delay_ms(1000);


//		delay_ms(100);
		//ITM_SendChar('A');

		//IWDG_Refresh();
	}

}

void ON_USART1_REC(){
	uint16_t Data;
	Flash_Unlock();

	switch(USART1_Read()){

	case 'A':
	{

		/*
		Data = Flash_Read(120, 5);
		USART1_Send((Data>>0) & 0xFF);
		USART1_Send((Data>>8) & 0xFF);


		Flash_Unlock();
		Flash_Write(120, 5, 0x1234);


		Data = Flash_Read(120, 5);
		USART1_Send((Data>>0) & 0xFF);
		USART1_Send((Data>>8) & 0xFF);
*/
		break;
	}
	case 'B':
		/*
		Data = Flash_Read(120, 5);
		USART1_Send((Data>>0) & 0xFF);
		USART1_Send((Data>>8) & 0xFF);
		*/
		break;

	case 'M':
		Flash_Write_16(121, 0, 0x4D);
		Flash_Write_16(121, 1, 0x6F);
		Flash_Write_16(121, 2, 0x68);
		Flash_Write_16(121, 3, 0x61);
		Flash_Write_16(121, 4, 0x6D);
		Flash_Write_16(121, 5, 0x6D);
		Flash_Write_16(121, 6, 0x65);
		Flash_Write_16(121, 7, 0x64);
		break;

	case 'N':
		for(int i = 0; i < 8 * 2; i += 2){
			Data = Flash_Read_8(121, i);
			USART1_Send((Data>>0) & 0xFF);
			//USART1_Send((Data>>8) & 0xFF);
		}
		break;

	case 'X':
		Flash_Page_Erase(121);
		break;
	}
}

