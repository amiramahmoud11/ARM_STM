#include "../../include/UART.h"

// System clock frequency
#define F_CLK  1600000

// Constants for UART baud rate calculation
#define UART_OVERFLOW_FRACTION 0x10
#define UART_MANTESSA  0xF0

// Bit manipulation constants
#define FOUR_BIT_SHIFT 4
#define FRACTION_MASK 0x0F
#define USART_ENABLE 0x00002000

// Number of USART peripherals
#define USART_PREPHERALS  3

// Structure representing UART registers
typedef struct 
{
   volatile  u32 SR;       /**< Status register */
    volatile u32 DR;       /**< Data register */
    volatile u32 BRR;      /**< Baud rate register */
    volatile u32 CR1;      /**< Control register 1 */
    volatile u32 CR2;      /**< Control register 2 */
    volatile u32 CR3;      /**< Control register 3 */
    volatile u32 GTPR;     /**< Guard time and prescaler register */
} UART_REG;

// Structure representing a data buffer
typedef struct
{
    u8 *data;   /**< Pointer to the data buffer */
    u32 pos;    /**< Current position in the buffer */
    u32 size;   /**< Size of the buffer */
} buffer_t;

// Structure representing a transmission request
typedef struct
{
    buffer_t buffer;        /**< Data buffer */
    u8 state;               /**< State of the transmission */
    CallBack_t CallBack;    /**< Callback function */
} TX_Req_t;

// Structure representing a receive request
typedef struct
{
    buffer_t buffer;        /**< Data buffer */
    u8 state;               /**< State of the reception */
    CallBack_t CallBack;    /**< Callback function */
} RX_Req_t;

// Array holding USART peripherals' base addresses
void* UsartPrepherals[USART_PREPHERALS]={(void*)0x40011000 , (void*)0x40004400,(void*)0x40011400}; 
TX_Req_t TX_Request[USART_PREPHERALS];    /**< Array of transmission requests */
RX_Req_t RX_Request[USART_PREPHERALS];    /**< Array of receive requests */
LBD_CallBack_t LBD_CB[USART_PREPHERALS]={NULL,NULL,NULL};

// Function to initialize USART peripheral
Error_tatuse uart_int(uart_configuration uart_config)
{
    u32 Loc_USARTDIV_Value;     /**< Variable to hold calculated USARTDIV value */
    u16 Loc_mantissa;           /**< Variable to hold mantissa part of BRR value */
    u16 loc_fraction ;          /**< Variable to hold fractional part of BRR value */
    u32 Loc_BBRValue=0;         /**< Variable to hold final BRR value */
    u32 Loc_CR1Value=0;         /**< Variable to hold value for CR1 register */
    u32 Loc_CR2Value=0;         /**< Variable to hold value for CR2 register */
    Error_tatuse loc_errorStatuse=Statuse_Ok; /**< Error status, initialized to OK */
    
    // Check for invalid input configurations
    if (uart_config.address>USART_6||uart_config.overSampling>USART_OVER_8)
    {
        loc_errorStatuse=Invalid_Inputs;
    }
    else if (uart_config.WordLength>USART_9_DATABIT||uart_config.stopBit>USART_2_STOP_BIT)
    {
        loc_errorStatuse=Invalid_Inputs;
    }
    else if (uart_config.paritycontrol>USART_PARITY_ENABLE||uart_config.parityselect>USART_PARITY_ODD)
    {
        loc_errorStatuse=Invalid_Inputs;
    }
    else
    {
        // Calculate USARTDIV value for baud rate generation
        Loc_USARTDIV_Value=(F_CLK)/(8*(2-uart_config.overSampling)*uart_config.baudrate);
        Loc_mantissa = Loc_USARTDIV_Value / 1000;
        loc_fraction=(Loc_USARTDIV_Value% 1000) * (8 * (2 - uart_config.overSampling));

        // Round fraction part
        if(loc_fraction%1000>=500)
        {
            loc_fraction=(loc_fraction/1000)+1;
        }
        else
        {
            loc_fraction=(loc_fraction/1000);
        }
        // Check if fraction exceeds maximum allowed
        if (loc_fraction>UART_OVERFLOW_FRACTION)
        {
            Loc_mantissa+=(loc_fraction&UART_MANTESSA);
        }

        // Combine mantissa and fraction to form BRR value
        Loc_BBRValue=(Loc_mantissa<<FOUR_BIT_SHIFT)|(loc_fraction&FRACTION_MASK);
        // Configure CR1 register
        Loc_CR1Value=USART_ENABLE|uart_config.overSampling|uart_config.WordLength|uart_config.paritycontrol|uart_config.parityselect;
        // Configure CR2 register
        Loc_CR2Value=uart_config.stopBit;

        // Write values to USART registers
        ((UART_REG *)UsartPrepherals[uart_config.address])->BRR=Loc_BBRValue;
        ((UART_REG *)UsartPrepherals[uart_config.address])->CR1=Loc_CR1Value;
        ((UART_REG *)UsartPrepherals[uart_config.address])->CR2=Loc_CR2Value;
    }
    
    // Return error status
    return loc_errorStatuse;
}

// Function to send a byte via USART
Error_tatuse UASART_SendByte(USART_Req_t Usart_Req)
{
    u32 Time_Out=1000;      /**< Timeout value */
    Error_tatuse loc_errorStatuse=Statuse_Nok; /**< Initialize error status to NOK */

    // Check for invalid input parameters
    if (Usart_Req.USART_Peri>USART_6)
    {
        loc_errorStatuse=Invalid_Inputs;
    }
    else if (Usart_Req.length>1)
    {
       loc_errorStatuse=Invalid_Inputs;
    }
    else if (TX_Request[Usart_Req.USART_Peri].state==USART_STATE_BUSY)
    {
       loc_errorStatuse=State_busy;
    }
    else
    {
        // Start transmission
        loc_errorStatuse=Statuse_Ok;
        TX_Request[Usart_Req.USART_Peri].state=USART_STATE_BUSY;
        ((UART_REG *)UsartPrepherals[Usart_Req.USART_Peri])->DR=*(Usart_Req.buffer);

        // Wait for transmission to complete or timeout
        while (Time_Out)
        {
            Time_Out--;
        }
        TX_Request[Usart_Req.USART_Peri].state=USART_STATE_READY;
    }
    
    // Return error status
    return loc_errorStatuse;
}

// Function to receive a byte via USART
Error_tatuse UASART_GetByte(USART_Req_t Usart_Req)
{
    u32 Time_Out=1000;      /**< Timeout value */
    Error_tatuse loc_errorStatuse=Statuse_Nok; /**< Initialize error status to NOK */

    // Check for invalid input parameters
    if (Usart_Req.USART_Peri>USART_6)
    {
        loc_errorStatuse=Invalid_Inputs;
    }
    else if (Usart_Req.buffer==NULL)
    {
       loc_errorStatuse=Status_NULL_Pointer;
    }
    else if (Usart_Req.length>1)
    {
       loc_errorStatuse=Invalid_Inputs;
    }
    else if ((RX_Request[Usart_Req.USART_Peri].state)==USART_STATE_BUSY)
    {
       loc_errorStatuse=State_busy;
    }
    else
    {
        loc_errorStatuse=Statuse_Ok;
        RX_Request[Usart_Req.USART_Peri].state=USART_STATE_BUSY;
        
        // Wait until receive buffer is not empty or timeout
        while (!((((UART_REG *)UsartPrepherals[Usart_Req.USART_Peri])->SR)&UART_TXE_MASK)&&Time_Out)
        {
            Time_Out--;
        }
        // Check for timeout
        if (Time_Out==0 && (((((UART_REG *)UsartPrepherals[Usart_Req.USART_Peri])->SR)&UART_TXE_MASK)==0))
        {
           loc_errorStatuse= Status_usart_timeout;
        }
        else
        {
            // Read received byte
            *(Usart_Req.buffer)=((UART_REG *)UsartPrepherals[Usart_Req.USART_Peri])->DR;
        }
        
        RX_Request[Usart_Req.USART_Peri].state=USART_STATE_READY;
    }
    
    // Return error status
    return loc_errorStatuse;
}

/* send buffer */

Error_tatuse UASART_SendBufferAsyncZeroCopy(USART_Req_t Usart_Req)
{
    Error_tatuse loc_errorStatuse=Statuse_Nok;

    // Check for invalid input parameters
    if (Usart_Req.USART_Peri>USART_6)
    {
        loc_errorStatuse=Invalid_Inputs;
    }
    else if (TX_Request[Usart_Req.USART_Peri].state==USART_STATE_BUSY)
    {
       loc_errorStatuse=State_busy;
    }
    else if (Usart_Req.buffer==NULL)
    {
       loc_errorStatuse=Status_NULL_Pointer;
    }
    else
    {
        // Start transmission
        loc_errorStatuse=Statuse_Ok;
        
        // Initialize transmission request parameters
        TX_Request[Usart_Req.USART_Peri].buffer.data=Usart_Req.buffer;
        TX_Request[Usart_Req.USART_Peri].buffer.size=Usart_Req.length;
        TX_Request[Usart_Req.USART_Peri].buffer.pos=0;
        TX_Request[Usart_Req.USART_Peri].CallBack=Usart_Req.CB;
        TX_Request[Usart_Req.USART_Peri].state=USART_STATE_BUSY;

        // Send first byte
        ((UART_REG *)UsartPrepherals[Usart_Req.USART_Peri])->DR=TX_Request[Usart_Req.USART_Peri].buffer.data[0];
        TX_Request[Usart_Req.USART_Peri].buffer.pos++;
        
        // Enable TX interrupt
        ((UART_REG *)UsartPrepherals[Usart_Req.USART_Peri])->CR1|=USART_RXNEIE_ENABLE_FLAG;
    }
    
    // Return error status
    return loc_errorStatuse;
}

/* receive buffer */

Error_tatuse UASART_ReciveBufferAsyncZeroCopy(USART_Req_t Usart_Req)
{
    Error_tatuse loc_errorStatuse=Statuse_Nok;

    // Check for invalid input parameters
    if (Usart_Req.USART_Peri>USART_6)
    {
        loc_errorStatuse=Invalid_Inputs;
    }
    else if (TX_Request[Usart_Req.USART_Peri].state==USART_STATE_BUSY)
    {
       loc_errorStatuse=State_busy;
    }
    else if (Usart_Req.buffer==NULL)
    {
       loc_errorStatuse=Status_NULL_Pointer;
    }
    else
    {
        // Start reception
        loc_errorStatuse=Statuse_Ok;
        
        // Initialize reception request parameters
        RX_Request[Usart_Req.USART_Peri].buffer.data=Usart_Req.buffer;
        RX_Request[Usart_Req.USART_Peri].buffer.size=Usart_Req.length;
        RX_Request[Usart_Req.USART_Peri].buffer.pos=0;
        RX_Request[Usart_Req.USART_Peri].CallBack=Usart_Req.CB;
        RX_Request[Usart_Req.USART_Peri].state=USART_STATE_BUSY;

         /* Clear RXNE flag */
        ((UART_REG *)UsartPrepherals[Usart_Req.USART_Peri])->SR&=~USART_RX_DONE_IRQ;
        TX_Request[Usart_Req.USART_Peri].buffer.pos++;
        /* Enable RXNE interrupt */
        ((UART_REG *)UsartPrepherals[Usart_Req.USART_Peri])->CR1|=USART_RXNEIE_ENABLE_FLAG;
    }
    
    // Return error status
    return loc_errorStatuse;
}

//USART1_IRQHandler();

void USART1_IRQHandler(void)
{
    if ( ((UART_REG *)UsartPrepherals[USART_1])->SR&USART_LBD_ENABLE)
    {
        /* clear LBD flag */
        ((UART_REG *)UsartPrepherals[USART_1])->SR&=~USART_LBD_ENABLE;
        if (LBD_CB[USART_1])
        {
           LBD_CB[USART_1](); 
        }
        

    }
    else
    {
        if (((UART_REG *)UsartPrepherals[USART_1])->SR&USART_TXE_ENABLE_FLAG)
        {
            if (TX_Request[USART_1].buffer.pos<TX_Request[USART_1].buffer.size)
            {
               ((UART_REG *)UsartPrepherals[USART_1])->DR=TX_Request[USART_1].buffer.data[TX_Request[USART_1].buffer.pos];
               TX_Request[USART_1].buffer.pos++;
            }
            else
            {
                TX_Request[USART_1].state=USART_STATE_READY;
                /*clear TEI*/
                ((UART_REG *)UsartPrepherals[USART_1])->CR1&=~UART_TXEIE_ENABLE_FLAG;
                /*notify user*/
                TX_Request[USART_1].CallBack();
            }
            
        }

        if (((UART_REG *)UsartPrepherals[USART_1])->SR&USART_RXE_ENABLE_FLAG)
        {
            if (RX_Request[USART_1].buffer.pos<RX_Request[USART_1].buffer.size)
            {
               ((UART_REG *)UsartPrepherals[USART_1])->DR=RX_Request[USART_1].buffer.data[RX_Request[USART_1].buffer.pos];
               RX_Request[USART_1].buffer.pos++;

               if(RX_Request[USART_1].buffer.pos==RX_Request[USART_1].buffer.size)
                {
                    RX_Request[USART_1].state=USART_STATE_READY;
                    /*clear REI*/
                    ((UART_REG *)UsartPrepherals[USART_1])->CR1&=~USART_RXNEIE_ENABLE_FLAG;
                    /*notify user*/
                    RX_Request[USART_1].CallBack();
                }
            }
            
            
        }
        
    }
    
}


//USART2_IRQHandler();

void USART2_IRQHandler(void)
{
    if ( ((UART_REG *)UsartPrepherals[USART_2])->SR&USART_LBD_ENABLE)
    {
        /* clear LBD flag */
        ((UART_REG *)UsartPrepherals[USART_2])->SR&=~USART_LBD_ENABLE;
        if (LBD_CB[USART_2])
        {
           LBD_CB[USART_2](); 
        }
        

    }
    else
    {
        if (((UART_REG *)UsartPrepherals[USART_2])->SR&USART_TXE_ENABLE_FLAG)
        {
            if (TX_Request[USART_2].buffer.pos<TX_Request[USART_2].buffer.size)
            {
               ((UART_REG *)UsartPrepherals[USART_2])->DR=TX_Request[USART_2].buffer.data[TX_Request[USART_2].buffer.pos];
               TX_Request[USART_2].buffer.pos++;
            }
            else
            {
                TX_Request[USART_2].state=USART_STATE_READY;
                /*clear TEI*/
                ((UART_REG *)UsartPrepherals[USART_2])->CR1&=~UART_TXEIE_ENABLE_FLAG;
                /*notify user*/
                TX_Request[USART_2].CallBack();
            }
            
        }

        if (((UART_REG *)UsartPrepherals[USART_2])->SR&USART_RXE_ENABLE_FLAG)
        {
            if (RX_Request[USART_2].buffer.pos<RX_Request[USART_2].buffer.size)
            {
               ((UART_REG *)UsartPrepherals[USART_2])->DR=RX_Request[USART_2].buffer.data[RX_Request[USART_2].buffer.pos];
               RX_Request[USART_2].buffer.pos++;

               if(RX_Request[USART_2].buffer.pos==RX_Request[USART_2].buffer.size)
                {
                    RX_Request[USART_2].state=USART_STATE_READY;
                    /*clear REI*/
                    ((UART_REG *)UsartPrepherals[USART_2])->CR1&=~USART_RXNEIE_ENABLE_FLAG;
                    /*notify user*/
                    RX_Request[USART_2].CallBack();
                }
            }
            
            
        }
        
    }
    
}


//USART6_IRQHandler();

void USART6_IRQHandler(void)
{
    if ( ((UART_REG *)UsartPrepherals[USART_6])->SR&USART_LBD_ENABLE)
    {
        /* clear LBD flag */
        ((UART_REG *)UsartPrepherals[USART_6])->SR&=~USART_LBD_ENABLE;
        if (LBD_CB[USART_6])
        {
           LBD_CB[USART_6](); 
        }
        

    }
    else
    {
        if (((UART_REG *)UsartPrepherals[USART_6])->SR&USART_TXE_ENABLE_FLAG)
        {
            if (TX_Request[USART_6].buffer.pos<TX_Request[USART_6].buffer.size)
            {
               ((UART_REG *)UsartPrepherals[USART_6])->DR=TX_Request[USART_6].buffer.data[TX_Request[USART_6].buffer.pos];
               TX_Request[USART_6].buffer.pos++;
            }
            else
            {
                TX_Request[USART_6].state=USART_STATE_READY;
                /*clear TEI*/
                ((UART_REG *)UsartPrepherals[USART_6])->CR1&=~UART_TXEIE_ENABLE_FLAG;
                /*notify user*/
                TX_Request[USART_6].CallBack();
            }
            
        }

        if (((UART_REG *)UsartPrepherals[USART_6])->SR&USART_RXE_ENABLE_FLAG)
        {
            if (RX_Request[USART_6].buffer.pos<RX_Request[USART_6].buffer.size)
            {
               ((UART_REG *)UsartPrepherals[USART_6])->DR=RX_Request[USART_6].buffer.data[RX_Request[USART_6].buffer.pos];
               RX_Request[USART_6].buffer.pos++;

               if(RX_Request[USART_6].buffer.pos==RX_Request[USART_6].buffer.size)
                {
                    RX_Request[USART_6].state=USART_STATE_READY;
                    /*clear REI*/
                    ((UART_REG *)UsartPrepherals[USART_6])->CR1&=~USART_RXNEIE_ENABLE_FLAG;
                    /*notify user*/
                    RX_Request[USART_6].CallBack();
                }
            }
            
            
        }
        
    }
    
}
