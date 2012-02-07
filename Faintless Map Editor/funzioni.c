#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pspiofilemgr.h>

void XORs(char *Buffer, char *Key, char *RetBuff,int blen);
void decrypt();

void scrividbg(int x,int y,char *frase,int variabile){
	 char numero[100];
	 sprintf(numero,"%s%d",frase, (int)variabile);
	 printTextScreen(x,y,numero,RGB(255,0,0));
}

//FPS
void FPS() {
	time_t currentTime;
	time(&currentTime);
	// aumenta il frame a ogni ciclo
	++framesPerSecond;
	if( difftime (currentTime,lastTime) > 1.0f ){
		lastTime = currentTime;
		sprintf(strFrameRate,"Fps: %d", (int)framesPerSecond);// inserisce nella variabile la frase
		framesPerSecond = 0;
	}
	printTextScreen(5,5,strFrameRate,RGB(255,0,0));
}

void initgame(){
	strcpy(nomeliv[0],"Terreno");
	strcpy(nomeliv[1],"Maschera");
	strcpy(nomeliv[2],"Maschera 2");
	strcpy(nomeliv[3],"Frangia");
	strcpy(nomeliv[4],"Frangia 2");
	 
	eroe = loadImage("Immagini/cursore.png");
	cursore = loadImage("Immagini/cursore.png");
	menubkg = loadImage("Immagini/menu.png");
	emptymenu= createImage(480,272);
	blitImageToImage(0,0,480,272,menubkg,0, 0,emptymenu);
	terra = createImage(960,544);
}

//carica
void carica(){// carica le immagini
	 char pathtile[100];
	 sprintf(pathtile,"../[PSP]Faintless/Immagini/tile%i.png",attbordo[4]);
	 tile = loadImage(pathtile);
	 tileset= createImage(480,256);
	 blitImageToImage(0,0,480,256,tile,0, 0,tileset);
}

void decrypt(int mappadacar){
	 
	 char fpath[50];
	 
	 sprintf(fpath,"../[PSP]Faintless/Mappe/mappa%i.txt",mappadacar);
	 
	 memset(ris,0,sizeof(ris));
	 memset(ris2,0,sizeof(ris2));
	 memset(valorimappa[0],0,sizeof(valorimappa[0]));
	 memset(valorimappa[1],0,sizeof(valorimappa[1]));
	 memset(attributi,0,sizeof(attributi));
	 memset(attbordo,0,sizeof(attbordo));
	 
	 int fd;
 	 int flen;
//apre e legge la mappa poi salva in ris
	  if(!(fd = sceIoOpen(fpath, PSP_O_RDONLY, 0777))) {
	 } else {
		flen = sceIoRead(fd, ris, sizeof(ris));
		if(flen <= 0) {
		}else{
		}
 	 }
	 sceIoClose(fd);
	 
	 //decript la mappa e salva in ris 2
	 XORs(ris,KEY,ris2,strlen(ris));
	 
	 int i=0;
	 for(i=0;i<4;i++){
	 	 attbordo[i]=0;
	 }
	 
	 i=0;
	 resultatt = strtok( ris2, delimatt );
	 while( resultatt != NULL ) {
		 sprintf(valorimappa[i],"%s", resultatt );
		 resultatt = strtok( NULL, delimatt );
		 i++; 
	 }
	 
	 sprintf(attributi,"%s",valorimappa[1]);
	 
	 i=0;
	 resultval = strtok(attributi, "&");
	 while( resultval != NULL ) {
		 attbordo[i]=atoi(resultval);
		 resultval = strtok( NULL, "&" );
		 i++; 
	 }
	 
	 
	 i=0;
	 resulty = strtok( valorimappa[0] ,delimy );
	 while( resulty != NULL ) {
		 sprintf(lineay[i],"%s", resulty );
		 resulty = strtok( NULL, delimy );
		 i++; 
	 }
	 
	 //variabili per prossimo split
	 int x;
	 int y;
	 int j;
	 int g;
	 for(y=0;y<34;y++){
		 //for y
		 j=0;
		 resultx = strtok( lineay[y], delimx );
		 while( resultx != NULL ) {
			 sprintf(lineax[j],"%s", resultx );
			 resultx = strtok( NULL, delimx );
			 j++; 
		 }
		 //fine split x
		 for(x=0;x<60;x++){
		    //split att
			 g=0;
			 resulta = strtok( lineax[x], delima );
			 while( resulta != NULL ) {
			 	 mappe[0][0][y][x][g]=atoi(resulta);
				 resulta = strtok( NULL,delima);
				 g++; 
			 }
		 	 //fine split att
		 }
	}
}

/*
void decrypt(){
	 
	 char fpath[50];
	 sprintf(fpath,"../[PSP]Faintless/Mappe/mappa%i.txt",carmap);
	 
	 memset(ris,0,sizeof(ris));
	 memset(ris2,0,sizeof(ris2));
	 memset(valorimappa[0],0,sizeof(valorimappa[0]));
	 memset(valorimappa[1],0,sizeof(valorimappa[1]));
	 memset(attributi,0,sizeof(attributi));
	 memset(attbordo,0,sizeof(attbordo));
			  
	 int fd;
 	 int flen;
//apre e legge la mappa poi salva in ris
	  if(!(fd = sceIoOpen(fpath, PSP_O_RDONLY, 0777))) {
	 } else {
		flen = sceIoRead(fd, ris, sizeof(ris));
		if(flen <= 0) {
		}else{
		}
 	 }
	 sceIoClose(fd);
	 
	 //decript la mappa e salva in ris 2
	 XORs(ris,KEY,ris2,strlen(ris));
	 
	 
	 int i=0;
	 resultatt = strtok( ris2, delimatt );
	 while( resultatt != NULL ) {
		 sprintf(valorimappa[i],"%s", resultatt );
		 resultatt = strtok( NULL, delimatt );
		 i++; 
	 }
	 
	 sprintf(attributi,"%s",valorimappa[1]);
	 
	 i=0;
	 resultval = strtok(attributi, "&");
	 while( resultval != NULL ) {
		 attbordo[i]=atoi(resultval);
		 resultval = strtok( NULL, "&" );
		 i++; 
	 }
	 
	 
	 i=0;
	 resulty = strtok( valorimappa[0] ,delimy );
	 while( resulty != NULL ) {
		 sprintf(lineay[i],"%s", resulty );
		 resulty = strtok( NULL, delimy );
		 i++; 
	 }
	 
	 //variabili per prossimo split
	 int x;
	 int y;
	 int j;
	 int g;
	 for(y=0;y<34;y++){
		 //for y
		 j=0;
		 resultx = strtok( lineay[y], delimx );
		 while( resultx != NULL ) {
			 sprintf(lineax[j],"%s", resultx );
			 resultx = strtok( NULL, delimx );
			 j++; 
		 }
		 //fine split x
		 for(x=0;x<60;x++){
		    //split att
			 g=0;
			 resulta = strtok( lineax[x], delima );
			 while( resulta != NULL ) {
			 	 mappe[0][0][y][x][g]=atoi(resulta);
				 resulta = strtok( NULL,delima);
				 g++; 
			 }
		 	 //fine split att
		 }
	}
}
*/
void salva(){
	 
	 int yyy;
	 int xxx;
	 
	 memset(totale,0,sizeof(totale));
	 memset(totalexor,0,sizeof(totalexor));
	 
	 for(yyy=0;yyy<34;yyy++){
	 	 for(xxx=0;xxx<60;xxx++){
			sprintf(totale,"%s%i|%i|%i|%i|%i|%i|%i",totale,mappe[0][0][yyy][xxx][0],mappe[0][0][yyy][xxx][1],mappe[0][0][yyy][xxx][2],mappe[0][0][yyy][xxx][3],mappe[0][0][yyy][xxx][4],mappe[0][0][yyy][xxx][5],mappe[0][0][yyy][xxx][6]);
			 if(xxx<59){
				  sprintf(totale,"%s#",totale);
			 }
	 	 }
		 if(yyy<33){
			  sprintf(totale,"%s$",totale);
		 }
	 }
	 
	 sprintf(totale,"%s!%i&%i&%i&%i&%i",totale,attbordo[0],attbordo[1],attbordo[2],attbordo[3],attbordo[4]);
	 XORs(totale,KEY,totalexor,strlen(totale));
	 
	 char fpath[50];
	 FILE * pFile;
	 sprintf(fpath,"../[PSP]Faintless/Mappe/mappa%i.txt",savmap);
	 remove(fpath);
	 pFile = fopen (fpath, "w");
	 fwrite (totalexor , 1 ,strlen(totalexor),pFile);
	 fclose (pFile);
	 
}

void XORs(char *Buffer, char *Key, char *RetBuff,int blen){
	int		x;
	int		y=0;
	for( x = 0 ; x < blen ; x++)
	{
		RetBuff[x] = ((unsigned char)Buffer[x] ^ (unsigned char)Key[y]);
		if(y < strlen(KEY)){
			y++;
		}else{
			y=0;
		}
	}

	return;
}
