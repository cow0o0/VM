//"VMEND"�������
#define		VM_END								__asm		push    esi \
												__asm		dec     ebp \
												__asm		inc     ebp \
												__asm		dec     esi \
												__asm		inc     esp

#define		INTCC								__asm		_emit	0xCC
// ���������
void VStartVM();
//����ջ�Ƿ񸲸�
void DCheckESP();

//��D��Ϊ�ڲ�Handler
//�ڲ�push popֻ��32λ����,�μĴ���Ҳ���Ĵ�������
void DPushReg32();
void DPushImm32();
void DPushMem32();

void DPopReg32();//���ؼĴ���
void DFree();//�ͷŶ�ջ
