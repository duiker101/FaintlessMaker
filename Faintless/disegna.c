#include <pspkernel.h>
#include <pspdebug.h> 
#include <pspdisplay.h> 
#include <pspgu.h>
#include <stdio.h>
#include <time.h> 
#include <png.h>
#include <math.h>
#include "graphics.h"

//mappa
void mappa(){
	 int y;
	 int x;
	 int xtile;
	 int ytile;
	 char pathtile[100];
	 sprintf(pathtile,"Immagini/tile%i.png",attbordo[4]);
	 tile = loadImage(pathtile);
	 
	 for(y=0;y<34;y++){
		 for(x=0;x<60;x++){
			 ytile=floor(mappe[0][0][y][x][0] / tilesetw);
			 xtile=mappe[0][0][y][x][0]-((ytile)*tilesetw);
			 blitImageToImage(xtile*16 ,ytile*16,unita , unita, tile, x*unita, y*unita,terra);
			  
			 if( mappe[0][0][y][x][1] > 1){
				 ytile=floor(mappe[0][0][y][x][1] / tilesetw);
				 xtile=mappe[0][0][y][x][1]-((ytile)*tilesetw);
				 blitAlphaImageToImage(xtile*16 ,ytile*16,unita , unita, tile, x*unita, y*unita,terra);
			 }
			 if( mappe[0][0][y][x][2] > 1){
				 ytile=floor(mappe[0][0][y][x][2] / tilesetw);
				 xtile=mappe[0][0][y][x][2]-((ytile)*tilesetw);
				 blitAlphaImageToImage(xtile*16 ,ytile*16,unita , unita, tile, x*unita, y*unita,terra);
			 }
	 	 }
	 }
	  sceDisplayWaitVblankStart();
}

void disfringe(){
	 int y=0;
	 int x=0;
	 int yy;
	 int xx;
	 int xtile;
	 int ytile;
	 int addy=0;
	 int addx=0;
	 
	 for(yy=0;yy<19;yy++){
		 for(xx=0;xx<32;xx++){
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
			 if( mappe[0][0][y][x][3] > 1){
				 ytile=floor(mappe[0][0][y][x][3] / tilesetw);
				 xtile=mappe[0][0][y][x][3]-((ytile)*tilesetw);
				 blitAlphaImageToScreen(xtile*16 ,ytile*16,unita , unita, tile, (xx-addx)*unita-scrollx, (yy-addy)*unita-scrolly);
			 }
			 if( mappe[0][0][y][x][4] > 1){
				 ytile=floor(mappe[0][0][y][x][4] / tilesetw);
				 xtile=mappe[0][0][y][x][4]-((ytile)*tilesetw);
				 blitAlphaImageToScreen(xtile*16 ,ytile*16,unita , unita, tile, (xx-addx)*unita-scrollx, (yy-addy)*unita-scrolly);
			 }
	 	 }
	 }
}

//Posizionemapscroll
void posizionemapscroll(){
	if(scrollx > unita){ 
		scrollx = 0;
		starttx += 1;
	}
		  
	if(scrollx < -unita){   
		scrollx = 0;
		starttx -= 1;
	}
		  
	if(scrolly > unita){ 
		scrolly = 0;
		startty += 1;
	}
		  
	if(scrolly < -unita){    
		scrolly = 0;
		startty -= 1;
	}
}
//disegna
void disegnamappa(){
	blitImageToScreen(starttx*unita+scrollx,startty*unita+scrolly ,skernw , skernh, terra, 0, 0);
	blitAlphaImageToScreen(playermov*22 ,playerdir*32.2+12 ,17 , 12, eroe, playerx ,playery);// stampa il pezzo sotto del pg
	blitAlphaImageToScreen(playermov*22 ,playerdir*32.2 ,17 , 12, eroe, playerx ,playery-12);// stampa il pezzo sopra del pg
	disfringe();
}


