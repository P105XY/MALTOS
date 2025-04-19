#pragma once
#include <cstdint>
#include <basetsd.h>

/*
�ش� ����� _emit x�� ����Ѵ�.
�ش� ����� ����Ʈ ��� x �� ���� ��ġ�� ��� �Է��Ѵٴ� �ǹ��̴�.
�ش� �ڵ�� ���� �⺻ ��ġ  x�� 1����Ʈ�� �Է�.
���� x�������� >> 8�� ���, 8��Ʈ�� �̵��� ���� 0xff�� �Է�.
>> 16��Ʈ �̵�, >>24 ��Ʈ �̵����� �� 24��Ʈ (0~3, 4����Ʈ)�� �̵��ϸ鼭 �����͸� �Է��Ѵ�.
 */
#define dd(x)                            \
        __asm _emit     (x)       & 0xff \
        __asm _emit     (x) >> 8  & 0xff \
        __asm _emit     (x) >> 16 & 0xff \
        __asm _emit     (x) >> 24 & 0xff

#define KERNEL_STACK			0x00400000
#define FREE_MEMORY_SPACE_ADDRESS       0x00400000

/*  �ش� ALIGN�����ʹ� GRUB���� PEĿ���� �ε�� �ʿ��� ������.
�̶� PE����� ���� ������� ���� �������� ���ʿ� �ִµ�, �� ALIGN�� 0x400ũ��� 1kb.
multiboot entry�Լ��� ������ ���� ó�� 80kb�ȿ� �ִµ�, 1kb�� ���ؼ� ã�� ����.
 */
#define   ALIGN               0x400

 /*   GRUB�̶�� 1mb���� Ŀ���Ѵ�.
 ��� ��Ŀ �ɼ��� �⺻ �ּ�,
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
	uint32_t flags; //�÷���, �ش� �÷��� ���� ����ؼ� VESA����� ��� ���θ� �����Ѵ�.

	uint32_t mem_lower;
	uint32_t mem_upper; //�� ������, ��� ������ �޸��� ���� ������ �����Ѵ�.

	uint32_t boot_device; //���� ���� ����̽��� ��ȣ.
	char* cmdline; //Ŀ�ο� �ѱ�� Ŀ�ǵ����.

	uint32_t mode_count;
	Module* module; //���� ���õ� ������.

	union
	{
		AOUTSymbolTable AOutTable;
		ELFHeaderTable ELFTable;
	} SymbolTables; //������ ���ϰ� ���õ� ����.

	uint32_t mmap_length;
	uint32_t mmap_addr; //�޸� ���� ���� -> �ش� �����ͷ� Ư�� �޸� ����� ��� ���� ���θ� üũ.

	uint32_t drives_lengths;
	drive_info drives_addr; //�ش� PC�� ����̺� ����.

	ROMConfigurationTable* ConfigTable; //���� ROM�� config ���̺�.

	char* boot_loader_name; //���� ��Ʈ�δ� �̸�.

	APMTable* APMTable; //���� APM ���̺�.

	VbeInfoBlock* vbe_control_info;
	VbeModeInfo* vbe_mode_info;
	uint16_t vbe_mode;
	uint16_t vbe_interface_seg;
	uint16_t vbe_interface_off;
	uint16_t vbe_interface_len; //���� ���� ��� ������.
};
typedef struct multiboot_info multiboot_info_t;
