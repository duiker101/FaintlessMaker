#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pspiofilemgr.h>

void XORs(char *Buffer, char *Key, char *RetBuff,int blen);
void decrypt(int mappadacar);
void collisioni(int xPos, int yPos,int x, int y);


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

//carica
void carica(){// carica le immagini
	 eroe = loadImage("Immagini/eroe.png");
	 terra = createImage(960,544);
}

//decrypt
void decrypt(int mappadacar){
	 
	 char fpath[50];
	 
	 sprintf(fpath,"Mappe/mappa%i.txt",mappadacar);
	 
	 memset(ris,0,sizeof(ris));
	 
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
	 
	 sprintf(attributit,"%s",valorimappa[1]);
	 
	 i=0;
	 resultval = strtok(attributit, "&");
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
//xors
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
//attributi
void attributi(){
	 int y=0;
	 int x=0;
	 int yy;
	 int xx;
	 int addy=0;
	 int addx=0;
	 
	 for(yy=0;yy<18;yy++){
		 for(xx=0;xx<31;xx++){
			 if(startty > 0){
			 	addy=1;
			 }else{
			 	addy=0;
			 }
			 if(starttx > 0){
			 	addx=1;
			 }else{
			 	addx=0;
			 }
			 x=xx+starttx-addx;
			 y=yy+startty-addy;
			 if( mappe[0][0][y][x][5] > 1){
				 collisioni((xx-addx)*unita-scrollx, (yy-addy)*unita-scrolly,x,y);
			 }
	 	 }
	 }
}
//collisioni
void collisioni(int xPos, int yPos,int x, int y){
	if((playerx+15 > xPos) && (playerx < xPos + 15) && (playery + 12 > yPos) && (playery < yPos +16)){
		playerx=playeroldx;
		playery=playeroldy;
		scrollx=scrolloldx;
		scrolly=scrolloldy;
	}
	 
	 //if (player.x + 15 > object.xPos) and (player.x < object.xPos + 15) and (player.y + 12 > object.yPos) and (player.y < object.yPos + 16) then
}

