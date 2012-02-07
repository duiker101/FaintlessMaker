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

PSP_MODULE_INFO("Faintless", 0, 1, 1);



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
	 carica(); // carica
	 decrypt(carmap);
	 mappa();
	 while(1){	// ciclo principale
		 pspDebugScreenSetXY(0,0);
		 sceCtrlReadBufferPositive(&pad, 1); 
		 if ( act == 0 ) {// act 0 = giokio
			 tasti();
			 attributi();
			 posizionemapscroll();
			 disegnamappa();
			 FPS();
		 }
		 flipScreen();
		 //123456789012345678901234567890123
	}
	sceKernelExitGame();
	return 0;
}
