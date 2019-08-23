#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "wss_shell.h"
#include <string.h>
#include <stdarg.h>
#include "ff.h"
#include "sd.h"

/* Generic large buffer.*/
static uint8_t fbuff[1024];

static void cmd_reset(BaseSequentialStream *chp, int argc, char *argv[]);
static void cmd_tree(BaseSequentialStream *chp, int argc, char *argv[]);
static void cmd_mkfs(BaseSequentialStream *chp, int argc, char* argv[]);

const ShellCommand shell_commands[] = {
  {"tree", cmd_tree},
  //{"cam_init", cmd_cam_init},
  //{"image", cmd_image},
  //{"i", cmd_image},
  //{"image_rgb", cmd_image_rgb},
  //{"membench", cmd_mem_external},
  //{"blink", cmd_blink},
  //{"sensors", cmd_sensors},
  {"reset", cmd_reset},
  {"mkfs", cmd_mkfs},
  {NULL, NULL}
};

static void cmd_reset(BaseSequentialStream *chp, int argc, char *argv[]) {
  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: reset\r\n");
    return;
  }

  chprintf(chp, "Will reset in 200ms\r\n");
  chThdSleepMilliseconds(200);
  NVIC_SystemReset();
}

static FRESULT scan_files(BaseSequentialStream *chp, char *path) {
  static FILINFO fno;
  FRESULT res;
  DIR dir;
  size_t i;
  char *fn;

  res = f_opendir(&dir, path);
  if (res == FR_OK) {
    i = strlen(path);
    while (((res = f_readdir(&dir, &fno)) == FR_OK) && fno.fname[0]) {
      if (FF_FS_RPATH && fno.fname[0] == '.')
        continue;
      fn = fno.fname;
      if (fno.fattrib & AM_DIR) {
        *(path + i) = '/';
        strcpy(path + i + 1, fn);
        res = scan_files(chp, path);
        *(path + i) = '\0';
        if (res != FR_OK)
          break;
      }
      else {
        chprintf(chp, "%s/%s\r\n", path, fn);
      }
    }
  }
  return res;
}

static void cmd_tree(BaseSequentialStream *chp, int argc, char *argv[]) {
  FRESULT err;
  uint32_t fre_clust;
  FATFS *fsp;

  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: tree\r\n");
    return;
  }
  if (!sd_fs_ready) {
    chprintf(chp, "File System not mounted\r\n");
    return;
  }
  err = f_getfree("/", &fre_clust, &fsp);
  if (err != FR_OK) {
    chprintf(chp, "FS: f_getfree() failed\r\n");
    return;
  }
  chprintf(chp,
           "FS: %lu free clusters with %lu sectors (%lu bytes) per cluster\r\n",
           fre_clust, (uint32_t)fsp->csize, (uint32_t)fsp->csize * 512);
  fbuff[0] = 0;
  scan_files(chp, (char *)fbuff);
}

static void cmd_mkfs(BaseSequentialStream* chp, int argc, char* argv[])
{
	if(sd_fs_ready)
	{
		chprintf(chp, "Filesystem currently mounted, aborting!\n");
		return;
	}

	if (!sd_block_ready)
	{
		chprintf(chp, "No SD card to mkfs() on!\n");
		return;
	}

	sd_mkfs();
}
