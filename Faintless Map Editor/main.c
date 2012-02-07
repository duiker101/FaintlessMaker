// Faintless

/*
    This program was created by Simone Masiero Aka Sora101 on 14 July 2008.
*/ 
#include <pspkernel.h>
#include <pspdebug.h> 
#include <time.h> 
#include "variabili.c"
#include "disegna.c"
#include "funzioni.c"
#include "tasti.c"

PSP_MODULE_INFO("FaintlessM", 0, 1, 1);



/* Exit callback */
int exit_callback(int arg1, int arg2, void *common) {
          sceKernelExitGame();
          return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp) {
          int cbid;

          cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
          sceKernelRegisterExitCallback(cbid);

          sceKernelSleepThreadCB();

          return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void) {
          int thid = 0;

          thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
          if(thid >= 0) {
                    sceKernelStartThread(thid, 0, 0);
          }

          return thid;
}


int main(){
	 pspDebugScreenInit();//init skermo
	 SetupCallbacks(); 
	 initGraphics();//init grafica
	 time(&lastTime); // per gli fps
	 decrypt(1);
	 initgame();
	 carica();
	 mappa();
	 while(1){	
		 pspDebugScreenSetXY(2,0);
		 sceCtrlReadBufferPositive(&pad, 1); 
		 if ( act == 0 ) {// act 0 = giokio
			 tastimappa();
			 posizionemap();
			 disegnamappa();
			 FPS();
			 if(metodo==0){
				  	 sprintf(fraselivello,"livello:%s",nomeliv[livello]);
					 printTextScreen(5,15,fraselivello,RGB(255,0,0));
			 }else if(metodo==1){
					 scrividbg(5,15,"Attributo: ",attributo);
			  }
		 }else if(act == 1){// act 1 = selezione tile
			 tastitile();
			 disegnatileset();
			 scrividbg(20,260,"Azione Multitile:",mselstate);
	 		 scrividbg(200,260,"Azione Fill: ",fillstate);
			 FPS();
		 }else if(act == 2){ // act 2 = menu
			 tastimenu();
			 blitImageToScreen(0,0,480,272,emptymenu,0,0);
			 printTextScreen(170,optsel*15+102,"-",RGB(255,0,0));
	 		 scrividbg(180,100,"Salva: ",savmap);//0
			 scrividbg(180,115,"Carica: ",carmap);//1
			 scrividbg(180,130,"Metodo: ",metodo);//2
			 scrividbg(180,145,"Mappa Su: ",attbordo[0]);//3
			 scrividbg(180,160,"Mappa Destra: ",attbordo[1]);//4
			 scrividbg(180,175,"Mappa giu: ",attbordo[2]);//5
			 scrividbg(180,190,"Mappa sinistra: ",attbordo[3]);//6
			 scrividbg(180,205,"Tileset: ",attbordo[4]);//7
			 printTextScreen(140,80,"Faintless Map Editor",RGB(255,0,0));
			 FPS();
		 }
		 flipScreen();
		 //12
	}
	sceKernelExitGame();
	return 0;
}
