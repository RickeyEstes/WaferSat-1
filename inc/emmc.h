#ifndef __EMMC_H__
#define __EMMC_H__
 
#define EMMCD SDCD1
#define emmc_init() sdcStart(&EMMCD, NULL)
 
#endif /* __EMMC_H__ */
