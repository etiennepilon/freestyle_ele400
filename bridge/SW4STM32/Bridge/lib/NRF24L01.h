

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* USER CODE BEGIN Private defines */

// 			 Rx Adresse

// Bridge
#define ADRESSE_PIPE_1_RX 0x555555

// Cable Cam
//#define ADRESSE_PIPE_1_RX 0x515151


//**********************************//
//				 SPI				//
//**********************************//
#define DUMMY_NRF24L01	0xFF
#define CSN_DELAY 1	// Delais en ms
#define SPI_TIMEOUT 500 // ms

//**********************************//
//				Pinout				//
//**********************************//

// Chip Enable Activates RX or TX mode
#ifndef CE_Pin
#define CE_Pin GPIO_PIN_15
#endif

#ifndef CE_GPIO_Port
#define CE_GPIO_Port GPIOA
#endif

// SPI Chip Select
#ifndef CSN_Pin
#define CSN_Pin GPIO_PIN_2
#endif

#ifndef CSN_GPIO_Port
#define CSN_GPIO_Port GPIOD
#endif

// IRQ Maskable interrupt pin. Active low

//**********************************//
//			 Registres				//
//**********************************//


#define CONFIG_REGISTER 0x00			//	Configuration Register
										//	Bit :
#define MASK_RX_DR	6
#define MASK_TX_DS	5
#define MASK_MAX_RT	4
#define EN_CRC		3
#define CRCO		2
#define PWR_UP		1
#define PRIM_RX		0

#define PRX			1
#define PTX			0
#define POWER_UP	1
#define POWER_DOWN	0


#define EN_AA_REGISTER 0x01				//	Enable Auto Acknowledgment
										//	Bit :
#define ENAA_P5		5
#define ENAA_P4		4
#define ENAA_P3		3
#define ENAA_P2		2
#define ENAA_P1		1
#define ENAA_P0		0

#define EN_RXADDR_REGISTER	0x02		//	Enabled RX Addresses
										//	Bit :
#define	ERX_P5		5
#define	ERX_P4		4
#define	ERX_P3		3
#define	ERX_P2		2
#define	ERX_P1		1
#define	ERX_P0		0

#define SETUP_AW_REGISTER	0x03		//	Setup of Address Widths
#define AW			0					//	Bit	1:0
#define NB_OCTET_MAX 5
#define NB_OCTET_MIN 3

#define SETUP_RETR_REGISTER	0x04		//	Setup of automatic retransmission
#define ARD			4					//	Bit : 7:4
#define WAIT_250	0
#define WAIT_500	1
#define WAIT_750	2
#define WAIT_1000	3
#define WAIT_1250	4
#define WAIT_1500	5
#define WAIT_1750	6
#define WAIT_2000	7
#define WAIT_2250	8
#define WAIT_2500	9
#define WAIT_2750	10
#define WAIT_3000	11
#define WAIT_3250	12
#define WAIT_3500	13
#define WAIT_3750	14
#define WAIT_4000	15
#define ARC			0					//	Bit : 3:0

#define RF_CH_REGISTER	0x05			//	RF Channel
#define RF_CH		0					//	Bit : 6:0
#define RF_CHANNEL	2

#define RF_SETUP_REGISTER	0x06		//	RF Setup Register
										//	Bit :
#define CONT_WAVE	7
#define RF_DR_LOW	5
#define PLL_LOCK	4
#define RF_DR_HIGH	3
#define RF_PWR		1					//	Bit : 2:1

#define _1MBPS		0
#define _2MBPS		1
#define _250KBPS	2

#define MINUS_18_DBM	0
#define MINUS_12_DBM	1
#define MINUS_6_DBM		2
#define ZERO_DBM		3

#define STATUS_REGISTER	0x07			//	Status Register
										//	Bit :
#define RX_DR		6
#define TX_DS		5
#define MAX_RT		4
#define RX_P_NO		1					//	Bit : 3:1
#define TX_FULL		0


#define OBSERVE_TX_REGISTER 0x08		//	Transmit observe register
#define PLOS_CNT	4					//	Bit : 7:4
#define ARC_CNT		0					//	Bit : 3:0


#define RPD_REGISTER	0x09			//	Received power detector (Carrier detect)
#define RPD			0

#define ADDRESS_FIELD_WIDTH 3			//	Nombre d'octets pour les adresses. Min 3 Max 5

										//	Rx address data pipe
#define RX_ADDR_P0_REGISTER 0x0A
//#define ADRESSE_PIPE_0 :
#define RX_PIPE_0_PAYLOAD	5

#define RX_ADDR_P1_REGISTER 0x0B
//#define ADRESSE_PIPE_1 :
#define RX_PIPE_1_PAYLOAD	3
										//	Les pipes 2 a 5 ont seulement un octet ( Le moins significatif). Les autres octets
										//	sont les memes que l'adresse de la pipe 1.
#define RX_ADDR_P2_REGISTER 0x0C
//#define ADRESSE_PIPE_2 :
//#define RX_PIPE_2_PAYLOAD

#define RX_ADDR_P3_REGISTER 0x0D
//#define ADRESSE_PIPE_3 :
//#define RX_PIPE_3_PAYLOAD

#define RX_ADDR_P4_REGISTER 0x0E
//#define ADRESSE_PIPE_4 :
//#define RX_PIPE_4_PAYLOAD

#define	RX_ADDR_P5_REGISTER 0x0F
//#define ADRESSE_PIPE_5 :
//#define RX_PIPE_5_PAYLOAD

#define TX_ADDR_REGISTER 0x10			//	Transmit address Register

										//	Number of bytes in RX payload pipe #
#define RX_PW_P0_REGISTER 0x11
#define RX_PW_P1_REGISTER 0x12
#define RX_PW_P2_REGISTER 0x13
#define RX_PW_P3_REGISTER 0x14
#define RX_PW_P4_REGISTER 0x15
#define RX_PW_P5_REGISTER 0x16

#define FIFO_STATUS_REGISTER 0x17		//	FIFO Status register
										//	Bit :
#define TX_REUSE	6
#define TX_FULL_	5
#define TX_EMPTY	4
#define RX_FULL		1
#define RX_EMPTY	0

#define DYNPD_REGISTER 0x1C				//	Enable dynamic payload length
										//	Bit :
#define DPL_P5		5
#define DPL_P4		4
#define DPL_P3		3
#define DPL_P2		2
#define DPL_P1		1
#define DPL_P0		0

#define FEATURE_REGISTER 0x1D			//	Feature register
										//	Bit :
#define EN_DPL		2
#define EN_ACK_PAY	1
#define EN_DYN_ACK	0


//**********************************//
//			Commandes				//
//**********************************//
										//	R_REGISTER 000AAAAA, utiliser avec un &
#define READ_REGISTER	0b00011111
										//	W_REGISTER 001AAAAA, utiliser avec un &
#define WRITE_REGISTER	(~((1<<7) | (1<<6)))|(1<<5)
#define TRUE 1
#define FALSE 0
#define W_TX_PAYLOAD	0b10100000
#define R_RX_PAYLOAD	0b01100001
#define FLUSH_TX		0b11100001
#define FLUSH_RX		0b11100010
#define REUSE_TX_PL		0b11100011
#define R_RX_PL_WIDTH	0b01100000
										// W_ACK_PAYLOAD	0b10101PPP  PPP = Pipe #
#define W_ACK_PAYLOAD	0b10101000
#define W_TX_PAYLOAD_NO_ACK	0b10110000

#define RX 1
#define TX 0

#define ACTIVE	1
#define STANDBY	0

#define TX_PAUSE	1					//	Le temps que CE est a un niveau haut pour indiquer au NRF24L01 que nous voulons transmettre. Delais en ms.


/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */

//**********************************//
//			 Fonctions				//
//**********************************//

void clear_NRF24L01_HAL_Status();

HAL_StatusTypeDef get_NRF24L01_HAL_Status();

/*	Passe la broche CSN d'un niveau Haut a Bas */
void NRF24L01_Set_CSN(void);

/*	Passe la broche CSN d'un niveau Haut a Bas */
void NRF24L01_Reset_CSN(void);

/*	Renvoit le status du NRF24l01. Remet la broche CSN a 1.	*/
uint8_t NRF24L01_Read_Status(SPI_HandleTypeDef* hspi);

/*	Renvoit la valeur du registre. Foncitonne seulement pour les registres avec 1 Octet. Remet la broche CSN a 1.	*/
uint8_t NRF24L01_Read_Register(SPI_HandleTypeDef* hspi,uint8_t Registre);

/*	Ecrit dans le registre la valeur desire. Remet la broche CSN a 1.	*/
void NRF24l01_Write_Register(SPI_HandleTypeDef* hspi, uint8_t Registre, uint8_t Data);

/*	Active / Desactive l'Auto Acknowledgment sur les pipes avec TRUE ou FALSE		*/
void NRF24L01_Enable_AA(SPI_HandleTypeDef* hspi, uint8_t Pipe_0, uint8_t Pipe_1, uint8_t Pipe_2, uint8_t Pipe_3, uint8_t Pipe_4, uint8_t Pipe_5);

/*	Active / Desactive les pipes avec TRUE ou FALSE	*/
void NRF24L01_Enable_RXADDR(SPI_HandleTypeDef* hspi, uint8_t Pipe_0, uint8_t Pipe_1, uint8_t Pipe_2, uint8_t Pipe_3, uint8_t Pipe_4, uint8_t Pipe_5);

/*	Determine la grandeur des adresses.
Nb_Octets : 3, 4, 5.	*/
void NRF24L01_Setup_Adress_Width(SPI_HandleTypeDef* hspi, uint8_t Nb_Octets);

/*	Configure le temps entre les retransmissions et le nombre de retransmission.
	Delay est en multiple de 250 us (WAIT_XXX). Count est entre 0 et 15. */
void NRF24L01_Setup_Retransmission(SPI_HandleTypeDef* hspi, uint8_t Delay, uint8_t Count);

/*	Determine le canal RF entre 0 et 127	*/
void NRF24L01_RF_Channel(SPI_HandleTypeDef* hspi, uint8_t Channel);

/*	Configure les options RF.
TX_Continu (Carrier) : TRUE, FALSE.
Data_Rate : _1MBPS, _2MBPS, _250KBPS.
Output_Power : MINUS_18_DBM, MINUS_12_DBM, MINUS_6_DBM, ZERO_DBM.	*/

void NRF24L01_RF_Setup(SPI_HandleTypeDef* hspi, uint8_t TX_Continu, uint8_t Data_Rate, uint8_t Output_Power);

/*	Retourne le nombre de paquets perdu		*/
uint8_t NRF24L01_Observe_TX(SPI_HandleTypeDef* hspi);

/* Retourne 1 si la porteuse est detecte	*/
uint8_t NRF24L01_RPD(SPI_HandleTypeDef* hspi);

/* Retourne le status du FIFO	*/
uint8_t NRF24L01_FIFO_Status(SPI_HandleTypeDef* hspi);

/* Active/Desactive le dynamic payload sur les pipes avec TRUE ou FALSE */
void NRF24L01_Dynamic_Payload(SPI_HandleTypeDef* hspi, uint8_t Pipe_0, uint8_t Pipe_1, uint8_t Pipe_2, uint8_t Pipe_3, uint8_t Pipe_4, uint8_t Pipe_5);

/*	Active/Desactive avec TRUE ou FALSE le Dynamic Payload Length, le Payload avec ACK et la commande W_TX_PAYLOAD_NOACK. */
void NRF24L01_Feature(SPI_HandleTypeDef* hspi, uint8_t Enable_Dynamic_Payload, uint8_t Enable_Payload_ACK, uint8_t Enable_W_TX_NOACK);

/*	Configuration du NRF24L01.
    Active/Desactive les masks et les CRC avec TRUE ou FALSE.
	CRC_En	: 0 = 1 Byte 1 = 2 bytes
	Power : POWER_UP ou POWER_DOWN.
	RX_TX_Cont : PRX ou PTX.
*/
void NRF24L01_Config(SPI_HandleTypeDef* hspi, uint8_t En_Mask_Rx_Dr, uint8_t En_Mask_Tx_Ds, uint8_t En_Mask_Max_Rt, uint8_t Enable_CRC, uint8_t CRC_Enc, uint8_t Power_Cont, uint8_t Rx_Tx_Cont);

/*	Configure le NRF24L01 en mode PRX ou PTX.	*/
void NRF24L01_Mode(SPI_HandleTypeDef* hspi, uint8_t Mode);

/*	Controle le pouvoir sur le NRF24L01 avec POWER_UP ou POWER_DOWN.	*/
void NRF24L01_Power_Control(SPI_HandleTypeDef* hspi, uint8_t Power);

/*	Assigne l'adresse RX_Address a la pipe #(Num_Pipe). La largeur de l'adresse est determiner par ADDRESS_FIELD_WIDTH.	*/
void NRF24L01_Write_RX_Address(SPI_HandleTypeDef* hspi, uint64_t RX_Address, uint8_t Num_Pipe);


/*	Retourne dans un tableau ( Rx_Data	) le nombre de valeurs voulu (Size) qu'il y a dans le registre	*/
void NRF24L01_Read_Data(SPI_HandleTypeDef* hspi, uint8_t Registre, uint8_t * Rx_Data, uint8_t Size);

/*	Ecrit l'adresse du destinataire. La largeur de l'adresse est determiner par ADDRESS_FIELD_WIDTH. */
void NRF24L01_Write_TX_Address(SPI_HandleTypeDef* hspi, uint64_t TX_Address);

/*	Determine le nombre d'octet (Width) dans le payload de la pipe #(Num_Pipe)	*/
void NRF24L01_Write_Payload_Width(SPI_HandleTypeDef* hspi, uint8_t Width, uint8_t Num_Pipe);

/*	Ecrit le data qui va etre envoyer dans le payload	*/
void NRF24L01_Write_TX_Payload(SPI_HandleTypeDef* hspi, uint8_t* Data, uint8_t Num_Byte);

/*	Retourne le nombre d'octet qu'il y a dans RX_PLD	*/
uint8_t NRF24L01_Read_RX_Payload_Width(SPI_HandleTypeDef* hspi);

/*	Retourne dans un tableau ( Rx_Data [Size]	) le nombre d'octet voulu qui sont dans le RX Payload	*/
void NRF24L01_Read_RX_Payload(SPI_HandleTypeDef* hspi, uint8_t* Data, uint8_t Size);

/*	Renvoit le dernier paquet envoyer jusqu'à ce qu'on ecrive dans TX_Payload ou qu'on efface TX_Payload avec Flush_Tx.	*/
void NRF24L01_Reuse_Tx_Payload(SPI_HandleTypeDef* hspi);

/*	Efface le payload (RX ou TX)	*/
void NRF24L01_Flush(SPI_HandleTypeDef* hspi, uint8_t Payload);

/*	Controle la broche CE pour activer le NRF24L01 ou le mettre en standby
	Control : ACTIVE ou STANDBY.	*/
void NRF24L01_Activation_Control(SPI_HandleTypeDef* hspi, uint8_t Control);

/*	Transmet le tableau (Data) à l'adresse (TX_Adresse). Payload_Width doit être égal au Payload_Width de la pipe du destinataire.
	Mettre Acknowledgment à TRUE si Auto Acknowledgment est activé sur la pipe.	Le NRF doit etre en mode TX !!!									*/
void NRF24L01_Transmit(SPI_HandleTypeDef* hspi, uint64_t TX_Adresse, uint8_t * Tx_Data, uint8_t Payload_Width, uint8_t Auto_Acknowledgment);

/*	Enleve le flag TX_DS.	*/
void NRF24L01_Clear_TX_DS(SPI_HandleTypeDef* hspi, uint8_t Status);

/*	Enleve le flag RX_DR.	*/
void NRF24L01_Clear_RX_DR(SPI_HandleTypeDef* hspi, uint8_t Status);

/*	Enleve le flag MAX_RT.	*/
void NRF24L01_Clear_MAX_RT(SPI_HandleTypeDef* hspi, uint8_t Status);

/*	Retourne la valeur de la pipe qui peut être lu. */
uint8_t NRF24L01_Read_Data_Pipe_Number(SPI_HandleTypeDef* hspi, uint8_t Status);

/*	Retourne le nombre de fois que le packet à été retransmis	*/
uint8_t NRF24L01_Read_Retransmitted_Packets(SPI_HandleTypeDef* hspi);

/*	Initialise le NRF24L01. Mode est le mode dans lequel le NRF24L01 va être après l'initialisation. Cette fonciton doit être construite en fonction du projet.	*/
void NRF24l01_Initialization(SPI_HandleTypeDef* hspi, uint8_t Mode);

/* USER CODE END Prototypes */


