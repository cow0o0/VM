#include "stdafx.h"
#include "asm/disasm.h"
#include "vmdisasm.h"

// Ϊһ�����������������.
void RandListIdx(int* idx,int cout)
{
	BOOL* IsUsed = new BOOL[cout];
	memset(IsUsed,FALSE,sizeof(BOOL)*cout);
	srand((unsigned)time(NULL));
	while(TRUE)
	{
		BOOL NotComplete = FALSE;
		for(int i = 0; i < cout; i++ )
		{
			if( !IsUsed[i] )
			{
				NotComplete = TRUE;
				break;
			}
		}
		if( !NotComplete )//ȫ�����
			return;
		int nrand = rand() % cout;
		//if( nrand == 0)//6.9.����Ϊ0,0����һ��NULL�Ŀռ�
		//	break;
		BOOL NoSame = FALSE;//Ĭ��Ϊû����ͬ��
		for( int i = 0; i < cout; i++ )
		{
			if( IsUsed[i] && nrand == idx[i] )//��������˲������ɵ������
			{
				NoSame = TRUE;
				break;
			}
		}
		if( NoSame )//�������ͬ��
			continue;
		for( int i = 0; i < cout; i++ )
		{
			if( !IsUsed[i]  )//���û�з���
			{
				idx[i] = nrand;
				IsUsed[i] = TRUE;//��Ϊ�ѷ���
				break;
			}
		}
	}
	delete[] IsUsed;IsUsed = NULL;
}
