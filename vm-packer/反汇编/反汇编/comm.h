
//#include "..\ByteCode\ByteCode\CodeAnalyse.h"

#define VMPACKERTITLE             "VMPacker"

//MessageBox
void MsgBox( char* content, UINT nType = MB_OK );

//ȥ�����з��Ϳո�
//����ֵ,��û������ʱ����NULL;
BOOL Trim( char* pstr,char* str );

//�ַ���ת16������
DWORD StringToHex(char* strSource);
void OutPutStr(char *str, ...);

struct MapStructrue
{
	WORD  Segment;                   //PE��
	DWORD Offset;                    //ƫ��
	char  SymbleName[512];           //��������
	DWORD VirtualAddress;            //�����ַ
	char  LibObject[512];            //�����ļ�����
	//CLink Codelink;					 //������
	MapStructrue()
	{
		Segment = 0;
		Offset = 0;
		VirtualAddress = 0;
		memset(SymbleName,0,512);
		memset(LibObject,0,512);
		//Codelink.RemoveAll();
	}
};