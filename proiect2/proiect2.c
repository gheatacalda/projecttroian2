#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#include <windows.h>
#include <GL/glut.h>
long int *pv;
char *string;
void display() {

	int i, j;
	float dx, ky;
	long int max;
	dx = 1.9 / 6;
	max = *pv;
	for(i = 2; i < 6; i++){
		if(max < *(pv + i)){
			max = *(pv + i);
		}
	}
	ky = 1.8 / max;

	for(i = 1; i < 6; i++){
			   glBegin(GL_QUADS);
			   glColor3f(0.0f, 0, 1.0f);
			   glVertex2f(-0.95 + i * dx, -0.9);
			   glVertex2f(-0.95 + (i + 1) * dx - 0.02, -0.9);
			   glVertex2f(-0.95 + (i + 1) * dx - 0.02, -0.9 + *(pv+i) * ky );
			   glVertex2f(-0.95 + i * dx, -0.9 + *(pv+i) * ky );
			   glEnd();
			   sprintf(string,"%ld ",*(pv+i));
			   	      glRasterPos2f(-0.95 + i * dx + dx / 2, -0.9 + *(pv+i) * ky + 0.05);
			   	     for(j = 1; j < strlen(string); j++)
			   		       glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,string[j]);
	}
		   glFlush();
}
struct utilizator
	{
		char nume[30], prenume[30];
		int an_nastere, varsta;
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
		printf("Ai o varsta nepotrivita pentru recomandarile de muzica!");
		return 1;
	}
	return 0;
}
int main(int argc, char** argv)
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

	int optiune, i=1, j=1, k=1;
	char genurimuzica[20][20];

	for(i=1;i<strlen(user.nume);i++){
		if(user.nume[0]>='a' && user.nume[0]<='z'){
			user.nume[0]-=32;
		}
	}

	for(i=1;i<strlen(user.prenume);i++){
			if(user.prenume[0]>='a' && user.prenume[0]<='z'){
				user.prenume[0]-=32;
			}
		}

	FILE *f1, *f2, *f3, *f4;

	f1=fopen("genurimuzicale.txt", "r");
	f2=fopen("artisti.txt","r");
	f3=fopen("datenumerice.txt","r");
	f4=fopen("informatii_utilizator.txt","w");

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

	if(f4==NULL)
	{
		printf("Eroare scriere in fisierul f4");
		return 1;
	}

	i=1;
	while(fscanf(f1,"%s",genurimuzica[i])!=EOF)
		i++;

	int n=i;

	printf("\nGenuri de muzica disponibile: \n");
	for(i=1;i<n;i++)
		{ printf("%d. %s\n", i, genurimuzica[i]); }
	printf("\nIntroduceti numarul categoriei pentru care vreti recomandari de artisti!: ");
	fflush(stdout);
	scanf("%d", &optiune);

	char artisti[50][50][50];
	i=1, j=1;

	for(i=1;i<n;i++){
		for(j=1;j<6;j++){
			fscanf(f2, "%s", artisti[i][j]);
              }
		}
//nu se copiaza in string aici
	for(i=1;i<n;i++){
			for(j=1;j<6;j++){
				if(i==optiune){
				    strcpy(string, artisti[i][j]);
	              }
			}
	}

	fprintf(f4, "%s %s, bazat pe alegerea ta ar trebui sa ascultati urmatorii artisti: \n", user.nume, user.prenume);
	for(i=1;i<n;i++) {
		for(j=1;j<6;j++) {
		        if(i==optiune) {
		           fprintf(f4, "%s ", artisti[i][j]);
		        }
		}
	}


	long int asc_lun[50][50];
	i=1;
	long int asclunmax;
	char mostpopular[50];

				for(i=1;i<n;i++){
					if(i==optiune) {
				       asclunmax=asc_lun[i][1];
					}
				}

				for(i=1;i<n;i++){
					for(j=1;j<6;j++){
					   fscanf(f3, "%ld", &asc_lun[i][j]);
					}
				}

				for(i=1;i<n;i++){
				   for(j=1;j<6;j++){
					    if(i==optiune){
					       if(asc_lun[i][j]>asclunmax)
					    	   {  asclunmax=asc_lun[i][j];
					    	      strcpy(mostpopular, artisti[i][j]);
					    	   }
					    }
				   }
				}

	for(i=1;i<n;i++){
		     if(i==optiune){
			     pv=asc_lun[i];
		    }
	    }

	fprintf(f4,"\n");
	for(i=1;i<n;i++){
		if(i==optiune){
			fprintf(f4, "\nCel mai popular artist din categoria %s este: %s!", genurimuzica[i], mostpopular);
		}
	}

	i=1;

	fprintf(f4, "\n");
	fprintf(f4, "\nNumarul de ascultatori lunari ai acestor artisti in ordinea afisarii lor sunt: \n");
	for(i=1; i<n; i++){
		for(j=1; j< 6; j++){
			if(i==optiune){
			    fprintf(f4, "%ld ", asc_lun[i][j]);
			}
		}
	}

	long int medie;
	long int suma=0;

	for(i=1;i<n;i++){
		for(j=1;j<6;j++){
			if(i==optiune){
				suma+=asc_lun[i][j];
			}
		}
	}

	medie=suma/5;

	fprintf(f4, "\n");
	for(i=1;i<n;i++){
		if(i==optiune){
		    fprintf(f4, "\nMedia ascultatorilor lunari ai artistilor din genul de muzica %s este: %ld.", genurimuzica[i],  medie);
		}
	}

	for(k=1; k< n; k++){
			 for (i = 1; i < 6; i++){
			     for (j = 1; j < 6; j++){
			    	 if(strncmp(artisti[k][i],artisti[k][j], 3)<0)
			    	 {
			    		 char aux[50];
			    		 strcpy(aux,artisti[k][j]);
			    		 strcpy(artisti[k][j],artisti[k][i]);
			    		 strcpy(artisti[k][i],aux);
			    	 }
			     }
			   }
	}
        fprintf(f4,"\n");
		fprintf(f4,"\nArtistii de la aceasta categorie ordonati alfabetic: \n");
			for(i=1;i<n;i++){
				 for(j=1;j<6;j++){
					 if(i==optiune){
			            fprintf(f4, "%s ",artisti[i][j]);
					 }
				 }
			}

	fclose(f1);
	fclose(f2);
	fclose(f3);
	fclose(f4);

	glutInit(&argc, argv);
		glutInitWindowSize(320, 320);
		glutInitWindowPosition(50, 50);
		glutCreateWindow("OpenGL Setup Test");
		glutDisplayFunc(display);
		glutMainLoop();

    return 0;
}

