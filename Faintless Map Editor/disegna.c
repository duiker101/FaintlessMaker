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
	 
	 for(yy=0;yy<17;yy++){
		 for(xx=0;xx<30;xx++){
			 x=xx+starttx;
			 y=yy+startty;
			 if( mappe[0][0][y][x][3] > 1){
				 ytile=floor(mappe[0][0][y][x][3] / tilesetw);
				 xtile=mappe[0][0][y][x][3]-((ytile)*tilesetw);
				 blitAlphaImageToScreen(xtile*16 ,ytile*16,unita , unita, tile, xx*unita, yy*unita);
			 }
			 if( mappe[0][0][y][x][4] > 1){
				 ytile=floor(mappe[0][0][y][x][4] / tilesetw);
				 xtile=mappe[0][0][y][x][4]-((ytile)*tilesetw);
				 blitAlphaImageToScreen(xtile*16 ,ytile*16,unita , unita, tile, xx*unita, yy*unita);
			 }
			 if( mappe[0][0][y][x][5] > 1){
				 if(mappe[0][0][y][x][5] == 2){
				 	 printTextScreen(xx*unita+5,yy*unita+5,"B", RGB(255,0,0));
				 }else{
				 	 printTextScreen(xx*unita+5,yy*unita+5,"?", RGB(0,0,0));
				 }
			 }
	 	 }
	 }
}

//Posizionemap
void posizionemap(){
	if(scrollx >= unita){ 
		scrollx = 0;
		starttx += 1;
	}
		  
	if(scrollx <= -unita){   
		scrollx = 0;
		starttx -= 1;
	}
		  
	if(scrolly >= unita){ 
		scrolly = 0;
		startty += 1;
	}
		  
	if(scrolly <= -unita){    
		scrolly = 0;
		startty -= 1;
	}
}
//disegna
void disegnamappa(){
	blitImageToScreen(starttx*unita,startty*unita ,skernw , skernh, terra, 0, 0);
	blitAlphaImageToScreen(0,0,unita,unita, eroe, playerx ,playery);// stampa il pezzo sotto del pg
	disfringe();
}

void disegnatileset(){
	 clearScreen(RGB(255,255,255));
	 blitImageToScreen(0,0,480,256,tileset,0,0);
	 blitAlphaImageToScreen(selecttilex*unita,selecttiley*unita,unita,unita,tile,0,256);
	 blitAlphaImageToScreen(0,0,unita,unita, cursore,tilecurposx*unita,tilecurposy*unita);// stampa il pezzo sotto del pg
}


