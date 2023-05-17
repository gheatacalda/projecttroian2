#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
struct utilizator
	{
		char nume[30], prenume[30];
		int an_nastere;
	};
int varstacalcul(int an_nastere)
{
	int an_curent=2023;
	int varsta=an_curent-an_nastere;
	return varsta;
}
int acces(int varsta)
{
	if(varsta<14)
	{
		printf("Aveti o varsta nepotrivita pentru recomandarile de muzica!");
		return 1;
	}
	return 0;
}
int main()
{
	struct utilizator user;

	printf("Introduceti numele si prenumele dumneavoastra: ");
	fflush(stdout);
	scanf("%s%s", user.nume, user.prenume);

	printf("Introduceti anul nasterii: ");
	fflush(stdout);
	scanf("%d", &user.an_nastere);
        
	varstacalcul(user.an_nastere);
	user.varsta=varstacalcul(user.an_nastere);
        if( acces(user.varsta)==1)
             { return 1;

              }
	
	int optiune, i=1, j=1;
	char genurimuzica[20][20];

	FILE *f1, *f2, *f3;

	f1=fopen("genurimuzicale.txt", "r");
	f2=fopen("artisti.txt","r");
	f3=fopen("datenumerice.txt","r");

	if(f1==NULL)
	{
		printf("Eroare citire fisier f1!");
		return 1;
	}

	if(f2==NULL)
			{
				printf("Eroare citire fisier f2!");
				return 1;
			}

	if(f3==NULL)
	{
		printf("Eroare citire fisier f3!");
		return 1;
	}

	while(fscanf(f1,"%s",genurimuzica[i])!=EOF)
		i++;

	int n=i;

	printf("\nGenuri de muzica disponibile: \n");
	for(i=1;i<n;i++)
		printf("%d. %s\n", i, genurimuzica[i]);
	printf("\nIntroduceti numarul categoriei pentru care vreti recomandari de artisti!: ");
	fflush(stdout);
	scanf("%d", &optiune);

	char artisti[50][50][50];
	i=1, j=1;

	for(i=1;i<n;i++)
		for(j=1;j<6;j++)
			    fscanf(f2, "%s", artisti[i][j]);

	printf("\nBazat pe alegerea dumneavoastra ar trebui sa ascultati urmatorii artisti: ");
	for(i=1;i<n;i++)
		for(j=1;j<6;j++)
		        if(i==optiune)
		           printf("%s ", artisti[i][j]);

	long int asc_lun[50][50];
	i=1;
	long int asclunmax;
	char mostpopular[50];

				for(i=1;i<n;i++)
					if(i==optiune)
				       asclunmax=asc_lun[i][1];

				for(i=1;i<n;i++)
					for(j=1;j<6;j++)
					   fscanf(f3, "%ld", &asc_lun[i][j]);

				for(i=1;i<n;i++)
				   for(j=1;j<6;j++)
					    if(i==optiune)
					       if(asc_lun[i][j]>asclunmax)
					    	   {  asclunmax=asc_lun[i][j];
					    	      strcpy(mostpopular, artisti[i][j]);
					    	   }
	printf("\nCel mai popular artist din aceasta categorie este: %s.", mostpopular);

	i=1;

	for(int k=1; k< n; k++)
	   for (i = 1; i < 6; i++)
	     for (j = 1; j < 6; j++)
	    	      if (asc_lun[k][i] > asc_lun[k][j])
	               { char aux[50];
	                 strcpy(aux,artisti[k][j]);
	                 strcpy(artisti[k][j],artisti[k][i]);
	                 strcpy(artisti[k][i],aux);
	               }

	printf("\nArtistii de la aceasta categorie ordonati dupa popularitate: \n");
	for(i=1;i<n;i++)
		 for(j=1;j<6;j++)
			 if(i==optiune)
	            printf("%s ",artisti[i][j]);

	long int medie;
	long int suma=0;

	for(i=1;i<n;i++)
		for(j=1;j<6;j++)
			if(i==optiune)
				suma+=asc_lun[i][j];

	medie=suma/5;

	printf("\nMedia ascultatorilor lunar al genului de muzica pe care l-ati ales este: %ld", medie);


	fclose(f1);
	fclose(f2);
	fclose(f3);
    return 0;
}

