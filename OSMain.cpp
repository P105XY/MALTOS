#include "MultiBootInfo.h"

__declspec(naked) void multiboot_entry(void)
{
	__asm
	{
		align 4
		multiboot_header:
		//해당 dd는 define double word의 매크로로 4바이트 데이터 공간을 확보한다.
		dd(MULTIBOOT_HEADER_MAGIC); magic number
			dd(MULTIBOOT_HEADER_FLAGS); flags
			dd(CHECKSUM) checksum
			dd(KERNEL_LOAD_ADDRESS); //커널 로드 주소.
		dd(00);
		dd(00);
		dd(HEADER_ADRESS + 0x20); //커널의 시작 주소 : 멀티부트 헤더 주소 + 0x20, 커널 엔트리.

	kernel_entry:
		mov esp, KERNEL_STACK; //커널 스택 설정.
		push 0; //플래그 레지스터 초기화.
		popf
			
		//GRUB에 담겨있는 정보값을 스택에 푸쉬.
		push ebx; //멀티부트 정보 포인터.
		push eax; //매직 넘버.

		call osmain; //실행할 함수, 

		//halt, jmp halt를 통해서 main함수의 종료 이전까지 루프.
		halt;
		jmp halt;
	}
}

void osmain(unsigned long magic, unsigned long addr)
{

}