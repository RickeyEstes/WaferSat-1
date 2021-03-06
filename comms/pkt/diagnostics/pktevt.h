/*
    Aerospace Decoder - Copyright (C) 2018 Bob Anderson (VK2GJ)

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*/

/**
 * @file    pktevt.h
 * @brief   Packet event tracing.
 *
 * @addtogroup pktdiag
 * @{
 */

#ifndef PKT_DIAGNOSTICS_PKTEVT_H_
#define PKT_DIAGNOSTICS_PKTEVT_H_

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
void pktTraceEvents(void);
void pktEnableEventTrace(radio_unit_t radio);
void pktDisableEventTrace(radio_unit_t radio);
#ifdef __cplusplus
}
#endif

#endif /* PKT_DIAGNOSTICS_PKTEVT_H_ */

/** @} */
