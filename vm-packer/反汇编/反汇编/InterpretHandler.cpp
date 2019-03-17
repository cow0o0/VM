#include "StdAfx.h"
#include "InterpretHandler.h"
#include "asm/disasm.h"

CInterpretHandler::CInterpretHandler(void)
{
}

CInterpretHandler::~CInterpretHandler(void)
{
}
// ��üĴ�����ƫ��
// 16��32λ��8λ���ֽھ�ʹ��32λenum��8λ���ֽ�ʹ��20���ϵ���
int CInterpretHandler::GetRegisterOffset(int RegType)
{
	if( RegType < 0 )
		return RegType;
	int offset = m_RegisterIdx[RegType]*4;
	if ( RegType >= 20 )
		offset++;//8λ���ֽڵĵط�
	return offset;
}
//��ʼ��
BOOL CInterpretHandler::Init()
{
	RandListIdx(m_RegisterIdx,REGCOUNT);	//���ҼĴ���ƫ�Ƶ�����

	return TRUE;
}

//���ò���
void CInterpretHandler::SetArg(VMTable* table,char* asmtext,int len)
{
	for(int i = 0; i < 3; i++)
	{
		if( i >= table->OperandNum )
			break;
		sprintf_s(asmtext,len,"%smov %s,[esp+%02x]\n",asmtext,ArgReg[i],i*4);//����ջ�е����ݽ��������Ĵ���
	}
}
//�ָ�����
void CInterpretHandler::RestoreArg(VMTable* table,char* asmtext,int len)
{
	//���������ض�ջ
	for(int i = 0; i < 3; i++)
	{
		if( i >= table->OperandNum )
			break;
		sprintf_s(asmtext,len,"%smov [esp+%02x],%s\n",asmtext,i*4,ArgReg[i]);
	}
}
//�ָ���־
void CInterpretHandler::RestoreFlag(char* asmtext,int len)
{
	sprintf_s(asmtext,len,"%sPush [edi+0x%02x]\nPopfd\n",asmtext,GetRegisterOffset(RT_EFlag));//�ָ���־
}
//�����־
void CInterpretHandler::SaveFlag(char* asmtext,int len)
{
	sprintf_s(asmtext,len,"%sPushfd\nPop [edi+0x%02x]\n",asmtext,GetRegisterOffset(RT_EFlag));//�����־
}
//���ݽṹ����ASM�ַ���
BOOL CInterpretHandler::InterpretASMStr(VMTable* table,char* asmtext,int len)
{
	if( strcmp(table->VMInstrName,"") == 0 || asmtext == NULL ) return FALSE;

	memset(asmtext,0,len);

	SetArg(table,asmtext,len);//���ò���

	//�ָ���Ҫ�ļĴ���
	for(int i = 0; i < 4; i++)
	{
		if( table->NeedReg[i] != NONE && table->NeedReg[i] < 14 )
		{
			sprintf_s(asmtext,len,"%smov %s,[edi+0x%02x]\n",asmtext,
				vregname[2][table->NeedReg[i]],GetRegisterOffset(table->NeedReg[i]));
		}
	}

	BOOL After = FALSE;
	if( _stricmp(table->strInstruction,"vBegin") == 0 )
	{
		After = InterpretvBegin(table,asmtext,len);
	}
	else if( _stricmp(table->strInstruction,"vtoReal") == 0 )
	{
		After = InterpretvtoReal(table,asmtext,len);
	}
///////////////////////////////////////////////////////////////////////////////
	else if( _stricmp(table->strInstruction,"push") == 0 )
	{
		After = InterpretPush(table,asmtext,len);
	}
	else if( _stricmp(table->strInstruction,"pop") == 0 )
	{
		After = InterpretPop(table,asmtext,len);
	}
	else if( _stricmp(table->strInstruction,"pushfd") == 0 )
	{
		After = InterpretPushfd(table,asmtext,len);
	}
	else if( _stricmp(table->strInstruction,"popfd") == 0 )
	{
		After = InterpretPopfd(table,asmtext,len);
	}
	else if( _stricmp(table->strInstruction,"pushad") == 0 )
	{
		After = InterpretPushad(table,asmtext,len);
	}
	else if( _stricmp(table->strInstruction,"popad") == 0 )
	{
		After = InterpretPopad(table,asmtext,len);
	}
	else if( _stricmp(table->strInstruction,"enter") == 0 )
	{
		After = InterpretEnter(table,asmtext,len);
	}
	else if( _stricmp(table->strInstruction,"leave") == 0 )
	{
		After = InterpretLeave(table,asmtext,len);
	}
/////////////////////////////////////////////////////////////////////////////////
	else if( _stricmp(table->strInstruction,"jcxz") == 0 )
	{
		RestoreFlag(asmtext,len);
		After = InterpretJCXZ(table,asmtext,len);
	}
	else if( _stricmp(table->strInstruction,"jmp") == 0 )
	{
		After = InterpretJMP(table,asmtext,len);
	}
	else if( table->strInstruction[0] == 'J' || table->strInstruction[0] == 'j' )//����jcxz��jmp,����������ת��
	{
		RestoreFlag(asmtext,len);
		After = InterpretJCC(table,asmtext,len);
	}
	else if( _stricmp(table->strInstruction,"loope") == 0 )
	{
		RestoreFlag(asmtext,len);
		After = InterpretLoope(table,asmtext,len);
		SaveFlag(asmtext,len);
	}
	else if( _stricmp(table->strInstruction,"retn") == 0 )
	{
		After = InterpretRetn(table,asmtext,len);
	}
	else if( _stricmp(table->strInstruction,"call") == 0 )
	{
		After = InterpretCall(table,asmtext,len);
	}
	else if( _stricmp(table->strInstruction,"SaveEsp") == 0 )
	{
		After = InterpretSaveEsp(table,asmtext,len);
	}
	else if( _stricmp(table->strInstruction,"RestoreEsp") == 0 )
	{
		After = InterpretRestoreEsp(table,asmtext,len);
	}
	else
	{
		After = CommonInstruction(table,asmtext,len);
	}

	//sprintf_s(asmtext,len,"%smov [edi+%02x],ebp\n",asmtext,GetRegisterOffset(RT_Esp));//��ebp(������esp)���浽esp�ĵ�ַ
	//����Ĵ�����ֵ
	for(int i = 0; i < 3; i++)
	{
		if( table->SaveReg[i] != NONE )
		{
			sprintf_s(asmtext,len,"%smov [edi+0x%02x],%s\n",asmtext,
				GetRegisterOffset(table->NeedReg[i]),vregname[2][table->NeedReg[i]]);
		}
	}

	if( After )
	{
		RestoreArg(table,asmtext,len);
	}

	_strupr_s(asmtext,ASMTEXTLEN);
	return TRUE;
}
int GetScalestr(int bit,OUT char* scalestr)
{
	int sizeidx = 0;
	if( bit == 8 )
	{
		sizeidx = 0;
		strcpy_s(scalestr,6,"byte");
	}
	else if( bit == 16 )
	{
		sizeidx = 1;
		strcpy_s(scalestr,6,"word");
	}
	else if( bit == 32 )
	{
		sizeidx = 2;
		strcpy_s(scalestr,6,"dword");
	}
	return sizeidx;
}

BOOL CInterpretHandler::CommonInstruction(VMTable* table,char* asmtext,int len)
{
	char scalestr[6] = {0};
	int sizeidx = 0;

	char stroperand[1024] = {0};
	for(int i = 0; i < 3; i++)
	{
		if( i >= table->OperandNum )
			break;
		sizeidx = GetScalestr(table->bitnum[i],scalestr);
		if( table->optype[i] == MEMTYPE )//�ڴ���
		{	//������˳��eax,ecx,edx
			sprintf_s(stroperand,1024,"%s%s ptr %s[%s],",stroperand,scalestr,GetSegStr(table->Segment),vregname[2][i]);//�õ�����
		}
		else//�������ͼĴ���
		{
			sprintf_s(stroperand,1024,"%s%s,",stroperand,vregname[sizeidx][i]);//�õ�����
		}
	}
	if( table->OperandNum > 0)
		stroperand[strlen(stroperand)-1] = '\0';//ȥ������

	RestoreFlag(asmtext,len);
	sprintf_s(asmtext,len,"%s%s %s\n",asmtext,table->strInstruction,stroperand);//����ִ�е�ָ��
	SaveFlag(asmtext,len);
	return TRUE;
}

// ��ö�ǰ׺
char* CInterpretHandler::GetSegStr(int Segment)
{
	static char segstr[10] = "";
	memset(segstr,0,10);
	if( Segment == SEG_FS )
		strcpy_s(segstr,10,"fs:");
	else if( Segment == SEG_GS )
		strcpy_s(segstr,10,"gs:");
	return segstr;
}
// ����ִ�е�ָ��
BOOL CInterpretHandler::InterpretvBegin(VMTable* table,char* asmtext,int len)
{
	//popfd
	//pop ebp
	//pop edi
	//pop esi
	//pop edx
	//pop ecx
	//pop eax
	int s_reg[8] = {RT_EFlag,RT_Ebp,RT_Edi,RT_Esi,RT_Edx,RT_Ecx,RT_Ebx,RT_Eax};

	// �����Ĵ���
	for(int i = 0; i < 8;i++)
	{
		sprintf_s(asmtext,len,"%smov eax,dword ptr [ebp]\n",asmtext);
		sprintf_s(asmtext,len,"%smov [edi+%02X],eax\n",asmtext,GetRegisterOffset(s_reg[i]));
		
		sprintf_s(asmtext,len,"%sadd ebp,4\n",asmtext);
	}
	// �ͷ�α��ַ��ջ
	sprintf_s(asmtext,len,"%sadd ebp,4\n",asmtext);
	sprintf_s(asmtext,len,"%smov [edi+%02x],ebp\n",asmtext,GetRegisterOffset(RT_Esp));//��ebp(������esp)���浽esp�ĵ�ַ

	return FALSE;
}

// ��ת����ʵָ��
BOOL CInterpretHandler::InterpretvtoReal(VMTable* table,char* asmtext,int len)
{
	int s_reg[9] = {RT_Esp,RT_EFlag,RT_Ebp,RT_Edi,RT_Esi,RT_Edx,RT_Ecx,RT_Ebx,RT_Eax};
	//֮ǰ��һ��pushimm32 xxxx��ַ

	//�����ֵ������ʵ��ջ
	sprintf_s(asmtext,len,"%smov eax,dword ptr [esi]\n",asmtext);//�ͷ�4�ֽڶ�ջ
	sprintf_s(asmtext,len,"%sadd esi,4\n",asmtext);
	sprintf_s(asmtext,len,"%ssub ebp,4\n",asmtext);
	sprintf_s(asmtext,len,"%smov dword ptr [ebp],eax\n",asmtext);//eax,��1������

	sprintf_s(asmtext,len,"%smov [edi+%02x],ebp\n",asmtext,GetRegisterOffset(RT_Esp));//��ebp(������esp)���浽esp�ĵ�ַ

	// �����Ĵ���
	for(int i = 0; i < 9;i++)
	{
		sprintf_s(asmtext,len,"%spush [edi+%02X]\n",asmtext,GetRegisterOffset(s_reg[i]));
	}
	sprintf_s(asmtext,len,"%spop eax\n",asmtext);
	sprintf_s(asmtext,len,"%spop ebx\n",asmtext);
	sprintf_s(asmtext,len,"%spop ecx\n",asmtext);
	sprintf_s(asmtext,len,"%spop edx\n",asmtext);
	sprintf_s(asmtext,len,"%spop esi\n",asmtext);
	sprintf_s(asmtext,len,"%spop edi\n",asmtext);
	sprintf_s(asmtext,len,"%spop ebp\n",asmtext);
	sprintf_s(asmtext,len,"%spopfd\n",asmtext);
	sprintf_s(asmtext,len,"%spop esp\n",asmtext);
	//����
	sprintf_s(asmtext,len,"%sretn\n",asmtext);
	return FALSE;
}
//		mov		eax,dword ptr [esp]
//		sub		ebp,4
//		mov		eax,[eax]
//		mov		word ptr [ebp],ax
//����push
BOOL CInterpretHandler::InterpretPush(VMTable* table,char* asmtext,int len)
{
	char scalestr[6] = {0};
	int sizeidx = 0;
	if( table->bitnum[0] == 8 )
	{
		sizeidx = 0;
		strcpy_s(scalestr,6,"byte");
	}
	else if( table->bitnum[0] == 16 )
	{
		sizeidx = 1;
		strcpy_s(scalestr,6,"word");
	}
	else if( table->bitnum[0] == 32 )
	{
		sizeidx = 2;
		strcpy_s(scalestr,6,"dword");
	}

	sprintf_s(asmtext,len,"%ssub ebp,%d\n",asmtext,table->bitnum[0] / 8);//�Ӷ�ջ���ڳ��ռ�
	if( table->optype[0] == MEMTYPE )
	{
		sprintf_s(asmtext,len,"%smov %s,%s ptr %s[eax]\n",asmtext,vregname[sizeidx][RT_Eax],scalestr,GetSegStr(table->Segment));//�õ��ڴ�����ֵ
	}
	sprintf_s(asmtext,len,"%smov %s ptr [ebp],%s\n",asmtext,scalestr,vregname[sizeidx][RT_Eax]);
	return TRUE;
}
//		mov		eax,dword ptr [ebp]
//		add		ebp,4
//		mov		eax,[eax]
//����pop
BOOL CInterpretHandler::InterpretPop(VMTable* table,char* asmtext,int len)
{
	char scalestr[6] = {0};
	int sizeidx = 0;
	if( table->bitnum[0] == 8 )
	{
		sizeidx = 0;
		strcpy_s(scalestr,6,"byte");
	}
	else if( table->bitnum[0] == 16 )
	{
		sizeidx = 1;
		strcpy_s(scalestr,6,"word");
	}
	else if( table->bitnum[0] == 32 )
	{
		sizeidx = 2;
		strcpy_s(scalestr,6,"dword");
	}
	sprintf_s(asmtext,len,"%smov %s,%s ptr [ebp]\n",asmtext,vregname[sizeidx][RT_Ecx],scalestr);//�õ���ջ��ֵ
	sprintf_s(asmtext,len,"%sadd ebp,%d\n",asmtext,table->bitnum[0] / 8);//�ͷ�4�ֽڶ�ջ
	if( table->optype[0] == MEMTYPE )
	{
		sprintf_s(asmtext,len,"%smov %s,%s ptr %s[eax]\n",asmtext,vregname[sizeidx][RT_Eax],scalestr,GetSegStr(table->Segment));//�õ��ڴ�����ֵ
	}
	sprintf_s(asmtext,len,"%smov eax,ecx\n",asmtext);//��ֵ��mem(ֻ��mem����Ϊ������reg����mem��vm�ж����ڴ��ַ)
	return TRUE;
}

//����pushfd
BOOL CInterpretHandler::InterpretPushfd(VMTable* table,char* asmtext,int len)
{
	sprintf_s(asmtext,len,"%ssub ebp,4\n",asmtext);//�Ӷ�ջ��ȡ�ò���
	sprintf_s(asmtext,len,"%smov eax,[edi+%02x]\n",asmtext,GetRegisterOffset(RT_EFlag));//�õ�EFL
	sprintf_s(asmtext,len,"%smov dword ptr [ebp],eax\n",asmtext);//��ֵEFL�Ĵ���
	return TRUE;
}
//����popfd
BOOL CInterpretHandler::InterpretPopfd(VMTable* table,char* asmtext,int len)
{
	sprintf_s(asmtext,len,"%smov eax,dword ptr [ebp]\n",asmtext);//��ֵEFL�Ĵ���
	sprintf_s(asmtext,len,"%sadd ebp,4\n",asmtext);//�ͷŶ�ջ
	sprintf_s(asmtext,len,"%smov [edi+%02x],eax\n",asmtext,GetRegisterOffset(RT_EFlag));//����EFL
	return TRUE;
}


// ����pushad
BOOL CInterpretHandler::InterpretPushad(VMTable* table,char* asmtext,int len)
{
	for(int i = 0 ; i < 8;i++)
	{
		sprintf_s(asmtext,len,"%ssub ebp,4\n",asmtext);//�Ӷ�ջ��ȡ�ò���
		sprintf_s(asmtext,len,"%smov eax,[edi+%02x]\n",asmtext,GetRegisterOffset(i));//i = enum RegType
		sprintf_s(asmtext,len,"%smov dword ptr [ebp],eax\n",asmtext);//push
	}
	return TRUE;
}

// ����popad
BOOL CInterpretHandler::InterpretPopad(VMTable* table,char* asmtext,int len)
{
	for(int i = 8 ; i > 0;i--)
	{
		sprintf_s(asmtext,len,"%smov eax,dword ptr [ebp]\n",asmtext);//
		sprintf_s(asmtext,len,"%sadd ebp,4\n",asmtext);//�ͷŶ�ջ
		sprintf_s(asmtext,len,"%smov [edi+%02x],eax\n",asmtext,GetRegisterOffset(i));//i = enum RegType
	}
	return TRUE;
}

// ����enter
//push ebp
//mov ebp,esp
//sub esp,(L - 1) * 4 ; L > 0�����ⲽ�����������洢Ƕ�׵�L - 1���ӹ��̵�ջ���ָ�루ע����ָ�룩
//push ebp ; ��ǰ���̵�ջ���ָ��
//sub esp,N
BOOL CInterpretHandler::InterpretEnter(VMTable* table,char* asmtext,int len)
{
	//push ebp
	sprintf_s(asmtext,len,"%smov edx,[edi+%02x]\n",asmtext,GetRegisterOffset(RT_Ebp));//
	sprintf_s(asmtext,len,"%ssub ebp,4\n",asmtext);//
	sprintf_s(asmtext,len,"%smov dword ptr [ebp],edx\n",asmtext);//push ebp

	//mov ebp,esp
	sprintf_s(asmtext,len,"%smov edx,ebp\n",asmtext);//
	sprintf_s(asmtext,len,"%smov [edi+%02x],edx\n",asmtext,GetRegisterOffset(RT_Esp));//
	
	//sub esp,(L - 1) * 4 ; L > 0�����ⲽ����
	sprintf_s(asmtext,len,"%smov edx,ebp\n",asmtext);//
	sprintf_s(asmtext,len,"%slea ecx,[ecx*4]\n",asmtext);//ecx = ��2������
	sprintf_s(asmtext,len,"%ssub edx,ecx\n",asmtext);//�����ǲ���0����ȥ
	sprintf_s(asmtext,len,"%ssub edx,4\n",asmtext);//�ټ�1��4
	sprintf_s(asmtext,len,"%stest ecx,ecx\n",asmtext);//�����Ƿ�Ϊ0
	sprintf_s(asmtext,len,"%scmovne ebp,edx\n",asmtext);//�����Ϊ0�͸�ֵ��ȥ��Ľ��

	//push ebp
	sprintf_s(asmtext,len,"%smov edx,[edi+%02x]\n",asmtext,GetRegisterOffset(RT_Ebp));//
	sprintf_s(asmtext,len,"%ssub ebp,4\n",asmtext);//
	sprintf_s(asmtext,len,"%smov dword ptr [ebp],edx\n",asmtext);//push ebp

	//sub esp,N
	sprintf_s(asmtext,len,"%ssub ebp,eax\n",asmtext);//eax,��1������
	return TRUE;
}

// ����leave
// mov ebp,esp
// pop ebp
BOOL CInterpretHandler::InterpretLeave(VMTable* table,char* asmtext,int len)
{
	//mov ebp,esp
	sprintf_s(asmtext,len,"%smov edx,ebp\n",asmtext);//
	sprintf_s(asmtext,len,"%smov [edi+%02x],edx\n",asmtext,GetRegisterOffset(RT_Esp));//
	//pop ebp
	sprintf_s(asmtext,len,"%smov eax,[ebp]\n",asmtext);//
	sprintf_s(asmtext,len,"%sadd ebp,4\n",asmtext);//�ͷŶ�ջ
	sprintf_s(asmtext,len,"%smov [edi+%02x],eax\n",asmtext,GetRegisterOffset(RT_Ebp));//
	return TRUE;
}
///////////////////////////////////////////////////
// ����jmp
BOOL CInterpretHandler::InterpretJMP(VMTable* table,char* asmtext,int len)
{
	sprintf_s(asmtext,len,"%smov esi,eax\n",asmtext);//
	sprintf_s(asmtext,len,"%sadd esp,4\n",asmtext);//
	return FALSE;
}
// ����jcxz\jecxz
BOOL CInterpretHandler::InterpretJCXZ(VMTable* table,char* asmtext,int len)
{
	sprintf_s(asmtext,len,"%stest ecx,ecx\n",asmtext);//
	sprintf_s(asmtext,len,"%sCMOVZ esi,eax\n",asmtext);//eaxΪ��1������
	sprintf_s(asmtext,len,"%sadd esp,4\n",asmtext);//
	return FALSE;
}	
// ����jcc
BOOL CInterpretHandler::InterpretJCC(VMTable* table,char* asmtext,int len)
{
	char strPostfix[16] = {0};//������׺
	strcpy_s(strPostfix,16,&table->strInstruction[1]);
	sprintf_s(asmtext,len,"%scmov%s esi,[esp]\n",asmtext,strPostfix);//
	sprintf_s(asmtext,len,"%sadd esp,4\n",asmtext);//
	return FALSE;
}
// ����loope
BOOL CInterpretHandler::InterpretLoope(VMTable* table,char* asmtext,int len)
{
	sprintf_s(asmtext,len,"%spushfd\n",asmtext);//
	sprintf_s(asmtext,len,"%stest ecx,ecx\n",asmtext);//
	sprintf_s(asmtext,len,"%scmovne edx,eax\n",asmtext);//eaxΪ��1������
	sprintf_s(asmtext,len,"%spopfd\n",asmtext);//
	sprintf_s(asmtext,len,"%scmovne edx, esi\n",asmtext);//
	sprintf_s(asmtext,len,"%scmove edx,eax\n",asmtext);//eaxΪ��1������
	sprintf_s(asmtext,len,"%sadd ebp,4\n",asmtext);//�ͷŶ�ջ
	return FALSE;
}


// ���ͷ���
BOOL CInterpretHandler::InterpretRetn(VMTable* table,char* asmtext,int len)
{
	int s_reg[9] = {RT_Esp,RT_EFlag,RT_Ebp,RT_Edi,RT_Esi,RT_Edx,RT_Ecx,RT_Ebx,RT_Eax};

	if( table->OperandNum == 1 )//retn xxx
	{
		sprintf_s(asmtext,len,"%smov edx,ebp\n",asmtext);
		sprintf_s(asmtext,len,"%sadd ebp,eax\n",asmtext);//retn xx,�ȷ���ȥ
		sprintf_s(asmtext,len,"%smov [ebp],edx\n",asmtext);//��PUSH��retn��ַ
		sprintf_s(asmtext,len,"%smov [edi+%02x],ebp\n",asmtext,GetRegisterOffset(RT_Esp));//��ebp(������esp)���浽esp�ĵ�ַ
	}
	// �����Ĵ���
	for(int i = 0; i < 9;i++)
	{
		sprintf_s(asmtext,len,"%spush [edi+%02X]\n",asmtext,GetRegisterOffset(s_reg[i]));
	}
	sprintf_s(asmtext,len,"%spop eax\n",asmtext);
	sprintf_s(asmtext,len,"%spop ebx\n",asmtext);
	sprintf_s(asmtext,len,"%spop ecx\n",asmtext);
	sprintf_s(asmtext,len,"%spop edx\n",asmtext);
	sprintf_s(asmtext,len,"%spop esi\n",asmtext);
	sprintf_s(asmtext,len,"%spop edi\n",asmtext);
	sprintf_s(asmtext,len,"%spop ebp\n",asmtext);
	sprintf_s(asmtext,len,"%spopfd\n",asmtext);
	sprintf_s(asmtext,len,"%spop esp\n",asmtext);

	//����
	sprintf_s(asmtext,len,"%sretn\n",asmtext);
	return FALSE;
}
// �����ӵ���
BOOL CInterpretHandler::InterpretCall(VMTable* table,char* asmtext,int len)
{
	int s_reg[9] = {RT_Esp,RT_EFlag,RT_Ebp,RT_Edi,RT_Esi,RT_Edx,RT_Ecx,RT_Ebx,RT_Eax};
	
	sprintf_s(asmtext,len,"%smov edx,[esi]\n",asmtext);
	sprintf_s(asmtext,len,"%ssub ebp,4\n",asmtext);//4�ֽڿռ�
	sprintf_s(asmtext,len,"%smov [ebp],edx\n",asmtext);//���ص�ַ
	sprintf_s(asmtext,len,"%ssub ebp,4\n",asmtext);//4�ֽڿռ�
	if( table->optype[0] == MEMTYPE )
	{
		sprintf_s(asmtext,len,"%smov eax,dword ptr [eax]\n",asmtext);//�õ��ڴ�����ֵ
	}
	sprintf_s(asmtext,len,"%smov [ebp],eax\n",asmtext);//CALL�ĵ�ַ eax = ��һ��������

	sprintf_s(asmtext,len,"%smov [edi+%02x],ebp\n",asmtext,GetRegisterOffset(RT_Esp));//��ebp(������esp)���浽esp�ĵ�ַ

	// �����Ĵ���
	for(int i = 0; i < 9;i++)
	{
		sprintf_s(asmtext,len,"%spush [edi+%02X]\n",asmtext,GetRegisterOffset(s_reg[i]));
	}
	sprintf_s(asmtext,len,"%spop eax\n",asmtext);
	sprintf_s(asmtext,len,"%spop ebx\n",asmtext);
	sprintf_s(asmtext,len,"%spop ecx\n",asmtext);
	sprintf_s(asmtext,len,"%spop edx\n",asmtext);
	sprintf_s(asmtext,len,"%spop esi\n",asmtext);
	sprintf_s(asmtext,len,"%spop edi\n",asmtext);
	sprintf_s(asmtext,len,"%spop ebp\n",asmtext);
	sprintf_s(asmtext,len,"%spopfd\n",asmtext);
	sprintf_s(asmtext,len,"%spop esp\n",asmtext);

	//����
	sprintf_s(asmtext,len,"%sretn\n",asmtext);

	return FALSE;//���ָ���
}
// ���ͱ�����ջHandler
BOOL CInterpretHandler::InterpretSaveEsp(VMTable* table,char* asmtext,int len)
{
	sprintf_s(asmtext,len,"%smov [edi+%02x],ebp\n",asmtext,GetRegisterOffset(RT_Esp));//��ebp(������esp)���浽esp�ĵ�ַ
	return FALSE;
}
// ���ͻָ���ջHandler
BOOL CInterpretHandler::InterpretRestoreEsp(VMTable* table,char* asmtext,int len)
{
	sprintf_s(asmtext,len,"%smov ebp,[edi+%02x]\n",asmtext,GetRegisterOffset(RT_Esp));//��vmesp��ֵ�ָ���ebp(������esp)
	return FALSE;
}  