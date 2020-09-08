

#include          <Windows.h>
#include           <stdlib.h>


////////////////////////////////////////////////////////////   str.c
char * str_str(const char *z1, const char *z2);

int    chek_LF(char *psz);

int   FRead_LF(char *psz);  

int find_pos(char *sz, int size);  
////////////////////////////////////////////////////////////

DWORD           dwFileSize, 
                    dwRead;  
HANDLE               hFile;
OVERLAPPED             ovl;



char       szWords[11][51];

int         nWords   =   4;

int                   *arr;


static int     row    =  1,
               column =  1,                
          
		       nWrd   = 14,	           // ���-�� ����, ������� ����� �������� � �����, �� ������� ������ ������ arr
               nBuf   =  0,   
               cnt    =  0,                                                  // ����� ���������� �����, ������� � 1
	           nCn    =  0;                                                  // ���-�� ���� ����� ���������� ������

       int        File_row, 
                    oldOfs,
		  EndOfFile =    0, 
		  File1_buf = 2047,	           
                 File_Ofst,
                        cp;              //  - ��� ������� �������� ������������ ������, ������������ �� ����� �����
             			 		



//  �������� ����� ��� ���������� � ��������� ������
////////////////////////////////////////////////////////////////////////////////////                  constructor
void init_analis()                                                                // 
{
	
	 nBuf   = (nWrd+1)*16;                                             //  16 = int * 4 ������� ��� ������� �����
	
	
	
	 arr = (UINT*)malloc(nBuf);	                                         // 100 int-���������� (25 - 1 = 24 �����)
	
	 arr[0] = 0;                                        //  ��� ����� ��������� ������, ���� �� ������� ����������  
	                                                        //printf("\n init nBuf = %d, arr = %d  \n", nBuf, arr);	
	 arr[1] = 0;
	 arr[2] = 0;	 
	 arr[3] = 0;
	 arr[4] = 0;
}







////////////////////////////////////////////////////////////////////////////////////
int Init(int p)                                                                   //
{
	
	if(p == -1) { CloseHandle(hFile); return 0; }                         //  ������� ����, ����� ����������� ������
	
	
	
	hFile = CreateFile
	(
	     szWords[0],
	     GENERIC_READ,
	     FILE_SHARE_READ,
	     NULL,
	     OPEN_EXISTING,
	     FILE_ATTRIBUTE_NORMAL,// | FILE_FLAG_OVERLAPPED, 
	     NULL
	); 	
	
	if(hFile == INVALID_HANDLE_VALUE) return 0;  //  printf("error Init()"); 
	
	arr[1] = GetFileSize(hFile, 0);       // printf("dwFileSize =  %d,  File1_buf = %d\n", dwFileSize,  File1_buf); 
	                                          // printf("i/o, row");
	

return arr[1];                                 ///dwFileSize;	
}




int   DDD(int N, const char *p);

//  ��������� �������. ���������� �� ���. 
///////////////////////////////////////////////////////////////////////////////////char *pszX[99]
int* wl_FileAnalysis(int N, const char *p) 
{
	
	init_analis();                                          //  !!! ������� ��������� ������ ��� arr[]
    
	arr[2] = DDD(N, p);

//  arr[2] = 1, ���� ������� ������         "Preceding characters:" ������������� �������	    
//  arr[2] = 3, ���� ������� ������            "Ending characters:"   ����������� �������	 
//  arr[2] = 4, ���� ������� ������������ � "Preceding characters:" & "Ending characters:" 	 
	
	int size  = Init(1); 
	if( size == 0)  return 0;    
    int pos;
	char       sz[4098];	 
				
	while(EndOfFile != 3)
	{
												
		pos = FRead_LF(sz); 
						
	    if(pos < 3) continue; 
						
		sz[pos]   = 0;      // ? ? ?
						
	    find_pos(sz, pos);	
	}
								
return arr;	 
}




//////////////////////////////////////////////////////////////////
int FRead(char *psz, int n)                                     // 
{


     ovl.Offset = File_Ofst; 

	 int b = ReadFile( hFile,            // ���������� �����
			             psz,            // ����� ������, ���� ������ ������
			               n,            // ���������� �������� ������
			         &dwRead,            // ���������� ����������� ������
			            &ovl             // ������ �����������
			         );	
			      
	   ovl.Offset += n;		      
			      
return b;	
}




                                                             //int  oldOfs = 0;
int mem = 1;


//  �������� ������ ������� Fread_LF()
//  ���������� ����� (psz), ����� ����������� � �����.
//  ��� ��������� ����� (�� ����� ������� ��������� � �����) � ��� ������, ���� � ������ �������� ��� ������.
//////////////////////////////////////////////////////////////////
int Stage_2(char *psz, int i)                                   // 
{
	
	int b = 0,
	    x = 0,                                //  ��������� ��������, ���� ������ LF  ('\n' - ������ �������� ������)
	    c = cp + i;
	    
	
	
    while(psz[c]) 
	{
								
		psz[b++] = psz[c]; 
		
		x  ++;	
		cp ++;	
			
		if(psz[c++] == '\n') 
		{  
		   psz[b] = 0;                                                                        //printf("%4d, ", c-1);
		   
		   File_row   ++  ;
		   
		   oldOfs = File_Ofst;  File_Ofst += x;  
				   
		   return x;		   		  	   
		}        							   			
	}	
	//.................................................
	if(EndOfFile == 1)         //  ��������� ������ ����� �� ����������� ��������� ������ (����� ������ ����� ������)
	{  EndOfFile  = 2;
	
	   psz[b++] = psz[c]; 
		
	   x  ++;		   
	   
	   psz[b-2] = 0;                                                                             //printf("%4d, ", c);
		   
	   File_row   ++  ;
		   
	   oldOfs = File_Ofst; File_Ofst += x;   
				   	   	   
	   return x+1;
	}    
	
	return 0;		
}

//////////////////////////////////////////////////////////////////   printf(" ! ");  printf("%d, ", b);
int FRead_LF(char *psz)                                         // 
{

	 static int i = 0;
	        int b = 0; 
	        
  
     if(i) 
	 {        
	       b = Stage_2(psz,  i);                                //    ����������� ������ �� ������ (���� ��������)	 
	    if(b)  return b; 
	    else   if(EndOfFile) { EndOfFile = 3;   return b; }  /// arr[2] = cnt;
     }
     
     //  ------------ STAGE 1 -------------                     //    ���� �� ����� � ��-������ (����� char *psz)
     
     cp = 0;
     i  = 0;	
     
     
	 ovl.Offset =  File_Ofst;
	 
	 int  bv = ReadFile( hFile,                                 //    ���������� �����
			             psz,                                   //    ����� ������, ���� ������ ������
			       File1_buf,                                   //    ���������� �������� ������
			         &dwRead,                                   //    ���������� ����������� ������
			            &ovl                                    //    ������ �����������
			         );	
		           
				     psz[File1_buf-1] = 0;	         
			         
     		         			
			         

     mem ++;                                                             // printf("\n%3d, %3d: ", mem++, File_row+1); 
	 
	 i = chek_LF(psz); 
	 	
	 i ++;	      	                                                                          // printf("%4d, ", i++);	 
	 
	 /////////////////////////////////
	 if(dwRead < File1_buf) {
	 
	                                                             //printf("\n End of File! dwRead = %d, -  ", dwRead);
	    psz[dwRead+1] = 0;
	    EndOfFile = 1;
     }	 
	 else psz[File1_buf] = '\0';
			         
	 /////////////////////////////////		      
	 oldOfs = File_Ofst; File_Ofst += i;	
	 File_row  ++  ;	  	 	  
			      
return i-1;	
}













////////////////////////////////////////////////////////////////////////////////////
int find_pos(char *sz, int size)                                                  //  
{

	int     k,
	      pos;

	char *psz;
	
	for(int i = 1; i <= 4; i ++)
	{
				
		psz = (char*)sz;   // + cp
		
L_01:	psz = str_str(psz, szWords[i]);
	   	
	   	if(psz == 0) continue;
	   	
	   	cnt ++; nCn ++;
	   	
	   	if(nCn > nWrd)        //  ����� ����� � ������ ����������� (������� ������� ����� ����������� ���� � �����)  
	   	{
	   		
	   	   nCn   =       1;	
	   	   nBuf += nWrd*16;
	   	   arr   = (UINT*)realloc(arr, nBuf);
	   	   
	   	   //printf("\n ----reSize nBuf = %d, cnt = %d, arr = %d  \n", nBuf, cnt, arr);
	    }
	   	
	   	arr[0] = cnt;
	   	
	   	k = cnt * 4;
	   	
	   	pos = psz - sz + 1;
	   	
	   	arr[k  ] = i;                                     // ����� �����  (������ � ������� const char *szWords[])
	   	arr[k+1] = File_row;                              // ����� ������
	   	arr[k+2] = pos;		                              // ����� ������� � ������	  
		arr[k+3] = oldOfs + pos;                          // ���������� ����� ������� �� ������ ����� 
		
		if(psz++ < sz + size - 1) goto L_01; 
	}
	
return 0;	
}




























