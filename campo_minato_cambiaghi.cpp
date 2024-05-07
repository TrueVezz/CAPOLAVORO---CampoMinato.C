#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define WHITE "\x1b[0m"
#define MAGENTA "\x1b[35m"
#define CIANO "\x1b[36m"

void initializeCharMatrix(char mtrx[][100], int size, char character);
void generateBomb(int mtrx[][100], int size, int nBomb);

void printMatrix(int mtrx[][100], int size);
void printCharMatrix(char mtrx[][100], int size);

void insertNearBomb(int mineMtrx[][100], int bombMtrx[][100], int size);
int howManyNearBomb(int mineMtrx[][100], int bombMtrx[][100], int size, int indexRow, int indexCol);
void nearZero(int bombMtrx[][100], char plrMtrx[][100], int size, int usrRow, int usrCol);
void insertZeroInPlayerCamp(char plrMtrx[][100], int bombMtrx[][100], int size, int indexRow, int indexCol);
void viewNumberNearZero(char plrMtrx[][100], int bombMtrx[][100], int size);

bool indexInRange(int index, int size);

int getUserInput(char plrMtrx[][100], int *usrRow, int *usrCol, int size);
void insertUserInput(int bombMtrx[][100], char plrMtrx[][100], int size, int usrRow, int usrCol);
void getAndInsertFlag(char plrMtrx[][100], int size, int usrRow, int usrCol);

bool didIWin(char plrMtrx[][100],int bombMtrx[][100], int size, int nBomb);
void menu();
void selectCampAndMine(int *size, int *nBomb);

int main()
{
	srand(time(NULL));
	int mine[100][100]={0}, nearBombCamp[100][100]={0}, matrixSize=0, userRow, userCol, numberOfBomb=0;
	char playerCamp[100][100];
	menu();
	selectCampAndMine(&matrixSize, &numberOfBomb);
	
	initializeCharMatrix(playerCamp, matrixSize, 32);
	generateBomb(mine, matrixSize, numberOfBomb);
	insertNearBomb(mine, nearBombCamp, matrixSize);

	
	do{	
		system("cls");
//		printMatrix(nearBombCamp, matrixSize);
		printCharMatrix(playerCamp, matrixSize);
		if(getUserInput(playerCamp, &userRow, &userCol, matrixSize)!=0){
			if(nearBombCamp[userRow][userCol]==0){
				insertZeroInPlayerCamp(playerCamp,nearBombCamp, matrixSize, userRow, userCol);
				nearZero(nearBombCamp, playerCamp, matrixSize, userRow, userCol);
			}
			//sistem cls per aggiornare la tabella
			insertUserInput(nearBombCamp, playerCamp, matrixSize, userRow, userCol);
			viewNumberNearZero(playerCamp, nearBombCamp, matrixSize);			
		}		
	}while(didIWin(playerCamp, nearBombCamp, matrixSize, numberOfBomb));
}

/*------------------------------------------------ MENU ------------------------------------------------*/
void menu(){
	printf("---------------------- BENVENUTO SU CAMPO MINATO ----------------------\n\nregole:\n");
	printf("1. inserire indice di riga e di colonna per scoprire la cella\n");
	printf("2. inserire nell'indice di riga -1 per inserire una bandiera(!)\n");
	printf("3. si vince quando si aprono tutte le celle tranne quelle delle bombe\n");
	printf("4. si perde quando viene trovata una bomba(/)\n\n\n");
	
	system("PAUSE");
}
/*------------------------------------------------ SELEZIONE CAMPO E QUANTE BOMBE ------------------------------------------------*/
void selectCampAndMine(int *size, int *nBomb){
	do{
		printf("\n\ninserire il lato del campo: ");
		scanf("%d", &*size);
	}while(*size==0);
	
	printf("inserire il numero di mine: ");
	scanf("%d", &*nBomb);	
}
/*------------------------------------------------ INIZIALIZZA MATRICE CHAR ------------------------------------------------*/
void initializeCharMatrix(char mtrx[][100], int size, char character){
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++) mtrx[i][j]=character;	
}
/*------------------------------------------------ GENERA BOMBE IN MATRICE ------------------------------------------------*/
void generateBomb(int mtrx[][100], int size, int nBomb){
	int rndRow, rndCol;
	int i=0;
	while(i<nBomb){
		rndRow=rand()%size;
		rndCol=rand()%size;
		if(mtrx[rndRow][rndCol]!=-1) {
			mtrx[rndRow][rndCol]=-1;
			i++;
		}
	}
}
/*------------------------------------------------ STAMPA MATRICE INT ------------------------------------------------*/
void printMatrix(int mtrx[][100], int size){
	printf("\n");
	printf("%2c|", 32);
	for(int i=0;i<size;i++) printf(RED"%2d"WHITE"|", i);
	//	riga di separazione
	printf("\n");		
	for(int h=0;h<(size+1)*3;h++) printf("-");
	printf("\n");
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(j==0) printf(RED "%2d" WHITE "|", i);
			printf("%2d|", mtrx[i][j]);
		}	
//		riga di separazione
		printf("\n");
		for(int h=0;h<(size+1)*3;h++) printf("-");
		printf("\n");		
	}	
}
/*------------------------------------------------ STAMPA MATRICE CHAR ------------------------------------------------*/
void printCharMatrix(char mtrx[][100], int size){
	printf("\n");
	printf("%2c|", 32);
	for(int i=0;i<size;i++) printf(RED"%2d"WHITE"|", i);
	
//	riga di separazione
	printf("\n");
	for(int h=0;h<(size+1)*3;h++) printf("-");
	printf("\n");
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(j==0) printf(RED "%2d" WHITE "|", i);
			if(mtrx[i][j]==49) printf(GREEN"%2c"WHITE"|", mtrx[i][j]);
			if(mtrx[i][j]==50) printf(YELLOW"%2c"WHITE"|", mtrx[i][j]);
			if(mtrx[i][j]>=51) printf(RED"%2c"WHITE"|", mtrx[i][j]);
			if(mtrx[i][j]==48)  printf(WHITE"%2c|", mtrx[i][j]);
			if(mtrx[i][j]==32)  printf(WHITE"%2c|", 32);
			if(mtrx[i][j]==33)  printf(CIANO"%2c"WHITE"|", mtrx[i][j]);
			if(mtrx[i][j]==47)  printf(MAGENTA"%2c"WHITE"|",mtrx[i][j]);
			
		}
//		riga di separazione
		printf("\n");
		for(int h=0;h<(size+1)*3;h++) printf("-");
		printf("\n");	
	}
}
/*------------------------------------------------ INSERISCI NUMERO DI BOMBE IN TORNO ------------------------------------------------*/
void insertNearBomb(int mineMtrx[][100], int bombMtrx[][100], int size){
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++){
			if(mineMtrx[i][j]==0){
//				printf("controllo %d[%d][%d]\n", mineMtrx[i][j], i, j);
				bombMtrx[i][j]=howManyNearBomb(mineMtrx, bombMtrx, size, i, j); //metti il numero di bombe vicine in bombMtrx
			}
			else if(mineMtrx[i][j]==-1)bombMtrx[i][j]=mineMtrx[i][j];// metti -1 in bombMtrx
		}
}
/*------------------------------------------------ CONTROLLA QUANTE BOMBE CI SONO NEL CONTORNO ------------------------------------------------*/
int howManyNearBomb(int mineMtrx[][100], int bombMtrx[][100], int size, int indexRow, int indexCol){
	int bomb=0;
	
	if(indexInRange(indexRow-1, size) && indexInRange(indexCol-1, size) && mineMtrx[indexRow-1][indexCol-1]==-1){
//		sopra sinistra - -
//		printf("%d[%d][%d]-->%d[%d][%d]\n",mineMtrx[indexRow][indexCol], indexRow, indexCol, mineMtrx[indexRow-1][indexCol-1], indexRow-1, indexCol-1 );
		bomb++;	
	}
	if(indexInRange(indexRow-1, size) && indexInRange(indexCol, size) && mineMtrx[indexRow-1][indexCol]==-1){
//		sopra - \
//		printf("%d[%d][%d]-->%d[%d][%d]\n",mineMtrx[indexRow][indexCol], indexRow, indexCol, mineMtrx[indexRow-1][indexCol], indexRow-1, indexCol );
		bomb++;	
	}
	if(indexInRange(indexRow-1, size) && indexInRange(indexCol+1, size) && mineMtrx[indexRow-1][indexCol+1]==-1){
//		sopra destra -  +
//		printf("%d[%d][%d]-->%d[%d][%d]\n",mineMtrx[indexRow][indexCol], indexRow, indexCol, mineMtrx[indexRow-1][indexCol+1], indexRow-1, indexCol+1);
		bomb++;	
	}
	if(indexInRange(indexRow, size) && indexInRange(indexCol+1, size) && mineMtrx[indexRow][indexCol+1]==-1){
//		destra \  +
//		printf("%d[%d][%d]-->%d[%d][%d]\n",mineMtrx[indexRow][indexCol], indexRow, indexCol, mineMtrx[indexRow][indexCol+1], indexRow, indexCol+1);
		bomb++;	
	}
	if(indexInRange(indexRow+1, size) && indexInRange(indexCol+1, size) && mineMtrx[indexRow+1][indexCol+1]==-1){
//		sotto destra +  +
//		printf("%d[%d][%d]-->%d[%d][%d]\n",mineMtrx[indexRow][indexCol], indexRow, indexCol, mineMtrx[indexRow+1][indexCol+1], indexRow+1, indexCol+1);
		bomb++;	
	}
	if(indexInRange(indexRow+1, size) && indexInRange(indexCol, size) && mineMtrx[indexRow+1][indexCol]==-1){
//		sotto +  \
//		printf("%d[%d][%d]-->%d[%d][%d]\n",mineMtrx[indexRow][indexCol], indexRow, indexCol, mineMtrx[indexRow-1][indexCol], indexRow-1, indexCol);
		bomb++;	
	}
	if(indexInRange(indexRow+1, size) && indexInRange(indexCol-1, size) && mineMtrx[indexRow+1][indexCol-1]==-1){
//		sotto sinistra +  -
//		printf("%d[%d][%d]-->%d[%d][%d]\n",mineMtrx[indexRow][indexCol], indexRow, indexCol, mineMtrx[indexRow+1][indexCol-1], indexRow+1, indexCol-1 );
		bomb++;	
	}
	if(indexInRange(indexRow, size) && indexInRange(indexCol-1, size) && mineMtrx[indexRow][indexCol-1]==-1){
//		sinistra \  -
//		printf("%d[%d][%d]-->%d[%d][%d]\n",mineMtrx[indexRow][indexCol], indexRow, indexCol, mineMtrx[indexRow][indexCol-1], indexRow, indexCol-1 );
		bomb++;	
	}
//	DEBUG
//	printf("\nmetto %d bombe in %d[%d][%d]\n", bomb,mineMtrx[indexRow][indexCol], indexRow, indexCol);
	return bomb;
}
/*------------------------------------------------ CONTROLLA SE CI SONO ALTRI ZERI VICINI ------------------------------------------------*/
void nearZero(int bombMtrx[][100], char plrMtrx[][100], int size, int usrRow, int usrCol){
//	printf("\n CHECK ZERO VICINI con indici %d[%d][%d]\n",bombMtrx[usrRow][usrCol], usrRow, usrCol);
	if(indexInRange(usrRow-1, size) && indexInRange(usrCol-1, size) && bombMtrx[usrRow-1][usrCol-1]==0 && plrMtrx[usrRow-1][usrCol-1]==32){
//		printf("sopra sinistra -  -\n");
		//metti in plrMtrx 0
		insertZeroInPlayerCamp(plrMtrx,bombMtrx, size, usrRow-1, usrCol-1);
/*
		printf("matrice che vede il giocatore ----------------------------");
		printCharMatrix(plrMtrx, size);
		printf("matrice bombe --------------------------------------------");
		printMatrix(bombMtrx, size);
		printf("\nfunzione ricorsiva\n");
*/
		nearZero(bombMtrx, plrMtrx, size, usrRow-1, usrCol-1);
	}
	
	if(indexInRange(usrRow-1, size) && indexInRange(usrCol, size) && bombMtrx[usrRow-1][usrCol]==0 && plrMtrx[usrRow-1][usrCol]==32){
//		printf("sopra -  0\n");
		//metti in plrMtrx 0
		insertZeroInPlayerCamp(plrMtrx,bombMtrx, size, usrRow-1, usrCol);
/*				
		printf("matrice che vede il giocatore ----------------------------");
		printCharMatrix(plrMtrx, size);
		printf("matrice bombe --------------------------------------------");
		printMatrix(bombMtrx, size);
		printf("\nfunzione ricorsiva\n");
*/
		nearZero(bombMtrx, plrMtrx, size, usrRow-1, usrCol);	
	}	
	
	if(indexInRange(usrRow-1, size) && indexInRange(usrCol+1, size) && bombMtrx[usrRow-1][usrCol+1]==0 && plrMtrx[usrRow-1][usrCol+1]==32){
//		printf("sopra destra -  +\n");
		//metti in plrMtrx 0
		insertZeroInPlayerCamp(plrMtrx,bombMtrx, size, usrRow-1, usrCol+1);
/*		
		printf("matrice che vede il giocatore ----------------------------");
		printCharMatrix(plrMtrx, size);
		printf("matrice bombe --------------------------------------------");
		printMatrix(bombMtrx, size);
		printf("\nfunzione ricorsiva\n");
*/
		nearZero(bombMtrx, plrMtrx, size, usrRow-1, usrCol+1);	
	}
	
	if(indexInRange(usrRow, size) && indexInRange(usrCol+1, size) && bombMtrx[usrRow][usrCol+1]==0 && plrMtrx[usrRow][usrCol+1]==32){
//		printf("destra 0  +\n");
		//metti in plrMtrx 0
		insertZeroInPlayerCamp(plrMtrx,bombMtrx, size, usrRow, usrCol+1);
/*
		printf("matrice che vede il giocatore ----------------------------");
		printCharMatrix(plrMtrx, size);
		printf("matrice bombe --------------------------------------------");
		printMatrix(bombMtrx, size);
		printf("\nfunzione ricorsiva\n");
*/		
		nearZero(bombMtrx, plrMtrx, size, usrRow, usrCol+1);	
	}	
	
	if(indexInRange(usrRow+1, size) && indexInRange(usrCol+1, size) && bombMtrx[usrRow+1][usrCol+1]==0 && plrMtrx[usrRow+1][usrCol+1]==32){
//		printf("sotto destra +  +\n");
		//metti in plrMtrx 0
		insertZeroInPlayerCamp(plrMtrx,bombMtrx, size, usrRow+1, usrCol+1);
/*		
		printf("matrice che vede il giocatore ----------------------------");
		printCharMatrix(plrMtrx, size);
		printf("matrice bombe --------------------------------------------");
		printMatrix(bombMtrx, size);
		printf("\nfunzione ricorsiva\n");
*/
		nearZero(bombMtrx, plrMtrx, size, usrRow+1, usrCol+1);				
	}
	
	if(indexInRange(usrRow+1, size) && indexInRange(usrCol, size) && bombMtrx[usrRow+1][usrCol]==0 && plrMtrx[usrRow+1][usrCol]==32){
//		printf("sotto  +  0\n");
		//metti in plrMtrx 0
		insertZeroInPlayerCamp(plrMtrx,bombMtrx, size, usrRow+1, usrCol);
/*		
		printf("matrice che vede il giocatore ----------------------------");
		printCharMatrix(plrMtrx, size);
		printf("matrice bombe --------------------------------------------");
		printMatrix(bombMtrx, size);	
		printf("\nfunzione ricorsiva\n");
*/
		nearZero(bombMtrx, plrMtrx, size, usrRow+1, usrCol);					
	}
	
	if(indexInRange(usrRow+1, size) && indexInRange(usrCol-1, size) && bombMtrx[usrRow+1][usrCol-1]==0 && plrMtrx[usrRow+1][usrCol-1]==32){
//		printf("sotto sinistra +  -\n");
		//metti in plrMtrx 0
		insertZeroInPlayerCamp(plrMtrx,bombMtrx, size, usrRow+1, usrCol-1);
/*		
		printf("matrice che vede il giocatore ----------------------------");
		printCharMatrix(plrMtrx, size);
		printf("matrice bombe --------------------------------------------");
		printMatrix(bombMtrx, size);		
		printf("\nfunzione ricorsiva\n");
*/
		nearZero(bombMtrx, plrMtrx, size, usrRow+1, usrCol-1);				
	}	
	if(indexInRange(usrRow, size) && indexInRange(usrCol-1, size) && bombMtrx[usrRow][usrCol-1]==0 && plrMtrx[usrRow][usrCol-1]==32){
//		printf("sinistra 0  -\n");
		//metti in plrMtrx 0
		insertZeroInPlayerCamp(plrMtrx,bombMtrx, size, usrRow, usrCol-1);
/*		
		printf("matrice che vede il giocatore ----------------------------");
		printCharMatrix(plrMtrx, size);
		printf("matrice bombe --------------------------------------------");
		printMatrix(bombMtrx, size);		
		printf("\nfunzione ricorsiva\n");
*/
		nearZero(bombMtrx, plrMtrx, size, usrRow, usrCol-1);			
	}
}
/*--------------------------------------- INSERISCI ZERO NEL CAMPO DELL'UTENTE SENZA STAMPA ---------------------------------------*/
void insertZeroInPlayerCamp(char plrMtrx[][100], int bombMtrx[][100], int size, int indexRow, int indexCol){
	plrMtrx[indexRow][indexCol]=48;
}
/*-------------------------------------- MOSTRA NUMERI VICINO ALLE CELLE CON 0--------------------------------------*/
void viewNumberNearZero(char plrMtrx[][100], int bombMtrx[][100], int size){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++) 
			if(plrMtrx[i][j]==48){
				if(indexInRange(i-1, size)&& indexInRange(j-1,size))plrMtrx[i-1][j-1]=bombMtrx[i-1][j-1]+48;
				if(indexInRange(i-1, size)&& indexInRange(j,size))plrMtrx[i-1][j]=bombMtrx[i-1][j]+48;
				if(indexInRange(i-1, size)&& indexInRange(j+1,size))plrMtrx[i-1][j+1]=bombMtrx[i-1][j+1]+48;
				
				if(indexInRange(i, size)&& indexInRange(j+1,size))plrMtrx[i][j+1]=bombMtrx[i][j+1]+48;
				if(indexInRange(i+1, size)&& indexInRange(j+1,size))plrMtrx[i+1][j+1]=bombMtrx[i+1][j+1]+48;
				
				if(indexInRange(i+1, size)&& indexInRange(j,size))plrMtrx[i+1][j]=bombMtrx[i+1][j]+48;
				if(indexInRange(i+1, size)&& indexInRange(j-1,size))plrMtrx[i+1][j-1]=bombMtrx[i+1][j-1]+48;
				if(indexInRange(i, size)&& indexInRange(j-1,size))plrMtrx[i][j-1]=bombMtrx[i][j-1]+48;
			}
	}
}
/*------------------------------------------------ CONTROLLO SE INDICI SONO VALIDI------------------------------------------------*/
bool indexInRange(int index, int size){
	return index>=0 && index<size;
}
/*------------------------------------------------ INPUT COLONNA RIGA UTENTE ------------------------------------------------*/
int getUserInput(char plrMtrx[][100], int *usrRow, int *usrCol, int size){
	do{
		printf("riga: ");
		scanf("%d", &*usrRow);
	}while(*usrRow!=-1&&!indexInRange(*usrRow,size));
	
	if(*usrRow==-1){
		getAndInsertFlag(plrMtrx, size, *usrRow, *usrCol);
		return 0;
	}
	else{
		do{
			printf("colonna: ");
			scanf("%d", &*usrCol);	
		}while(!indexInRange(*usrCol,size));
		return 1;
	}
}
/*------------------------------------------------ STAMPA DATO MATRICE NEGLI INDICI SCELTI ------------------------------------------------*/
void insertUserInput(int bombMtrx[][100], char plrMtrx[][100], int size, int usrRow, int usrCol){
	plrMtrx[usrRow][usrCol]=bombMtrx[usrRow][usrCol]+48;
}
/*------------------------------------------------ INSERISCE/TOGLIE LA FLAG DA UNA CELLA ------------------------------------------------*/
void getAndInsertFlag(char plrMtrx[][100], int size, int usrRow, int usrCol){
	
	printf("FLAG\n\n");
	do{
		printf("riga: ");
		scanf("%d", &usrRow);
		
	}while(!indexInRange(usrRow,size));

	do{
		printf("colonna: ");
		scanf("%d", &usrCol);	
	}while(!indexInRange(usrCol,size));
	if(plrMtrx[usrRow][usrCol]==32) plrMtrx[usrRow][usrCol]=33;
	else plrMtrx[usrRow][usrCol]=32;
/*	
	printf("matrice con flag:");
	printCharMatrix(plrMtrx, size);
*/	
}
/*------------------------------------------------ CONTROLLO VINCITA ------------------------------------------------*/
bool didIWin(char plrMtrx[][100], int bombMtrx[][100], int size, int nBomb){
	int occupiedCell=0;
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++){
			if(plrMtrx[i][j]=='/'){
				system("cls");
				printMatrix(bombMtrx, size);
				printCharMatrix(plrMtrx, size);		
				printf("\n\nHAI PRESO UNA BOMBA");	
				return false;
			} 
			else if(plrMtrx[i][j]!=33 && plrMtrx[i][j]!=32) occupiedCell++;
		}	
	
	printf("occupiedCell: %d=%d", occupiedCell, size*size-nBomb);
	if(occupiedCell==size*size-nBomb){
		system("cls");
		printf("matrice scoperta:"),
		printMatrix(bombMtrx, size);
		printf("\nla tua matrice:\n");
		printCharMatrix(plrMtrx, size);
		printf("\n\nCOMPLIMENTI, HAI VINTO!!!!!");
		return false;	
	}
	return true;
}
