

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
          
		       nWrd   = 14,	           // кол-во слов, которые можно добавить в буфер, не изменяя размер буфера arr
               nBuf   =  0,   
               cnt    =  0,                                                  // номер найденного слова, ничиная с 1
	           nCn    =  0;                                                  // кол-во слов после увеличения буфера

       int        File_row, 
                    oldOfs,
		  EndOfFile =    0, 
		  File1_buf = 2047,	           
                 File_Ofst,
                        cp;              //  - это счётчик символов относительно начала, прочитанного из файла блока
             			 		



//  Выделяет место для информации о найденных словах
////////////////////////////////////////////////////////////////////////////////////                  constructor
void init_analis()                                                                // 
{
	
	 nBuf   = (nWrd+1)*16;                                             //  16 = int * 4 паратра для каждого слова
	
	
	
	 arr = (UINT*)malloc(nBuf);	                                         // 100 int-переменных (25 - 1 = 24 слова)
	
	 arr[0] = 0;                                        //  Без этого возникнет ошибка, если не найдены совпадения  
	                                                        //printf("\n init nBuf = %d, arr = %d  \n", nBuf, arr);	
	 arr[1] = 0;
	 arr[2] = 0;	 
	 arr[3] = 0;
	 arr[4] = 0;
}







////////////////////////////////////////////////////////////////////////////////////
int Init(int p)                                                                   //
{
	
	if(p == -1) { CloseHandle(hFile); return 0; }                         //  закрыть файл, перед завершением работы
	
	
	
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

//  Стартовая функция. Вызывается из вне. 
///////////////////////////////////////////////////////////////////////////////////char *pszX[99]
int* wl_FileAnalysis(int N, const char *p) 
{
	
	init_analis();                                          //  !!! Вначале выделение памяти для arr[]
    
	arr[2] = DDD(N, p);

//  arr[2] = 1, если найдены только         "Preceding characters:" предшестуюшие символы	    
//  arr[2] = 3, если найдены только            "Ending characters:"   завершаюшие символы	 
//  arr[2] = 4, если найдены одновременно и "Preceding characters:" & "Ending characters:" 	 
	
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

	 int b = ReadFile( hFile,            // дескриптор файла
			             psz,            // адрес буфера, куда читаем данные
			               n,            // количество читаемых байтов
			         &dwRead,            // количество прочитанных байтов
			            &ovl             // чтение асинхронное
			         );	
			      
	   ovl.Offset += n;		      
			      
return b;	
}




                                                             //int  oldOfs = 0;
int mem = 1;


//  Является частью функции Fread_LF()
//  Дочитывает буфер (psz), ранее прочитанный с диска.
//  Это сэкономит время (не будет лишнего обращения к диску) в том случае, если в буфере остались ещё строки.
//////////////////////////////////////////////////////////////////
int Stage_2(char *psz, int i)                                   // 
{
	
	int b = 0,
	    x = 0,                                //  Очередное смещение, если найден LF  ('\n' - символ перевода строки)
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
	if(EndOfFile == 1)         //  Последняя строка может не завершаться переводом строки (здесь именно такой случай)
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
	       b = Stage_2(psz,  i);                                //    Дочитывание данных из буфера (если остались)	 
	    if(b)  return b; 
	    else   if(EndOfFile) { EndOfFile = 3;   return b; }  /// arr[2] = cnt;
     }
     
     //  ------------ STAGE 1 -------------                     //    Берём из файла в Си-строку (буфер char *psz)
     
     cp = 0;
     i  = 0;	
     
     
	 ovl.Offset =  File_Ofst;
	 
	 int  bv = ReadFile( hFile,                                 //    дескриптор файла
			             psz,                                   //    адрес буфера, куда читаем данные
			       File1_buf,                                   //    количество читаемых байтов
			         &dwRead,                                   //    количество прочитанных байтов
			            &ovl                                    //    чтение асинхронное
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
	   	
	   	if(nCn > nWrd)        //  Ессли место в буфере закончилось (найдено слишком много совпадающих слов в файле)  
	   	{
	   		
	   	   nCn   =       1;	
	   	   nBuf += nWrd*16;
	   	   arr   = (UINT*)realloc(arr, nBuf);
	   	   
	   	   //printf("\n ----reSize nBuf = %d, cnt = %d, arr = %d  \n", nBuf, cnt, arr);
	    }
	   	
	   	arr[0] = cnt;
	   	
	   	k = cnt * 4;
	   	
	   	pos = psz - sz + 1;
	   	
	   	arr[k  ] = i;                                     // номер слова  (Индекс в массиве const char *szWords[])
	   	arr[k+1] = File_row;                              // номер строки
	   	arr[k+2] = pos;		                              // номер позиции в строке	  
		arr[k+3] = oldOfs + pos;                          // Абсолютный номер позиции от начала файла 
		
		if(psz++ < sz + size - 1) goto L_01; 
	}
	
return 0;	
}




























