#pragma once
#include <cstdint>
#include <basetsd.h>

/*
해당 기능은 _emit x을 사용한다.
해당 기능은 바이트 상수 x 를 현재 위치의 기계어에 입력한다는 의미이다.
해당 코드는 가장 기본 위치  x에 1바이트를 입력.
이후 x기준으로 >> 8을 사용, 8비트를 이동한 값에 0xff를 입력.
>> 16비트 이동, >>24 비트 이동으로 총 24비트 (0~3, 4바이트)를 이동하면서 데이터를 입력한다.
 */
#define dd(x)                            \
        __asm _emit     (x)       & 0xff \
        __asm _emit     (x) >> 8  & 0xff \
        __asm _emit     (x) >> 16 & 0xff \
        __asm _emit     (x) >> 24 & 0xff

#define KERNEL_STACK			0x00400000
#define FREE_MEMORY_SPACE_ADDRESS       0x00400000

/*  해당 ALIGN데이터는 GRUB에서 PE커널을 로드시 필요한 데이터.
이때 PE사용을 위한 헤더들은 보통 데이터의 앞쪽에 있는데, 이 ALIGN의 0x400크기는 1kb.
multiboot entry함수는 파일의 가장 처음 80kb안에 있는데, 1kb를 통해서 찾기 가능.
 */
#define   ALIGN               0x400

 /*   GRUB이라면 1mb보다 커야한다.
 고급 링커 옵션의 기본 주소,
 */
#define KERNEL_LOAD_ADDRESS            0x100000

#define   HEADER_ADRESS         KERNEL_LOAD_ADDRESS+ALIGN

#define MULTIBOOT_HEADER_MAGIC         0x1BADB002
#define MULTIBOOT_BOOTLOADER_MAGIC      0x2BADB002
#define MULTIBOOT_HEADER_FLAGS         0x00010003 
#define STACK_SIZE              0x4000    
#define CHECKSUM            -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

struct Module
{
	void* ModuleStart;
	void* ModuleEnd;
	char* Name;
	unsigned int Reserved;
};

struct ELFHeaderTable
{
	uint32_t num;
	uint32_t size;
	uint32_t addr;
	uint32_t shndx;
};
typedef struct multiboot_elf_section_header_table multiboot_elf_section_header_table_t;

struct AOUTSymbolTable
{
	unsigned int tabsize;
	unsigned int strsize;
	unsigned int addr;
	unsigned int reserved;
};

/* Drive Info structure.  */
struct drive_info
{
	/* The size of this structure.  */
	unsigned long size;

	/* The BIOS drive number.  */
	unsigned char drive_number;

	/* The access mode (see below).  */
	unsigned char drive_mode;

	/* The BIOS geometry.  */
	unsigned short drive_cylinders;
	unsigned char drive_heads;
	unsigned char drive_sectors;

	/* The array of I/O ports used for the drive.  */
	unsigned short drive_ports;
};

//Bochs 2.4 doesn't provide a ROM configuration table. Virtual PC does.
struct ROMConfigurationTable
{
	unsigned short Length;
	unsigned char Model;
	unsigned char Submodel;
	unsigned char BiosRevision;
	bool DualBus : 1;
	bool MicroChannelBus : 1;
	bool EBDAExists : 1;
	bool WaitForExternalEventSupported : 1;
	bool Reserved0 : 1;
	bool HasRTC : 1;
	bool MultipleInterruptControllers : 1;
	bool BiosUsesDMA3 : 1;
	bool Reserved1 : 1;
	bool DataStreamingSupported : 1;
	bool NonStandardKeyboard : 1;
	bool BiosControlCpu : 1;
	bool BiosGetMemoryMap : 1;
	bool BiosGetPosData : 1;
	bool BiosKeyboard : 1;
	bool DMA32Supported : 1;
	bool ImlSCSISupported : 1;
	bool ImlLoad : 1;
	bool InformationPanelInstalled : 1;
	bool SCSISupported : 1;
	bool RomToRamSupported : 1;
	bool Reserved2 : 3;
	bool ExtendedPOST : 1;
	bool MemorySplit16MB : 1;
	unsigned char Reserved3 : 1;
	unsigned char AdvancedBIOSPresence : 3;
	bool EEPROMPresent : 1;
	bool Reserved4 : 1;
	bool FlashEPROMPresent : 1;
	bool EnhancedMouseMode : 1;
	unsigned char Reserved5 : 6;
};

#pragma pack(push,1)
struct MULTIBOOT_HEADER {
	uint32_t magic;
	uint32_t flags;
	uint32_t checksum;
	uint32_t header_addr;
	uint32_t load_addr;
	uint32_t load_end_addr;
	uint32_t bss_end_addr;
	uint32_t entry_addr;
};

struct APMTable
{
	unsigned short Version;
	unsigned short CS;
	unsigned int Offset;
	unsigned short CS16Bit;	//This is the 16-bit protected mode code segment
	unsigned short DS;
	unsigned short Flags;
	unsigned short CSLength;
	unsigned short CS16BitLength;
	unsigned short DSLength;
};

struct VbeInfoBlock
{
	char Signature[4];
	unsigned short Version;
	short OEMString[2];
	unsigned char Capabilities[4];
	short VideoModes[2];
	short TotalMemory;
};

struct VbeModeInfo
{
	UINT16 ModeAttributes;
	char WinAAttributes;
	char WinBAttributes;
	UINT16 WinGranularity;
	UINT16 WinSize;
	UINT16 WinASegment;
	UINT16 WinBSegment;
	UINT32 WinFuncPtr;
	short BytesPerScanLine;
	short XRes;
	short YRes;
	char XCharSize;
	char YCharSize;
	char NumberOfPlanes;
	char BitsPerPixel;
	char NumberOfBanks;
	char MemoryModel;
	char BankSize;
	char NumberOfImagePages;
	char res1;
	char RedMaskSize;
	char RedFieldPosition;
	char GreenMaskSize;
	char GreenFieldPosition;
	char BlueMaskSize;
	char BlueFieldPosition;
	char RsvedMaskSize;
	char RsvedFieldPosition;
	char DirectColorModeInfo; //MISSED IN THIS TUTORIAL!! SEE ABOVE
	//VBE 2.0
	UINT32 PhysBasePtr;
	UINT32 OffScreenMemOffset;
	short OffScreenMemSize;
	//VBE 2.1
	short LinbytesPerScanLine;
	char BankNumberOfImagePages;
	char LinNumberOfImagePages;
	char LinRedMaskSize;
	char LinRedFieldPosition;
	char LingreenMaskSize;
	char LinGreenFieldPosition;
	char LinBlueMaskSize;
	char LinBlueFieldPosition;
	char LinRsvdMaskSize;
	char LinRsvdFieldPosition;
	char res2[194];
};

#pragma pack(push,1)
struct MULTIBOOT_HEADER {
	uint32_t magic;
	uint32_t flags;
	uint32_t checksum;
	uint32_t header_addr;
	uint32_t load_addr;
	uint32_t load_end_addr;
	uint32_t bss_end_addr;
	uint32_t entry_addr;
};

struct multiboot_info
{
	uint32_t flags; //플래스, 해당 플래그 값을 사용해서 VESA모드의 사용 여부를 설정한다.

	uint32_t mem_lower;
	uint32_t mem_upper; //두 변수로, 사용 가능한 메모리의 영역 정보를 설정한다.

	uint32_t boot_device; //현재 부팅 디바이스의 번호.
	char* cmdline; //커널에 넘기는 커맨드라인.

	uint32_t mode_count;
	Module* module; //모듈과 관련된 데이터.

	union
	{
		AOUTSymbolTable AOutTable;
		ELFHeaderTable ELFTable;
	} SymbolTables; //리눅스 파일과 관련된 정보.

	uint32_t mmap_length;
	uint32_t mmap_addr; //메모리 매핑 정보 -> 해당 데이터로 특정 메모리 블록의 사용 가능 여부를 체크.

	uint32_t drives_lengths;
	drive_info drives_addr; //해당 PC의 드라이브 정보.

	ROMConfigurationTable* ConfigTable; //현재 ROM의 config 테이블.

	char* boot_loader_name; //현재 부트로더 이름.

	APMTable* APMTable; //현재 APM 테이블.

	VbeInfoBlock* vbe_control_info;
	VbeModeInfo* vbe_mode_info;
	uint16_t vbe_mode;
	uint16_t vbe_interface_seg;
	uint16_t vbe_interface_off;
	uint16_t vbe_interface_len; //비디오 관련 모드 데이터.
};
typedef struct multiboot_info multiboot_info_t;
