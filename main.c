


#include         <stdio.h>
#include    "File\\File.h"


int   nW = 4;                                   //  Кол-во слов для поиска в файле
//  Двумерный массив
 char szW[16][77] = {"resource\\Test_1.txt",    //  Путь к файлу и имя файла.
                                     "SONY",    //  1-е слово
                                   "Nikita",    //  2-е слово
                                 "Benjamin",    //  3-е слово
                                "Coca-Cola",    //  4-е слово
			       "Preceding characters: ",    //  Символы, которые могут предшествовать слову					
			          "Ending characters: )",   //  Символу, которые могут ЗАВЕРШАТЬ      слово
							              };

/*
//   В таком формате (const char *szW[]) параметры тоже можно передать.
//   Массив указателей на константные строки
const char *szW[] = {  "resource\\Test.txt",    //  Путь к файлу и имя файла.
                           "Ctrl+Shift+Tab",    //  1-е слово
                       "Windows 2k/XP/2003",    //  2-е слово
                         "AKD_GETTEXTRANGE",    //  3-е слово
                            "Alt+Backspace",    //  4-е слово
			     "Preceding characters: -(",    //  Символы, которые могут предшествовать слову				
				   "Ending characters: ),.",    //  Символу, которые могут ЗАВЕРШАТЬ      слово
							              };
*/  

////////////////////////////////////////////////////
int main()                                        // 
{
	
	int *pArr  = wl_FileAnalysis(nW, szW[0]);
	
	if(pArr == 0) { printf("File \"%s\" not found.\n", szWords[0]);      return 0; }
	
	
	printf("\n Quantity = %d   ",   pArr[0]);	
	printf("\nFile size = %d \n",   pArr[1]);
	
	switch(pArr[2])
	{
		
	     case  1: printf("pArr[2]   = 1, Found \"Preceding characters:\""); break;	              	                 
	     case  3: printf("pArr[2]   = 3, Found \"Ending    characters:\""); break;	              	                 
	     case  4: printf("pArr[2]   = 4, Found \"Preceding characters:\" & \"Ending characters:\"");
	              break;	  		
	}
	 	
		
	    int k;
	for(int o = 1; o <= nW; o ++) 
	{		
	
	    printf("\n\n%s : ", szWords[o]); 
	
		for(int i = 1; i <= pArr[0]; i++)
		{
			
			k = i * 4; 
			
		    if(pArr[k] == o) printf("%d, %d, (%d); ", pArr[k+1], pArr[k+2], pArr[k+3]);		
		}
    }
	
	getchar();
	
return 0;	
}















               






















//			                                                                   (   )       
//													                          (    )
//													                           (    )
//													                          (    )
//			   										                            )  )
//													                           (  (                  /\
//													                            (_)                 /  \  /\
//													                    ________[_]________      /\/    \/  \
//													           /\      /\        ______    \    /   /\/\  /\/\
//													          /  \    //_\       \    /\    \  /\/\/    \/    \
//													   /\    / /\/\  //___\       \__/  \    \/
//													  /  \  /\/    \//_____\       \ |[]|     \
//													 /\/\/\/       //_______\       \|__|      \
//													/      \      /XXXXXXXXXX\                  \
//													        \    /_I_II  I__I_\__________________\
//													               I_I|  I__I_____[]_|_[]_____I
//													               I_II  I__I_____[]_|_[]_____I
//													               I II__I  I     WinLego     I
//					                                             E-mail:    dllbridge@gmail.com










