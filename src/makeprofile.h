/**********************************************************
 * Datoteka: makeprofile.h                                *
 * Autor: Hrvoje Babaja                                   *
 **********************************************************/

//funkcija potrebna za olaksanje sortiranja frekvencija
bool compare_frequencies(CvScalar first, CvScalar second)
{
    return frequencies[first] > frequencies[second];
}

//funkcija koja provjerava je li piksel oznacen
/*bool contains(HighlightPixel p)
{
	bool returnVal = false;

	set<HighlightPixel,lthp>::iterator it =highlightPixel.find(p);
	if(!(it == highlightPixel.end()))
	{
		returnVal = true;
		highlightPixel.erase(it);
	}

	return returnVal;
}*/
bool contains(HighlightPixel p)
{
	bool returnVal = false;

	for(set<HighlightPixel,lthp>::iterator it=highlightPixel.begin(); it != highlightPixel.end(); it++)
	{
		if ((*it).i == p.i && (*it).j == p.j)
		{
			returnVal = true;
			highlightPixel.erase(it);
			break;
		}
	}

	return returnVal;
}
//funkcija koja izraduje profil ruke
void makeProfile(IplImage* img)
{
	CvScalar red;
	red.val[0] = 0;
	red.val[1] = 0;
	red.val[2] = 0;
	red.val[3] = 255;

    cvShowImage("Camera", img );

    //iteracija kroz vertikalni segment
    for(int i= 0; i < img->height - 1; i++)
    {
        //iteracija kroz horizontalni segment
        for(int j = 0; j < img->width - 1; j++)
        {
            //dobavimo podatke od trenutnog piksela
            CvScalar color = cvGet2D(img,i,j);
            HighlightPixel p;
            p.i = i;
            p.j = j;

            //cout << "\n R:" << color.val[0] << " G:" <<color.val[1] << " B:" << color.val[2] <<endl;
            //provjeri je li piksel veæ bio oznacen kod flood fill-a
            if(contains(p))
            {
                cvShowImage("Camera", img);
                cvSet2D(img,i,j,red);
                //provjeri jesmo li veæ dodali ovaj piksel
                if(frequencies.find(color) == frequencies.end())
                {
                    //ako nismo kreiraj novi element u mapu
                    frequencies[color] = 1;
                }
                else
                {
                    //ako jesmo dodaj jos jedan
                    frequencies[color] += 1;
                }
            }
        }
    }

    list<CvScalar> colorList;

    //dodaj elemente mape u privremenu listu
    for (map<CvScalar,int,ltstr>::iterator it=frequencies.begin() ; it != frequencies.end(); it++)
    {
        colorList.push_back((*it).first);
    }

    //sortiraj listu po frekvencijama
    colorList.sort(compare_frequencies);

    //prvih sto iz liste stavi u profil ruke
    list<CvScalar>::iterator it = colorList.begin();
    for (int x = 0; it != colorList.end() && x < PROFILE_SIZE; it++)
    {
        //cout << "\n R:" << (*it).val[0] << " G:" <<(*it).val[1] << " B:" << (*it).val[2] << " F:" << frequencies[(*it)];
        profile[x] = (*it);
        x++;
    }

}
