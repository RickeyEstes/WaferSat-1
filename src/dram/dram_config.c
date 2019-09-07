
#include "ch.h"
#include "hal.h"
#include "dram_config.h"


const SDRAMConfig sdram_cfg = {
  .sdcr = (uint32_t)(FMC_ColumnBits_Number_8b |
                     FMC_RowBits_Number_12b |
                     FMC_SDMemory_Width_16b |
                     FMC_InternalBank_Number_4 |
                     FMC_CAS_Latency_3 |
                     FMC_Write_Protection_Disable |
                     FMC_SDClock_Period_2 |
                     FMC_Read_Burst_Disable |
                     FMC_ReadPipe_Delay_1),

  .sdtr = (uint32_t)((2   - 1) |  // FMC_LoadToActiveDelay = 2 (TMRD: 2 Clock cycles)
                     (7 <<  4) |  // FMC_ExitSelfRefreshDelay = 7 (TXSR: min=70ns (7x11.11ns))
                     (4 <<  8) |  // FMC_SelfRefreshTime = 4 (TRAS: min=42ns (4x11.11ns) max=120k (ns))
                     (7 << 12) |  // FMC_RowCycleDelay = 7 (TRC:  min=70 (7x11.11ns))
                     (2 << 16) |  // FMC_WriteRecoveryTime = 2 (TWR:  min=1+ 7ns (1+1x11.11ns))
                     (2 << 20) |  // FMC_RPDelay = 2 (TRP:  20ns => 2x11.11ns)
                     (2 << 24)),  // FMC_RCDDelay = 2 (TRCD: 20ns => 2x11.11ns)

  .sdcmr = (uint32_t)(((4 - 1) << 5) |
                      ((FMC_SDCMR_MRD_BURST_LENGTH_2 |
                        FMC_SDCMR_MRD_BURST_TYPE_SEQUENTIAL |
                        FMC_SDCMR_MRD_CAS_LATENCY_3 |
                        FMC_SDCMR_MRD_OPERATING_MODE_STANDARD |
                        FMC_SDCMR_MRD_WRITEBURST_MODE_SINGLE) << 9)),

  /* if (STM32_SYSCLK == 180000000) ->
     64ms / 4096 = 15.625us
     15.625us * 90MHz = 1406 - 20 = 1386 */
  //.sdrtr = (1386 << 1),
  .sdrtr = (uint32_t)(683 << 1),
};
