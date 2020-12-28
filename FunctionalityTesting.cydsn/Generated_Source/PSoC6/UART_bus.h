/***************************************************************************//**
* \file UART_bus.h
* \version 2.0
*
*  This file provides constants and parameter values for the UART component.
*
********************************************************************************
* \copyright
* Copyright 2016-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(UART_bus_CY_SCB_UART_PDL_H)
#define UART_bus_CY_SCB_UART_PDL_H

#include "cyfitter.h"
#include "scb/cy_scb_uart.h"

#if defined(__cplusplus)
extern "C" {
#endif

/***************************************
*   Initial Parameter Constants
****************************************/

#define UART_bus_DIRECTION  (3U)
#define UART_bus_ENABLE_RTS (0U)
#define UART_bus_ENABLE_CTS (0U)

/* UART direction enum */
#define UART_bus_RX    (0x1U)
#define UART_bus_TX    (0x2U)

#define UART_bus_ENABLE_RX  (0UL != (UART_bus_DIRECTION & UART_bus_RX))
#define UART_bus_ENABLE_TX  (0UL != (UART_bus_DIRECTION & UART_bus_TX))


/***************************************
*        Function Prototypes
***************************************/
/**
* \addtogroup group_general
* @{
*/
/* Component specific functions. */
void UART_bus_Start(void);

/* Basic functions */
__STATIC_INLINE cy_en_scb_uart_status_t UART_bus_Init(cy_stc_scb_uart_config_t const *config);
__STATIC_INLINE void UART_bus_DeInit(void);
__STATIC_INLINE void UART_bus_Enable(void);
__STATIC_INLINE void UART_bus_Disable(void);

/* Register callback. */
__STATIC_INLINE void UART_bus_RegisterCallback(cy_cb_scb_uart_handle_events_t callback);

/* Configuration change. */
#if (UART_bus_ENABLE_CTS)
__STATIC_INLINE void UART_bus_EnableCts(void);
__STATIC_INLINE void UART_bus_DisableCts(void);
#endif /* (UART_bus_ENABLE_CTS) */

#if (UART_bus_ENABLE_RTS)
__STATIC_INLINE void     UART_bus_SetRtsFifoLevel(uint32_t level);
__STATIC_INLINE uint32_t UART_bus_GetRtsFifoLevel(void);
#endif /* (UART_bus_ENABLE_RTS) */

__STATIC_INLINE void UART_bus_EnableSkipStart(void);
__STATIC_INLINE void UART_bus_DisableSkipStart(void);

#if (UART_bus_ENABLE_RX)
/* Low level: Receive direction. */
__STATIC_INLINE uint32_t UART_bus_Get(void);
__STATIC_INLINE uint32_t UART_bus_GetArray(void *buffer, uint32_t size);
__STATIC_INLINE void     UART_bus_GetArrayBlocking(void *buffer, uint32_t size);
__STATIC_INLINE uint32_t UART_bus_GetRxFifoStatus(void);
__STATIC_INLINE void     UART_bus_ClearRxFifoStatus(uint32_t clearMask);
__STATIC_INLINE uint32_t UART_bus_GetNumInRxFifo(void);
__STATIC_INLINE void     UART_bus_ClearRxFifo(void);
#endif /* (UART_bus_ENABLE_RX) */

#if (UART_bus_ENABLE_TX)
/* Low level: Transmit direction. */
__STATIC_INLINE uint32_t UART_bus_Put(uint32_t data);
__STATIC_INLINE uint32_t UART_bus_PutArray(void *buffer, uint32_t size);
__STATIC_INLINE void     UART_bus_PutArrayBlocking(void *buffer, uint32_t size);
__STATIC_INLINE void     UART_bus_PutString(char_t const string[]);
__STATIC_INLINE void     UART_bus_SendBreakBlocking(uint32_t breakWidth);
__STATIC_INLINE uint32_t UART_bus_GetTxFifoStatus(void);
__STATIC_INLINE void     UART_bus_ClearTxFifoStatus(uint32_t clearMask);
__STATIC_INLINE uint32_t UART_bus_GetNumInTxFifo(void);
__STATIC_INLINE bool     UART_bus_IsTxComplete(void);
__STATIC_INLINE void     UART_bus_ClearTxFifo(void);
#endif /* (UART_bus_ENABLE_TX) */

#if (UART_bus_ENABLE_RX)
/* High level: Ring buffer functions. */
__STATIC_INLINE void     UART_bus_StartRingBuffer(void *buffer, uint32_t size);
__STATIC_INLINE void     UART_bus_StopRingBuffer(void);
__STATIC_INLINE void     UART_bus_ClearRingBuffer(void);
__STATIC_INLINE uint32_t UART_bus_GetNumInRingBuffer(void);

/* High level: Receive direction functions. */
__STATIC_INLINE cy_en_scb_uart_status_t UART_bus_Receive(void *buffer, uint32_t size);
__STATIC_INLINE void     UART_bus_AbortReceive(void);
__STATIC_INLINE uint32_t UART_bus_GetReceiveStatus(void);
__STATIC_INLINE uint32_t UART_bus_GetNumReceived(void);
#endif /* (UART_bus_ENABLE_RX) */

#if (UART_bus_ENABLE_TX)
/* High level: Transmit direction functions. */
__STATIC_INLINE cy_en_scb_uart_status_t UART_bus_Transmit(void *buffer, uint32_t size);
__STATIC_INLINE void     UART_bus_AbortTransmit(void);
__STATIC_INLINE uint32_t UART_bus_GetTransmitStatus(void);
__STATIC_INLINE uint32_t UART_bus_GetNumLeftToTransmit(void);
#endif /* (UART_bus_ENABLE_TX) */

/* Interrupt handler */
__STATIC_INLINE void UART_bus_Interrupt(void);
/** @} group_general */


/***************************************
*    Variables with External Linkage
***************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8_t UART_bus_initVar;
extern cy_stc_scb_uart_config_t const UART_bus_config;
extern cy_stc_scb_uart_context_t UART_bus_context;
/** @} group_globals */


/***************************************
*         Preprocessor Macros
***************************************/
/**
* \addtogroup group_macros
* @{
*/
/** The pointer to the base address of the hardware */
#define UART_bus_HW     ((CySCB_Type *) UART_bus_SCB__HW)
/** @} group_macros */


/***************************************
*    In-line Function Implementation
***************************************/

/*******************************************************************************
* Function Name: UART_bus_Init
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Init() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_uart_status_t UART_bus_Init(cy_stc_scb_uart_config_t const *config)
{
   return Cy_SCB_UART_Init(UART_bus_HW, config, &UART_bus_context);
}


/*******************************************************************************
* Function Name: UART_bus_DeInit
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_DeInit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_bus_DeInit(void)
{
    Cy_SCB_UART_DeInit(UART_bus_HW);
}


/*******************************************************************************
* Function Name: UART_bus_Enable
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Enable() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_bus_Enable(void)
{
    Cy_SCB_UART_Enable(UART_bus_HW);
}


/*******************************************************************************
* Function Name: UART_bus_Disable
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Disable() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_bus_Disable(void)
{
    Cy_SCB_UART_Disable(UART_bus_HW, &UART_bus_context);
}


/*******************************************************************************
* Function Name: UART_bus_RegisterCallback
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_RegisterCallback() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_bus_RegisterCallback(cy_cb_scb_uart_handle_events_t callback)
{
    Cy_SCB_UART_RegisterCallback(UART_bus_HW, callback, &UART_bus_context);
}


#if (UART_bus_ENABLE_CTS)
/*******************************************************************************
* Function Name: UART_bus_EnableCts
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_EnableCts() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_bus_EnableCts(void)
{
    Cy_SCB_UART_EnableCts(UART_bus_HW);
}


/*******************************************************************************
* Function Name: Cy_SCB_UART_DisableCts
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_DisableCts() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_bus_DisableCts(void)
{
    Cy_SCB_UART_DisableCts(UART_bus_HW);
}
#endif /* (UART_bus_ENABLE_CTS) */


#if (UART_bus_ENABLE_RTS)
/*******************************************************************************
* Function Name: UART_bus_SetRtsFifoLevel
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_SetRtsFifoLevel() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_bus_SetRtsFifoLevel(uint32_t level)
{
    Cy_SCB_UART_SetRtsFifoLevel(UART_bus_HW, level);
}


/*******************************************************************************
* Function Name: UART_bus_GetRtsFifoLevel
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetRtsFifoLevel() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_bus_GetRtsFifoLevel(void)
{
    return Cy_SCB_UART_GetRtsFifoLevel(UART_bus_HW);
}
#endif /* (UART_bus_ENABLE_RTS) */


/*******************************************************************************
* Function Name: UART_bus_EnableSkipStart
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_EnableSkipStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_bus_EnableSkipStart(void)
{
    Cy_SCB_UART_EnableSkipStart(UART_bus_HW);
}


/*******************************************************************************
* Function Name: UART_bus_DisableSkipStart
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_DisableSkipStart() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_bus_DisableSkipStart(void)
{
    Cy_SCB_UART_DisableSkipStart(UART_bus_HW);
}


#if (UART_bus_ENABLE_RX)
/*******************************************************************************
* Function Name: UART_bus_Get
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Get() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_bus_Get(void)
{
    return Cy_SCB_UART_Get(UART_bus_HW);
}


/*******************************************************************************
* Function Name: UART_bus_GetArray
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetArray() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_bus_GetArray(void *buffer, uint32_t size)
{
    return Cy_SCB_UART_GetArray(UART_bus_HW, buffer, size);
}


/*******************************************************************************
* Function Name: UART_bus_GetArrayBlocking
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetArrayBlocking() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_bus_GetArrayBlocking(void *buffer, uint32_t size)
{
    Cy_SCB_UART_GetArrayBlocking(UART_bus_HW, buffer, size);
}


/*******************************************************************************
* Function Name: UART_bus_GetRxFifoStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetRxFifoStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_bus_GetRxFifoStatus(void)
{
    return Cy_SCB_UART_GetRxFifoStatus(UART_bus_HW);
}


/*******************************************************************************
* Function Name: UART_bus_ClearRxFifoStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_ClearRxFifoStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_bus_ClearRxFifoStatus(uint32_t clearMask)
{
    Cy_SCB_UART_ClearRxFifoStatus(UART_bus_HW, clearMask);
}


/*******************************************************************************
* Function Name: UART_bus_GetNumInRxFifo
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetNumInRxFifo() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_bus_GetNumInRxFifo(void)
{
    return Cy_SCB_UART_GetNumInRxFifo(UART_bus_HW);
}


/*******************************************************************************
* Function Name: UART_bus_ClearRxFifo
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_ClearRxFifo() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_bus_ClearRxFifo(void)
{
    Cy_SCB_UART_ClearRxFifo(UART_bus_HW);
}
#endif /* (UART_bus_ENABLE_RX) */


#if (UART_bus_ENABLE_TX)
/*******************************************************************************
* Function Name: UART_bus_Put
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Put() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_bus_Put(uint32_t data)
{
    return Cy_SCB_UART_Put(UART_bus_HW,data);
}


/*******************************************************************************
* Function Name: UART_bus_PutArray
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_PutArray() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_bus_PutArray(void *buffer, uint32_t size)
{
    return Cy_SCB_UART_PutArray(UART_bus_HW, buffer, size);
}


/*******************************************************************************
* Function Name: UART_bus_PutArrayBlocking
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_PutArrayBlocking() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_bus_PutArrayBlocking(void *buffer, uint32_t size)
{
    Cy_SCB_UART_PutArrayBlocking(UART_bus_HW, buffer, size);
}


/*******************************************************************************
* Function Name: UART_bus_PutString
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_PutString() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_bus_PutString(char_t const string[])
{
    Cy_SCB_UART_PutString(UART_bus_HW, string);
}


/*******************************************************************************
* Function Name: UART_bus_SendBreakBlocking
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_SendBreakBlocking() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_bus_SendBreakBlocking(uint32_t breakWidth)
{
    Cy_SCB_UART_SendBreakBlocking(UART_bus_HW, breakWidth);
}


/*******************************************************************************
* Function Name: UART_bus_GetTxFifoStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetTxFifoStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_bus_GetTxFifoStatus(void)
{
    return Cy_SCB_UART_GetTxFifoStatus(UART_bus_HW);
}


/*******************************************************************************
* Function Name: UART_bus_ClearTxFifoStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_ClearTxFifoStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_bus_ClearTxFifoStatus(uint32_t clearMask)
{
    Cy_SCB_UART_ClearTxFifoStatus(UART_bus_HW, clearMask);
}


/*******************************************************************************
* Function Name: UART_bus_GetNumInTxFifo
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetNumInTxFifo() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_bus_GetNumInTxFifo(void)
{
    return Cy_SCB_UART_GetNumInTxFifo(UART_bus_HW);
}


/*******************************************************************************
* Function Name: UART_bus_IsTxComplete
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_IsTxComplete() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE bool UART_bus_IsTxComplete(void)
{
    return Cy_SCB_UART_IsTxComplete(UART_bus_HW);
}


/*******************************************************************************
* Function Name: UART_bus_ClearTxFifo
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_ClearTxFifo() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_bus_ClearTxFifo(void)
{
    Cy_SCB_UART_ClearTxFifo(UART_bus_HW);
}
#endif /* (UART_bus_ENABLE_TX) */


#if (UART_bus_ENABLE_RX)
/*******************************************************************************
* Function Name: UART_bus_StartRingBuffer
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_StartRingBuffer() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_bus_StartRingBuffer(void *buffer, uint32_t size)
{
    Cy_SCB_UART_StartRingBuffer(UART_bus_HW, buffer, size, &UART_bus_context);
}


/*******************************************************************************
* Function Name: UART_bus_StopRingBuffer
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_StopRingBuffer() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_bus_StopRingBuffer(void)
{
    Cy_SCB_UART_StopRingBuffer(UART_bus_HW, &UART_bus_context);
}


/*******************************************************************************
* Function Name: UART_bus_ClearRingBuffer
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_ClearRingBuffer() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_bus_ClearRingBuffer(void)
{
    Cy_SCB_UART_ClearRingBuffer(UART_bus_HW, &UART_bus_context);
}


/*******************************************************************************
* Function Name: UART_bus_GetNumInRingBuffer
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetNumInRingBuffer() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_bus_GetNumInRingBuffer(void)
{
    return Cy_SCB_UART_GetNumInRingBuffer(UART_bus_HW, &UART_bus_context);
}


/*******************************************************************************
* Function Name: UART_bus_Receive
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Receive() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_uart_status_t UART_bus_Receive(void *buffer, uint32_t size)
{
    return Cy_SCB_UART_Receive(UART_bus_HW, buffer, size, &UART_bus_context);
}


/*******************************************************************************
* Function Name: UART_bus_GetReceiveStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetReceiveStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_bus_GetReceiveStatus(void)
{
    return Cy_SCB_UART_GetReceiveStatus(UART_bus_HW, &UART_bus_context);
}


/*******************************************************************************
* Function Name: UART_bus_AbortReceive
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_AbortReceive() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_bus_AbortReceive(void)
{
    Cy_SCB_UART_AbortReceive(UART_bus_HW, &UART_bus_context);
}


/*******************************************************************************
* Function Name: UART_bus_GetNumReceived
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetNumReceived() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_bus_GetNumReceived(void)
{
    return Cy_SCB_UART_GetNumReceived(UART_bus_HW, &UART_bus_context);
}
#endif /* (UART_bus_ENABLE_RX) */


#if (UART_bus_ENABLE_TX)
/*******************************************************************************
* Function Name: UART_bus_Transmit
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Transmit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE cy_en_scb_uart_status_t UART_bus_Transmit(void *buffer, uint32_t size)
{
    return Cy_SCB_UART_Transmit(UART_bus_HW, buffer, size, &UART_bus_context);
}


/*******************************************************************************
* Function Name: UART_bus_GetTransmitStatus
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetTransmitStatus() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_bus_GetTransmitStatus(void)
{
    return Cy_SCB_UART_GetTransmitStatus(UART_bus_HW, &UART_bus_context);
}


/*******************************************************************************
* Function Name: UART_bus_AbortTransmit
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_AbortTransmit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_bus_AbortTransmit(void)
{
    Cy_SCB_UART_AbortTransmit(UART_bus_HW, &UART_bus_context);
}


/*******************************************************************************
* Function Name: UART_bus_GetNumLeftToTransmit
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_GetNumLeftToTransmit() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE uint32_t UART_bus_GetNumLeftToTransmit(void)
{
    return Cy_SCB_UART_GetNumLeftToTransmit(UART_bus_HW, &UART_bus_context);
}
#endif /* (UART_bus_ENABLE_TX) */


/*******************************************************************************
* Function Name: UART_bus_Interrupt
****************************************************************************//**
*
* Invokes the Cy_SCB_UART_Interrupt() PDL driver function.
*
*******************************************************************************/
__STATIC_INLINE void UART_bus_Interrupt(void)
{
    Cy_SCB_UART_Interrupt(UART_bus_HW, &UART_bus_context);
}

#if defined(__cplusplus)
}
#endif

#endif /* UART_bus_CY_SCB_UART_PDL_H */


/* [] END OF FILE */
