/*
    Aerospace Decoder - Copyright (C) 2018 Bob Anderson (VK2GJ)

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*/

#include "pktconf.h"
#include "portab.h"

/*===========================================================================*/
/* Module local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported variables.                                                */
/*===========================================================================*/

memory_heap_t *ccm_heap = NULL;
//guarded_memory_pool_t *ccm_pool = NULL;

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

#if PKT_SVC_USE_RADIO1 || defined(__DOXYGEN__)
packet_svc_t RPKTD1;
#endif

#if PKT_SVC_USE_RADIO2 || defined(__DOXYGEN__)
packet_svc_t RPKTD2;
#endif

/*===========================================================================*/
/* Module local types.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module local variables.                                                   */
/*===========================================================================*/

#if USE_CCM_HEAP_FOR_PKT == TRUE
static memory_heap_t _ccm_heap;
/*#elif USE_CCM_FOR_PKT_POOL == TRUE
static guarded_memory_pool_t _ccm_pool;*/
#endif

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/


/**
 * @brief   Initializes the packet system.
 * @notes   Allocates a heap in remaining available CCM.
 * @notes   Unless variables are allocated to CCM the heap will be all of CCM.
 * @notes   Buffers (non DMA) are then allocated from the CCM heap.
 *
 *@return   result of operation.
 *@retval   true    system initialized.
 *@retval   false   initialization failed.
 *
 * @notapi
 */
bool pktSystemInit(void) {

/*
 * The definition for CCM is in pktconf.h as follows...
 *  #define useCCM  __attribute__((section(".ram4")))
 * How to allocate a variable in CCM...
 *  int example useCCM;
 *
 * The remainder available in CCM is used to create a heap.
 * This can be used for non-DMA access data only in the F413.
 */

 /* Reference the linker created CCM variables to get the available heap area. */
  extern uint8_t __ram4_free__[];
  extern uint8_t __ram4_end__[];

  chDbgAssert(ccm_heap == NULL, "CCM heap already exists");
  /*
   * Create heap in CCM.
   * Once created the CCM heap remains available.
   * TODO: Move CCM heap creation to system level.
   * Include in sysConfigureCoreIO(...) and rename that function. */
  if(ccm_heap == NULL) {
    /* CCM heap not created yet. */
  ccm_heap = &_ccm_heap;
  chHeapObjectInit(ccm_heap, (void *)__ram4_free__,
                   (size_t)(__ram4_end__ - __ram4_free__));
  }

#if USE_CCM_HEAP_FOR_PKT == TRUE
  /*
   * Create common AX25 transmit packet buffer control.
   */
  if(pktInitBufferControl() == NULL) {
    return false;
  }
#endif
  return true;
}

/**
 * @brief   Deinits the packet system.
 *
 *@return   result of operation.
 *@retval   true    deinit success.
 *@retval   false   deinit failed.
 *
 * @api
 */
bool pktSystemDeinit(void) {

  /*
   * Remove common packet buffer control.
   */
  chDbgAssert(ccm_heap != NULL, "CCM heap does not exist");
  //chSysLock();

  pktDeinitBufferControl();

  return true;
}

/**
 * @brief   Initializes packet handlers and starts the radio manager.
 * @note    The option to manage multiple radios across the system is incomplete.
 * @note    Once initialized the transmit service is available.
 * @note    To activate receive requires an open to be made.
 *
 * @param[in]   radio unit ID.
 *
 *@return   result of operation.
 *@retval   true    service was created.
 *@retval   false   service creation failed or state was not idle.
 *
 * @api
 */
bool pktServiceCreate(const radio_unit_t radio) {

  /*
   * Get service object maps radio IDs to service objects
   */
  packet_svc_t *handler = pktGetServiceObject(radio);
  if(handler == NULL)
    return false;

  if(handler->state != PACKET_IDLE)
    return false;

  /*
   * Initialize the packet common event object.
   */
  chEvtObjectInit(pktGetEventSource(handler));

  memset(&handler->radio_rx_config, 0, sizeof(radio_task_object_t));
  memset(&handler->radio_tx_config, 0, sizeof(radio_task_object_t));

  /* Set flags and radio ID. */
  handler->radio_init = false;
  handler->radio = radio;

  /* Set service semaphore to idle state. */
  chBSemObjectInit(&handler->close_sem, false);

#if PKT_USE_RADIO_MUTEX == TRUE
  chMtxObjectInit(&handler->radio_mtx);
#else
  /* Set radio semaphore to free state. */
  chBSemObjectInit(&handler->radio_sem, false);
#endif
  /* Send request to create radio manager. */
  if (pktRadioManagerCreate(radio) == NULL)
    return false;
  handler->state = PACKET_READY;
  return true;
}

/**
 * @brief   Releases packet service.
 * @note    The option to manage multiple radios is not yet implemented.
 * @post    The packet service is no longer available for transmit or receive.
 *
 * @param[in] radio unit ID
 *
 *@return   result of operation.
 *@retval   true    service was released.
 *@retval   false   service state is incorrect or invalid radio ID.
 *
 * @api
 */
bool pktServiceRelease(const radio_unit_t radio) {

  /*
   * Lookup radio and assign handler (RPKTDx).
   */
  packet_svc_t *handler = pktGetServiceObject(radio);
  if(handler == NULL)
    return false;

  if(handler->state != PACKET_READY)
    return false;

  pktReleaseBufferSemaphore(radio);

  pktRadioManagerRelease(radio);
  handler->state = PACKET_IDLE;
  return true;
}

/**
 * @brief   Hibernate a packet service on a radio.
 * @note    The option to manage multiple radios is not yet implemented.
 * @note    In hibernation the receive and transmit services are unavailable.
 * @note    This is an empty function - may not be needed ever.
 *
 * @param[in]   radio unit ID.
 *
 *@return   result of operation.
 *@retval   true    service was put into hibernation state.
 *@retval   false   hibernation request failed.
 *
 * @api
 */
bool pktServiceHibernate(const radio_unit_t radio) {

  /*
   * Get service object maps radio IDs to service objects
   */
  packet_svc_t *handler = pktGetServiceObject(radio);
  if(handler == NULL)
    return false;
  return false;
}

/**
 * @brief   Wake up a packet service on a radio from hibernation state.
 * @note    The option to manage multiple radios is not yet implemented.
 * @note    Once woken up the prior services become available.
 * @note    This is an empty function - may not be needed ever.
 *
 * @param[in]   radio unit ID.
 *
 *@return   result of operation.
 *@retval   true    service was woken up.
 *@retval   false   wake up request failed.
 *
 * @api
 */
bool pktServiceWakeup(const radio_unit_t radio) {

  /*
   * Lookup radio and assign handler (RPKTDx).
   */
  packet_svc_t *handler = pktGetServiceObject(radio);
  if(handler == NULL)
    return false;
  return false;
}

/**
 * @brief   Opens a packet receive service.
 * @post    The packet service is initialized and ready to be started.
 *
 * @param[in] radio     radio unit identifier.
 * @param[in] encoding  radio link level encoding.
 * @param[in] frequency operating frequency (in Hz).
 * @param[in] ch_step   frequency step per channel (in Hz).
 *
 * @return              status of operation.
 * @retval MSG_OK       if the open request was processed.
 * @retval MSG_TIMEOUT  if the open request timed out waiting for resources.
 * @retval MSG_RESET    if state is invalid or a bad parameter is submitted.
 *
 * @api
 */
msg_t pktOpenRadioReceive(const radio_unit_t radio,
                          const encoding_type_t encoding,
                          const radio_freq_t frequency,
                          const channel_hz_t ch_step) {

  packet_svc_t *handler = pktGetServiceObject(radio);
  if(handler == NULL)
    return MSG_RESET;

  chDbgCheck(handler->state == PACKET_READY);

  if(handler->state != PACKET_READY)
    return MSG_RESET;

  /* Wait for any prior session to complete closing. */
  chBSemWait(&handler->close_sem);

  /* Save radio configuration. */
  handler->radio_rx_config.type = encoding;
  handler->radio_rx_config.base_frequency = frequency;
  handler->radio_rx_config.step_hz = ch_step;

  /* Reset the statistics collection variables. */
  handler->sync_count = 0;
  handler->frame_count = 0;
  handler->valid_count = 0;
  handler->good_count = 0;

  radio_task_object_t rt = handler->radio_rx_config;

  /* Set parameters for radio command. */
  rt.command = PKT_RADIO_RX_OPEN;

  /*
   * Open (init) the radio (via submit radio task).
   */
  msg_t msg = pktSendRadioCommand(radio, &rt, NULL);

  if(msg != MSG_OK)
    return msg;

  handler->state = PACKET_OPEN;
  pktAddEventFlags(handler, EVT_PKT_CHANNEL_OPEN);

  return MSG_OK;
}

/**
 * @brief   Starts packet reception.
 * @pre     The packet service must have been opened.
 * @post    The radio is tuned to the specified channel.
 * @post    The packet reception is running if it was stopped.
 *
 * @param[in]   handler pointer to a @p packet handler object.
 * @param[in]   channel radio channel number to select
 * @param[in]   sq      the RSSI setting to be used.
 * @param[in]   cb      callback function called on receipt of packet.
 *
 * @return              Status of the operation.
 * @retval MSG_OK       if the service was started.
 * @retval MSG_RESET    parameter error or service not in correct state.
 * @retval MSG_TIMEOUT  if the service could not be started.
 *
 * @api
 */
msg_t pktEnableDataReception(const radio_unit_t radio,
                             const radio_ch_t channel,
                             const radio_squelch_t sq,
                             const pkt_buffer_cb_t cb) {

  packet_svc_t *handler = pktGetServiceObject(radio);
  if(handler == NULL)
    return MSG_RESET;

  if(!(handler->state == PACKET_OPEN || handler->state == PACKET_STOP))
    return MSG_RESET;

  handler->usr_callback = cb;

  handler->radio_rx_config.channel = channel;
  handler->radio_rx_config.squelch = sq;

  radio_task_object_t rt = handler->radio_rx_config;

  rt.command = PKT_RADIO_RX_START;

  msg_t msg = pktSendRadioCommand(radio, &rt, NULL);
  if(msg != MSG_OK)
    return MSG_TIMEOUT;

  /* Wait in PAUSE state for a decoder start. */
  handler->state = PACKET_PAUSE;
  pktAddEventFlags(handler, EVT_PKT_DECODER_START);
  return MSG_OK;
}

/**
 * @brief   Enables a packet decoder.
 * @pre     The packet channel must have been opened.
 * @post    The packet decoder is running.
 *
 * @param[in]   radio unit ID.
 *
 * @api
 */
void pktStartDecoder(const radio_unit_t radio) {

  packet_svc_t *handler = pktGetServiceObject(radio);

  if(!pktIsReceivePaused(radio)) {
    /* Wrong state. */
    chDbgAssert(false, "wrong state for decoder start");
    return;
  }

  event_listener_t el;
  event_source_t *esp;

  switch(handler->radio_rx_config.type) {
    case MOD_AFSK: {

      esp = pktGetEventSource((AFSKDemodDriver *)handler->link_controller);

      pktRegisterEventListener(esp, &el, USR_COMMAND_ACK, DEC_START_EXEC);

      thread_t *the_decoder =
          ((AFSKDemodDriver *)handler->link_controller)->decoder_thd;
      chEvtSignal(the_decoder, DEC_COMMAND_START);
      break;
    } /* End case. */

    case MOD_2FSK: {
      return;
    }

    default:
      return;
  } /* End switch. */

  /* Wait for the decoder to start. */
  eventflags_t evt;
  do {
    /* In reality this is redundant as the only masked event is START. */
    chEvtWaitAny(USR_COMMAND_ACK);

    /* Wait for correct event at source.
     */
    evt = chEvtGetAndClearFlags(&el);
  } while (evt != DEC_START_EXEC);
  pktUnregisterEventListener(esp, &el);
  handler->state = PACKET_DECODE;
}

/**
 * @brief   Stop reception.
 * @notes   Decoding is stopped.
 * @notes   Any packets out for processing remain in effect.
 * @pre     The packet channel must be running.
 * @post    The packet channel is stopped.
 *
 * @param[in] radio     radio unit ID..
 *
 * @return              Status of the operation.
 * @retval MSG_OK       if the channel was stopped.
 * @retval MSG_RESET    if the channel was not in the correct state.
 * @retval MSG_TIMEOUT  if the channel could not be stopped or is invalid.
 *
 * @api
 */
msg_t pktDisableDataReception(radio_unit_t radio) {


  packet_svc_t *handler = pktGetServiceObject(radio);

  if(handler == NULL)
    return MSG_RESET;

  if(handler->state != PACKET_DECODE || handler->state != PACKET_PAUSE)
    return MSG_RESET;

  /* Stop the radio processing. */

  radio_task_object_t rt = handler->radio_rx_config;

  rt.command = PKT_RADIO_RX_STOP;

  msg_t msg = pktSendRadioCommand(radio, &rt, NULL);
  if(msg != MSG_OK)
    return msg;

  handler->state = PACKET_STOP;
  pktAddEventFlags(handler, EVT_PKT_CHANNEL_STOP);
  return MSG_OK;
}

/**
 * @brief   Disables a packet decoder.
 * @pre     The packet channel must be running.
 * @post    The packet decoder is stopped.
 *
 * @param[in]   radio unit ID.
 *
 * @api
 */
void pktStopDecoder(radio_unit_t radio) {

  packet_svc_t *handler = pktGetServiceObject(radio);

  if(!pktIsReceiveActive(radio)) {
    /* Wrong state. */
    chDbgAssert(false, "wrong state for decoder stop");
    return;
  }
  event_listener_t el;
  event_source_t *esp;

  switch(handler->radio_rx_config.type) {
    case MOD_AFSK: {
      esp = pktGetEventSource((AFSKDemodDriver *)handler->link_controller);

      pktRegisterEventListener(esp, &el, USR_COMMAND_ACK, DEC_STOP_EXEC);

      thread_t *the_decoder =
          ((AFSKDemodDriver *)handler->link_controller)->decoder_thd;
      chEvtSignal(the_decoder, DEC_COMMAND_STOP);
      break;
    } /* End case. */

    case MOD_2FSK: {
      return;
    }

    default:
      return;
  } /* End switch. */

  /* Wait for the decoder to stop. */
  eventflags_t evt;
  do {
    chEvtWaitAny(USR_COMMAND_ACK);

    /* Wait for correct event at source.
     */
    evt = chEvtGetAndClearFlags(&el);
  } while (evt != DEC_STOP_EXEC);
  pktUnregisterEventListener(esp, &el);
  handler->state = PACKET_PAUSE;
}

/**
 * @brief   Closes a packet receive service.
 * @pre     The packet service must have been stopped.
 * @post    The packet service is closed and returned to ready state.
 * @post    Memory used by the decoder thread is released.
 *
 * @param[in] radio     radio unit ID.
 *
 * @return              Status of the operation.
 * @retval MSG_OK       if the service was closed successfully.
 * @retval MSG_RESET    service not in the correct state or invalid parameter.
 * @retval MSG_TIMEOUT  if the service could not be closed.
 *
 * @api
 */
msg_t pktCloseRadioReceive(radio_unit_t radio) {

  packet_svc_t *handler = pktGetServiceObject(radio);
  if(handler == NULL)
    return MSG_RESET;

  if(!(handler->state == PACKET_STOP || handler->state == PACKET_CLOSE))
    return MSG_RESET;

  handler->state = PACKET_CLOSE;

  /* Set parameters for radio. */;

  radio_task_object_t rt = handler->radio_rx_config;

  rt.command = PKT_RADIO_RX_CLOSE;

  /* Submit command. A timeout can occur waiting for a command queue object. */
  msg_t msg = pktSendRadioCommand(radio, &rt, NULL);
  if(msg != MSG_OK)
    return msg;

  pktAddEventFlags(handler, EVT_PKT_CHANNEL_CLOSE);
  handler->state = PACKET_READY;
  return MSG_OK;
}

/**
 * @brief   Stores data in a packet channel buffer.
 * @notes   If the data is an HDLC value it will be escape encoded.
 * @post    The character is stored and the internal buffer index is updated.
 *
 * @param[in] pkt_buffer    pointer to a @p packet buffer object.
 * @param[in] data          the character to be stored
 *
 * @return              Status of the operation.
 * @retval true         The data was stored.
 * @retval false        The data could not be stored (buffer full).
 *
 * @api
 */
bool pktStoreBufferData(pkt_data_object_t *pkt_buffer, ax25char_t data) {
  if((pkt_buffer->packet_size + 1U) > pkt_buffer->buffer_size) {
    /* Buffer full. */
    return false;
  }
  /* Buffer space available. */
#if USE_CCM_HEAP_RX_BUFFERS == TRUE
  *((pkt_buffer->buffer) + pkt_buffer->packet_size++) = data;
#else
  pkt_buffer->buffer[pkt_buffer->packet_size++] = data;
#endif
  return true;
}

/**
 * @brief   Dispatch a received buffer object.
 * @notes   The buffer is checked to determine validity and CRC.
 * @post    The buffer status is updated in the packet FIFO.
 * @post    Packet quality statistics are updated.
 * @post    Where no callback is used the buffer is posted to the FIFO mailbox.
 * @post    Where a callback is used a thread is created to execute the callback.
 *
 * @param[in] pkt_buffer    pointer to a @p packet buffer object.
 *
 * @return  Status flags added after packet validity check.
 *
 * @api
 */
eventflags_t pktDispatchReceivedBuffer(pkt_data_object_t *pkt_buffer) {

  chDbgAssert(pkt_buffer != NULL, "no packet buffer");

  packet_svc_t *handler = pkt_buffer->handler;

  chDbgAssert(handler != NULL, "invalid handler");

  eventflags_t flags = EVT_NONE;
  handler->frame_count++;
  if(pktIsBufferValidAX25Frame(pkt_buffer)) {
    handler->valid_count++;
    uint16_t magicCRC =
        calc_crc16(pkt_buffer->buffer, 0,
                   pkt_buffer->packet_size);
    if(magicCRC == CRC_INCLUSIVE_CONSTANT)
        handler->good_count++;
    flags |= (magicCRC == CRC_INCLUSIVE_CONSTANT)
                ? STA_PKT_FRAME_RDY
                : STA_PKT_CRC_ERROR;
  } else {
    flags |= STA_PKT_INVALID_FRAME;
  }

  /* Update status in packet buffer object. */
  pkt_buffer->status |= flags;

  objects_fifo_t *pkt_fifo = chFactoryGetObjectsFIFO(pkt_buffer->pkt_factory);

  chDbgAssert(pkt_fifo != NULL, "no packet FIFO");

  if(pkt_buffer->cb_func == NULL) {

    /* Send the packet buffer to the FIFO queue. */
    chFifoSendObject(pkt_fifo, pkt_buffer);
  } else {
    /* Schedule a callback. */
    thread_t *cb_thd = pktCreateBufferCallback(pkt_buffer);

    chDbgAssert(cb_thd != NULL, "failed to create callback thread");

    if(cb_thd == NULL) {
      /* Failed to create CB thread. Release buffer. Broadcast event. */
      chFifoReturnObject(pkt_fifo, pkt_buffer);
      pktAddEventFlags(handler, EVT_PKT_FAILED_CB_THD);
    } else {
      /* Increase outstanding callback count. */
      handler->cb_count++;
    }
  }
  return flags;
}

/**
 * @brief   Create a callback processing thread.
 * @notes   Packet callbacks are processed by individual threads.
 * @notes   Thus packet callbacks are non-blocking to the decoder thread.
 * @notes   After callback completes the thread it is scheduled for release.
 * @notes   Release is initiated by posting the packet buffer to the queue.
 *
 * @post    Call back has been executed (for however long it takes).
 * @post    Callback thread release is completed in the terminator thread.
 *
 * @param[in] pkt_data_object_t    pointer to a @p packet buffer object.
 *
 * @return  The callback thread.
 *
 * @api
 */
thread_t *pktCreateBufferCallback(pkt_data_object_t *pkt_buffer) {

  chDbgAssert(pkt_buffer != NULL, "invalid packet buffer");

  /* Create a callback thread name which is the address of the buffer. */
  /* TODO: Create a more meaningful but still unique thread name. */
  chsnprintf(pkt_buffer->cb_thd_name, sizeof(pkt_buffer->cb_thd_name),
             PKT_CALLBACK_THD_PREFIX"%x", pkt_buffer);

  /* Start a callback dispatcher thread. */
  thread_t *cb_thd = chThdCreateFromHeap(NULL,
              THD_WORKING_AREA_SIZE(PKT_CALLBACK_WA_SIZE),
              pkt_buffer->cb_thd_name,
              NORMALPRIO - 20,
              pktCallback,
              pkt_buffer);

  return cb_thd;
}

/**
 * @brief   Run a callback processing thread.
 * @notes   Packet callbacks are processed by individual threads.
 * @notes   Thus packet callbacks are non-blocking to the decoder thread.
 * @notes   After callback completes the thread it is scheduled for release.
 * @notes   Release is initiated by posting the packet buffer to the queue.
 *
 * @post    Call back has been executed (for however long it takes).
 * @post    Callback thread release is completed in the terminator thread.
 *
 * @param[in] arg pointer to a @p packet buffer object.
 *
 * @return  status (MSG_OK).
 *
 * @notapi
 */
THD_FUNCTION(pktCallback, arg) {

  chDbgAssert(arg != NULL, "invalid buffer reference");

  pkt_data_object_t *pkt_buffer = arg;

  chDbgAssert(pkt_buffer->cb_func != NULL, "no callback set");

  dyn_objects_fifo_t *pkt_factory = pkt_buffer->pkt_factory;
  chDbgAssert(pkt_factory != NULL, "invalid packet factory reference");

  objects_fifo_t *pkt_fifo = chFactoryGetObjectsFIFO(pkt_factory);
  chDbgAssert(pkt_fifo != NULL, "no packet FIFO");

  /* Save thread pointer for use later in terminator. */
  pkt_buffer->cb_thread = chThdGetSelfX();

  /* Perform the callback. */
  pkt_buffer->cb_func(pkt_buffer);

  /*
   * Upon return the buffer control object is queued for release.
   * Thread is scheduled for destruction in pktReleaseDataBuffer(...).
   * .i.e pktReleaseDataBuffer does not return to callback.
   */
  pktReleaseDataBuffer(pkt_buffer);
}

#if PKT_RX_RLS_USE_NO_FIFO != TRUE
/**
 * @brief   Process release of completed callbacks.
 * @notes   Release is initiated by posting the packet buffer to the queue.
 * @notes   The queue is used as a completion mechanism in callback mode.
 * @notes   In poll mode the received packet is posted to the consumer
 *
 * @post    Call back thread has been released.
 * @post    Packet buffer object is returned to free pool.
 * @post    Packet object is released (for this instance).
 * @post    If the FIFO is now unused it will be released.
 *
 * @param[in] arg pointer to packet service handler object.
 *
 * @return  status (MSG_OK) on exit.
 *
 * @notapi
 */

/* TODO: Deprecate and use radio manager thread for callback release? */
THD_FUNCTION(pktCompletion, arg) {
  packet_svc_t *handler = arg;
#define PKT_COMPLETION_THREAD_TIMER 100 /* 100 mS. */

  chDbgAssert(handler != NULL, "invalid handler reference");

  dyn_objects_fifo_t *pkt_factory = handler->the_packet_fifo;
  objects_fifo_t *pkt_queue = chFactoryGetObjectsFIFO(pkt_factory);
  chDbgAssert(pkt_queue != NULL, "no packet fifo list");

  /* TODO: Implement thread events to control start/stop. */
  while(true) {

    /*
     * Wait for a callback to be outstanding.
     * If no callbacks outstanding check for termination request.
     */
    if(handler->cb_count == 0) {
      if(chThdShouldTerminateX())
        chThdExit(MSG_OK);
      chThdSleep(TIME_MS2I(PKT_COMPLETION_THREAD_TIMER));
      continue;
    }
    /* Wait for a buffer to be released. */
    pkt_data_object_t *pkt_object;

    msg_t fmsg = chFifoReceiveObjectTimeout(pkt_queue,
                         (void *)&pkt_object,
                         TIME_MS2I(PKT_COMPLETION_THREAD_TIMER));
    if(fmsg == MSG_TIMEOUT)
      continue;

    /* Release the callback thread and recover heap. */
    chThdRelease(pkt_object->cb_thread);

    /* Return packet buffer object to free list. */
    chFifoReturnObject(pkt_queue, (pkt_data_object_t *)pkt_object);

    /*
     * Decrease FIFO reference counter (increased by decoder).
     * FIFO will be destroyed if all references now released.
     */
    chFactoryReleaseObjectsFIFO(pkt_factory);

    /* Decrease count of outstanding callbacks. */
    --handler->cb_count;
  }
  chThdExit(MSG_OK);
}
#endif

/**
 * @brief   Create receive callback thread terminator.
 *
 * @param[in] arg radio unit ID.
 *
 * @notapi
 */
void pktCallbackManagerOpen(radio_unit_t radio) {

  packet_svc_t *handler = pktGetServiceObject(radio);

  //chDbgAssert(handler != NULL, "invalid radio ID");

  /* Create the callback handler thread name. */
  chsnprintf(handler->cbend_name, sizeof(handler->cbend_name),
             "%s%02i", PKT_CALLBACK_TERMINATOR_PREFIX, radio);

  /* Start the callback thread terminator. */
  thread_t *cbh = chThdCreateFromHeap(NULL,
              THD_WORKING_AREA_SIZE(PKT_TERMINATOR_WA_SIZE),
              handler->cbend_name,
              NORMALPRIO - 30,
              pktCompletion,
              handler);

  chDbgAssert(cbh != NULL, "failed to create callback terminator thread");
  handler->cb_terminator = cbh;
}

/*
 *
 */
dyn_objects_fifo_t *pktIncomingBufferPoolCreate(radio_unit_t radio) {

  packet_svc_t *handler = pktGetServiceObject(radio);

  //chDbgAssert(handler != NULL, "invalid radio ID");

  /* Create the packet buffer name for this radio. */
  chsnprintf(handler->pbuff_name, sizeof(handler->pbuff_name),
             "%s%02i", PKT_FRAME_QUEUE_PREFIX, radio);

  /* Check if the packet buffer factory is still in existence.
   * If so we get a pointer to it.
   */
  dyn_objects_fifo_t *dyn_fifo =
      chFactoryFindObjectsFIFO(handler->pbuff_name);

  if(dyn_fifo == NULL) {
    /* Create the dynamic objects FIFO for the packet data queue. */
    dyn_fifo = chFactoryCreateObjectsFIFO(handler->pbuff_name,
        sizeof(pkt_data_object_t),
        NUMBER_RX_PKT_BUFFERS, sizeof(msg_t));

    chDbgAssert(dyn_fifo != NULL, "failed to create receive PKT objects FIFO");

    if(dyn_fifo == NULL) {
      /* TODO: Close decoder on fail. */
      return NULL;
    }
  }

  /* Save the factory FIFO reference. */
  handler->the_packet_fifo = dyn_fifo;

  /* Initialize packet buffer pointer. */
  handler->active_packet_object = NULL;
  return dyn_fifo;
}

/*
 * Send and packet analysis share a common pool of buffers.
 */
dyn_semaphore_t *pktInitBufferControl() {

  /* Check if the transmit packet buffer semaphore already exists.
   * Calling this twice is an error so assert if enabled.
   * Otherwise get a pointer to it and just return that.
   * If it does not exist create the semaphore and return result.
   */
  dyn_semaphore_t *dyn_sem =
      chFactoryFindSemaphore(PKT_SEND_BUFFER_SEM_NAME);

  if(dyn_sem == NULL) {
    /* Create the semaphore for limiting the packet allocation. */
    dyn_sem = chFactoryCreateSemaphore(PKT_SEND_BUFFER_SEM_NAME,
                                       NUMBER_COMMON_PKT_BUFFERS);

    chDbgAssert(dyn_sem != NULL, "failed to create common packet semaphore");
    if(dyn_sem == NULL)
      return NULL;
    return dyn_sem;
  } else {
    chDbgAssert(false, "common packet semaphore already created");
    return dyn_sem;
  }
}

/*
 * Radio send and APRS packet analysis share a common pool of buffers.
 */
void pktDeinitBufferControl() {

  /* Check if the transmit packet buffer semaphore exists.
   * If so wait for all references to be released.
   * Then release the semaphore.
   */
  dyn_semaphore_t *dyn_sem =
      chFactoryFindSemaphore(PKT_SEND_BUFFER_SEM_NAME);
  chDbgAssert(dyn_sem != NULL, "common packet semaphore does not exist");
  if(dyn_sem == NULL)
    return;
  chSysLock();
  chSemWaitTimeoutS(chFactoryGetSemaphore(dyn_sem), TIME_INFINITE);
  /*
   *  Kick everyone off and set available buffers to zero.
   *  Users need to look for MSG_RESET from wait.
   */
  chSemResetI(&dyn_sem->sem, 0);
  chSchRescheduleS();
  chSysUnlock();
  chFactoryReleaseSemaphore(dyn_sem);
}

/*
 * Send shares a common pool of buffers.
 * @retval MSG_RESET    if the semaphore has been reset using @p chSemReset().
 * @retval MSG_TIMEOUT  if the semaphore has not been signaled or reset within
 *                      the specified timeout.
 */
msg_t pktGetPacketBuffer(packet_t *pp, sysinterval_t timeout) {

  /* Check if the packet buffer semaphore already exists.
   * If so we get a pointer to it and get the semaphore.
   */
  dyn_semaphore_t *dyn_sem =
      chFactoryFindSemaphore(PKT_SEND_BUFFER_SEM_NAME);

  chDbgAssert(dyn_sem != NULL, "no send PKT semaphore");

  *pp = NULL;

  if(dyn_sem == NULL)
    return MSG_TIMEOUT;

  /* Wait in queue for permission to allocate a buffer. */
  msg_t msg = chSemWaitTimeout(chFactoryGetSemaphore(dyn_sem), timeout);

  /* Decrease ref count. */
  chFactoryReleaseSemaphore(dyn_sem);

  if(msg != MSG_OK)
    /* This can be MSG_TIMEOUT or MSG_RESET. */
    return msg;

  /* Allocate buffer.
   * If this returns null then all heap is consumed.
   */
  *pp = ax25_new();
  if(pp == NULL)
   return MSG_TIMEOUT;
  return MSG_OK;
}

/*
 * A common pool of AX25 buffers used in TX and APRS.
 */
void pktReleasePacketBuffer(packet_t pp) {
  /* Check if the packet buffer semaphore exists.
   * If not this is a system error.
   */
  dyn_semaphore_t *dyn_sem =
      chFactoryFindSemaphore(PKT_SEND_BUFFER_SEM_NAME);

  chDbgAssert(dyn_sem != NULL, "no general packet buffer semaphore");

  /* Free buffer memory. */
  ax25_delete(pp);

  /* Signal buffer is available. */
  chSemSignal(chFactoryGetSemaphore(dyn_sem));

  /* Decrease factory ref count. */
  chFactoryReleaseSemaphore(dyn_sem);
}

/*
 * Send shares a common pool of buffers.
 */
void pktReleaseBufferSemaphore(radio_unit_t radio) {
/*
#if USE_CCM_FOR_PKT_POOL != TRUE
  packet_svc_t *handler = pktGetServiceObject(radio);

  chDbgAssert(handler != NULL, "invalid radio ID");


   *  Release Semaphore.
   *  If this is the last radio using the semaphore it is released.

  chFactoryReleaseSemaphore(handler->tx_packet_sem);
  handler->tx_packet_sem = NULL;
#else
*/
  (void)radio;
/*#endif*/
}

/*
 *
 */
thread_t *pktCallbackManagerCreate(radio_unit_t radio) {

  packet_svc_t *handler = pktGetServiceObject(radio);

  //chDbgAssert(handler != NULL, "invalid radio ID");

  /* Create the callback termination thread name. */
  chsnprintf(handler->cbend_name, sizeof(handler->cbend_name),
             "%s%02i", PKT_CALLBACK_TERMINATOR_PREFIX, radio);

  /*
   * Initialize the outstanding callback count.
   */
  handler->cb_count = 0;

  /* Start the callback thread terminator. */
  thread_t *cbh = chThdCreateFromHeap(NULL,
              THD_WORKING_AREA_SIZE(PKT_TERMINATOR_WA_SIZE),
              handler->cbend_name,
              NORMALPRIO - 30,
              pktCompletion,
              handler);

  chDbgAssert(cbh != NULL, "failed to create callback terminator thread");
  handler->cb_terminator = cbh;
  return cbh;
}

/**
 *
 */
void pktIncomingBufferPoolRelease(packet_svc_t *handler) {

  /* Release the dynamic objects FIFO for the incoming packet data queue. */
  chFactoryReleaseObjectsFIFO(handler->the_packet_fifo);
  handler->the_packet_fifo = NULL;
}

/**
 *
 */
void pktCallbackManagerRelease(packet_svc_t *handler) {

  /* Tell the callback terminator it should exit. */
  chThdTerminate(handler->cb_terminator);

  /* Wait for it to terminate and release. */
  chThdWait(handler->cb_terminator);
}


/**
 * @brief   Gets service object associated with radio.
 *
 * @param[in] radio    radio unit ID.
 *
 * @return        pointer to the service object.
 * @retval NULL   If the radio ID is invalid or no service object assigned.
 *
 * @api
 */
packet_svc_t *pktGetServiceObject(radio_unit_t radio) {
  /*
   * Get radio configuration object.
   */
  const radio_config_t *data = pktGetRadioData(radio);
  chDbgAssert(data != NULL, "invalid radio ID");
  if(data == NULL)
    return NULL;
  /*
   * Get packet handler object for this radio.
   */
  packet_svc_t *handler = data->pkt;

/*  if(radio == PKT_RADIO_1) {
    handler = &RPKTD1;
  }*/

  chDbgAssert(handler != NULL, "invalid radio packet driver");

  return handler;
}

/** @} */
