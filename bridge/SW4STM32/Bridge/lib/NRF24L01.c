/*		Setting		*/
/*
 * TX Et RX Device :
 *  Avec Auto Ack :
 * Enable_RXADDR Pipe 0 = TRUE
 * Enable_AA Pipe 0 = TRUE
 * Enable CRC dans config
 *
 * Sans Auto Ack :
 * CRC = FALSE
 * Enable_AA Pipe = FALSE
 * Setup Retransmission = 0
 */

/* Includes ------------------------------------------------------------------*/
#include "NRF24L01.h"
#include "spi.h"
#include "gpio.h"

static uint8_t CONFIG_Register_Val;
static HAL_StatusTypeDef HAL_Status_NRF24L01;

void clear_NRF24L01_HAL_Status(){
	HAL_Status_NRF24L01 = 0;
}

HAL_StatusTypeDef get_NRF24L01_HAL_Status(){
	return HAL_Status_NRF24L01;
}

void NRF24L01_Set_CSN(void){
	HAL_GPIO_WritePin(CSN_GPIO_Port, CSN_Pin, GPIO_PIN_SET);
}

void NRF24L01_Reset_CSN(void){
	HAL_GPIO_WritePin(CSN_GPIO_Port, CSN_Pin, GPIO_PIN_RESET);
}


uint8_t NRF24L01_Read_Status(SPI_HandleTypeDef* hspi)
{
	uint8_t Rx_Data[1];
	uint8_t Commande[1] = {DUMMY_NRF24L01};

	NRF24L01_Reset_CSN();
	HAL_Status_NRF24L01 = HAL_SPI_TransmitReceive(hspi, Commande, Rx_Data, 1,SPI_TIMEOUT);
	NRF24L01_Set_CSN();

	return Rx_Data[0];
}

uint8_t NRF24L01_Read_Register(SPI_HandleTypeDef* hspi,uint8_t Registre){
	uint8_t size = 2;
	uint8_t Rx_Data[size];
	uint8_t Tx_Data[size];

	Tx_Data[0] = (Registre & READ_REGISTER);;
	Tx_Data[1] = DUMMY_NRF24L01;
	NRF24L01_Reset_CSN();
	HAL_Delay(CSN_DELAY);
	HAL_Status_NRF24L01 = HAL_SPI_TransmitReceive(hspi, Tx_Data, Rx_Data, size,SPI_TIMEOUT);
	NRF24L01_Set_CSN();

	return Rx_Data[1];
}

void NRF24l01_Write_Register(SPI_HandleTypeDef* hspi, uint8_t Registre, uint8_t Data){
	uint8_t size = 2;
	uint8_t Rx_Data[size];
	uint8_t Tx_Data[size];

	Tx_Data[0]= ((Registre & (~(((1<<7) | (1<<6)))))|(1<<5));
	Tx_Data[1]= Data;
	NRF24L01_Reset_CSN();
	HAL_Delay(CSN_DELAY);
	HAL_Status_NRF24L01 = HAL_SPI_TransmitReceive(hspi, Tx_Data, Rx_Data,size,SPI_TIMEOUT);
	NRF24L01_Set_CSN();
}

void NRF24L01_Enable_AA(SPI_HandleTypeDef* hspi, uint8_t Pipe_0, uint8_t Pipe_1, uint8_t Pipe_2, uint8_t Pipe_3, uint8_t Pipe_4, uint8_t Pipe_5){
	uint8_t EN_AA_Register_Val;

	EN_AA_Register_Val = (0 | (Pipe_0<<ENAA_P0) | (Pipe_1<<ENAA_P1) | (Pipe_2<<ENAA_P2) | (Pipe_3<<ENAA_P3) | (Pipe_4<<ENAA_P4) | (Pipe_5<<ENAA_P5));
	NRF24l01_Write_Register(hspi,EN_AA_REGISTER,EN_AA_Register_Val);
}

void NRF24L01_Enable_RXADDR(SPI_HandleTypeDef* hspi, uint8_t Pipe_0, uint8_t Pipe_1, uint8_t Pipe_2, uint8_t Pipe_3, uint8_t Pipe_4, uint8_t Pipe_5){
	uint8_t EN_RXADDR_Register_Val;

	EN_RXADDR_Register_Val = (0 | (Pipe_0<<ERX_P0) | (Pipe_1<<ERX_P1) | (Pipe_2<<ERX_P2) | (Pipe_3<<ERX_P3) | (Pipe_4<<ERX_P4) | (Pipe_5<<ERX_P5));

	NRF24l01_Write_Register(hspi,EN_RXADDR_REGISTER,EN_RXADDR_Register_Val);
}

void NRF24L01_Setup_Adress_Width(SPI_HandleTypeDef* hspi, uint8_t Nb_Octets){
	uint8_t SETUP_AW_Register_Val;

	if ((Nb_Octets <= NB_OCTET_MAX) && (Nb_Octets >= NB_OCTET_MIN))
		{
			SETUP_AW_Register_Val = (Nb_Octets - 2);
		}

	else SETUP_AW_Register_Val = (NB_OCTET_MAX-2);
	NRF24l01_Write_Register(hspi,SETUP_AW_REGISTER,SETUP_AW_Register_Val);
}

void NRF24L01_Setup_Retransmission(SPI_HandleTypeDef* hspi, uint8_t Delay, uint8_t Count){
	uint8_t SETUP_RETR_Register_Val;

	SETUP_RETR_Register_Val = 0 | (Delay << ARD) | Count;

	NRF24l01_Write_Register(hspi,SETUP_RETR_REGISTER,SETUP_RETR_Register_Val);
}

void NRF24L01_RF_Channel(SPI_HandleTypeDef* hspi, uint8_t Channel){
	uint8_t RF_CH_Register_Val;

	RF_CH_Register_Val = Channel &(~(1<<7));

	NRF24l01_Write_Register(hspi,RF_CH_REGISTER,RF_CH_Register_Val);
}

void NRF24L01_RF_Setup(SPI_HandleTypeDef* hspi, uint8_t TX_Continu, uint8_t Data_Rate, uint8_t Output_Power){
	uint8_t RF_SETUP_Register_Val;

	RF_SETUP_Register_Val = 0 | (TX_Continu << CONT_WAVE) | (Output_Power<<RF_PWR);

	switch(Data_Rate)
	{
		case (_1MBPS) :	RF_SETUP_Register_Val &= (~((1<<RF_DR_LOW) | (1<<RF_DR_HIGH)));
		break;

		case (_2MBPS) :	RF_SETUP_Register_Val = (RF_SETUP_Register_Val & (~(1<<RF_DR_LOW))) | (1<<RF_DR_HIGH);
		break;

		case (_250KBPS) : RF_SETUP_Register_Val = (RF_SETUP_Register_Val & (~(1<<RF_DR_HIGH))) | (1<<RF_DR_LOW);
		break;
	}

	NRF24l01_Write_Register(hspi,RF_SETUP_REGISTER, RF_SETUP_Register_Val);
}

uint8_t NRF24L01_Observe_TX(SPI_HandleTypeDef* hspi){
	uint8_t OBSERVE_TX_Register_Val;

	OBSERVE_TX_Register_Val = (NRF24L01_Read_Register(hspi,OBSERVE_TX_REGISTER)>>PLOS_CNT);

	return OBSERVE_TX_Register_Val;
}

uint8_t NRF24L01_RPD(SPI_HandleTypeDef* hspi){
	uint8_t RPD_Register_Val;

	RPD_Register_Val = NRF24L01_Read_Register(hspi,RPD_REGISTER) & 1;

	return RPD_Register_Val;
}

uint8_t NRF24L01_FIFO_Status(SPI_HandleTypeDef* hspi){
	uint8_t FIFO_STATUS_Register_Val;

	FIFO_STATUS_Register_Val = NRF24L01_Read_Register(hspi,FIFO_STATUS_REGISTER);

	return FIFO_STATUS_Register_Val;
}

void NRF24L01_Dynamic_Payload(SPI_HandleTypeDef* hspi, uint8_t Pipe_0, uint8_t Pipe_1, uint8_t Pipe_2, uint8_t Pipe_3, uint8_t Pipe_4, uint8_t Pipe_5){
	uint8_t DYNPD_Register_Val;

	DYNPD_Register_Val = 0 | (Pipe_0 << DPL_P0) | (Pipe_1 << DPL_P1) | (Pipe_2 << DPL_P2) | (Pipe_3 << DPL_P3) | (Pipe_4 << DPL_P4) | (Pipe_5 << DPL_P5);

	NRF24l01_Write_Register(hspi, DYNPD_REGISTER, DYNPD_Register_Val);
}

void NRF24L01_Feature(SPI_HandleTypeDef* hspi, uint8_t Enable_Dynamic_Payload, uint8_t Enable_Payload_ACK, uint8_t Enable_W_TX_NOACK){
	uint8_t FEATURE_Register_Val;

	FEATURE_Register_Val = 0 | (Enable_Dynamic_Payload<<EN_DPL) | (Enable_Payload_ACK<<EN_ACK_PAY) | (Enable_W_TX_NOACK<<EN_DYN_ACK);

	NRF24l01_Write_Register(hspi,FEATURE_REGISTER,FEATURE_Register_Val);
}

void NRF24L01_Config(SPI_HandleTypeDef* hspi, uint8_t En_Mask_Rx_Dr, uint8_t En_Mask_Tx_Ds, uint8_t En_Mask_Max_Rt, uint8_t Enable_CRC, uint8_t CRC_Enc, uint8_t Power_Cont, uint8_t Rx_Tx_Cont){
	CONFIG_Register_Val = 0 | ((~(En_Mask_Rx_Dr)&1) << MASK_RX_DR) | ((~(En_Mask_Tx_Ds)&1) << MASK_TX_DS) | ((~(En_Mask_Max_Rt)&1) << MASK_MAX_RT) | (Enable_CRC << EN_CRC) | (CRC_Enc << CRCO) | (Power_Cont << PWR_UP) | (Rx_Tx_Cont << PRIM_RX);

	NRF24l01_Write_Register(hspi,CONFIG_REGISTER, CONFIG_Register_Val);
}

void NRF24L01_Mode(SPI_HandleTypeDef* hspi, uint8_t Mode){
	CONFIG_Register_Val = (CONFIG_Register_Val & (~(1<<PRIM_RX))) | (Mode << PRIM_RX);

	NRF24L01_Activation_Control(hspi,STANDBY);
	NRF24l01_Write_Register(hspi, CONFIG_REGISTER, CONFIG_Register_Val);
	if(Mode == PRX){
		NRF24L01_Activation_Control(hspi,ACTIVE);
	}
}

void NRF24L01_Power_Control(SPI_HandleTypeDef* hspi, uint8_t Power){
	CONFIG_Register_Val = (CONFIG_Register_Val & (~(1<<PWR_UP))) | (Power << PWR_UP);

	NRF24l01_Write_Register(hspi,CONFIG_REGISTER, CONFIG_Register_Val);
}

void NRF24L01_Write_RX_Address(SPI_HandleTypeDef* hspi, uint64_t RX_Address, uint8_t Num_Pipe){
	uint8_t Registre, Size;

	switch (Num_Pipe)
	{
	case(0) :
		Registre = RX_ADDR_P0_REGISTER;
		Size = ADDRESS_FIELD_WIDTH;
		break;
	case(1) :
		Registre = RX_ADDR_P1_REGISTER;
		Size = ADDRESS_FIELD_WIDTH;
		break;
	case(2) :
		Registre = RX_ADDR_P2_REGISTER;
		Size = 1;
		break;
	case(3) :
		Registre = RX_ADDR_P3_REGISTER;
		Size = 1;
		break;
	case(4) :
		Registre = RX_ADDR_P4_REGISTER;
		Size = 1;
		break;
	case(5) :
		Registre = RX_ADDR_P5_REGISTER;
		Size = 1;
		break;
	default:
		Registre = DUMMY_NRF24L01;
	    Size = 1;
		break;
	}

	uint8_t Tx_Data[Size+1];
	uint8_t Rx_Data[Size+1];
	Tx_Data[0] = ((Registre & (~(((1<<7) | (1<<6)))))|(1<<5));

	uint8_t Index = 1;
	while (Index < (Size+1))
	{
		Tx_Data[Index] = (RX_Address >> ((Index-1)*8)) & 0xFF;
		Index ++ ;
	}


	NRF24L01_Reset_CSN();
	HAL_Delay(CSN_DELAY);
	HAL_Status_NRF24L01 = HAL_SPI_TransmitReceive(hspi, Tx_Data, Rx_Data,Size+1,SPI_TIMEOUT);

	NRF24L01_Set_CSN();
}

void NRF24L01_Read_Data(SPI_HandleTypeDef* hspi, uint8_t Registre, uint8_t * Rx_Data, uint8_t Size){
	uint8_t	Index;
	uint8_t Tx_Data[Size];
	uint8_t Commande[1];

	Commande[0] = (Registre & READ_REGISTER);

	Index = 0;
	while ((Index < Size))
	{
		Tx_Data[Index] = DUMMY_NRF24L01;
		Index++;
	}

	NRF24L01_Reset_CSN();
	HAL_Delay(CSN_DELAY);
	HAL_Status_NRF24L01 = HAL_SPI_TransmitReceive(hspi, Commande, Rx_Data,1,SPI_TIMEOUT);
	HAL_Status_NRF24L01 = HAL_SPI_TransmitReceive(hspi, Tx_Data, Rx_Data,Size,SPI_TIMEOUT);
	NRF24L01_Set_CSN();
}

void NRF24L01_Write_TX_Address(SPI_HandleTypeDef* hspi, uint64_t TX_Address){
	uint8_t	Index;
	uint8_t Size = ADDRESS_FIELD_WIDTH+1;
	uint8_t Tx_Data[Size];
	uint8_t Rx_Data[Size];

	Tx_Data[0] = ((TX_ADDR_REGISTER & (~(((1<<7) | (1<<6)))))|(1<<5));

	Index = 1;
	while ((Index < Size))
	{
		Tx_Data[Index] = (TX_Address >> ((Index-1)*8)) & 0xFF;
		Index++;
	}

	NRF24L01_Reset_CSN();
	HAL_Delay(CSN_DELAY);
	HAL_Status_NRF24L01 = HAL_SPI_TransmitReceive(hspi, Tx_Data, Rx_Data,Size,SPI_TIMEOUT);
	NRF24L01_Set_CSN();
}

void NRF24L01_Write_Payload_Width(SPI_HandleTypeDef* hspi, uint8_t Width, uint8_t Num_Pipe){
	uint8_t Registre;

	switch (Num_Pipe)
	{
	case (0):	Registre = RX_PW_P0_REGISTER;
		break;
	case (1):	Registre = RX_PW_P1_REGISTER;
		break;
	case (2):	Registre = RX_PW_P2_REGISTER;
		break;
	case (3):	Registre = RX_PW_P3_REGISTER;
		break;
	case (4):	Registre = RX_PW_P4_REGISTER;
		break;
	case (5):	Registre = RX_PW_P5_REGISTER;
		break;
	default:    Registre = DUMMY_NRF24L01;
		break;
	}

	NRF24l01_Write_Register(hspi,Registre,Width);
}

void NRF24L01_Write_TX_Payload(SPI_HandleTypeDef* hspi, uint8_t* Tx_Data, uint8_t Size){
	uint8_t Rx_Data[Size];
	uint8_t Commande[1] = {W_TX_PAYLOAD};

	NRF24L01_Reset_CSN();
	HAL_Delay(CSN_DELAY);
	HAL_Status_NRF24L01 = HAL_SPI_TransmitReceive(hspi, Commande, Rx_Data,1,SPI_TIMEOUT);
	HAL_Status_NRF24L01 = HAL_SPI_TransmitReceive(hspi, Tx_Data, Rx_Data,Size,SPI_TIMEOUT);
	NRF24L01_Set_CSN();
}

uint8_t NRF24L01_Read_RX_Payload_Width(SPI_HandleTypeDef* hspi){
	uint8_t Tx_data[2] = {R_RX_PL_WIDTH,DUMMY_NRF24L01};
	uint8_t Rx_data[2];
	NRF24L01_Reset_CSN();
	HAL_Delay(CSN_DELAY);
	HAL_Status_NRF24L01 = HAL_SPI_TransmitReceive(hspi, Tx_data, Rx_data,2,SPI_TIMEOUT);
	NRF24L01_Set_CSN();

	return Rx_data[1];
}

void NRF24L01_Read_RX_Payload(SPI_HandleTypeDef* hspi, uint8_t* Rx_Data, uint8_t Size){
	uint8_t Tx_Data[Size];
	uint8_t Commande[0];

	Commande[0] = R_RX_PAYLOAD;

	uint8_t i =0;
	while(i<Size){
		Tx_Data[i] = DUMMY_NRF24L01;
		i++;
	}
	NRF24L01_Reset_CSN();
	HAL_Delay(CSN_DELAY);
	HAL_Status_NRF24L01 = HAL_SPI_TransmitReceive(hspi, Commande, Rx_Data,1,SPI_TIMEOUT);
	HAL_Status_NRF24L01 = HAL_SPI_TransmitReceive(hspi, Tx_Data, Rx_Data,Size,SPI_TIMEOUT);
	NRF24L01_Set_CSN();
}

void NRF24L01_Reuse_Tx_Payload(SPI_HandleTypeDef* hspi){
	uint8_t Commande[1]={REUSE_TX_PL};
	uint8_t Rx_Data[1];

	NRF24L01_Reset_CSN();
	HAL_Delay(CSN_DELAY);
	HAL_Status_NRF24L01 = HAL_SPI_TransmitReceive(hspi, Commande, Rx_Data,1,SPI_TIMEOUT);
	NRF24L01_Set_CSN();
}

void NRF24L01_Flush(SPI_HandleTypeDef* hspi, uint8_t Payload){
	uint8_t Commande[1];
	uint8_t Rx_Data[1];

	switch (Payload)
	{
	case(RX):	Commande[0] = FLUSH_RX;
		break;
	case(TX):	Commande[0] = FLUSH_TX;
		break;
	}

	NRF24L01_Reset_CSN();
	HAL_Delay(CSN_DELAY);
	HAL_Status_NRF24L01 = HAL_SPI_TransmitReceive(hspi, Commande, Rx_Data,1,SPI_TIMEOUT);
	NRF24L01_Set_CSN();
}

void NRF24L01_Activation_Control(SPI_HandleTypeDef* hspi, uint8_t Control){
	switch(Control)
	{
	case (ACTIVE) : HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_SET);
		break;
	case (STANDBY): HAL_GPIO_WritePin(CE_GPIO_Port, CE_Pin, GPIO_PIN_RESET);
		break;
	}
}

void NRF24L01_Transmit(SPI_HandleTypeDef* hspi, uint64_t TX_Adresse, uint8_t * Tx_Data, uint8_t Payload_Width, uint8_t Auto_Acknowledgment){

	NRF24L01_Write_TX_Address(hspi,TX_Adresse);
	if (Auto_Acknowledgment)
	{
		NRF24L01_Write_RX_Address(hspi,TX_Adresse,0);
	}
	NRF24L01_Write_TX_Payload(hspi, Tx_Data, Payload_Width);
	//
	NRF24L01_Activation_Control(hspi,ACTIVE);
	HAL_Delay(TX_PAUSE);
	NRF24L01_Activation_Control(hspi,STANDBY);

}

void NRF24L01_Clear_TX_DS(SPI_HandleTypeDef* hspi, uint8_t Status){
	NRF24l01_Write_Register(hspi,STATUS_REGISTER,(Status | (1<<TX_DS)));
}

void NRF24L01_Clear_RX_DR(SPI_HandleTypeDef* hspi, uint8_t Status){
	NRF24l01_Write_Register(hspi,STATUS_REGISTER,(Status | (1<<RX_DR)));
}

void NRF24L01_Clear_MAX_RT(SPI_HandleTypeDef* hspi, uint8_t Status){
	NRF24l01_Write_Register(hspi,STATUS_REGISTER,(Status | (1<<MAX_RT)));
}

uint8_t NRF24L01_Read_Data_Pipe_Number(SPI_HandleTypeDef* hspi, uint8_t Status){
	uint8_t Pipe_Num;

	Pipe_Num = (Status >> RX_P_NO) & 0x07;

	return Pipe_Num;
}

uint8_t NRF24L01_Read_Retransmitted_Packets(SPI_HandleTypeDef* hspi){
	uint8_t Count;

	Count = NRF24L01_Read_Register(hspi,OBSERVE_TX_REGISTER) & 0x07;

	return Count;
}

void NRF24l01_Initialization(SPI_HandleTypeDef* hspi, uint8_t Mode){
	// Initialisation des IO => CubeMx

	NRF24L01_Activation_Control(hspi,STANDBY);
	NRF24L01_Config(hspi,TRUE,TRUE,TRUE,TRUE,0,POWER_DOWN,Mode);
	NRF24L01_Enable_AA(hspi,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE);
	NRF24L01_Setup_Retransmission(hspi, WAIT_250,1);
	NRF24L01_Setup_Adress_Width(hspi,ADDRESS_FIELD_WIDTH);
	NRF24L01_RF_Channel(hspi,RF_CHANNEL);
	NRF24L01_RF_Setup(hspi,FALSE,_1MBPS,MINUS_12_DBM);
	NRF24L01_Dynamic_Payload(hspi,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE);
	NRF24L01_Feature(hspi,FALSE,FALSE,FALSE);
	NRF24L01_Enable_RXADDR(hspi,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE);
	NRF24L01_Write_Payload_Width(hspi,RX_PIPE_1_PAYLOAD,1);
	NRF24L01_Write_RX_Address(hspi,ADRESSE_PIPE_1_RX,1);
	NRF24L01_Flush(hspi,RX);
	NRF24L01_Flush(hspi,TX);
	NRF24L01_Power_Control(hspi,POWER_UP);

	if(Mode == PRX){
		NRF24L01_Activation_Control(hspi,ACTIVE);
	}
}

