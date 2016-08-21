#include "modbus.h"

/**************** CRC ¸ßÎ»×Ö½ÚÖµ±í CRC high byte ******************/
const unsigned char  PROGMEM auchCRCHi[] =
{
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
};
/****************CRCµÍÎ»×Ö½ÚÖµ±í CRC low byte*********************/
const unsigned char  PROGMEM  auchCRCLo[] =
{
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
    0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
    0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
    0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
    0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
    0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
    0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
    0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
    0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
    0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
    0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
    0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
    0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
    0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
    0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
    0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
    0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
    0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
    0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
    0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
    0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
    0x43, 0x83, 0x41, 0x81, 0x80, 0x40
};

XYZ_Value XYZ_Data_Buf[20];
XiMoVaule ABC_XiMo_Data[20];
System_Value  Global_Data;
JiXieShou JiXieShou_Data;
//volatile BitBuf My_Bit;
/**************************MODBUS¹¦ÄÜÂë´¦Àí***************************/
/********Ä¿Ç°Ö»ÄÜÊ¶±ð01£¬03£¬05£¬06¹¦ÄÜÂë£¬¶øÇÒÖ»ÄÜ¹ÒÔØµ¥Ì¨***********/
/**
 ÏÂÃæ¡°ÏßÈ¦¡±¡°¼Ä´æÆ÷¡±ÆäÊµ·Ö±ðÖ±µÄ¾ÍÊÇ¡°Î»±äÁ¿¡±¡°16Î»±äÁ¿¡±
        01 (0x01)        ¶ÁÏßÈ¦
        02 (0x02)        ¶ÁÀëÉ¢Á¿ÊäÈë
        03 (0x03)        ¶Á±£³Ö¼Ä´æÆ÷
        04 (0x04)        ¶ÁÊäÈë¼Ä´æÆ÷
        05 (0x05)        Ð´µ¥¸öÏßÈ¦
        06 (0x06)        Ð´µ¥¸ö¼Ä´æÆ÷
        xxx15 (0x0F)        Ð´¶à¸öÏßÈ¦
        16 (0x10)        Ð´¶à¸ö¼Ä´æÆ÷
**/

/**************16Î»CRCÐ£Ñéº¯Êý,²é±í·¨********************/
unsigned int CRC16(unsigned char *Pushdata,unsigned char length)
{
    unsigned char uchCRCHi=0xFF;
    unsigned char uchCRCLo=0xFF;
    unsigned char uIndex;

    while(length--)
    {
        uIndex = uchCRCHi^*Pushdata++;
        uchCRCHi = uchCRCLo^pgm_read_byte(auchCRCHi + uIndex);
        uchCRCLo = pgm_read_byte(auchCRCLo + uIndex);
    }
    return ((unsigned int)(uchCRCHi)<<8|uchCRCLo);
}

void Uart_send_start(unsigned char * date, unsigned char length)
{
    USART0_Send_word(*date);
    UartMRB.buff_data_num = length;
}

void Modbus_Int()
{
    USART0_initial();
    Time0_init();
    UART0_INT_RX_Start;
}

void Modbus_Processing(void) 
{

    unsigned int crc_end = 0, My_Reg_Value = 0;										  //CECÐ£ÑéÖµºÍ03¹¦ÄÜÂë·¢ËÍµÄÎ»µÄ³¤¶È
    unsigned int byte_count = 0, Start_Adrr = 0, bit_count = 0, Value_Y = 0;
    unsigned int i = 0;

    unsigned char (*pFunction)(unsigned char i);

    if((TimerT3_5 == 1))
    { 
        if(UartMRB.pUartModbusBuffer[0] == MACHINNUM)
        switch(UartMRB.pUartModbusBuffer[1])
        {
            case 0x01:
            case 0x02:							  //02¹¦ÄÜÂë,1x¶ÁÒ»¸öX»òÕß¶à¸öÊäÈëµã×´Ì¬ £¬
		    case 0x03:
            case 0x04:
            case 0x05:
            case 0x06:
                crc_end = CRC16(UartMRB.pUartModbusBuffer,6);                   //Ð£Ñé
                
                if(byte8_1(crc_end) == UartMRB.pUartModbusBuffer[6] && \
                    byte8_0(crc_end) == UartMRB.pUartModbusBuffer[7])   //µ±Ð£ÑéÒ»ÖÂÊ±
                switch(UartMRB.pUartModbusBuffer[1])
                {
                    case 0x01:
                    case 0x02:
                    {
                        UartMRB.pUartModbusBuffer[2] = (UartMRB.pUartModbusBuffer[5] & 0x07) ? \
                            (UartMRB.pUartModbusBuffer[5]/8 + 1):(UartMRB.pUartModbusBuffer[5]/8);

                        byte_count = UartMRB.pUartModbusBuffer[2];                 //Î»Êý
                        bit_count  = UartMRB.pUartModbusBuffer[5];      //2 4
                        Start_Adrr = UartMRB.pUartModbusBuffer[3];
                        
                        switch(UartMRB.pUartModbusBuffer[1])
                        {
                            case 0x01:
                                pFunction = Reg_Y_bit;
                            break;
                            
                            case 0x02:
                                pFunction = In_X;
                            break;
                        }

                        for(i = 0; i < bit_count; i++)              //·¢ËÍÏàÓ¦×Ö½Ú
                        {
                            UartMRB.pUartModbusBuffer[3 + i/8] &= ~(1<<(i%8));
                            UartMRB.pUartModbusBuffer[3 + i/8] |= (pFunction(Start_Adrr + i)<<(i%8));
                        }

                        crc_end = CRC16(UartMRB.pUartModbusBuffer,byte_count + 3);                      //Ð£Ñé
                        UartMRB.pUartModbusBuffer[byte_count + 3] = byte8_1(crc_end);                   //Ð£ÑéµÍÎ»
                        UartMRB.pUartModbusBuffer[byte_count + 4] = crc_end;                    //Ð£Ñé¸ßÎ»
                        Uart_send_start(UartMRB.pUartModbusBuffer,byte_count + 5);            //·¢ËÍ·µ»ØÆÁ
                    }
                    break;

                    case 0x03:                          //03¹¦ÄÜÂë£¬¶Á³öµ¥¸ö¡¢¶à¸ö¼Ä´æÆ÷Öµ£¬4x\6x¶Áµ¥¸ö¡¢¶à¸ö¼Ä´æÆ÷Öµ¡£¶ÁÈ¡µç»úÖáÎ»ÖÃºÍMy_Reg¼Ä´æÆ÷Öµ
                    case 0x04:
                        UartMRB.pUartModbusBuffer[2] = UartMRB.pUartModbusBuffer[5]*2;                  //×Ö½ÚÊý


                        Start_Adrr = UartMRB.pUartModbusBuffer[3];
                        byte_count = UartMRB.pUartModbusBuffer[2];
                        for(i = 0; i < byte_count; i = i + 2)
                        {
                              /*¶àword£¨16Î»£©·¢ËÍ£¬ÏÈ·¢ËÍµÍwordÔÙ·¢¸ßword*/
                              /*Ò»¸öword·¢ËÍÊ±£¬ÏÈ·¢¸ß8Î»ÔÙ·¢µÍ8Î»*/
                              My_Reg_Value = Read_XYZWRV_My_Reg(Start_Adrr + i/2);
                              UartMRB.pUartModbusBuffer[i+3] = byte8_1(My_Reg_Value);     //×Ö¸ß×Ö½Ú
                              UartMRB.pUartModbusBuffer[i+4] = byte8_0(My_Reg_Value);     //×ÖµÍ×Ö½Ú
                        }

                        crc_end = CRC16(UartMRB.pUartModbusBuffer,byte_count + 3);                //Ð£Ñé
                        UartMRB.pUartModbusBuffer[byte_count + 3] = byte8_1(crc_end);             //Ð£ÑéµÍÎ»
                        UartMRB.pUartModbusBuffer[byte_count + 4] = crc_end;              //Ð£Ñé¸ßÎ»
                        Uart_send_start(UartMRB.pUartModbusBuffer, byte_count + 5);                   //·µ»ØÆÁ
                    break;

                    case 0x05:                            //05¹¦ÄÜÂë £¬0xÐ´ÏßÈ¦£¬ÉèÖÃYÊä³ö
                        Start_Adrr  = UartMRB.pUartModbusBuffer[3];
                        Value_Y = UartMRB.pUartModbusBuffer[4];
                        Write_Y_and_Bit(Start_Adrr,Value_Y>>7);

                        crc_end = CRC16(UartMRB.pUartModbusBuffer,6);                 //Ð£Ñé
                        UartMRB.pUartModbusBuffer[6] = byte8_1(crc_end);                  //Ð£ÑéµÍÎ»
                        UartMRB.pUartModbusBuffer[7] = crc_end;                   //Ð£Ñé¸ßÎ»
                        Uart_send_start(UartMRB.pUartModbusBuffer,8);                     //·¢ËÍ·µ»ØÆÁ
                    break;

                    case 0x06:                          //06¹¦ÄÜÂë,Ð´µ¥¸ö¼Ä´æÆ÷£¬6xÐ´µ¥¸ö¼Ä´æÆ÷¡£
                        Start_Adrr  = UartMRB.pUartModbusBuffer[3];

                        byte8_1(My_Reg_Value) = UartMRB.pUartModbusBuffer[4];
                        byte8_0(My_Reg_Value) = UartMRB.pUartModbusBuffer[5];
                        Write_XYZWRV_My_Reg(Start_Adrr, My_Reg_Value);

                        crc_end = CRC16(UartMRB.pUartModbusBuffer,6);                 //Ð£Ñé
                        UartMRB.pUartModbusBuffer[6] = byte8_1(crc_end);                  //Ð£ÑéµÍÎ»
                        UartMRB.pUartModbusBuffer[7] = crc_end;                   //Ð£Ñé¸ßÎ»
                        Uart_send_start(UartMRB.pUartModbusBuffer,8);              //·µ»ØÆÁ
                    break;
                }
            break;  

            case 0x0F:
            case 0x10:
                byte_count = UartMRB.pUartModbusBuffer[6];
                crc_end = CRC16(UartMRB.pUartModbusBuffer,7 + byte_count);                      //Ð£Ñé

                if(byte8_1(crc_end) == UartMRB.pUartModbusBuffer[7 + byte_count] && \
                    byte8_0(crc_end) == UartMRB.pUartModbusBuffer[8 + byte_count])      //µ±Ð£ÑéÒ»ÖÂÊ±
                switch(UartMRB.pUartModbusBuffer[1])
                {
                    case 0x0F:                             //Ð´¶à¸öÏßÈ¦
                        bit_count   = UartMRB.pUartModbusBuffer[5];
                        Start_Adrr  = UartMRB.pUartModbusBuffer[3];
                        for(i = 0; i < bit_count; i++)
                        {
                            Write_Y_and_Bit(Start_Adrr + i, (UartMRB.pUartModbusBuffer[7 + i/8]>>(i%8))&0x01);
                        }
                        crc_end = CRC16(UartMRB.pUartModbusBuffer,6);                   //Ð£Ñé
                        UartMRB.pUartModbusBuffer[6] = byte8_1(crc_end);                    //Ð£ÑéµÍÎ»
                        UartMRB.pUartModbusBuffer[7] = crc_end;                     //Ð£Ñé¸ßÎ»
                        Uart_send_start(UartMRB.pUartModbusBuffer,8);         //·¢ËÍ·µ»ØÆÁ
                    break;

                    case 0x10:                            //10¹¦ÄÜÂë ,Ð´¶à¸ö¼Ä´æÆ÷£¬4xÉèÖÃ¶à¸ö¼Ä´æÆ÷ ¡£Ð´My_Reg¶à¸ö¼Ä´æÆ÷¡¢µç»úÖáÎ»ÖÃ
                        Start_Adrr  = UartMRB.pUartModbusBuffer[3];
                        byte_count  = UartMRB.pUartModbusBuffer[6];

                        for(i = 0; i < byte_count; i = i + 2)
                        {
                              /*¶àword£¨16Î»£©½ÓÊÕÊ±£¬ÏÈÊÕËÍµÍwordÔÙÊÕ¸ßword*/
                              /*Ò»¸öword½ÓÊÕÊ±£¬ÏÈÊÕ¸ß8Î»ÔÙÊÕµÍ8Î»*/
                              byte8_1(My_Reg_Value) = UartMRB.pUartModbusBuffer[7 + i];
                              byte8_0(My_Reg_Value) = UartMRB.pUartModbusBuffer[8 + i];
                              Write_XYZWRV_My_Reg(Start_Adrr + i/2,My_Reg_Value);
                        }

                        crc_end = CRC16(UartMRB.pUartModbusBuffer,6);                   //Ð£Ñé
                        UartMRB.pUartModbusBuffer[6] = byte8_1(crc_end);                    //Ð£ÑéµÍÎ»
                        UartMRB.pUartModbusBuffer[7] = crc_end;                     //Ð£Ñé¸ßÎ»
                        Uart_send_start(UartMRB.pUartModbusBuffer,8);         //·¢ËÍ·µ»ØÆÁ
                    break;
                }
            break;

            default:
                break;
        }
        UART0_INT_RX_Start;
        TimerT3_5 = 0;
    }
}

void Write_Y_and_Bit(unsigned char Adrr_Y_Bit, unsigned char Value_Y_Bit)
{
    switch(Adrr_Y_Bit)
    {
        case 0: Y0(Value_Y_Bit); break;
        case 1: Y1(Value_Y_Bit); break;
        case 2: Y2(Value_Y_Bit); break;
        case 3: Y3(Value_Y_Bit); break;
        case 4: Y4(Value_Y_Bit); break;
        case 5: Y5(Value_Y_Bit); break;
        case 6: Y6(Value_Y_Bit); break;
        case 7: Y7(Value_Y_Bit); break;
        case 8: Y8(Value_Y_Bit); break;
        case 9: Y9(Value_Y_Bit); break;
        case 10: Y10(Value_Y_Bit); break;
        case 11: Y11(Value_Y_Bit); break;
        case 12: Y12(Value_Y_Bit); break;
        case 13: Y13(Value_Y_Bit); break;
        case 14: Y14(Value_Y_Bit); break;
        case 15: Y15(Value_Y_Bit); break;
        case 16: Y16(Value_Y_Bit); break;
        case 17: Y17(Value_Y_Bit); break;
        case 18: Y18(Value_Y_Bit); break;
        case 19: Y19(Value_Y_Bit); break;
        case 20: Y20(Value_Y_Bit); break;
        case 21: Y21(Value_Y_Bit); break;
        //case 22: Y22(Value_Y_Bit); break;

        case 24: My_Bit.Bit0  = Value_Y_Bit; break;
        case 25: My_Bit.Bit1  = Value_Y_Bit; break;
        case 26: My_Bit.Bit2  = Value_Y_Bit; break;
        case 27: My_Bit.Bit3  = Value_Y_Bit; break;
        case 28: My_Bit.Bit4  = Value_Y_Bit; break;
        case 29: My_Bit.Bit5  = Value_Y_Bit; break;
        case 30: My_Bit.Bit6  = Value_Y_Bit; break;
        case 31: My_Bit.Bit7  = Value_Y_Bit; break;

        case 32: My_Bit.Bit8  = Value_Y_Bit; break;
        case 33: My_Bit.Bit9  = Value_Y_Bit; break;
        case 34: My_Bit.Bit10 = Value_Y_Bit; break;
        case 35: My_Bit.Bit11 = Value_Y_Bit; break;
        case 36: My_Bit.Bit12 = Value_Y_Bit; break;
        case 37: My_Bit.Bit13 = Value_Y_Bit; break;
        case 38: My_Bit.Bit14 = Value_Y_Bit; break;
        case 39: My_Bit.Bit15 = Value_Y_Bit; break;

        case 40: My_Bit.Bit16 = Value_Y_Bit; break;
        case 41: My_Bit.Bit17 = Value_Y_Bit; break;
        case 42: My_Bit.Bit18 = Value_Y_Bit; break;
        case 43: My_Bit.Bit19 = Value_Y_Bit; break;
        case 44: My_Bit.Bit20 = Value_Y_Bit; break;
        case 45: My_Bit.Bit21 = Value_Y_Bit; break;
        case 46: My_Bit.Bit22 = Value_Y_Bit; break;
        case 47: My_Bit.Bit23 = Value_Y_Bit; break;

        case 48: My_Bit.Bit24 = Value_Y_Bit; break;
        case 49: My_Bit.Bit25 = Value_Y_Bit; break;
        case 50: My_Bit.Bit26 = Value_Y_Bit; break;
        case 51: My_Bit.Bit27 = Value_Y_Bit; break;
        case 52: My_Bit.Bit28 = Value_Y_Bit; break;
        case 53: My_Bit.Bit29 = Value_Y_Bit; break;
        case 54: My_Bit.Bit30 = Value_Y_Bit; break;
        case 55: My_Bit.Bit31 = Value_Y_Bit; break;

        case 56: My_Bit.Bit32 = Value_Y_Bit; break;
        case 57: My_Bit.Bit33 = Value_Y_Bit; break;
        case 58: My_Bit.Bit34 = Value_Y_Bit; break;
        case 59: My_Bit.Bit35 = Value_Y_Bit; break;
        case 60: My_Bit.Bit36 = Value_Y_Bit; break;
        case 61: My_Bit.Bit37 = Value_Y_Bit; break;
        case 62: My_Bit.Bit38 = Value_Y_Bit; break;
        case 63: My_Bit.Bit39 = Value_Y_Bit; break;
        default:break;
    }

}

unsigned char In_X(unsigned char Adrr_X)
{
    unsigned char temp = 0;

    switch(Adrr_X)
    {
        case 0:  temp = X0; break;
        case 1:  temp = X1; break;
        case 2:  temp = X2; break;
        case 3:  temp = X3; break;
        case 4:  temp = X4; break;
        case 5:  temp = X5; break;
        case 6:  temp = X6; break;
        case 7:  temp = X7; break;
        case 8:  temp = X8; break;
        case 9:  temp = X9; break;
        case 10: temp = X10; break;
        case 11: temp = X11; break;
        case 12: temp = X12; break;
        case 13: temp = X13; break;
        case 14: temp = X14; break;
        case 15: temp = X15; break;
        case 16: temp = X16; break;
        case 17: temp = X17; break;
        case 18: temp = X18; break;
        case 19: temp = X19; break;
        case 20: temp = X20; break;
        case 21: temp = X21; break;
        case 22: temp = X22; break;
        case 23: temp = X23; break;
        default: temp = 0;break;
    }
    return temp;
}

unsigned char Reg_Y_bit(unsigned char Adrr_Y)
{
    unsigned char temp;
    switch(Adrr_Y)
    {

        case 0: temp = R_Y0; break;
        case 1: temp = R_Y1; break;
        case 2: temp = R_Y2; break;
        case 3: temp = R_Y3; break;
        case 4: temp = R_Y4; break;
        case 5: temp = R_Y5; break;
        case 6: temp = R_Y6; break;
        case 7: temp = R_Y7; break;
        case 8: temp = R_Y8; break;
        case 9: temp = R_Y9; break;
        case 10: temp = R_Y10; break;
        case 11: temp = R_Y11; break;
        case 12: temp = R_Y12; break;
        case 13: temp = R_Y13; break;
        case 14: temp = R_Y14; break;
        case 15: temp = R_Y15; break;
        case 16: temp = R_Y16; break;
        case 17: temp = R_Y17; break;
        case 18: temp = R_Y18; break;
        case 19: temp = R_Y19; break;
        case 20: temp = R_Y20; break;
        case 21: temp = R_Y21; break;
        case 22: temp = R_Y22; break;

        case 24: temp = My_Bit.Bit0; break;
        case 25: temp = My_Bit.Bit1; break;
        case 26: temp = My_Bit.Bit2; break;
        case 27: temp = My_Bit.Bit3; break;
        case 28: temp = My_Bit.Bit4; break;
        case 29: temp = My_Bit.Bit5; break;
        case 30: temp = My_Bit.Bit6; break;
        case 31: temp = My_Bit.Bit7; break;

        case 32: temp = My_Bit.Bit8; break;
        case 33: temp = My_Bit.Bit9; break;
        case 34: temp = My_Bit.Bit10; break;
        case 35: temp = My_Bit.Bit11; break;
        case 36: temp = My_Bit.Bit12; break;
        case 37: temp = My_Bit.Bit13; break;
        case 38: temp = My_Bit.Bit14; break;
        case 39: temp = My_Bit.Bit15; break;

        case 40: temp = My_Bit.Bit16; break;
        case 41: temp = My_Bit.Bit17; break;
        case 42: temp = My_Bit.Bit18; break;
        case 43: temp = My_Bit.Bit19; break;
        case 44: temp = My_Bit.Bit20; break;
        case 45: temp = My_Bit.Bit21; break;
        case 46: temp = My_Bit.Bit22; break;
        case 47: temp = My_Bit.Bit23; break;

        case 48: temp = My_Bit.Bit24; break;
        case 49: temp = My_Bit.Bit25; break;
        case 50: temp = My_Bit.Bit26; break;
        case 51: temp = My_Bit.Bit27; break;
        case 52: temp = My_Bit.Bit28; break;
        case 53: temp = My_Bit.Bit29; break;
        case 54: temp = My_Bit.Bit30; break;
        case 55: temp = My_Bit.Bit31; break;

        case 56: temp = My_Bit.Bit32; break;
        case 57: temp = My_Bit.Bit33; break;
        case 58: temp = My_Bit.Bit34; break;
        case 59: temp = My_Bit.Bit35; break;
        case 60: temp = My_Bit.Bit36; break;
        case 61: temp = My_Bit.Bit37; break;
        case 62: temp = My_Bit.Bit38; break;
        case 63: temp = My_Bit.Bit39; break;
        default:
            break;
    }
    return temp;
}

unsigned char Current_Mian = 0;
unsigned char HuanLiao_state;
void Write_XYZWRV_My_Reg(unsigned char Adrr_Data,unsigned int Value_Axis)
{
    unsigned int HangJu = 0,temp1 = 0,temp2 = 0;
    static unsigned char Temp_Mian = 0;

    switch(Adrr_Data)
    {
        //²ÎÊýÉèÖÃ
        case 0:  XYZ_Data_Buf[Temp_Mian].X_Start_Point         = (long)Value_Axis*X_Bili; break;
        case 1:  XYZ_Data_Buf[Temp_Mian].Y_Start_Point         = (long)Value_Axis*Y_Bili; break;
        case 2:  XYZ_Data_Buf[Temp_Mian].Z_Start_Point         = (long)Value_Axis*Z_Bili; break;
        case 3:  XYZ_Data_Buf[Temp_Mian].W_Start_Point         = (long)((int)Value_Axis)*W_Bili; break;
        case 4:  XYZ_Data_Buf[Temp_Mian].V_Start_Point         = (long)((int)Value_Axis)*A_Bili; break;
        case 5:  XYZ_Data_Buf[Temp_Mian].R_Start_Point         = (long)Value_Axis*B_Bili; break;
        case 6:  XYZ_Data_Buf[Temp_Mian].X_Stop_Point          = (long)Value_Axis*X_Bili; break;
        case 7:  XYZ_Data_Buf[Temp_Mian].Y_Stop_Point          = (long)Value_Axis*Y_Bili; break;
        case 8:  XYZ_Data_Buf[Temp_Mian].Z_Stop_Point          = (long)Value_Axis*Z_Bili; break;
        case 9:  XYZ_Data_Buf[Temp_Mian].W_Stop_Point          = (long)((int)Value_Axis)*W_Bili; break;
        case 10: XYZ_Data_Buf[Temp_Mian].V_Stop_Point          = (long)((int)Value_Axis)*A_Bili; break;
        case 11: XYZ_Data_Buf[Temp_Mian].R_Stop_Point          = (long)Value_Axis*B_Bili; break;
        case 12: XYZ_Data_Buf[Temp_Mian].X_Speed               = Speed_Bili*Value_Axis;         break;
        case 13: XYZ_Data_Buf[Temp_Mian].Y_Speed               = Speed_Bili*Value_Axis;         break;
        case 14: XYZ_Data_Buf[Temp_Mian].Z_Speed               = Speed_Bili*Value_Axis;         break;
        case 15: XYZ_Data_Buf[Temp_Mian].W_Speed               = Speed_Bili*Value_Axis;         break;
        case 16: XYZ_Data_Buf[Temp_Mian].V_Speed               = Speed_Bili*Value_Axis;         break;
        case 17: XYZ_Data_Buf[Temp_Mian].R_Speed               = Speed_Bili*Value_Axis;         break;

        case 18: XYZ_Data_Buf[Temp_Mian].WangFu_CiShu          = Value_Axis;         break;
        case 19: XYZ_Data_Buf[Temp_Mian].BuJin_HangCi          = Value_Axis;         break;
        case 20: XYZ_Data_Buf[Temp_Mian].BuJin_HangJu          = (long)((int)Value_Axis);    break;
        case 21: XYZ_Data_Buf[Temp_Mian].PenTu_Model           = (unsigned char)Value_Axis;
                 switch(XYZ_Data_Buf[Temp_Mian].PenTu_Model)
                 {
                    case 5:
                    case 9:
                    case 13:
                    case 17: HangJu = X_Bili;break;
                    case 1:
                    case 10:
                    case 14:
                    case 18: HangJu = Y_Bili;break;
                    case 2:
                    case 6:
                    case 15:
                    case 19: HangJu = W_Bili;break;
                    case 3:
                    case 7:
                    case 11:
                    case 20: HangJu = Z_Bili;break;
                    case 21:
                    case 22:
                    case 23:
                        if(XYZ_Data_Buf[Temp_Mian].Y_Start_Point > XYZ_Data_Buf[Temp_Mian].Y_Stop_Point)
                            temp1 = (XYZ_Data_Buf[Temp_Mian].Y_Start_Point - XYZ_Data_Buf[Temp_Mian].Y_Stop_Point);
                        else
                            temp1 = (XYZ_Data_Buf[Temp_Mian].Y_Stop_Point - XYZ_Data_Buf[Temp_Mian].Y_Start_Point);

                        if(XYZ_Data_Buf[Temp_Mian].X_Start_Point > XYZ_Data_Buf[Temp_Mian].X_Stop_Point)
                            temp2 = (XYZ_Data_Buf[Temp_Mian].X_Start_Point - XYZ_Data_Buf[Temp_Mian].X_Stop_Point);
                        else
                            temp2 = (XYZ_Data_Buf[Temp_Mian].X_Stop_Point - XYZ_Data_Buf[Temp_Mian].X_Start_Point);

                        if(temp1 > temp2)
                            XYZ_Data_Buf[Temp_Mian].X_Speed = temp2/(temp1/XYZ_Data_Buf[Temp_Mian].Y_Speed);
                        else
                            XYZ_Data_Buf[Temp_Mian].Y_Speed = temp1/(temp2/XYZ_Data_Buf[Temp_Mian].X_Speed);
                    break;

                    case 24:
                    case 25:
                    case 26:
                        if(XYZ_Data_Buf[Temp_Mian].Z_Start_Point > XYZ_Data_Buf[Temp_Mian].Z_Stop_Point)
                            temp1 = (XYZ_Data_Buf[Temp_Mian].Z_Start_Point - XYZ_Data_Buf[Temp_Mian].Z_Stop_Point);
                        else
                            temp1 = (XYZ_Data_Buf[Temp_Mian].Z_Stop_Point - XYZ_Data_Buf[Temp_Mian].Z_Start_Point);

                        if(XYZ_Data_Buf[Temp_Mian].X_Start_Point > XYZ_Data_Buf[Temp_Mian].X_Stop_Point)
                            temp2 = (XYZ_Data_Buf[Temp_Mian].X_Start_Point - XYZ_Data_Buf[Temp_Mian].X_Stop_Point);
                        else
                            temp2 = (XYZ_Data_Buf[Temp_Mian].X_Stop_Point - XYZ_Data_Buf[Temp_Mian].X_Start_Point);

                        if(temp1 > temp2)
                            XYZ_Data_Buf[Temp_Mian].X_Speed = temp2/(temp1/XYZ_Data_Buf[Temp_Mian].Z_Speed);
                        else
                            XYZ_Data_Buf[Temp_Mian].Z_Speed = temp1/(temp2/XYZ_Data_Buf[Temp_Mian].X_Speed);
                    break;

                    case 27:
                    case 28:
                    case 29:
                        if(XYZ_Data_Buf[Temp_Mian].Z_Start_Point > XYZ_Data_Buf[Temp_Mian].Z_Stop_Point)
                            temp1 = (XYZ_Data_Buf[Temp_Mian].Z_Start_Point - XYZ_Data_Buf[Temp_Mian].Z_Stop_Point);
                        else
                            temp1 = (XYZ_Data_Buf[Temp_Mian].Z_Stop_Point - XYZ_Data_Buf[Temp_Mian].Z_Start_Point);

                        if(XYZ_Data_Buf[Temp_Mian].Y_Start_Point > XYZ_Data_Buf[Temp_Mian].Y_Stop_Point)
                            temp2 = (XYZ_Data_Buf[Temp_Mian].Y_Start_Point - XYZ_Data_Buf[Temp_Mian].Y_Stop_Point);
                        else
                            temp2 = (XYZ_Data_Buf[Temp_Mian].Y_Stop_Point - XYZ_Data_Buf[Temp_Mian].Y_Start_Point);

                        if(temp1 > temp2)
                            XYZ_Data_Buf[Temp_Mian].Y_Speed = temp2/(temp1/XYZ_Data_Buf[Temp_Mian].Z_Speed);
                        else
                            XYZ_Data_Buf[Temp_Mian].Z_Speed = temp1/(temp2/XYZ_Data_Buf[Temp_Mian].Y_Speed);
                    break;
                 }
                 switch(XYZ_Data_Buf[Temp_Mian].PenTu_Model)
                {
                    case 21:
                    case 24:
                    case 27: HangJu = X_Bili;break;
                    case 22:
                    case 25:
                    case 28: HangJu = Y_Bili;break;
                    case 23:
                    case 26:
                    case 29: HangJu = Z_Bili;break;
                    default:break;
                }
                 XYZ_Data_Buf[Temp_Mian].BuJin_HangJu          = XYZ_Data_Buf[Temp_Mian].BuJin_HangJu*HangJu;break;
        case 22: XYZ_Data_Buf[Temp_Mian].TingQiang_XuanZe      = (unsigned char)Value_Axis;  break;
        case 23: XYZ_Data_Buf[Temp_Mian].PenQiang_Model        = (unsigned char)Value_Axis;  break;
        case 24: XYZ_Data_Buf[Temp_Mian].ZuHe_Model            = (unsigned char)Value_Axis;  break;
        case 25: XYZ_Data_Buf[Temp_Mian].Actual_Mian           = (long)Value_Axis;

                if((++Temp_Mian) >= 20)
                {
                    Temp_Mian = 0;
                    Trans_finish(0);
                }
                else
                    Trans_finish(1);
                break;
         //ÏµÍ³²ÎÊý¼Ä´æÆ÷
        case 26: Global_Data.X_Back_Speed           =  Speed_Bili*Value_Axis;        break;
        case 27: Global_Data.X_Init_Speed           =  Speed_Bili*Value_Axis;        break;
        case 28: Global_Data.Y_Back_Speed           =  Speed_Bili*Value_Axis;        break;
        case 29: Global_Data.Y_Init_Speed           =  Speed_Bili*Value_Axis;        break;
        case 30: Global_Data.X_Safe_Point           =  (long)Value_Axis*X_Bili;     break;
        case 31: Global_Data.Y_Safe_Point           =  (long)Value_Axis*Y_Bili;     break;
        case 32: Global_Data.Z_Init_Speed           =  Speed_Bili*Value_Axis;        break;
        case 33: Global_Data.W_Init_Speed           =  Speed_Bili*Value_Axis;        break;

        case 34: Global_Data.Z_Back_Speed           =  Speed_Bili*Value_Axis;        break;
        case 35: Global_Data.Z_Safe_Point           =  (long)Value_Axis*Z_Bili;    break;
        case 36: Global_Data.W_Safe_Point           =  (long)((int)Value_Axis)*W_Bili;     break;
        case 37: Global_Data.SpeedX                 =  (float)Value_Axis*0.2;              break;

        case 38: Global_Data.X_AnQuan_FanWei        = (long)Value_Axis*X_Bili;        break;
        case 39: Global_Data.Y_AnQuan_FanWei        = (long)Value_Axis*Y_Bili;        break;
        case 40: Global_Data.Z_AnQuan_FanWei        = (long)Value_Axis*Z_Bili;        break;
        case 41: Global_Data.W_AnQuan_FanWei        = (long)((int)Value_Axis)*W_Bili;  break;
        case 42: Global_Data.CuiMo_Speed            = Value_Axis*Speed_Bili;               break;
        case 43: Global_Data.DingDianQi_YanShi      = Value_Axis;        break;

        case 44: Global_Data.ShuiBeng_YanShi         =  (long)Value_Axis*10000;        break;
        case 45: Global_Data.ShuLiang_XiMo          =   Value_Axis;        break;
        case 46: Global_Data.CuiMo_CiShu             =  Value_Axis;        break;
        case 47: Global_Data.ShangCuiQi_CiShu       =  Value_Axis;    break;
        case 48: Global_Data.KaiQiang_YanShi        =  Value_Axis*10;     break;
        case 49: Global_Data.WuHua_YanShi           =  Value_Axis*10;     break;


        case 50: ABC_XiMo_Data[Temp_Mian].A_Start_Point                  =  (long)Value_Axis*A_Bili;        break;
        case 51: ABC_XiMo_Data[Temp_Mian].B_Start_Point                  =  (long)Value_Axis*B_Bili;        break;
        case 52: ABC_XiMo_Data[Temp_Mian].C_Point                        =  (long)Value_Axis*C_Bili;        break;
        case 53: ABC_XiMo_Data[Temp_Mian].A_Stop_Point                   =  (long)Value_Axis*A_Bili;        break;
        case 54: ABC_XiMo_Data[Temp_Mian].B_Stop_Point                   =  (long)Value_Axis*B_Bili;        break;
        case 55: ABC_XiMo_Data[Temp_Mian].XiMo_WangFu_Speed              =  Value_Axis*Speed_Bili;        break;
        case 56: ABC_XiMo_Data[Temp_Mian].XiMo_WangFu_Num                =  Value_Axis;                   break;
        case 57: ABC_XiMo_Data[Temp_Mian].XiMo_BuJin_Num                 =  Value_Axis;                  break;
        case 58: ABC_XiMo_Data[Temp_Mian].XiMo_Model                     =  Value_Axis;                  break;
        case 59: ABC_XiMo_Data[Temp_Mian].XiMo_ZuHe_Model           =  Value_Axis;
                if((++Temp_Mian) >= 20)
                {
                    Temp_Mian = 0;
                    Trans_finish2(0);
                }
                else
                    Trans_finish2(1);
                break;

        case 60: JiXieShou_Data.Move_Start = (long)Value_Axis*D_Bili;   break;
        case 61: JiXieShou_Data.Move_Stop = (long)Value_Axis*D_Bili;   break;
        case 62: JiXieShou_Data.Move_Speed = Value_Axis*Speed_Bili;   break;
         /*
        case 58:  Set_Actual_Point(MOTOR_X, (long)Value_Axis*X_Bili);  break;
        case 59:  Set_Actual_Point(MOTOR_Y, (long)Value_Axis*Y_Bili);  break;
        case 60:  Set_Actual_Point(MOTOR_Z, (long)Value_Axis*Z_Bili);  break;
        case 61:  Set_Actual_Point(MOTOR_W, (long)Value_Axis*W_Bili);  break;
        case 62:  Set_Actual_Point(motor_temp, (long)Value_Axis*A_Bili);  break;
        case 63:  Set_Actual_Point(MOTOR_B, (long)Value_Axis*B_Bili);  break;
        case 64:  break;
           */
        case 66:  My_Reg[0]                          = Value_Axis;   break;
        case 67:  My_Reg[1]                          = Value_Axis;   break;
        case 68:  My_Reg[2]                          = Value_Axis;   break;
        case 69:  My_Reg[3]                          = Value_Axis;   break;
        case 70:  My_Reg[4]                          = Value_Axis;   break;
        case 71:  My_Reg[5]                          = Value_Axis;   break;
        case 72:  My_Reg[6]                          = Value_Axis;   break;
        case 73:  My_Reg[7]                          = Value_Axis;   break;
        case 74:  My_Reg[8]                          = Value_Axis;   break;
        case 75:  My_Reg[9]                          = Value_Axis;   break;
        case 76:  My_Reg[10]                         = Value_Axis;   break;
        case 77:  My_Reg[11]                         = Value_Axis;   break;
        case 78:  My_Reg[12]                         = Value_Axis;   break;
        case 79:  My_Reg[13]                         = Value_Axis;   break;
        case 80:  My_Reg[14]                         = Value_Axis;   break;
        case 81:  My_Reg[15]                         = Value_Axis;   break;
        case 82:  My_Reg[16]                         = Value_Axis;   break;
        case 83:  My_Reg[17]                         = Value_Axis;   break;
        case 84:  My_Reg[18]                         = Value_Axis;   break;
        case 85:  My_Reg[19]                         = Value_Axis;   break;
        default:    break;
    }

}

float AxisNum[3] = {'X','Y','Z'};
#define XAXISNUM    (AxisNum[0])
#define YAXISNUM    (AxisNum[1])
#define ZAXISNUM    (AxisNum[2])
unsigned char count,count2;
unsigned int Read_XYZWRV_My_Reg(unsigned char Start_Adrr)
{
    unsigned int temp,HangJu = 0;
    switch(Start_Adrr)
    {
        //²ÎÊýÉèÖÃ
        case 0:  temp   = XYZ_Data_Buf[Current_Mian].X_Start_Point/X_Bili;       break;
        case 1:  temp   = XYZ_Data_Buf[Current_Mian].Y_Start_Point/Y_Bili;       break;
        case 2:  temp   = XYZ_Data_Buf[Current_Mian].Z_Start_Point/Z_Bili;       break;
        case 3:  temp   = XYZ_Data_Buf[Current_Mian].W_Start_Point/W_Bili;       break;
        case 4:  temp   = XYZ_Data_Buf[Current_Mian].V_Start_Point/A_Bili;       break;
        case 5:  temp   = XYZ_Data_Buf[Current_Mian].R_Start_Point/B_Bili;       break;
        case 6:  temp   = XYZ_Data_Buf[Current_Mian].X_Stop_Point/X_Bili;        break;
        case 7:  temp   = XYZ_Data_Buf[Current_Mian].Y_Stop_Point/Y_Bili;        break;
        case 8:  temp   = XYZ_Data_Buf[Current_Mian].Z_Stop_Point/Z_Bili;        break;
        case 9:  temp   = XYZ_Data_Buf[Current_Mian].W_Stop_Point/W_Bili;        break;
        case 10: temp   = XYZ_Data_Buf[Current_Mian].V_Stop_Point/A_Bili;        break;
        case 11: temp   = XYZ_Data_Buf[Current_Mian].R_Stop_Point/B_Bili;        break;
        case 12: temp   = XYZ_Data_Buf[Current_Mian].X_Speed/Speed_Bili;             break;
        case 13: temp   = XYZ_Data_Buf[Current_Mian].Y_Speed/Speed_Bili;             break;
        case 14: temp   = XYZ_Data_Buf[Current_Mian].Z_Speed/Speed_Bili;             break;
        case 15: temp   = XYZ_Data_Buf[Current_Mian].W_Speed/Speed_Bili;             break;
        case 16: temp   = XYZ_Data_Buf[Current_Mian].V_Speed/Speed_Bili;             break;
        case 17: temp   = XYZ_Data_Buf[Current_Mian].R_Speed/Speed_Bili;             break;

        case 18: temp   = XYZ_Data_Buf[Current_Mian].WangFu_CiShu;        break;
        case 19: temp   = XYZ_Data_Buf[Current_Mian].BuJin_HangCi;        break;
        case 20:
                 switch(XYZ_Data_Buf[Current_Mian].PenTu_Model)
                 {
                    case 5:
                    case 9:
                    case 13:
                    case 17: HangJu = X_Bili;break;
                    case 1:
                    case 10:
                    case 14:
                    case 18: HangJu = Y_Bili;break;
                    case 2:
                    case 6:
                    case 15:
                    case 19: HangJu = W_Bili;break;
                    case 3:
                    case 7:
                    case 11:
                    case 16:
                    case 20: HangJu = A_Bili;break;
                 }
                 temp   = XYZ_Data_Buf[Current_Mian].BuJin_HangJu/HangJu;break;
        case 21: temp   = XYZ_Data_Buf[Current_Mian].PenTu_Model;         break;
        case 22: temp   = XYZ_Data_Buf[Current_Mian].TingQiang_XuanZe;    break;
        case 23: temp   = XYZ_Data_Buf[Current_Mian].PenQiang_Model;      break;
        case 24: temp   = XYZ_Data_Buf[Current_Mian].ZuHe_Model;          break;
        case 25: temp   = XYZ_Data_Buf[Current_Mian].Actual_Mian;         break;

         //ÏµÍ³²ÎÊý¼Ä´æÆ÷
        case 26: temp   = Global_Data.X_Back_Speed/Speed_Bili;         break;
        case 27: temp   = Global_Data.X_Init_Speed/Speed_Bili;         break;
        case 28: temp   = Global_Data.Y_Back_Speed/Speed_Bili;         break;
        case 29: temp   = Global_Data.Y_Init_Speed/Speed_Bili;         break;
        case 30: temp   = Global_Data.X_Safe_Point/X_Bili;      break;
        case 31: temp   = Global_Data.Y_Safe_Point/Y_Bili;      break;
        case 32: temp   = Global_Data.Z_Init_Speed/Speed_Bili;         break;
        case 33: temp   = Global_Data.W_Init_Speed/Speed_Bili;         break;
        case 34: temp   = Global_Data.Z_Back_Speed/Speed_Bili;          break;
        case 35: temp   = Global_Data.Z_Safe_Point/Z_Bili;          break;
        case 36: temp   = Global_Data.W_Safe_Point/W_Bili;      break;
        case 37: temp   = Global_Data.SpeedX;              break;

        case 38: temp   = Global_Data.X_AnQuan_FanWei/X_Bili;      break;
        case 39: temp   = Global_Data.Y_AnQuan_FanWei/Y_Bili;      break;
        case 40: temp   = Global_Data.Z_AnQuan_FanWei/Z_Bili;     break;
        case 41: temp   = Global_Data.W_AnQuan_FanWei/W_Bili;      break;
        case 42: temp   = Global_Data.CuiMo_Speed;           break;
        case 43: temp   = Global_Data.DingDianQi_YanShi;       break;

        case 44: temp   = Global_Data.ShuiBeng_YanShi;                  break;
        case 45: temp   = Global_Data.ShuLiang_XiMo;                break;
        case 46: temp   = Global_Data.CuiMo_CiShu;                   break;
        case 47: temp   = Global_Data.ShangCuiQi_CiShu;   break;
        case 48: temp   = Global_Data.KaiQiang_YanShi/10;           break;
        case 49: temp   = Global_Data.WuHua_YanShi/10;              break;


        case 58: temp   = QueueGetDataCount(&Uart1QCMDr); break;
        case 59: temp   = QueueGetDataCount(&Uart1QCMDs); break;
        case 60: temp   = QueueGetDataCount(&Uart2QCMDr); break;
        case 61: temp   = QueueGetDataCount(&Uart2QCMDs); break;
        case 62:  /*GetActualPosition(MOTOR_A, &A_Actual_Point); temp = (A_Actual_Point)/A_Bili;*/break;
        case 63:  /*GetActualPosition(MOTOR_B, &B_Actual_Point); temp = (B_Actual_Point)/B_Bili;*/break;
        case 64:  /*GetActualPosition(MOTOR_C, &C_Actual_Point); temp = (C_Actual_Point)/C_Bili;*/break;
        case 65:  /*GetActualPosition(MOTOR_D, &D_Actual_Point); temp = (D_Actual_Point)/D_Bili;*/break;

        case 66:  temp   = My_Reg[0];   break;
        case 67:  temp   = My_Reg[1];   break;
        case 68:  temp   = My_Reg[2];   break;
        case 69:  temp   = My_Reg[3];   break;
        case 70:  temp   = My_Reg[4];   break;
        case 71:  temp   = My_Reg[5];   break;
        case 72:  temp   = My_Reg[6];   break;
        case 73:  temp   = My_Reg[7];   break;

        case 74:  temp   = My_Reg[8];   break;
        case 75:  temp   = My_Reg[9];   break;
        case 76:  temp   = My_Reg[10];  break;
        case 77:  temp   = My_Reg[11];  break;
        case 78:  temp   = My_Reg[12];  break;
        case 79:  temp   = My_Reg[13];  break;
        case 80:  temp   = My_Reg[14];  break;
        case 81:  temp   = My_Reg[15];  break;

        case 82:  temp   = My_Reg[16];  break;
        case 83:  temp   = My_Reg[17];  break;
        case 84:  temp   = My_Reg[18];  break;
        case 85:  temp   = My_Reg[19];  break;
        default:break;
    }
    return temp;
}

