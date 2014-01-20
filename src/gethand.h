/**********************************************************
 * Datoteka: gethand.h                                    *
 * Autor: Hrvoje Babaja                                   *
 **********************************************************/

//funkcija koja pronalazi ruku u slici koristeci vec izradeni profil
void getHand(IplImage* img)
{
    set<HighlightPixel,lthp> handPixels;

    //varijable potrebne za paralelizaciju ove funkcije
    int nthreads, tid;

#ifdef DISPLAYFPS
    clock_t init, final;
    init = clock();
#endif


    //paralelni segment
#pragma omp parallel num_threads(NUMTHREADS) private(nthreads, tid)
    {
        //dobavi broj niti
        nthreads = omp_get_num_threads();
        //dobavi id trenutne niti
        tid = omp_get_thread_num();

        //iteracija kroz svaki red
        for(int i = tid * (img->height - 1)/nthreads; i < (tid+1) * (img->height - 1)/nthreads; i++)
        {
            //iteracija kroz svaki piksel u 'i' redu
            for(int j = 10; j < img->width -10; j++)
            {
                //dohvacanje boje tog piksela
                CvScalar color = cvGet2D(img,i,j);

                //prodi kroz svaki element u profilu ruke
                for(int x = 0; x < PROFILE_SIZE; x++)
                {
                    //usporedi piksel s elementom iz profila ruke
                    if(compareColor(color,profile[x],15))
                    {
                        //selektiraj piksel
                        cvSet2D(img,i,j,selectX);
                        HighlightPixel p;
                        p.i = i;
                        p.j = j;

                        //kriticni dio, ne smiju threadovi u isto vrijeme pristupiti
#pragma omp critical
                        {
                        handPixels.insert(p);
                        }

                        break;
                    }
                }
            }
        }
    }


    //inicijalizacija varijabli potrebnih u sljedecoj iteraciji
    int highestY = -1;
    int lowestY = -1;
    int highestX = -1;
    int lowestX = -1;

    //iteracija kroz sve piksele, pronalazak sume, najvise tocke i najnize tocke
    for(set<HighlightPixel,lthp>::iterator it = handPixels.begin(); it != handPixels.end(); it++)
    {
        if(highestY == -1 || (*it).j > highestY)
        {
            highestY = (*it).j;
        }
        if(lowestY == -1 || (*it).j < lowestY)
        {
            lowestY = (*it).j;
        }
        if(highestX == -1 || (*it).i > highestX)
        {
            highestX = (*it).i;
        }
        if(lowestX == -1 || (*it).i < lowestX)
        {
            lowestX = (*it).i;
        }
    }

    //crta mali krug u centru ruke
    //cvCircle(img,cvPoint((highestY-lowestY)/2 + lowestY,highestX-lowestX),5,cvScalar(0, 0, 255, 0),2,8,0);

    cvCircle(img,cvPoint((highestY-lowestY)/2 + lowestY,highestX - lowestX),5,cvScalar(0, 0, 255, 0),2,8,0);

    //crta pravokutnik kao granice ruke
    cvRectangle(img,cvPoint(lowestY, lowestX),cvPoint(highestY, highestX),cvScalar(0, 0, 255, 0),1, 8, 0);


    if(openHandWidth == -1)
    {
        openHandWidth = highestX - lowestX;
    }
    if(openHandHeight == -1)
    {
        openHandHeight = highestY - lowestY;
    }

    //postavlja sva stanja u false
    for (map<const char*,bool>::iterator it=state.begin() ; it != state.end(); it++ )
    {
        (*it).second = false;
    }

    //hvata novo stanje
    HandStateCatcher(highestX - lowestX,highestY - lowestY);

    //hvata definirane pokrete
    HandGestureCatcher((highestY-lowestY)/2 + lowestY,highestX-lowestX);

    #ifdef DISPLAYFPS
        final=clock();

        fps.push_back( 1/ ((double)(final-init) / (double)(CLOCKS_PER_SEC)) );

        double sum = 0;
        for(list<double>::iterator it = fps.begin(); it != fps.end(); it++)
        {
            sum += (*it);
        }

        cout << "Average FPS is " << sum/fps.size()<<endl;

    #endif

    //prikazuje trenutno stanje u prozoru kamere
    int i = 0;
    for (map<const char*,bool>::iterator it=state.begin() ; it != state.end(); it++ )
    {
        if((*it).second == true)
        {
            cvPutText (img,(*it).first,cvPoint(0,i*20+20), &font, cvScalar(255,255,0));
            ++i;
        }
    }

}
