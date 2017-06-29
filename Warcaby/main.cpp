// Gra Warcaby z modyfikowalna plansza. Jej dodatkowym zalozeniem bylo unikanie podejscia obiektowego.
// Poczatkowo byla dedykowana dla systemu Windows XP. Obecnie dziala rowniez na najnowszych systemach operacyjnych.

// Jesli gra nie wyswietla sie prawidlowo, warto pogrzebac w opcjach wlasciwosci konsoli i np. zmniejszyc czcionke
// lub wylaczyc w konsoli tryb wstawiania i tryb szykiej edycji
// Gra byla testowana na ekranie 1024x 1280
#include <iostream>
#include <cstdlib>
#include <windows.h>

#define REP(x) for(int j= 0; j< x; j++)
#define REP2(a, x) for(int a= 0; a< x; a++)
using namespace std;

// stale do dowolnej modyfikacji( zwlaszcza 2 pierwsze wiersze)
const short WYSOKOSC= 6,   SZEROKOSC= 12;
const short ILOSC_RZEDOW_PION_BIALYCH= 2;

const short WYSOKOSC_POLA= 9,   SZEROKOSC_POLA= 9;
const short WIELKOSC_PIONKA= 9;		// UWAGA!  Powi¹zana z wielkosci¹ pola ... Mniejsze lub równe
const short POCZATEK_PLANSZY_X= 5,   POCZATEK_PLANSZY_Y= 2;

const short KOORDYNATY_KOLOR= 15;
const short BIALY_KOLOR= 11;
const short CZARNY_KOLOR= 12;
const short POLE_KOLOR_Z= 2;		// zielony
const short POLE_KOLOR_S= 7;		// szary
const short ZAZNACZ_KOLOR= 14;		// kolor zaznaczenia    14 == z³oty

const short PASEK_OKNA= 26;

short __FOREGROUND= 7, __BACKGROUND= 0;			// obecnie ustawione t³o i kolor tekstu

struct strip{
	short pocz : 8;			// od 1 do WIELKOSC_PIONKA
	short dl : 8;
};

// *********************************************************************************************************************
// Funkcje narzedziowe *****************************************************************************************************************
inline void gotoxy(const short &x, const short &y)
{
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){ x-1, y-1 } );
}

void textcolor(const short &color)
{
  __FOREGROUND = color;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color + (__BACKGROUND << 4));		// parametr + obecne tlo * 16
}

void textbackground(const short &color)
{
  __BACKGROUND = color;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), __FOREGROUND + (color << 4));		// obecny kolor tekstu + parametr * 16
}

void writeXY( const short &x, const short &y, const char &znak){
		gotoxy( x, y);
		cout<< znak;
}

// Dwie funkcje pomocnicze do funkcji odznacz
void linia( const int color, const int number){
	
	 	textcolor( color );			 
		REP(number)
			  cout<< "\333";
}

void linia_i_wspolrzedne( const int color, const int x, const int y, const int number){
	
	 	textcolor( color );			 
		gotoxy( x, y );
		REP(number)
			  cout<< "\333";
}

// Funkcje programowe *************************************************************************************************************
// ****************************************************************************************************************************
// Funkcja rysujaca wspolrzedne obok planszy
void koordynaty(const short &p)
{
	textcolor(p);
	
	for(short z=0; z< WYSOKOSC; z++)		// w dol			
			writeXY( POCZATEK_PLANSZY_X - 2, POCZATEK_PLANSZY_Y+ z*WYSOKOSC_POLA+ WYSOKOSC_POLA/ 2, 48+ WYSOKOSC- z);			//char 48+ 8-z    48 == '0'
	for(short z=0; z< SZEROKOSC; z++)		// w prawo
			writeXY( POCZATEK_PLANSZY_X + z*SZEROKOSC_POLA+ SZEROKOSC_POLA/ 2, POCZATEK_PLANSZY_Y+ WYSOKOSC_POLA* WYSOKOSC + 1, 65+ z);			// 65 == 'A'

	textcolor(15);	// bialy
}
	
// Funkcja rysuj¹ca pust¹ planszê
void rysuj_plansze( const short &pozX, const short &pozY, const short &szerokosc_pola, const short &wysokosc_pola, const short &ilosc_x, const short &ilosc_y ){
	  
 	for(short i= 1; i<=ilosc_y; i++)			// polami 8, 7, 6, 5
		  	for (short z=1 ; z<=wysokosc_pola ; z++)			// ka¿dy ma jakas wysokosc czyli powtorzyc kilka razy dla wysokosci jednego pola
		  	{
		  	 		gotoxy( pozX, wysokosc_pola* (i-1)+ z+ pozY- 1);				// wskaz na poczatek
						 	
	 				for (short x=1 ; x<= ilosc_x ; x++){    		// polami A, B, C, D
	 				
							if( !( (i+ x)&1 ) )				// (i+ x) % 2 == 0	 suma szerokosci i wysokosci
								textcolor(POLE_KOLOR_S);
							else
								textcolor(POLE_KOLOR_Z);
								
	 		 		    	for (short a= 1; a<=szerokosc_pola ;a++)  		  
									 cout<<"\333";	
					}
	    	}
}

// Funkcja restartujaca plansze do pozycji za poczatku gry
bool inicjuj_plansze(bool &ruch_bialych, bool &ruch_zmiana, bool &zaznaczylem_figure, char plansza[][SZEROKOSC] ){
	if( WYSOKOSC< (ILOSC_RZEDOW_PION_BIALYCH<<1) )		// za mala plansza nie mozna rozmiescic figur <<1 to *2
		return false;
		
	ruch_bialych= true;
	ruch_zmiana= false;
	zaznaczylem_figure= false;
	
	for(int i= 0; i< WYSOKOSC; i++)
			for(int j= 0; j< SZEROKOSC; j++)
					if( !((i+j)&1) )	// (i+j) %2 == 0  zapelniamy przekatne na ktorych nie odbywa sie gra	
						plansza[i][j]= '0';
					else if( i < ILOSC_RZEDOW_PION_BIALYCH) // jesli odpowiednio na gorze wstawiaj pionki czerw 
						 	 plansza[i][j]= '2';	
						 else if( i>= WYSOKOSC- ILOSC_RZEDOW_PION_BIALYCH )		// na dole pionki przeciwnika
						  	 plansza[i][j]= '1';
						 else 
						 	 plansza[i][j]= '0';	   							
	
	return true;
}

// Funkcja uzupelniajaca tablice wedlug wielkosci pionka
void uzup_strip(strip tab[]){
	int x;
	
	for(int y= 0; y< WIELKOSC_PIONKA; y++){
		x= -WIELKOSC_PIONKA/2;
		
		while(x*x+ (y- WIELKOSC_PIONKA/2)*(y- WIELKOSC_PIONKA/2) > WIELKOSC_PIONKA/2* WIELKOSC_PIONKA/2 && x<= WIELKOSC_PIONKA/2 )
			    x++;
			   
		tab[y].pocz= x+ WIELKOSC_PIONKA/2+ 1;	   
        while(x*x+ (y- WIELKOSC_PIONKA/2)*(y- WIELKOSC_PIONKA/2) <= WIELKOSC_PIONKA/2* WIELKOSC_PIONKA/2 && x<= WIELKOSC_PIONKA/2 )
        	   	x++;
        	   
 	    tab[y].dl= x+ WIELKOSC_PIONKA/2+ 1 - tab[y].pocz;
	}
}

// Funkcja rysujaca pionka
void pionek(const short &x, const short &y, const short &color, const strip tab[]){
	textcolor(color);						// x i y zawiera adres 1 komorki(gorny lewy) w polu
	
	for(int i=0; i< WIELKOSC_PIONKA; i++){
		gotoxy( x- 1+ tab[i].pocz+ (SZEROKOSC_POLA- WIELKOSC_PIONKA)/ 2 , y+ i+ (WYSOKOSC_POLA- WIELKOSC_PIONKA)/2);		// wsp y wysrodkowana
		
		REP(tab[i].dl)
			cout<<"\333";
	}
}

// Funkcja rysujaca damke
void damka(const short &x, const short &y, const short &color, const strip tab[]){
	pionek( x, y, color, tab);
	
	textcolor(14);		// zloty
	
	writeXY(x+ SZEROKOSC_POLA/2, y+ WYSOKOSC_POLA/2- 1, 219);		// 219 to '\333'
	writeXY(x+ SZEROKOSC_POLA/2- 1, y+ WYSOKOSC_POLA/2, 219);
	cout<< "\333\333";
	writeXY(x+ SZEROKOSC_POLA/2, y+ WYSOKOSC_POLA/2+ 1, 219);
}

// Funkcja rysujaca wszystkie figury na planszy
void rysuj_figury( const char plansza[][SZEROKOSC] , const strip tab[] ){
	
	for(short i=1; i<=WYSOKOSC; i++)
			for( short j=1; j<=SZEROKOSC; j++)
				 switch(plansza[i-1][j-1] ){
				 	case '0':			// usun pionka czyli zamaluj go ale kolorem szachownicy
				 		pionek( (j-1)* SZEROKOSC_POLA + POCZATEK_PLANSZY_X, (i-1)* WYSOKOSC_POLA + POCZATEK_PLANSZY_Y,
						  !( (i+ j)&1 )? POLE_KOLOR_S : POLE_KOLOR_Z , tab);		// w zaleznossci od przekatnej wybierz kolor
				 		break;
				 	case '1':		// bialy pionek
				 		pionek( (j-1)* SZEROKOSC_POLA + POCZATEK_PLANSZY_X, (i-1)* WYSOKOSC_POLA + POCZATEK_PLANSZY_Y, BIALY_KOLOR, tab);
				 		break;
				 	case '2':		// czarny pionek
				 		pionek( (j-1)* SZEROKOSC_POLA + POCZATEK_PLANSZY_X, (i-1)* WYSOKOSC_POLA + POCZATEK_PLANSZY_Y, CZARNY_KOLOR, tab);
				 		break;
			 		case '3':		// biala dama
			 			damka( (j-1)* SZEROKOSC_POLA + POCZATEK_PLANSZY_X, (i-1)* WYSOKOSC_POLA + POCZATEK_PLANSZY_Y, BIALY_KOLOR, tab);
			 			break;
		 			case '4':		// czarna dama
		 				damka( (j-1)* SZEROKOSC_POLA + POCZATEK_PLANSZY_X, (i-1)* WYSOKOSC_POLA + POCZATEK_PLANSZY_Y, CZARNY_KOLOR, tab);
		 				break;
				 }
}

// Funkcja rysujaca przycisk
void przycisk(int xp, int yp, int dlx, int dly, string napis, bool wlaczony, bool najechany)
	{
		if(wlaczony)
		    textcolor(2);
		else
			textcolor(7);
			
		if(najechany)
			textcolor(14);
				 
		// rysuj obrys ramki
		for(int i=0; i< dly; i++){
			gotoxy(xp, yp+ i);
			REP(dlx)
				cout<< "\333";
		}		
	
	    // wypisz tekst w okienku
		if (wlaczony)
			textcolor(15), textbackground(2);
		else
			textcolor(9), textbackground(7);
			
		if(najechany)
			textbackground(14);
		
		if(najechany && wlaczony)
			textcolor(9);
		
		gotoxy( xp+(dlx- napis.length())/ 2, ((yp<<1) + dly) / 2 );		// yp<<1 znaczy yp * 2
		cout<< napis;
		textbackground(0);
	}
	
//funkcja zaznaczajaca obiekt
void zaznacz(int x, int y, int color)
	{
		textcolor(color);
			
		// gorna i dolna linia zaznaczenie			 
		gotoxy(SZEROKOSC_POLA* (x-1)+ POCZATEK_PLANSZY_X , POCZATEK_PLANSZY_Y+ WYSOKOSC_POLA* (WYSOKOSC - y) );
		REP(SZEROKOSC_POLA)
			  cout<< "\333";
		gotoxy(SZEROKOSC_POLA* (x-1)+ POCZATEK_PLANSZY_X , POCZATEK_PLANSZY_Y+ (WYSOKOSC_POLA)* (WYSOKOSC - y+ 1)- 1 );
		REP(SZEROKOSC_POLA)
			  cout<< "\333";
		
		// linie po bokach
		for(int i= 1; i< WYSOKOSC_POLA- 1; i++)
		{
			writeXY( SZEROKOSC_POLA* (x-1)+ POCZATEK_PLANSZY_X , POCZATEK_PLANSZY_Y+ WYSOKOSC_POLA* (WYSOKOSC - y)+ i, 219);
			writeXY( SZEROKOSC_POLA* x+ POCZATEK_PLANSZY_X- 1, POCZATEK_PLANSZY_Y+ WYSOKOSC_POLA* (WYSOKOSC - y)+ i, 219);
		}
		textcolor(15);
	}

// Funkcja odznaczajaca pole ktora zostawia elementy pionka	
void odznacz(int x, int y, int color, strip tab[])
	 {	
	 	short i= 1;
	 
		// gorna linia odznaczenia ( dwie obok pionka i jeden rysujacy go)
		linia_i_wspolrzedne(POLE_KOLOR_Z, SZEROKOSC_POLA* (x-1)+ POCZATEK_PLANSZY_X , POCZATEK_PLANSZY_Y+ WYSOKOSC_POLA* (WYSOKOSC - y), tab[0].pocz - 1);
		linia(color, tab[0].dl);
		linia(POLE_KOLOR_Z, SZEROKOSC_POLA- tab[0].pocz + 1- tab[0].dl );
		
		// dolna linia odznaczenia ( dwie obok pionka i jeden rysujacy go)
		linia_i_wspolrzedne( POLE_KOLOR_Z, SZEROKOSC_POLA* (x-1)+ POCZATEK_PLANSZY_X , POCZATEK_PLANSZY_Y+ (WYSOKOSC_POLA)* (WYSOKOSC - y+ 1)- 1 , tab[0].pocz - 1 );
		linia( color, tab[0].dl);
  		linia( POLE_KOLOR_Z, SZEROKOSC_POLA- tab[0].pocz + 1- tab[0].dl);
		
		// linie po bokach
		for(i; i< WYSOKOSC_POLA- 1 && tab[i].pocz != 1; i++)
		{
			writeXY( SZEROKOSC_POLA* (x-1)+ POCZATEK_PLANSZY_X , POCZATEK_PLANSZY_Y+ WYSOKOSC_POLA* (WYSOKOSC - y)+ i, 219);
			writeXY( SZEROKOSC_POLA* x+ POCZATEK_PLANSZY_X- 1, POCZATEK_PLANSZY_Y+ WYSOKOSC_POLA* (WYSOKOSC - y)+ i, 219);
		}
		
		textcolor(color);
		for(i; i< WYSOKOSC_POLA- 1 && tab[i].pocz == 1; i++)
		{
			writeXY( SZEROKOSC_POLA* (x-1)+ POCZATEK_PLANSZY_X , POCZATEK_PLANSZY_Y+ WYSOKOSC_POLA* (WYSOKOSC - y)+ i, 219);
			writeXY( SZEROKOSC_POLA* x+ POCZATEK_PLANSZY_X- 1, POCZATEK_PLANSZY_Y+ WYSOKOSC_POLA* (WYSOKOSC - y)+ i, 219);
		}
		
		textcolor( POLE_KOLOR_Z );
		for(i; i< WYSOKOSC_POLA- 1 && tab[i].pocz != 1; i++)
		{
			writeXY( SZEROKOSC_POLA* (x-1)+ POCZATEK_PLANSZY_X , POCZATEK_PLANSZY_Y+ WYSOKOSC_POLA* (WYSOKOSC - y)+ i, 219);
			writeXY( SZEROKOSC_POLA* x+ POCZATEK_PLANSZY_X- 1, POCZATEK_PLANSZY_Y+ WYSOKOSC_POLA* (WYSOKOSC - y)+ i, 219);
		}
		
		textcolor(15);
	}

// funkcja sprawdzajaca czy kliknieto w obszar o wsp. konsoli x i y
bool klikniecie_w_pozycji(short x, short y, short dlx, short dly, int cursorX, int cursorY, RECT okn, COORD rozmiar_cz){
	
	
	if( cursorX > x* rozmiar_cz.X + okn.left- 4 && cursorX < (x+ dlx)* rozmiar_cz.X + okn.left- 4 &&
		cursorY > (y-1)* rozmiar_cz.Y + okn.top+ PASEK_OKNA+ 6 && cursorY < (y-1+ dly)* rozmiar_cz.Y + okn.top+ PASEK_OKNA+ 6 )
				return true;
	return false;						// + 26 na y bo uwzgledniamy pasek na gorze    && y> 376 && y< 412) //97
}

// funkcja zapisujaca przebieg gry
bool zapisz_gre(){
	
	
	return true;
}

// funkcja sprawdza mo¿liwosc bicia przez damke
bool spr_dla_damki2( const int &a, const int &b, const char plansza[][SZEROKOSC], const char &znak1, const char &znak2 ){
	
	if( b < SZEROKOSC- 2 && a > 1 && (plansza[a-1][b+1] == znak1 || plansza[a-1][b+1] == znak2) && plansza[a-2][b+2] == '0' )
	  		 return true;
	  		 	  						  	 
	if( b > 1 && a > 1 && (plansza[a-1][b-1] == znak1 || plansza[a-1][b-1] == znak2) && plansza[a-2][b-2] == '0')
		  	 return true;
					
	if( b > 1 && a < WYSOKOSC- 2 && (plansza[a+1][b-1] == znak1 || plansza[a+1][b-1] == znak2) && plansza[a+2][b-2] == '0')
		  	 return true;
					
	if( b < SZEROKOSC- 2 && a < WYSOKOSC- 2 && (plansza[a+1][b+1] == znak1 || plansza[a+1][b+1] == znak2) && plansza[a+2][b+2] == '0')
		  	 return true;
			   	
	return false;	 	  						  	 
}

// funkcja sprawdzajaca czy gracz ma przymusowe bicie
bool musisz_bic( bool ruch_bialych, const char plansza[][SZEROKOSC]){
	
	for(int a= 0; a< WYSOKOSC; a++)
		for(int b= (a+ 1)&1; b< SZEROKOSC; b+= 2){		// co drugi zaczynamy spr. od 1 kolumny
					
				if(ruch_bialych)
				{
					// dla pionków
					if( plansza[a][b] == '1'){		// jesli wjezdzamy na bialego pionka
					
							if( b > 1)
								if( plansza[a-1][b-1] == '2' || plansza[a-1][b-1] == '4' )
									if( plansza[a-2][b-2] == '0')				  
							  		 	 return true;
							
							if( b < SZEROKOSC-2)
								if( plansza[a-1][b+1] == '2' || plansza[a-1][b+1] == '4' )
									if( plansza[a-2][b+2] == '0')				  
							  		 	 return true;	   
					}
					
					// dla damek
					if( plansza[a][b]== '3' ){
						 if ( spr_dla_damki2( a, b, plansza, '2', '4') )
						 		   return true;			 									 	  
					}
							
				}
				else
				{
					if( plansza[a][b] == '2'){		// jesli wjezdzamy na czerwonego pionka
					
							if( b > 1)
								  if( plansza[a+1][b-1] == '1' || plansza[a+1][b-1] == '3' )
									if( plansza[a+2][b-2] == '0')				  
							  		 	 return true;
							
							if( b < SZEROKOSC-2)
								if( plansza[a+1][b+1] == '1' || plansza[a+1][b+1] == '3' )
									if( plansza[a+2][b+2] == '0')				  
							  		 	 return true;	
					}
					
					// dla damek
					if( plansza[a][b]== '4' ){
						 if ( spr_dla_damki2( a, b, plansza, '1', '3') )
						 		   return true;			 									 	  
					}
				}
				
		}			
	
	return false;
}

// funkcja sprawdza kombinacje dla damki sprawdza czy sa wolne miejsca obok 
bool spr_dla_damki( const int &a, const int &b, const char plansza[][SZEROKOSC] ){
	
	if( b != SZEROKOSC- 1 && a != 0 && plansza[a-1][b+1] == '0')
	  		 return false;
	  		 	  						  	 
	if( b != 0 && a != 0 && plansza[a-1][b-1] == '0')
		  	 return false;
					
	if( b != 0 && a != WYSOKOSC- 1 && plansza[a+1][b-1] == '0')
		  	 return false;
					
	if( b != SZEROKOSC- 1 && a != WYSOKOSC- 1 && plansza[a+1][b+1] == '0')
		  	 return false;
			   	
	return true;	 	  						  	 
}

// funkcja zwroci true jesli zawodnik nie ma mozliwosci ruchu (przegrywa)
bool czy_zablokowany(bool ruch_bialych, const char plansza[][SZEROKOSC]){
	
		for(int a= 0; a< WYSOKOSC; a++)
			for(int b= (a+1)&1; b< SZEROKOSC; b+= 2){		// co drugi zaczynamy spr. od 1 kolumny
						
					if(ruch_bialych)
					{
						// dla pionków
						if( plansza[a][b] == '1'){		// jesli wjezdzamy na bialego pionka
						
								if( b > 0)
									if( plansza[a-1][b-1] == '0' )
								  		 return false;
								
								if( b < SZEROKOSC-1)
									if( plansza[a-1][b+1] == '0' )
									     return false;	   
						}
						
						// dla damek
						if( plansza[a][b]== '3' ){
							 if ( !spr_dla_damki( a, b, plansza)	)
							 		   return false;			 									 	  
						}
								
					}
					else
					{
						if( plansza[a][b] == '2'){		// jesli wjezdzamy na czerwonego pionka
						
								if( b > 0)
									  if( plansza[a+1][b-1] == '0' )
									  	 	return false;
								
								if( b < SZEROKOSC-1)
									  if( plansza[a+1][b+1] == '0' )
									   		return false;
						}
						
						// dla damek
						if( plansza[a][b]== '4' ){
							 if ( !spr_dla_damki( a, b, plansza)	)
							 		   return false;			 									 	  
						}
					}
					
			}			
	
	return true;
}

// funkcja ustawiajaca wielkosc czcionki
void setFontSize(  short &width,  short &height) 
{
	
    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    PCONSOLE_FONT_INFOEX lpFontInfo = new CONSOLE_FONT_INFOEX();
    lpFontInfo->cbSize = sizeof(CONSOLE_FONT_INFOEX);

	// pobierz czcionke z konsoli - bez tego nie dziala
	GetCurrentConsoleFontEx(Handle,0,lpFontInfo);
	 
	// ustaw wielkosc czcionki
 	lpFontInfo->dwFontSize.X = width;
 	lpFontInfo->dwFontSize.Y = height;
    
    SetCurrentConsoleFontEx (Handle, 0, lpFontInfo);
    
    delete lpFontInfo;
}

// funkcja ustawiajaca rozmiar okna i bufora
void setWindow(int Width, int Height) 
{ 
    COORD coord; 
    coord.X = Width; 
    coord.Y = Height; 

    SMALL_RECT Rect; 
    Rect.Top = 0; 
    Rect.Left = 0; 
    Rect.Bottom = Height - 1; 
    Rect.Right = Width - 1; 

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
    SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size 
    SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size 
} 

// funkcja która sprawdza czym mo¿na dalej biæ trzyman¹ figur¹
bool czy_moze_bic(const short &x, const short &y, char plansza[][SZEROKOSC] ){
	
	if( plansza[y][x] == '1' || plansza[y][x] == '3')	// jesli bialy
	{
		// dla pionków
		if( plansza[y][x] == '1'){		// dla bialego pionka
		
				if( x > 1)
					if( plansza[y-1][x-1] == '2' || plansza[y-1][x-1] == '4' )
						if( plansza[y-2][x-2] == '0')				  
				  		 	 return true;
				
				if( x < SZEROKOSC-2)
					if( plansza[y-1][x+1] == '2' || plansza[y-1][x+1] == '4' )
						if( plansza[y-2][x+2] == '0')				  
				  		 	 return true;	   
		}
		
		// dla damek
		if( plansza[y][x]== '3' ){
			 if ( spr_dla_damki2( y, x, plansza, '2', '4') )
			 		   return true;			 									 	  
		}
				
	}
	else
	{
		if( plansza[y][x] == '2'){		// dla czerwonego pionka
		
				if( x > 1)
					  if( plansza[y+1][x-1] == '1' || plansza[y+1][x-1] == '3' )
						if( plansza[y+2][x-2] == '0')				  
				  		 	 return true;
				
				if( x < SZEROKOSC-2)
					if( plansza[y+1][x+1] == '1' || plansza[y+1][x+1] == '3' )
						if( plansza[y+2][x+2] == '0')				  
				  		 	 return true;	
		}
		
		// dla damek
		if( plansza[y][x]== '4' ){
			 if ( spr_dla_damki2( y, x, plansza, '1', '3') )
			 		   return true;			 									 	  
		}
	}
	
	return false;
}


// **********************************************************************************************************************	
// Main function *******************************************************************************************************************
int main(int argc, char** argv) {

	char plansza[ WYSOKOSC ][ SZEROKOSC ];		// 0- puste 1- pion bial 2- pion czarn 3- damka bial 4- damka czarn
	// dla podswietlania przyciskow
	char nr_przycisku= '0';
	bool najechano= false;
	
	int x, y;
	short x_zazn, y_zazn;
	bool koniec_gry= false, kliknieto= false, zazn_koordynaty= true;
	bool ruch_bialych, ruch_zmiana, zaznaczylem_figure;		
	
	// liczba figur
	short l_bialych= ((SZEROKOSC+ 1)>>1)* (((ILOSC_RZEDOW_PION_BIALYCH- 1)>>1) +1) + (SZEROKOSC>>1)* (ILOSC_RZEDOW_PION_BIALYCH>>1) ;
	short l_czarnych= l_bialych;		// ">>1" ozn dzielenie przez 2 bez reszty
		
	const int ODSTEP_PLANSZY_OD_PRZYCISKOW = 20;	
	const int DLUGOSC_STANDARDOWEGO_PRZYCISKU = 20;
	const int PRAWY_MARGINES = 10;
	const int DOLNY_MARGINES = 10;
		
	const int MAX_BUFFOR_SIZE_X = 	POCZATEK_PLANSZY_X+ SZEROKOSC_POLA* SZEROKOSC+ ODSTEP_PLANSZY_OD_PRZYCISKOW +
		 DLUGOSC_STANDARDOWEGO_PRZYCISKU + PRAWY_MARGINES;
	const int MAX_BUFFOR_SIZE_Y = 	POCZATEK_PLANSZY_Y+ WYSOKOSC_POLA* SZEROKOSC+ DOLNY_MARGINES ;
	
	// Zapamietaj w³aœciwoœci okna i czcionki
	CONSOLE_SCREEN_BUFFER_INFO wlOkna;
	CONSOLE_FONT_INFO fontInfo; 
	
	strip tab[WIELKOSC_PIONKA];
		
	POINT cursorPos;
	RECT PozOkna;			// LPRECT PozOkna;  ta struktura nie dziala jesli zbyt duzo zainicjowanych zmiennych
	COORD rozmiar_cz= {6,12};
	
	HWND console = GetConsoleWindow();				//pobranie uchytu konsoli
	
	
	
	SetConsoleTitle("WARCABY");		// funkcja z wincon.h ustawia tytu³ na pasku tytu³owym
	setFontSize(rozmiar_cz.X, rozmiar_cz.Y);		// wielkosc czcionki
  	setWindow( MAX_BUFFOR_SIZE_X, MAX_BUFFOR_SIZE_Y );	// ustaw bufor ekranu konsoli		
	
	ShowWindow(console, SW_MAXIMIZE);		//maksymalizacja tego okna
	
	// wspolrzedne poczatku okna i jego wielkosc
	GetWindowRect(console, &PozOkna);
  	
	// zapamiêtaj wstêpne w³aœciwoœci okna i czcionki
	GetCurrentConsoleFont( console, true, &fontInfo);
    GetConsoleScreenBufferInfo( console, &wlOkna);
	
	
	
    // dzia³ania na strukturach danych
    inicjuj_plansze( ruch_bialych, ruch_zmiana, zaznaczylem_figure, plansza); 
	uzup_strip(tab);		// okresl budowe pionkow
	
    //***********************************************
	// NARYSUJ wszystkie elementy na konsoli		 
	rysuj_plansze( POCZATEK_PLANSZY_X, POCZATEK_PLANSZY_Y, SZEROKOSC_POLA, WYSOKOSC_POLA, SZEROKOSC, WYSOKOSC);			
	rysuj_figury( plansza, tab );
	koordynaty(KOORDYNATY_KOLOR);					// wspolrzedne
	przycisk(MAX_BUFFOR_SIZE_X - PRAWY_MARGINES - DLUGOSC_STANDARDOWEGO_PRZYCISKU, 30, DLUGOSC_STANDARDOWEGO_PRZYCISKU, 5, "Nowa gra", false, false);
	przycisk(MAX_BUFFOR_SIZE_X - PRAWY_MARGINES - DLUGOSC_STANDARDOWEGO_PRZYCISKU, 40, DLUGOSC_STANDARDOWEGO_PRZYCISKU, 3, "Zapisz", false, false);
	przycisk(MAX_BUFFOR_SIZE_X - PRAWY_MARGINES - DLUGOSC_STANDARDOWEGO_PRZYCISKU, 50, DLUGOSC_STANDARDOWEGO_PRZYCISKU, 3, "Koordynaty", true, false);
	przycisk(MAX_BUFFOR_SIZE_X - PRAWY_MARGINES - DLUGOSC_STANDARDOWEGO_PRZYCISKU, 60, DLUGOSC_STANDARDOWEGO_PRZYCISKU, 3, "WYJ\227CIE", false, false);
 
	// g³ówna pêtla programu obslugujaca wykonywanie ruchów do koñca gry	 		
	do
	{
		// wyswietl informacje o wsp. kursora
	   	GetCursorPos(&cursorPos);
		x = cursorPos.x;			// bez tych pomocniczych zmiennych program sie wiesza
		y = cursorPos.y;			// bo nie powinnismy ruszac zmiennej cursorPos
		
		// W ifie obsluga podswietlen przyciskow
		if(!najechano){
			nr_przycisku='0';		// wyzeruj przycisk bez tego czasem pojawiaja sie bugi
			
			if(klikniecie_w_pozycji(POCZATEK_PLANSZY_X+ SZEROKOSC_POLA* SZEROKOSC+ 20, 30, 20, 5 , x, y, PozOkna, rozmiar_cz) )
				  nr_przycisku= '1', przycisk(POCZATEK_PLANSZY_X+ SZEROKOSC_POLA* SZEROKOSC+ 20, 30, 20, 5, "Nowa gra", false, true);
			
			if(klikniecie_w_pozycji(POCZATEK_PLANSZY_X+ SZEROKOSC_POLA* SZEROKOSC+ 20, 40, 20, 3 , x, y, PozOkna, rozmiar_cz) )
				  nr_przycisku= '2', przycisk(POCZATEK_PLANSZY_X+ SZEROKOSC_POLA* SZEROKOSC+ 20, 40, 20, 3, "Zapisz", false, true);	
				  									
			if(klikniecie_w_pozycji(POCZATEK_PLANSZY_X+ SZEROKOSC_POLA* SZEROKOSC+ 20, 50, 20, 3, x, y, PozOkna, rozmiar_cz) )
				  nr_przycisku= '3', przycisk(POCZATEK_PLANSZY_X+ SZEROKOSC_POLA* SZEROKOSC+ 20, 50, 20, 3, "Koordynaty", true, true);
				  																				
			if(klikniecie_w_pozycji(POCZATEK_PLANSZY_X+ SZEROKOSC_POLA* SZEROKOSC+ 20, 60, 20, 3, x, y, PozOkna, rozmiar_cz) )
				  nr_przycisku= '4', przycisk(POCZATEK_PLANSZY_X+ SZEROKOSC_POLA* SZEROKOSC+ 20, 60, 20, 3, "WYJ\227CIE", false, true);
			
			if( nr_przycisku != '0' )
				  	najechano= true;  
		}
		else{
			switch(nr_przycisku){
				case '1':
					if(!klikniecie_w_pozycji(POCZATEK_PLANSZY_X+ SZEROKOSC_POLA* SZEROKOSC+ 20, 30, 20, 5 , x, y, PozOkna, rozmiar_cz) )
							najechano= false, przycisk(POCZATEK_PLANSZY_X+ SZEROKOSC_POLA* SZEROKOSC+ 20, 30, 20, 5, "Nowa gra", false, false);									
					
					break;
				case '2':
					if(!klikniecie_w_pozycji(POCZATEK_PLANSZY_X+ SZEROKOSC_POLA* SZEROKOSC+ 20, 40, 20, 3 , x, y, PozOkna, rozmiar_cz) )
							najechano= false, przycisk(POCZATEK_PLANSZY_X+ SZEROKOSC_POLA* SZEROKOSC+ 20, 40, 20, 3, "Zapisz", false, false);			
					
					break;
				case '3':
					if(!klikniecie_w_pozycji(POCZATEK_PLANSZY_X+ SZEROKOSC_POLA* SZEROKOSC+ 20, 50, 20, 3, x, y, PozOkna, rozmiar_cz) )
							najechano= false, przycisk(POCZATEK_PLANSZY_X+ SZEROKOSC_POLA* SZEROKOSC+ 20, 50, 20, 3, "Koordynaty", zazn_koordynaty, false);
					
					break;
				case '4':
					if(!klikniecie_w_pozycji(POCZATEK_PLANSZY_X+ SZEROKOSC_POLA* SZEROKOSC+ 20, 60, 20, 3, x, y, PozOkna, rozmiar_cz) )
							najechano= false, przycisk(POCZATEK_PLANSZY_X+ SZEROKOSC_POLA* SZEROKOSC+ 20, 60, 20, 3, "WYJ\227CIE", false, false);
					
					break;	
				
			}
		}
		 			
		// OBsLUGA WSZELKICH ZDARZEN ( Jakiekolwiek klikniecie myszk¹ ) ************************************************
		// *************************************************************************************************************
		if(kliknieto && !HIBYTE( GetKeyState( VK_LBUTTON ) ) ){	 		 // jesli puszczono lewy przycisk myszy
	  	    
			GetWindowRect(console, &PozOkna);		// pobierz informacje o wsp. okna
				  
	  	    // PRZYCISK WYJSCIE
			if(klikniecie_w_pozycji(POCZATEK_PLANSZY_X+ SZEROKOSC_POLA* SZEROKOSC+ 20, 60, 20, 3 , x, y, PozOkna, rozmiar_cz) )
				  koniec_gry= true;
			
			// SZACHOWNICA
			if(klikniecie_w_pozycji(POCZATEK_PLANSZY_X, POCZATEK_PLANSZY_Y, SZEROKOSC_POLA* SZEROKOSC, WYSOKOSC_POLA* WYSOKOSC , x, y, PozOkna, rozmiar_cz) ){
			  	
				// przekonwertuj na wsp. szachownicy klikniecia
			  	x= 1+ ( x- PozOkna.left- POCZATEK_PLANSZY_X* rozmiar_cz.X + 2)/ (SZEROKOSC_POLA* rozmiar_cz.X);
			  	y= WYSOKOSC- (y- PozOkna.top- POCZATEK_PLANSZY_Y* rozmiar_cz.Y - 20 )/ (WYSOKOSC_POLA* rozmiar_cz.Y );
			  	
			  	// jesli nic nie zaznaczono
			  	if( !zaznaczylem_figure){			
			  		  if( ruch_bialych ){		// dla bialych
			  		  	  if(plansza[WYSOKOSC- y][x- 1] == '1' || plansza[WYSOKOSC- y][x- 1] == '3'){
							    zaznacz(x,y,ZAZNACZ_KOLOR); 	
				  		  	    zaznaczylem_figure= true;	
				  		  	    x_zazn= x;
				  		  	    y_zazn= y;
			  			  }
			  		  }
			  		  else{						// dla czerwonych
			  		  	   if(plansza[WYSOKOSC- y][x- 1] == '2' || plansza[WYSOKOSC- y][x- 1] == '4'){
							    zaznacz(x,y,ZAZNACZ_KOLOR); 	
					  	  	    zaznaczylem_figure= true;	
					  	  	  	x_zazn= x;
					  		  	y_zazn= y;
			  			   }
			  		  }
			    }
			    
			    // po zaznaczeniu figury  ************************************************************
			    // TUTAJ PODEJMUJEMY DECYZJE CZY I GDZIE PRZESUWAMY NASZA FIGURE  ********************
			    else
				{		
					if( musisz_bic( ruch_bialych, plansza) ){
							
							// jesli kliknieto w prawdopodobnym miejscu bicia:   puste miejsce i odleglosc 2		
							if( plansza[WYSOKOSC- y][x- 1] == '0' && abs(y- y_zazn) == 2 && abs(x- x_zazn) == 2){
									
									// czy obok stoi cos przeciwnego koloru			  
									if( (plansza[WYSOKOSC- y_zazn][x_zazn- 1] == '1'  ||  plansza[WYSOKOSC- y_zazn][x_zazn- 1] == '3') &&
										(plansza[WYSOKOSC- (y_zazn+y)/2][(x+ x_zazn)/2 - 1] == '2'  ||  plansza[WYSOKOSC- (y_zazn+y)/2][(x+ x_zazn)/2- 1] == '4') || 
										(plansza[WYSOKOSC- y_zazn][x_zazn- 1] == '2'  ||  plansza[WYSOKOSC- y_zazn][x_zazn- 1] == '4') &&
										(plansza[WYSOKOSC- (y_zazn+y)/2][(x+ x_zazn)/2- 1] == '1'  ||  plansza[WYSOKOSC- (y_zazn+y)/2][(x+ x_zazn)/2- 1] == '3')  ){
										
												
											// Jesli zaznaczono ktor¹s z damek													 
										   	if( plansza[WYSOKOSC- y_zazn][x_zazn- 1] == '3' || plansza[WYSOKOSC- y_zazn][x_zazn- 1] == '4'){
												    		
													// usun dwa pola	
									    			plansza[WYSOKOSC- y_zazn][x_zazn- 1] = '0';
									    			plansza[WYSOKOSC- (y+y_zazn)/2][(x+x_zazn)/2- 1] = '0';
									    			
									    			//postaw bialego lub czarnego oraz zmniejsz licznik
									    			if( ruch_bialych){
									    				plansza[WYSOKOSC- y][x- 1] = '3';
									    				l_czarnych--;
									    			}
									    			else
													{
									    				plansza[WYSOKOSC- y][x- 1] = '4';
									    				l_bialych--;
									    			}
									    			
									    			zaznacz(x_zazn,y_zazn, POLE_KOLOR_Z); 	// ramka w kolorze tla
													
													// jesli nie ma wiecej bic przekasz ruch
													if( czy_moze_bic(x- 1, WYSOKOSC- y, plansza ) ){
														
														zaznaczylem_figure= false;	
											  	  	  	rysuj_figury( plansza, tab );
													}else
													{
														ruch_zmiana= true;
													}	
										    	
						  			    	}															 
											else if( ruch_bialych ) {
							    			
					 						    // ruch czerwonych  if klikniecie w gorna czesc
									    		if( y == y_zazn+2){
										    			
														// jesli nie osiagnieto pola promocji  if( y != WYSOKOSC )
														plansza[WYSOKOSC- y][x- 1] = (y- WYSOKOSC) ? '1' : '3';
										    			plansza[WYSOKOSC- y_zazn][x_zazn- 1] = '0';
										    			
										    			// usun czarnego
										    			plansza[WYSOKOSC- (y+y_zazn)/2][(x+x_zazn)/2- 1] = '0';
										    			l_czarnych--;
										    			
										    			zaznacz(x_zazn,y_zazn, POLE_KOLOR_Z); 	// ramka w kolorze tla
														
														// jesli nie ma wiecej bic przekasz ruch
														if( czy_moze_bic(x- 1, WYSOKOSC- y, plansza ) ){
															
											  		  			 zaznaczylem_figure= false;	
												  	  	    	 rysuj_figury( plansza, tab );
														}else
														{
															ruch_zmiana= true;
														}	
									    		}
										    }
											else	// nie musimy nawet sprawdzac przypadkow z brzegow bo warunkiem koniecznym jest klik w szachownice		
											{
												// ruch czerwonych  if klikniecie w dolna czesc
												if( y == y_zazn-2){
											    		
											    		// jesli nie osiagnieto pola promocji   if ( y == 1)
														plansza[WYSOKOSC- y][x- 1] = (y- 1) ? '2' : '4';				
											    		plansza[WYSOKOSC- y_zazn][x_zazn- 1] = '0';
											    		
											    		// usun bialego
										    			plansza[WYSOKOSC- (y+y_zazn)/2][(x+x_zazn)/2- 1] = '0';
										    			l_bialych--;
										    			
											    		zaznacz(x_zazn,y_zazn, POLE_KOLOR_Z); 	// ramka w kolorze tla
														
														// jesli nie ma wiecej bic przekasz ruch
														if( czy_moze_bic(x- 1, WYSOKOSC- y, plansza ) ){
															
											  		  		zaznaczylem_figure= false;	
												  	  	  	rysuj_figury( plansza, tab );
														}else{
															ruch_zmiana= true;
														}	
												}			  
											}
										}
							}		
					}	// Sprawdzamy czy kliknieto na skos w lewo lub w prawo i czy jest pole wolne
					else if( plansza[WYSOKOSC- y][x- 1] == '0' && abs(y- y_zazn) == 1 && abs(x- x_zazn) == 1 ){		    	
						
						   		// Jesli zaznaczono ktor¹s z damek													 
						   	if(plansza[WYSOKOSC- y_zazn][x_zazn- 1] == '3' || plansza[WYSOKOSC- y_zazn][x_zazn- 1] == '4'){
								    		
											// przestaw, odznacz zaznaczenie i ustaw flage	
							    			plansza[WYSOKOSC- y_zazn][x_zazn- 1] = '0';
							    			plansza[WYSOKOSC- y][x- 1] = ruch_bialych? '3': '4';
							    			zaznacz(x_zazn,y_zazn, POLE_KOLOR_Z); 	// ramka w kolorze tla
											
											ruch_zmiana= true;
						    	
		  			    	}															 
							else if( ruch_bialych ) {
			    			
	 						    // ruch czerwonych  if klikniecie w gorna czesc
					    		if( y == y_zazn+1){
						    			
										// jesli nie osiagnieto pola promocji  if( y != WYSOKOSC )
										plansza[WYSOKOSC- y][x- 1] = (y- WYSOKOSC) ? '1' : '3';
						    			plansza[WYSOKOSC- y_zazn][x_zazn- 1] = '0';
						    			zaznacz(x_zazn,y_zazn, POLE_KOLOR_Z); 	// ramka w kolorze tla
										
										ruch_zmiana= true;
					    		}
						    }
							else	// nie musimy nawet sprawdzac przypadkow z brzegow bo warunkiem koniecznym jest klik w szachownice		
							{
								// ruch czerwonych  if klikniecie w dolna czesc
								if( y == y_zazn-1){
							    		
							    		// jesli nie osiagnieto pola promocji   if ( y == 1)
										plansza[WYSOKOSC- y][x- 1] = (y- 1) ? '2' : '4';				
							    		plansza[WYSOKOSC- y_zazn][x_zazn- 1] = '0';
							    		zaznacz(x_zazn,y_zazn, POLE_KOLOR_Z); 	// ramka w kolorze tla
											
										ruch_zmiana= true;
						    	}	
							}
					}				
		    		
					
					// jesli znowu na niego kliknieto , niezaleznie od przymusu bicia
		  		  	if( x == x_zazn && y == y_zazn ){	
		  		  	
		  		  		// ODZNACZENIE figury jesci pionek wielki jak pole - inaczej go wymazujemy
						if( WIELKOSC_PIONKA < WYSOKOSC_POLA )	
		  		  			zaznacz(x_zazn, y_zazn, POLE_KOLOR_Z); 	// ramka
		  		  		else
							odznacz(x_zazn, y_zazn, ruch_bialych? BIALY_KOLOR: CZARNY_KOLOR, tab);
							
								
		  		  	  	zaznaczylem_figure= false;
		  		  	}  	
			    }
			}
			
			// klikniecie w Nowa gra  
			if(klikniecie_w_pozycji(POCZATEK_PLANSZY_X+ SZEROKOSC_POLA* SZEROKOSC+ 20, 30, 20, 5 , x, y, PozOkna, rozmiar_cz) ){
				
				// jesli jakas figura zostala zaznaczona trzeba ja najpierw odznaczyc
				if(zaznaczylem_figure){
					if( WIELKOSC_PIONKA < WYSOKOSC_POLA )	
		  		  		   zaznacz(x_zazn, y_zazn, POLE_KOLOR_Z); 	// ramka
		  		  	else
						   odznacz(x_zazn, y_zazn, ruch_bialych? BIALY_KOLOR: CZARNY_KOLOR, tab);
				}
				
				inicjuj_plansze( ruch_bialych, ruch_zmiana, zaznaczylem_figure, plansza);
				rysuj_figury( plansza, tab );
				
				// reset liczba figur
				l_bialych= ((SZEROKOSC+ 1)>>1)* (((ILOSC_RZEDOW_PION_BIALYCH- 1)>>1) +1) + (SZEROKOSC>>1)* (ILOSC_RZEDOW_PION_BIALYCH>>1) ;
				l_czarnych= l_bialych;	
			}
			 
			// klikniecie w zapisz  
			if(klikniecie_w_pozycji(POCZATEK_PLANSZY_X+ SZEROKOSC_POLA* SZEROKOSC+ 20, 40, 20, 3, x, y, PozOkna, rozmiar_cz) )
				  zapisz_gre();
				  
			// klikniecie w Koordynaty
			if(klikniecie_w_pozycji(POCZATEK_PLANSZY_X+ SZEROKOSC_POLA* SZEROKOSC+ 20, 50, 20, 3, x, y, PozOkna, rozmiar_cz) ){
				koordynaty( zazn_koordynaty?0:KOORDYNATY_KOLOR );
				zazn_koordynaty= !zazn_koordynaty ;
				przycisk(POCZATEK_PLANSZY_X+ SZEROKOSC_POLA* SZEROKOSC+ 20, 50, 20, 3, "Koordynaty", zazn_koordynaty, true);
			}
				  
			  
			  
			// Jesli ZROBIONO POSUNIECIE  
			if( ruch_zmiana){
				rysuj_figury( plansza, tab );
				zaznaczylem_figure= false;
				ruch_bialych= !ruch_bialych;
				
				// jesli po zmianie ruchu przeciwnik nie moze wykonac posuniecia( jest zablokowany, brak figur)
				if( czy_zablokowany( ruch_bialych, plansza) || !(l_bialych) || !(l_czarnych ) ){
					
					// Przegrana bia³ych
					if(ruch_bialych){
						if( MessageBox( console, "Wygraly Czarne. Czy zapisaæ?", "Koniec gry", MB_OKCANCEL) == MB_OK )
								 zapisz_gre();
					}
					else{
						if( MessageBox( console, "Wygraly Bia³e. Czy zapisaæ?", "Koniec gry", MB_OKCANCEL) == MB_OK )
								 zapisz_gre();	
					}
					
					// Rozpocznij now¹ grê
					inicjuj_plansze( ruch_bialych, ruch_zmiana, zaznaczylem_figure, plansza);
					rysuj_figury( plansza, tab );
					
					// rest liczbe figur
					l_bialych= ((SZEROKOSC+ 1)>>1)* (((ILOSC_RZEDOW_PION_BIALYCH- 1)>>1) +1) + (SZEROKOSC>>1)* (ILOSC_RZEDOW_PION_BIALYCH>>1) ;
					l_czarnych= l_bialych;
					
				}
					
					
				// zablokuj wywolywanie tego po ka¿dorazowym kliknieciu 
				ruch_zmiana= false;
			}  
			
			// przelacz flage
			kliknieto= false;	
		}
		
		if(HIBYTE( GetKeyState( VK_LBUTTON ) ) )	// jesli trzymany lewy przycisk myszy wlacz flage
			kliknieto= true;
		else
			kliknieto= false;
		Sleep(16);									// poczekaj przynajmniej 16 milisekund
	}while( !koniec_gry ); 
	
	setWindow( wlOkna.dwSize.X, wlOkna.dwSize.Y);
	setFontSize(fontInfo.dwFontSize.X, fontInfo.dwFontSize.Y);
		
		
	return 0;
}
