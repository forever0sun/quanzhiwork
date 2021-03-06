#ifndef __NAND_FOR_HWSCAN__
#define __NAND_FOR_HWSCAN__


#define SUCCESS	0
#define FAIL	-1
#define BADBLOCK -2

typedef struct
{
    __u8 id[8];
    __u8 chip_cnt;
    __u8 chip_connect;
    __u8 rb_cnt;
    __u8 rb_connect;
    __u32 good_block_ratio;
} _nand_connect_info_t;


struct boot_physical_param
{
    __u8   chip; //chip no
    __u16  block; // block no within chip
    __u16  page; // page no within block
    __u16  sectorbitmap; //done't care
    void   *mainbuf; //data buf
    void   *oobbuf; //oob buf
};

struct boot_flash_info
{
    __u32 chip_cnt;
    __u32 blk_cnt_per_chip;
    __u32 blocksize; //unit by sector
    __u32 pagesize; //unit by sector
    __u32 pagewithbadflag; /*bad block flag was written at the first byte of spare area of this page*/
};

/*
************************************************************************************************************************
*                       SCAN NAND HW
*
*Description: initial nand flash,request hardware resources;
*
*Arguments  : void.
*
*Return     :   = SUCESS  initial ok;
*               = FAIL    initial fail.
************************************************************************************************************************
*/
__s32 NAND_HWScanStart(_nand_connect_info_t *nand_connect);


/************************************************************************************************************************
*                       NAND_HWScanStop
*
*Description: release  nand flash and free hardware resources;
*
*Arguments  : void.
*
*Return     :   = SUCESS  release ok;
*               = FAIL    release fail.
************************************************************************************************************************
*/
__s32 NAND_HWScanStop(void);


/*
************************************************************************************************************************
*                       GET FLASH INFO
*
*Description: get some info about nand flash;
*
*Arguments  : *param     the stucture with info.
*
*Return     :   = SUCESS  get ok;
*               = FAIL    get fail.
************************************************************************************************************************
*/
__s32 NAND_GetFlashInfo(struct boot_flash_info *param);

/*
************************************************************************************************************************
*                       GET NAND VERSION INFO
*
*Description: get some info about nand flash;
*
*Arguments  : *param     the stucture with info.
*
*Return     :   >0     get ok;
*               =0    get fail.
************************************************************************************************************************
*/
__u32 NAND_GetNandVersion(void);

/*
************************************************************************************************************************
*                       READ ONE SINGLE PAGE
*
*Description: read one page data from nand based on single plane;
*
*Arguments  : *readop - the structure with physical address in nand and data buffer
*
*Return     :   = SUCESS  read ok;
*               = FAIL    read fail.
************************************************************************************************************************
*/
__s32 NAND_PhyRead (struct boot_physical_param *readop);

/*
************************************************************************************************************************
*                       READ ONE SINGLE PAGE
*
*Description: read one page data from nand based on single plane;
*
*Arguments  : *readop - the structure with physical address in nand and data buffer
*
*Return     :   = SUCESS  read ok;
*               = FAIL    read fail.
************************************************************************************************************************
*/
__s32 NAND_PhyRead_Seq (struct boot_physical_param *readop);

__s32 NAND_PhyRead_1K (struct boot_physical_param *readop);

/*
************************************************************************************************************************
*                       WRITE ONE SINGLE PAGE
*
*Description: write one page data to nand based on single plane;
*
*Arguments  : *writeop - the structure with physical address in nand and data buffer
*
*Return     :   = SUCESS  	write ok;
*               = FAIL    	write fail.
*				= BADBLOCK	write fail and bad block made by program
************************************************************************************************************************
*/
__s32 NAND_PhyWrite (struct boot_physical_param *writeop);

/*
************************************************************************************************************************
*                       ERASE ONE SINGLE BLOCK
*
*Description: erase one block in nand based on single plane;
*
*Arguments  : *eraseop - the structure with physical address in nand and data buffer
*
*Return     :   = SUCESS  	erase ok;
*               = FAIL    	erase fail.
*				= BADBLOCK	erase fail and bad block made by erase
************************************************************************************************************************
*/
__s32 NAND_PhyErase(struct boot_physical_param *eraseop);


/*
************************************************************************************************************************
*                       NAND_VersionCheck
*
*Description: Check the nand flash driver is current version
*
*Arguments  : void.
*
*Return     :   = 0  nand driver version match;
*                -1  nand driver version not match
************************************************************************************************************************
*/
__s32 NAND_VersionCheck(void);


/*
************************************************************************************************************************
*                       NAND_EraseBootBlocks
*
*Description: Check the nand flash driver is current version
*
*Arguments  : connecnt info.
*
*Return     :   = 0     OK;
*               other  Fail.
************************************************************************************************************************
*/
__s32  NAND_EraseBootBlocks( const _nand_connect_info_t *connect_info_p);


/*
************************************************************************************************************************
*                       NAND_EraseChip
*
*Description: Erase chip, only erase the all 0x0 blocks
*
*Arguments  : connecnt info.
*
*Return     :   = 0     OK;
*               other  Fail.
************************************************************************************************************************
*/
__s32  NAND_EraseChip( const _nand_connect_info_t *connect_info_p);

/*******************************************************************************
*函数名称: NAND_BadBlockScan
*函数原型：bad_blcok_scan(const _nand_connect_info_t *connect_info_p)
*函数功能: 标记blk_num指定的块为坏块。
*入口参数: connect_info_p
*返 回 值: >0              编程操作成功
*          -1              编程操作失败
*
*备    注:
*******************************************************************************/
__s32 NAND_BadBlockScan(const _nand_connect_info_t *connect_info_p);


#endif
