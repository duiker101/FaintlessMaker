#include <time.h> 
#include <png.h>
#include "graphics.h" 

#define printf pspDebugScreenPrintf
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y)) 
#define RGB(r, g, b) ((r)|((g)<<8)|((b)<<16))

//variabili di gioco
int act = 0;
int vel=16;
int unita = 16;

//DEBUG

//variabili di skermo 

int skernh=272;
int skernw=480;

int scrollx=0;
int scrolly=0;

int actvscx=240;
int actvscy=128;

int tilexskx=30;
int tilexsky=17;

int starttx=0;
int startty=0;

int bordd=464;//da cambiare in caso di cambio unita
int bordg=256;//da cambiare in caso di cambio unita

int curposy=0;
int curposx=0;

int tilecurposy=0;
int tilecurposx=0;

//Variabili x FPS
static char strFrameRate[50] = {0};
static float framesPerSecond = 0.0f; // prende gli fps
time_t lastTime;

//contatore x camminata
clock_t laststep;
float stepvel = 75000.0f;

//Variabili x sckermo
int rosso= RGB(255,0,0);


//tmpi x bottoni
float trivel = 150000.0f;
clock_t lastcross;
float cross = 100000.0f;
clock_t lastrl;
float rl = 150000.0f;

//Variabil x mappa
Image* terra;
Image* eroe;
Image* tile;
int actmap = 0;


int tilesetw=30;
int tileseth=16;

int attbordo[10];

//variabili x il menu
int optsel=0;
int savmap=1;
int carmap=1;

int livello=0;

int attributo=0;//attributo
int valattrib=0;//valore dell'attriburto
int attval=0;//per scegliere quale scorrere

char nomeliv[4][120];
char fraselivello[150];

int metodo=0;

//variabili x tileset menu
Image* tileset;
Image* cursore;
Image* menubkg;
Image* emptymenu;

int selecttile=0;
int selecttilex=0;
int selecttiley=0;
int tempseltile=0;

//funzioni x il caricamento
//char *KEY = "xq,cj8h4k%zxcvbnm&*2my7d7^%(*OlkjhnbgvcxJNfdyhY%sdkluqwertyuiopytre@$%^&*)IvclkjhgfdergbTR$HY%@&I*O(DO*";
char *KEY = "xq,cj";

int mappe[10][1][34][60][7];

char ris[100000];
char ris2[100000];
char lineay[35][15000];
char lineax[60][10000];


char valorimappa[1][150000];
char attributi[100];

char delimatt[] = "!";
char *resultatt = NULL;

char delimval[] = "&";
char *resultval = NULL;

char delimy[] = "$";
char *resulty = NULL;

char delimx[] = "#";
char *resultx = NULL;

char delima[] = "|";
char *resulta = NULL;

//variabili per multiselezione
int mselx;//coordina del blocco d'inizio e finale
int mselx1;
int msely;
int msely1;
int mselw;//larghezza ed altezza del blocco
int mselh;
int mselstate;// se bisogna selezionare il punto iniziale o finale
int msel; //se il blocco è pronto
int mselsel;

//variabili per fill
int fillx;
int filly;
int fillh;
int fillw;
int fillstate;
int fill;

//funzioni x il salvataggio
char totale[100000];
char totalexor[100000];
char totali[500000];


//variabili giocatore
int playerx = 0;
int playery = 0;
int playermov = 1;
int playerdir = 2;
int posx = 0;
int posy = 0;
