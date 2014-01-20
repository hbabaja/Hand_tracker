/**********************************************************
 * Datoteka: main.cpp                                     *
 * Autor: Hrvoje Babaja                                   *
 **********************************************************/

#include "defs.h"
#include "handstate.h"
#include "mouseactions.h"
#include "handgestures.h"
#include "floodfill.h"
#include "makeprofile.h"
#include "gethand.h"

int main()
{
    //prikaz teksta u prozoru kamere
    cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, 0.5,0.5,0,1);

    selectX.val[0] = 255;
    selectX.val[1] = 255;
    selectX.val[2] = 0;
    selectX.val[3] = 255;

    profileMaking = false;
    cvNamedWindow("Camera", CV_WINDOW_AUTOSIZE);
    cvMoveWindow("Camera", 0, 0);

    //postavke kamere
    CvCapture *camera = cvCaptureFromCAM(-1);
    cvSetCaptureProperty( camera, CV_CAP_PROP_FRAME_WIDTH, CAMINPUTWIDTH  );
    cvSetCaptureProperty( camera, CV_CAP_PROP_FRAME_HEIGHT, CAMINPUTHEIGHT  );

    IplImage* img;

    IplImage* img2;

    img = 0;
    img2 = 0;

    if(!cvGrabFrame(camera))
    {
        printf("Could not grab a frame\n\7");
        exit(0);
    }

    img=cvRetrieveFrame(camera);

    cvShowImage("Camera", img );

    cvWaitKey(10);

    //Postavlja funkciju mousecallback da obavi mouse event-ove
    cvSetMouseCallback("Camera", mousecallback, (void*)img);

    //dok korisnik ne selektira dio slike prikazuj video kamere
    while(profileMaking == false)
    {
        if(!cvGrabFrame(camera))
        {
            printf("Could not grab a frame\n\7");
            exit(0);
        }

        IplImage* img = cvRetrieveFrame(camera);

        cvShowImage("Camera", img);

        cvWaitKey(10);
    }

    //cvWaitKey(0);

    if(!cvGrabFrame(camera))
    {
        printf("Could not grab a frame\n\7");
        exit(0);
    }

    img2=cvRetrieveFrame(camera);

    //napravi profil ruke
    makeProfile(img2);

    cvShowImage("Camera", img );

    //zapocinje rad prepoznavanja pokreta ruke
    while(1)
    {
        if(!cvGrabFrame(camera))
        {
            printf("Could not grab a frame\n\7");
            exit(0);
        }

        IplImage* img3 = cvRetrieveFrame(camera);

        getHand(img3);

        cvShowImage("Camera", img3);

        cvWaitKey(10);
    }

    return 0;
}
