/*-----------------------------------------------------------------------
第20章  虚拟机的设计
《加密与解密（第四版）》
(c)  看雪学院 www.kanxue.com 2000-2018
-----------------------------------------------------------------------*/

#include "stdafx.h"
#include "CCodeILFactory.h"
#include ".\pestructure.h"

int main()
{

	CPEStructure pestruct;
	CCodeILFactory codefactory;
	//CLink CodeList;
	list<CodeNode*> CodeList;
	list<CodeNode*> CodeList1;
	pestruct.OpenFileName("G:\\项目\\VMPacker\\ConvertCrackMe\\Release\\ConvertCrackMe.exe");
	pestruct.LoadMap("G:\\项目\\VMPacker\\ConvertCrackMe\\Release\\ConvertCrackMe.map");
	getchar();
	codefactory.Init(0x400000+pestruct.GetNewSection());//创建虚拟内存段

	//MapStructrue* stu = pestruct.GetMap("CmpThread(void *)");

	MapStructrue* stu = pestruct.GetMap("CrackMe(struct HWND__ *)");


	if( !stu )
		return 0;
	char * Base_Addr = pestruct.image_section[stu->Segment-1] + stu->Offset;//得到基地址


	codefactory.DisasmFunction(&CodeList,Base_Addr,stu->VirtualAddress);
	list<CodeNode*>::iterator itr;

	//for( itr = CodeList.begin(); itr != CodeList.end(); itr++ )
	//{
	//	CodeNode* code = *itr;
	//	if( code )
	//	{
	//		char str[255] = "";
	//		sprintf_s(str,255,"vcode:%s\n",code->disasm.vm_name);
	//		OutputDebugStringA(str);
	//		printf("%-24s  %-24s   (MASM)\n",code->disasm.dump,code->disasm.result);
	//	}
	//}

	itr = CodeList.begin();
	CodeNode* code = *itr;
	itr = CodeList.end();
	itr--;
	CodeNode* endcode = *itr;
	int asmlen = endcode->disasm.ip+endcode->disasm.codelen - code->disasm.ip;
	codefactory.VMFactory.CompileEnterStubCode(Base_Addr,code->disasm.ip,asmlen);
	pestruct.UpdateHeadersSections(FALSE);

	char errtext[255] = {0};
	codefactory.BuildCode(Base_Addr,&CodeList,errtext);

	int len = codefactory.m_JumpTable.m_addrlen + codefactory.m_CodeEngine.m_addrlen +
				codefactory.m_EnterStub.m_addrlen + codefactory.m_VMEnterStubCode.m_addrlen + 
				codefactory.m_VMCode.m_addrlen;
	char *newdata = new char[len];
	char *p = newdata;
	memcpy( p,codefactory.m_JumpTable.m_BaseAddr,codefactory.m_JumpTable.m_addrlen );
	p += codefactory.m_JumpTable.m_addrlen;
	memcpy( p,codefactory.m_CodeEngine.m_BaseAddr,codefactory.m_CodeEngine.m_addrlen );
	p += codefactory.m_CodeEngine.m_addrlen;
	memcpy( p,codefactory.m_EnterStub.m_BaseAddr,codefactory.m_EnterStub.m_addrlen );
	p += codefactory.m_EnterStub.m_addrlen;
	memcpy( p,codefactory.m_VMEnterStubCode.m_BaseAddr,codefactory.m_VMEnterStubCode.m_addrlen );
	p += codefactory.m_VMEnterStubCode.m_addrlen;
	memcpy( p,codefactory.m_VMCode.m_BaseAddr,codefactory.m_VMCode.m_addrlen );
	p += codefactory.m_VMCode.m_addrlen;

	pestruct.AddSection(newdata,len,".bug");
	pestruct.UpdateHeaders(FALSE);
	pestruct.UpdateHeadersSections(TRUE);
	pestruct.UpdateHeadersSections(FALSE);
	pestruct.MakePE("G:\\项目\\VMPacker\\ConvertCrackMe\\Release\\ConvertCrackMe.vm.exe",len);

	//#include "asm\disasm.h"
	//ulong l = 0;
	//t_disasm da;
	//char errtext[TEXTLEN] = {0};

	//memset(&da,0,sizeof(t_disasm));
	//// Demonstration of Disassembler.
	//printf("Disassembler:\n");
	//ideal=0; lowercase=1; putdefseg=0;
	//l=Disasm("\xCC",
	//	MAXCMDSIZE,0x400000,&da,DISASM_CODE);
	//printf("%3i  %-24s  %-24s   (MASM)\n",l,da.dump,da.result);
	//getchar();

	return 0;
}