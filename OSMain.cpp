#include "MultiBootInfo.h"

__declspec(naked) void multiboot_entry(void)
{
	__asm
	{
		align 4
		multiboot_header:
		//�ش� dd�� define double word�� ��ũ�η� 4����Ʈ ������ ������ Ȯ���Ѵ�.
		dd(MULTIBOOT_HEADER_MAGIC); magic number
			dd(MULTIBOOT_HEADER_FLAGS); flags
			dd(CHECKSUM) checksum
			dd(KERNEL_LOAD_ADDRESS); //Ŀ�� �ε� �ּ�.
		dd(00);
		dd(00);
		dd(HEADER_ADRESS + 0x20); //Ŀ���� ���� �ּ� : ��Ƽ��Ʈ ��� �ּ� + 0x20, Ŀ�� ��Ʈ��.

	kernel_entry:
		mov esp, KERNEL_STACK; //Ŀ�� ���� ����.
		push 0; //�÷��� �������� �ʱ�ȭ.
		popf
			
		//GRUB�� ����ִ� �������� ���ÿ� Ǫ��.
		push ebx; //��Ƽ��Ʈ ���� ������.
		push eax; //���� �ѹ�.

		call osmain; //������ �Լ�, 

		//halt, jmp halt�� ���ؼ� main�Լ��� ���� �������� ����.
		halt;
		jmp halt;
	}
}

void osmain(unsigned long magic, unsigned long addr)
{

}