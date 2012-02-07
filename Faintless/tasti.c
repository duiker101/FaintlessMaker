#include <pspkernel.h>
#include <pspdebug.h> 
#include <pspdisplay.h> 
#include <pspctrl.h>
#include <math.h>

SceCtrlData pad;

void tasti(){
	 playeroldx=playerx;
	 playeroldy=playery;
	 scrolloldx=scrollx;
	 scrolloldy=scrolly;
	clock_t curstep = clock(); // per gli step
	 
	if(pad.Buttons & PSP_CTRL_RTRIGGER){
		vel=4;
		stepvel = 100000.0f; 
	}else{
		vel=2;
		stepvel = 150000.0f;
	}
			
	if(pad.Buttons & PSP_CTRL_LEFT){
		playerdir = 3;
		if(playerx - vel >= 0 ){
			if(starttx > 0 && playerx < actvscx){
				 scrollx -= vel;
			}else if(playerx > 0){
				playerx -= vel;
			}
			if(curstep - laststep >= stepvel ){
				playermov += 1;
				if(playermov == 3){
					playermov = 0;
						}
				laststep=curstep;
			}
		}else if(attbordo[3] > 0){
			 decrypt(attbordo[3]);
			 playerx= 480-16;
			 scrollx=0;
			 starttx=30;
			 mappa();
		}
	}else if (pad.Buttons & PSP_CTRL_RIGHT){
		playerdir = 1;
		if(playerx + vel <= skernw - unita){
			if(starttx < tilexskx && playerx > actvscx){
				 scrollx +=vel;
			}else if(playerx < bordd){
				playerx += vel;
			}
			if(curstep - laststep >= stepvel ){
				playermov += 1;
				if(playermov == 3){
					playermov = 0;
				}
				laststep=curstep;
			}
		}else if(attbordo[1] > 0){
			 decrypt(attbordo[1]);
			 playerx=0;
			 scrollx=0;
			 starttx=0;
			 mappa();
		}
	}else if (pad.Buttons & PSP_CTRL_UP){
		playerdir = 0;
		if(playery - vel >= 0 ){
			playerdir = 0;
			if(startty > 0 && playery < actvscy){
				 scrolly -=vel;
			}else if(playery > 0){
				playery -= vel;
			}
			if(curstep - laststep >= stepvel ){
				playermov += 1;
				if(playermov == 3){
					playermov = 0;
				}
				laststep=curstep;
			}
		}else if(attbordo[0] > 0){
			 decrypt(attbordo[0]);
			 playery=272-16;
			 scrolly=0;
			 startty=17;
			 mappa();
		}
	}else if (pad.Buttons & PSP_CTRL_DOWN){
		playerdir = 2;
		 if(playery + vel <= skernh - unita ){
			playerdir = 2;
			 if(startty < tilexsky && playery > actvscy){
				 scrolly +=vel;
			}else if(playery < bordg){
				playery += vel;
			}
			if(curstep - laststep >= stepvel ){
				playermov += 1;
				if(playermov == 3){
					playermov = 0;
				}
				laststep=curstep;
			}
		}else if(attbordo[2] > 0){
			 decrypt(attbordo[2]);
			 playery=0;
			 scrolly=0;
			 startty=0;
			 mappa();
		}
	}else{
		playermov = 1;
	}
	 
}
