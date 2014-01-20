/**********************************************************
 * Datoteka: defs.h                                       *
 * Autor: Hrvoje Babaja                                   *
 **********************************************************/

//Velicina profila ruke
#define PROFILE_SIZE 50

//#define DISPLAYFPS

//Broj jezgri procesora (toliko cemo threadova paralelno izvrsavati)
#define NUMTHREADS 4

//širina i visina kamere
#define CAMINPUTWIDTH 320
#define CAMINPUTHEIGHT 240

//Broj starih frame-ova koji ce se provjeravati kod svakog novog
#define FRAMESTOBACKTRACK 5

#define LEFTMOUSEBTN 1
#define RIGHTMOUSEBTN 3

#include <queue>
#include <list>
#include <map>
#include <set>
#include <iostream>
#include <ctime>

//Omogucava paralelizaciju u izvrsavanju nekih dijelova programa
#include <omp.h>

//opencv biblioteke
#include <opencv/cv.h>
#include <opencv/cvaux.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//X11 biblioteke
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>

using namespace std;

//Struktura za pohranu podataka o pikselu
struct Pixel
{
    int x;
    int y;
    CvScalar color;
};


//Struktura za pohranu piksela bez podataka o boji
struct HighlightPixel
{
    int i;
    int j;
    bool operator == (HighlightPixel p1)
    {
        return i == p1.i && j == p1.j;
    }
};

//operator za usporeðivanje dvaju piksela
struct lthp
{
  bool operator()(HighlightPixel s1, HighlightPixel s2) const
  {
	  return (s1.i*800 + s1.j) < (s2.i*1000 + s2.j);
  }
};

//Funkcija za usporeðivanje CVScalar-a sa statièkim thresholdom
bool compareColor(CvScalar first, CvScalar second)
{
    int threshold = 15;
    return ( (abs(first.val[0] - second.val[0]) < threshold)  );
}

//Funkcija za usporeðivanje CVScalara sa dinamièkim thresholdom
bool compareColor(CvScalar first, CvScalar second, int threshold)
{
    return ( (abs(first.val[0] - second.val[0]) < threshold) && (abs(first.val[1] - second.val[1]) < threshold)  );
}

//'<' operator za CvScalare
struct ltstr
{
  bool operator()(CvScalar s1, CvScalar s2) const
  {
	  return (s1.val[0]*0.3 + s1.val[2]*0.59 + s1.val[3]*0.11) < (s2.val[0]*0.3 + s2.val[2]*0.59 + s2.val[3]*0.11);
  }
};



#ifdef DISPLAYFPS
//prosjecni frame per second
list<double> fps;
#endif

//Podatak o tome da li je program u stadiju izrade profila ruke, ili u radu
bool profileMaking;

CvScalar selectX;

//prikazujemo na prozoru kamere
CvFont font;

//Set za spremanje oznacenih piksela
set<HighlightPixel,lthp> highlightPixel;

//Profil ruke
CvScalar profile[PROFILE_SIZE];

//Mapa za spremanje frekvencija
map<CvScalar,int,ltstr> frequencies;


