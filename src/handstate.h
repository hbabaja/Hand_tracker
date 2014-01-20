/**********************************************************
 * Datoteka: handstate.h                                  *
 * Autor: Hrvoje Babaja                                   *
 **********************************************************/

//Mapa za spremanje informacija o stanju (string i bool), string mozemo poslije prikazati u prozoru kamere
map<const char*, bool> state;

//Spremanje dimenzija otvorene ruke
int openHandWidth = -1;
int openHandHeight = -1;

void HandStateCatcher(int width, int height)
{
    //omjer sa otvorenom rukom
    float w = (float)width/(float)openHandWidth;
    float h = (float)height/(float)openHandHeight;



    //stanje otvorene ruke
    if(1.0f - h < 0.23f)
    {
        state["Open Hand"] = true;
    }

    //stanje zatvorene ruke (sake)
    if(1.0f - h > 0.23f && 1.0f - w > 0.3f)
    {
        state["Fist"] = true;
    }

    //stanje kada je na slici jedan/dva/tri prsta
    if(1.0f - h > 0.23f && 1.0f - w < 0.3f)
    {
        state["Finger Out"] = true;
    }
}
