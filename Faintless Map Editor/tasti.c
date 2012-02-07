#include <pspkernel.h>
#include <pspdebug.h> 
#include <pspdisplay.h> 
#include <pspctrl.h>
#include "graphics.h"

SceCtrlData pad;

void tastimappa(){
	 
	 int x;
	 int y;
	 clock_t curstep = clock(); // per gli step
	 clock_t curcross = clock();
	 clock_t currl = clock();
	 
	if(pad.Buttons & PSP_CTRL_LEFT){
		if(playerx - vel >=0 ){
			if(curstep - laststep >= stepvel ){
				if(starttx > 0 && playerx < actvscx){
					 scrollx -= vel;
				}else if(playerx > 0){
					 playerx -= vel;
				}
				 laststep=curstep;
				 curposx--;
			}
		}
	}else if (pad.Buttons & PSP_CTRL_RIGHT){
		if(playerx + vel <= skernw - unita){
			 if(curstep - laststep >= stepvel ){
				 if(starttx < tilexskx && playerx > actvscx){
				 	 scrollx +=vel;
				 }else if(playerx < bordd){
					 playerx += vel;
				 }
			 	 laststep=curstep;
				 curposx++;
			 }
		 }
	}else if (pad.Buttons & PSP_CTRL_UP){
		if(playery - vel >= 0 ){
			 if(curstep - laststep >= stepvel ){
				 if(startty > 0 && playery < actvscy){
				 	 scrolly -=vel;
				 }else if(playery > 0){
					 playery -= vel;
				}
				 laststep=curstep;
				 curposy--;
			}
		}
	}else if (pad.Buttons & PSP_CTRL_DOWN){
		 if(playery + vel <= skernh - unita ){
			 if(curstep - laststep >= stepvel ){
			 	 if(startty < tilexsky && playery > actvscy){
				 	 scrolly +=vel;
				 }else if(playery < bordg){
					 playery += vel;
				}
				 laststep=curstep;
				 curposy++;
			}
		}
	}
	 
	 if (pad.Buttons & PSP_CTRL_CROSS){
		 if(curcross - lastcross >= cross ){
			 if(metodo==0){
				 if(msel==0){
			 	 	mappe[0][0][curposy][curposx][livello]=selecttile;
				 }else if(msel==1){
					mselh=msely1-msely+1;
					mselw=mselx1-mselx+1;
					for(y=0;y<mselh;y++){
						for(x=0;x<mselw;x++){
							mappe[0][0][curposy+y][curposx+x][livello]=mselsel+y*tilesetw+x;
						 }
					}
				 }
			 }else if(metodo==1){
			 	 mappe[0][0][curposy][curposx][5]=attributo;
				 mappe[0][0][curposy][curposx][6]=valattrib;
			 }
			 lastcross=curcross;
			 mappa();
		 }
	 }
	 
	 if (pad.Buttons & PSP_CTRL_RTRIGGER){
		 if(currl - lastrl >= rl){
			 if( livello < 4 && metodo == 0){
			 	 livello++;
		 	 }else if( metodo == 1 && attval==0){
				 attributo++;
			 }else if( metodo == 1 && attval==1){
			 	 valattrib++;
			 }
			 lastrl=currl;
		 }
	 }
	 
	 if (pad.Buttons & PSP_CTRL_LTRIGGER){
		 if(currl - lastrl >= rl){
			 if( livello > 0 && metodo == 0){
			 	 livello--;
		 	 }else if( metodo == 1 && attval==0 && attributo > 0){
			 	 attributo--;
			 }else if( metodo == 1 && attval==1 && valattrib > 0){
			 	 valattrib--;
			 }
			 lastrl=currl;
		 }
	 }
	 
	 if (pad.Buttons & PSP_CTRL_TRIANGLE){
		 if(curstep - laststep >= trivel ){
			 act=1;
			 laststep=curstep;
		 }
	 }
	 
	 if (pad.Buttons & PSP_CTRL_CIRCLE){
		 if(curcross - lastcross >= cross ){
			 	 mappe[0][0][curposy][curposx][livello]=0;
				 mappa();
			 }
			 lastcross=curcross;
		 }
	 
	 if (pad.Buttons & PSP_CTRL_SQUARE){
		 if(curstep - laststep >= trivel ){
			 if(fillstate==0){
			 	 filly=curposy;
			 	 fillx=curposx;
				 fillstate=1;
			 }else if(fillstate==1){
			 	 fillh=curposy-filly+1;
				 fillw=curposx-fillx+1;
				 for(y=0;y<fillh;y++){
					 for(x=0;x<fillw;x++){
						 mappe[0][0][filly+y][fillx+x][livello]=selecttile;
					 }
				 }
			 	 fillstate=0;
				 mappa();
			 }
			  
			 laststep=curstep;
		 }
	 }
	 
	 if (pad.Buttons & PSP_CTRL_START){
		 if(curstep - laststep >= trivel ){
			 act=2;
			 laststep=curstep;
		 }
	 }
	 
	 if (pad.Buttons & PSP_CTRL_SELECT){
		 if(curstep - laststep >= 350000.0f ){
			 if(attval==0){
			 	attval=1;
			 }else if(attval==1){
			 	attval=0;
			 }
			 laststep=curstep;
		 }
	 }
	 
}


void tastitile(){
	 clock_t curstep = clock(); // per gli step
	 
	if (pad.Buttons & PSP_CTRL_TRIANGLE){
		 if(curstep - laststep >= trivel ){
			 act=0;
			 clearScreen(RGB(0,0,0));
			 laststep=curstep;
		 }
	 }
	 
	 if (pad.Buttons & PSP_CTRL_CROSS){
		 if(curstep - laststep >= trivel ){
			 selecttiley=floor(tempseltile / tilesetw);
			 selecttilex=tempseltile-((selecttiley)*tilesetw);
			 selecttile=tempseltile;
			 laststep=curstep;
			 msel=0;
			 mselstate=0;
		 }
	 }
	 
	 if (pad.Buttons & PSP_CTRL_SQUARE){
		 if(curstep - laststep >= trivel ){
			 if(mselstate==0){
			 	mselx=tilecurposx;
				msely=tilecurposy;
				mselstate=1;
				mselsel=tempseltile;
			 }else if(mselstate==1){
			 	mselx1=tilecurposx;
				msely1=tilecurposy;
				mselstate=0;
				msel=1;
			 }
			 laststep=curstep;
		 }
	 }
	 
	 //cur.sel=cur.tempsel+paginatile*tilesetw*tilesetsh
	 
	 if((pad.Buttons & PSP_CTRL_LEFT) && (curstep - laststep >= trivel)){
		 tilecurposx--;
		 tempseltile--;
		 laststep=curstep;
	 }else if ((pad.Buttons & PSP_CTRL_RIGHT) && (curstep - laststep >= trivel)){
		 tilecurposx++;
		 tempseltile++;
		 laststep=curstep;
	 }else if ((pad.Buttons & PSP_CTRL_UP) && (curstep - laststep >= trivel)){
		 tilecurposy--;
		 tempseltile -=tilesetw;
		 laststep=curstep;
	 }else if ((pad.Buttons & PSP_CTRL_DOWN) && (curstep - laststep >= trivel)){
		 tilecurposy++;
		 tempseltile +=tilesetw;
		 laststep=curstep;
	}
}

void tastimenu(){
	 clock_t curstep = clock(); // per gli step
	 if (pad.Buttons & PSP_CTRL_START){
		 if(curstep - laststep >= trivel ){
			 act=0;
			  
			 laststep=curstep;
		 }
	 }
	 
	 if (pad.Buttons & PSP_CTRL_UP){
		 if(curstep - laststep >= trivel && optsel > 0 ){
			 optsel--;
			 laststep=curstep;
		 }
	 }
	 if (pad.Buttons & PSP_CTRL_DOWN){
		 if(curstep - laststep >= trivel && optsel < 7){
			 optsel++;
			 laststep=curstep;
		 }
	 }
	 
	 if (pad.Buttons & PSP_CTRL_RIGHT){
		 if(curstep - laststep >= trivel){
			 if(optsel==0){
			 	 savmap++;
			 }else if(optsel==1){
			 	 carmap++;
			 }else if(optsel==2 && metodo == 0){
			 	metodo=1;
			 }else if(optsel==3){
			 	 attbordo[0]++;
			 }else if(optsel==4){
			 	 attbordo[1]++;
			 }else if(optsel==5){
			 	 attbordo[2]++;
			 }else if(optsel==6){
			 	 attbordo[3]++;
			 }else if(optsel==7){
			 	 attbordo[4]++;
				 carica();
				 mappa();
			 }
			 laststep=curstep;
		 }
	 }
	 
	 if (pad.Buttons & PSP_CTRL_LEFT){
		 if(curstep - laststep >= trivel){
			 if(optsel==0 && savmap > 1){
			 	 savmap--;
			 }else if(optsel==1 && carmap > 1){
			 	 carmap--;
			 }else if(optsel==2 && metodo == 1){
			 	metodo=0;
			 }else if(optsel==3 && attbordo[0] > 0){
			 	 attbordo[0]--;
			 }else if(optsel==4 && attbordo[1] > 0){
			 	 attbordo[1]--;
			 }else if(optsel==5 && attbordo[2] > 0){
			 	 attbordo[2]--;
			 }else if(optsel==6 && attbordo[3] > 0){
			 	 attbordo[3]--;
			 }else if(optsel==7 && attbordo[4] > 0){
			 	 attbordo[4]--;
				 carica();
				 mappa();
			 }
			 laststep=curstep;
		 }
	 }

	 
	 if (pad.Buttons & PSP_CTRL_CROSS){
		 if(curstep - laststep >= trivel){
			 if(optsel==0){
			 	 salva();
			 }else if(optsel==1){
			 	 decrypt(1);
				 //carica();
			    //mappa();
			 }
			 laststep=curstep;
		 }
	 }
	 
	 
}

