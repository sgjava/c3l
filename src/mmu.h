/*
 * C128 8722 MMU.
 *
 * Copyright (c) Steven P. Goldsmith. All rights reserved.
 */

#define mmuCtrlReg1     0xd500 /* Configuration register */
#define mmuPreCfgRegA   0xd501 /* Preconfiguration register A */
#define mmuPreCfgRegB   0xd502 /* Preconfiguration register B */
#define mmuPreCfgRegC   0xd503 /* Preconfiguration register C */
#define mmuPreCfgRegD   0xd504 /* Preconfiguration register D */
#define mmuModeCfg      0xd505 /* Mode configuration register */
#define mmuRamCfg       0xd506 /* RAM configuration register */
#define mmuPage0PagePtr 0xd507 /* Page 0 page pointer */
#define mmuPage0lkPtr   0xd508 /* Page 0 block pointer */
#define mmuPage1PagePtr 0xd509 /* Page 1 page pointer */
#define mmuPage1BlkPtr  0xd50a /* Page 1 block pointer */
#define mmuVerReg       0xd50b /* MMU version register */
