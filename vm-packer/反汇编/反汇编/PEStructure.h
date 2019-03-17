#pragma once
#include "comm.h"

#include <math.h>

#include <vector>
using namespace std;

#define MAX_SECTION_NUM 20
const DWORD PackerCode_Size = 0;//�Ǵ�����󳤶�
const DWORD ALIGN_CORRECTION = 0;//�ļ�����

class CPEStructure
{
public:
	CPEStructure(void);
	~CPEStructure(void);
private:
	DWORD   ReservedHeaderSize;//����ͷ����
	DWORD   ReservedHeaderRO;  //DOSͷ����

	BOOL    SectionAssigned;//�Ƿ��ѷ���
	HANDLE  hFile;//PE�ļ����
	DWORD   dwFsize;//PE�ļ�����
	DWORD   dwOutPutSize;//PE�ļ��������
	char    *pMem;//PE�ļ�������
private:
	char    m_FileName[256];//�ļ���
	char    m_MapFileName[256];//map�ļ���
public://ӳ���ļ�
	vector<MapStructrue*> MapVector;
	void LoadMap(char* pmapfilename);//�������map�ļ�
	BOOL GetFileAddr(char* StrAddress,int* Segment,int* FileOffset);//�ָ�õ��κ�ƫ��
public:
	MapStructrue* GetMap(char* funcname);
public:
	DWORD					dwRO_first_section;
	IMAGE_DOS_HEADER		image_dos_header;
	char					*reservedheader;
	IMAGE_NT_HEADERS		image_nt_headers;
	IMAGE_SECTION_HEADER	image_section_header[MAX_SECTION_NUM];
	char					*image_section[MAX_SECTION_NUM];
	BOOL OpenFileName(char* FileName);
	void UpdateHeaders(BOOL bSaveAndValidate);							   //����PEͷ
	void UpdateHeadersSections(BOOL bSaveAndValidate);					   //����PE��
	DWORD PEAlign(DWORD dwTarNum,DWORD dwAlignTo);						   //PE�ڶ���
	PIMAGE_SECTION_HEADER AddSection(char* Base,int len,char* SectionName);//��ӽ�
	DWORD GetNewSection();												   //����½ڵ�VirtualAddress��ַ
	void Init();
	void Free();
	void FreeMapVector();
	void MakePE(char* filename,int len);//����һ��PE
};
