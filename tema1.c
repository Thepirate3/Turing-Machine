#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"tranzitie.h"



//Functie ce sare un numar dat de linii din fisier
FILE *sari(FILE *f,int nr_linii)
{
	char line[256];
	size_t len = 0;
	ssize_t read;
	int i=0;
	char ok;
	while( i != nr_linii)
	{
		fscanf(f,"%c",&ok);
		while(ok != '\n' )
		{
		  fscanf(f,"%c",&ok);
		}	
		i++;	
	 }
	return f;
}

// Functie ce verifica daca starea curenta e stare finala
int verifica_stare(char **c,int lungime,char curenta[100])
{
	int b=0;
	int mid;
	int top = lungime -1;
	
	while(b<= top)
	 {
		mid = (b+top)/2;
		
		if( strcmp(c[mid],curenta) == 0) return 0;
		if( strcmp(c[mid],curenta) > 0 ) top= mid-1;
		if(strcmp(c[mid],curenta) < 0 ) b = mid+1;
	}
	return 1;
	
}

// Functie ce compara doua elemente de tip tranzitie
int cmp(const void *a,const void *b)
{
	Tranzitie *a1 = (Tranzitie *)a;
	Tranzitie *b1 = (Tranzitie *)b;
	
	if(strcmp(a1->stare_cur,b1->stare_cur) < 0)
	 {
		return  -1;
			
	}
	 if(strcmp(a1->stare_cur,b1->stare_cur) > 0)
	 {
		return 1 ;
			
	}
	if(strcmp(a1->stare_cur,b1->stare_cur) == 0)
	 {
		if(a1->cuv1 > b1->cuv1)
		 {
			return 1;
		}
		else 
		{
			if(a1->cuv1 == b1->cuv1)
			 {
				if(a1->cuv2 > b1->cuv2) return 1;
				else return -1;
			 }
		return -1;
		}
	}

}

// Functie ce cauta tranzitia curenta
int cautare_stare(Tranzitie *t,int lungime,char stare_cur[],char cuv1,char cuv2)
{
	int baza = 0;
	int mid;
	int capat = lungime -1;
	while(baza <= capat)
	 {
		mid = (baza+capat)/2;
		if( strcmp(t[mid].stare_cur,stare_cur)== 0 &&
			t[mid].cuv1 == cuv1 && t[mid].cuv2 == cuv2)
		return mid;
		
		if( strcmp(t[mid].stare_cur,stare_cur) == 0 )
		{
			if(t[mid].cuv1 > cuv1) capat = mid -1;
			
			if(t[mid].cuv1 < cuv1) baza = mid+1;
			
			if(t[mid].cuv1 == cuv1)
			{
				if(t[mid].cuv2 > cuv2) capat = mid -1;
				if(t[mid].cuv2 < cuv2) baza = mid+1;
			}

		}
		if( strcmp(t[mid].stare_cur,stare_cur) > 0 )
			capat = mid-1;
		if( strcmp(t[mid].stare_cur,stare_cur) < 0 )
			baza = mid+1;
		
	}
	return -1;
}

// Functia principala
void functie(FILE *f)
{
	char stare_cur[100];
	char stare_finala[100];
	char caracter_banda1;
	char caracter_banda2;
	int cap_banda1;
	int cap_banda2;
	int N;
	int M;
	int P;
	char banda1[10000];
	char banda2[10000];
	int i=1;	
	FILE *f_out=fopen("task1.out","w");
	
	fscanf(f,"%d ",&N);//citesc N
	
	f=sari(f,1);// sar linia starilor
	fscanf(f,"%d",&M);//citesc M

	f=sari(f,1);// sar linia starilor finale
	f=sari(f,1);
	fscanf(f,"%s",stare_cur);//citesc starea initiala
	fscanf(f,"%d",&P); // citesc numarul tranzitiilor
	rewind(f);// ma repozitionez la inceputul fisierului

	f=sari(f,6+P);//ma pozitionez pe penultima linie pentru a citi prima banda
	
	fscanf(f,"%s",banda1); //citesc prima banda
	fscanf(f,"%s",banda2); //citesc a doua banda
	
	rewind(f);// readuc pointerul la inceputl functiei
	
	cap_banda1=1;
	cap_banda2=1;	

	//adaug '#' dupa caracterele de pe fiecare banda
	while(1)
	{
		if(banda1[i] == '#' )
		 {
			int k=i;
			for(k=i+1;k<1000;k++)
			 {	
				banda1[k]='#';
			 }
			break;
		 }
		i++;
	}
	i=1;
	while(1)
	{
		if(banda2[i] == '#' )
		 {
			int k=i;
			for(k=i+1;k<1000;k++)
			 {	
				banda2[k]='#';
			 }
			break;
		 }
		i++;
	}

	rewind(f);// repozitionare la inceputl fisierului
	f=sari(f,6);
	
	Tranzitie *t = malloc(P*sizeof(Tranzitie));	

	// citirea tuturor tranziitilor in vectorul de tranzitii 't'
	for(i=0;i<P;i++)
	 {
	 	fscanf(f,"%s",t[i].stare_cur);
			
						
			fscanf(f,"%c",&t[i].cuv1);
			fscanf(f,"%c",&t[i].cuv1);
			fscanf(f,"%c",&t[i].cuv2);
			fscanf(f,"%c",&t[i].cuv2);
			
		fscanf(f,"%s",t[i].stare_urm);
		fscanf(f,"%c",&t[i].cuv1_next);
		fscanf(f,"%c",&t[i].cuv1_next);
		fscanf(f,"%c",&t[i].deplasare1);
		fscanf(f,"%c",&t[i].deplasare1);
		fscanf(f,"%c",&t[i].cuv2_next);
		fscanf(f,"%c",&t[i].cuv2_next);				
		fscanf(f,"%c",&t[i].deplasare2);
		fscanf(f,"%c",&t[i].deplasare2);
	
	 }
	
	//sortarea vectorului tranzitiilor
	qsort(t,P,sizeof(Tranzitie),cmp);
	
	int poz=0;
	rewind(f);
	
	// alocare vector stari finale
	char **stari_finale= malloc(M*sizeof(char*));
	for(i=0;i<M;i++)
	{
		stari_finale[i]= malloc(100);
	}

	f=sari(f,3);
	
	//citire  stari finale
	for(i=0;i<M;i++)
	{
		fscanf(f,"%s",stari_finale[i]);
	}
	i=0;
	while( verifica_stare(stari_finale,M,stare_cur) != 0 )// daca nu am ajuns in stare finala
	{
	   				
	   poz = cautare_stare(t,P,stare_cur,banda1[cap_banda1],banda2[cap_banda2]);//caut pozitia curent din vectorul de tanzitii
				
			if( poz != -1)// daca am gasit tranzitia corespunzatoare
			 {
				strcpy(stare_cur,t[poz].stare_urm); // actualizez starea curenta
				banda1[cap_banda1] = t[poz].cuv1_next;	// actualizez banda 1
				banda2[cap_banda2] = t[poz].cuv2_next;	// actualizez banda 2
				
				if( t[poz].deplasare1 == 'R') cap_banda1++; // actualizez capul benzii 1
				if( t[poz].deplasare1 == 'L') cap_banda1--;
				if( t[poz].deplasare2 == 'R') cap_banda2++; // actualizez capul benzii 2
				if( t[poz].deplasare2 == 'L') cap_banda2--;
			 }
			
			// altfel	
			else {
				char error[100]="The machine has blocked!";
				fprintf(f_out,"%s\n",error);
				return;
			     }
		
		
	}
	
	
	free(t);// eliberez vectorul de tranzitii
	fprintf(f_out,"%s\n%s\n",banda1,banda2); // printez cele doua benzi
	fclose(f_out);
	
}



int main()
{
	FILE *f= fopen("task1.in","r+");
	functie(f);
	fclose(f);
	return 0;
}
