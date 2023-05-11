#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
struct utilizator
	{
		char nume[30], prenume[30];
		int an_nastere;
	};
int varsta(int an_nastere)
{
	int an_curent=2023;
	return an_curent-an_nastere;
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

	int optiune, i=1;
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

	char artisti[100][100];
	i=1;

	while(fgets(artisti[i], 100, f2)!=NULL)
					     i++;

	printf("\nBazat pe alegerea dumneavoastra ar trebui sa ascultati urmatorii artisti: ");
	for(i=1;i<n;i++)
		{ if(i==optiune)
		    printf("%s", artisti[i]);
		}

	long int *asc_lun;
	i=1;

	asc_lun=(long int*)malloc(30*sizeof(long int));
	for(i=1;i<n;i++)
		fscanf(f3,"%ld", (asc_lun+i));

	for(i=1;i<n;i++)
	  { if(optiune==i)
		  printf("%ld", *(asc_lun+i));
	  }

	fclose(f1);
	fclose(f2);
	fclose(f3);
    return 0;
}

