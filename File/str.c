

//   Предстоящий символ не проверяется, если слово находится в самом начале строки
//  ПОСЛЕстоящий символ не проверяется, если слово находится в самом КОНЦЕ  строки

//char   Symb1[111] =  " (=";
//char   Symb1[111] = ". ,)"; 
//char   Symb2[111] = ". ,)"; 


//#include           <string.h>

static int           Flag = 0; //  1 - Использование разделительных символов ( 0 - без учёта разделителей) 

static char   Symb1[111] = "", 
              Symb2[111] = ""; 

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
//
// Аналог strstr() 			 
////////////////////////////////////////////////////
char * str_str(const char *z1, const char *z2)    //
{
	
	int i = 0,
	    k = 1,
	    p = 0,
	    q = 0;
	
	while(z1[i])
	{
		
		if(z1[i] == z2[0]) 
		{
		   
		   k =   1; 	                                               //  счётчик символов для слова, которое ищем	   
		   p = i+1;                      // счётчик в основной строке относительно позиции, где найденно совпадение
		   
		   while(z2[k])
		   {
				
			    if(z1[p] != z2[k]) goto L_02; 	
			    
			    k++; p++;		
		   } ////////////////////////////////	                       Проверки на предстоящий и завершающий символы  			       		  
		   
		   if(Flag) return (char*)(z1+i);  
		   
		   if(i < 1) goto L_01;		                                        q = 0;
		   		 
			  if(Symb1[0]  == 0)                     goto L_01; 	  
		   while(Symb1[q]) if(z1[i-1] == Symb1[q++]) goto L_01;  		   
		                                             goto L_02;  
		   		   
L_01:	 	                if(z1[p] == 13) 	    return (char*)(z1+i);                         //  Перевод строки
                            if(z1[p] ==  0) 	    return (char*)(z1+i);   q = 0;                    // Конец файла
		      if(Symb2[0] == 0)                     return (char*)(z1+i);  												    
		   while(Symb2[q])  if(z1[p] == Symb2[q++]) return (char*)(z1+i);                     //  Завершающий символ
		 //  }
		   ////////////////////////////////// 		   	   	   		   
	    }
	    
L_02:	i++;
    }
	
return 0;	
}
			    



//  Ищет символ перевода строки
////////////////////////////////////////////////////
int chek_LF(char *psz)                            //
{


    int i = 0;
    
    while(psz[i])
	{
	
	   if(psz[i] == '\n') return i;
	   
	   i++;
    }

return -1;
}






extern char     szWords[11][51];

//  Передать кол-во слов
//  Не считая путь к файлу, который занимает строку с индексом НОЛЬ.
//////////////////////////////////////////////
int DDD(int N, const char *p)
{
	
	char word[111];
	
	int i = 0, u = 0,
	    n = 0,
	    k = 0,
	  res = 0;
	  
	Flag = 1;  

    for(int A = 0; A <= N; A++)
    {
		
		k = 0;                                           //  Индекс символов слова 
		 
		while(szWords[A][k++] = p[i++]);                 // Копируем символы, пока не встретим НОЛЬ    
		     
	    while(p[i++] == 0); i --; 
		
		n ++ ;
    }
    
    k = 0;
    
    while(word[k++] = p[i++]); 
    
	if(str_str(word, "Preceding characters:"))  
	{
		
	   res += 1;  

	   while(Symb1[u] = word[21+u]) u ++; 	               //strcpy(Symb1, &word[21]); 
	} 
	  
    else {  if(str_str(word, "Ending characters:")) 
			{ 
			   res += 3;  
	
			   while(Symb2[u] = word[18+u]) u ++; 		   //strcpy(Symb2, &word[18]); 
			}  
		    
		    Flag = 0; return res;
	}
	
	while(p[i++] == 0); i --;
    
	k = 0;
    
    while(word[k++] = p[i++]); 	
    
	if(str_str(word, "Ending characters:")) 
	{ 
		
	   res += 3; u = 0;

	   while(Symb2[u] = word[18+u]) u ++;    	                                          // strcpy(Symb2, &word[18]); 
	}     
    
Flag = 0; return res;
}
	
	






















