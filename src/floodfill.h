/**********************************************************
 * Datoteka: floodfill.h                                  *
 * Autor: Hrvoje Babaja                                   *
 **********************************************************/

//Flood fill algoritam
void floodfill(Pixel start, CvScalar targetColor, CvScalar replacementColor,IplImage* img)
{
    //inicijalizacija novog reda
    queue<Pixel> Q;

    //dodavanje pocetnog elementa u red
    Q.push(start);

    //petlja ide dok red nije prazan
    while(Q.size() != 0)
    {
        //prvi element reda spremi u 'n'
        Pixel n = Q.front();

        //provjeri je li 'n' boja na koju je korisnik kliknuo i zapoceo ovaj algoritam
        if(compareColor(n.color,targetColor))
        {
            cvSet2D(img,n.x,n.y,replacementColor);
        }
        Q.pop();

        //dodaj n u listu oznaæenih piksela, ta lista se poslije koristi u izradi profila ruke
        HighlightPixel p;
        p.i = n.x;
        p.j = n.y;
        highlightPixel.insert(p);

        //provjeri X+1
        Pixel newN;
        newN.x = n.x+1;
        newN.y = n.y;
        if(newN.x < img->height - 1 && newN.x > 0 && newN.y < img->width && newN.y > 0)
        {
            newN.color = cvGet2D(img,newN.x,newN.y);
            if(compareColor(newN.color,targetColor))
            {
                cvSet2D(img,newN.x,newN.y,replacementColor);
                Q.push(newN);
            }
        }

        //provjeri X-1
        newN.x = n.x-1;
        newN.y = n.y;
        if(newN.x < img->height - 1 && newN.x > 0 && newN.y < img->width && newN.y > 0)
        {
            newN.color = cvGet2D(img,newN.x,newN.y);
            if(compareColor(newN.color,targetColor))
            {
                cvSet2D(img,newN.x,newN.y,replacementColor);
                Q.push(newN);
            }
        }

        //provjeri Y+1
        newN.x = n.x;
        newN.y = n.y + 1;
        if(newN.x < img->height - 1 && newN.x > 0 && newN.y < img->width && newN.y > 0)
        {
            newN.color = cvGet2D(img,newN.x,newN.y);
            if(compareColor(newN.color,targetColor))
            {
                cvSet2D(img,newN.x,newN.y,replacementColor);
                Q.push(newN);
            }
        }

        //provjeri Y-1
        newN.x = n.x;
        newN.y = n.y - 1;
        if(newN.x < img->height - 1 && newN.x > 0 && newN.y < img->width && newN.y > 0)
        {
            newN.color = cvGet2D(img,newN.x,newN.y);
            if(compareColor(newN.color,targetColor))
            {
                cvSet2D(img,newN.x,newN.y,replacementColor);
                Q.push(newN);
            }
        }

        //provjeri X+1,Y+1
        newN.x = n.x + 1;
        newN.y = n.y + 1;
        if(newN.x < img->height - 1 && newN.x > 0 && newN.y < img->width && newN.y > 0)
        {
            newN.color = cvGet2D(img,newN.x,newN.y);
            if(compareColor(newN.color,targetColor))
            {
                cvSet2D(img,newN.x,newN.y,replacementColor);
                Q.push(newN);
            }
        }

        //provjeri X+1,Y-1
        newN.x = n.x + 1;
        newN.y = n.y - 1;
        if(newN.x < img->height - 1 && newN.x > 0 && newN.y < img->width && newN.y > 0)
        {
            newN.color = cvGet2D(img,newN.x,newN.y);
            if(compareColor(newN.color,targetColor))
            {
                cvSet2D(img,newN.x,newN.y,replacementColor);
                Q.push(newN);
            }
        }

        //provjeri X-1,Y+1
        newN.x = n.x - 1;
        newN.y = n.y + 1;
        if(newN.x < img->height - 1 && newN.x > 0 && newN.y < img->width && newN.y > 0)
        {
            newN.color = cvGet2D(img,newN.x,newN.y);
            if(compareColor(newN.color,targetColor))
            {
                cvSet2D(img,newN.x,newN.y,replacementColor);
                Q.push(newN);
            }
        }

        //provjeri X-1,Y-1
        newN.x = n.x - 1;
        newN.y = n.y - 1;
        if(newN.x < img->height - 1 && newN.x > 0 && newN.y < img->width && newN.y > 0)
        {
            newN.color = cvGet2D(img,newN.x,newN.y);
            if(compareColor(newN.color,targetColor))
            {
                cvSet2D(img,newN.x,newN.y,replacementColor);
                Q.push(newN);
            }
        }

    }
}

//funkcija koja odgovara na mouse event-ove koji se dogode na prozoru kamere
void mousecallback( int event, int x, int y, int flags, void* param )
{

    IplImage* img = (IplImage*) param;

    if(event == CV_EVENT_LBUTTONDOWN)
    {
        profileMaking = true;

        //boja kojom se zamjenjuje
        CvScalar rep;
        rep.val[0] = 255;
        rep.val[1] = 0;
        rep.val[2] = 0;
        rep.val[3] = 255;

        //koordinate i boja piksela na koji je korisnik kliknuo
        Pixel start;
        start.x = y;
        start.y = x;
        start.color = cvGet2D(img,y,x);

        floodfill(start,start.color,rep,img);
    }

    cvShowImage("Camera", img);
}
