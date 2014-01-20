/**********************************************************
 * Datoteka: handgestures.h                               *
 * Autor: Hrvoje Babaja                                   *
 **********************************************************/

//nizovi za spremanje stanja proslih frame-ova
bool handPreviousFrame[FRAMESTOBACKTRACK];
bool fistPreviousFrame[FRAMESTOBACKTRACK];
bool fingerPreviousFrame[FRAMESTOBACKTRACK];

//nizovi za spremanje pozicija proslih frame-ova
int xPreviousFrame[FRAMESTOBACKTRACK];
int yPreviousFrame[FRAMESTOBACKTRACK];

int xAverage;
int yAverage;
int xSum;
int ySum;
int xAverageLast;
int yAverageLast;

int delay = 5;

bool gestureDetected;

void HandGestureCatcher(int x, int y)
{
    //prepoznavanje pokreta zatvaranja ruke (otvorena ruka -> saka)
    for(int i = 0; i < FRAMESTOBACKTRACK; i++)
    {
        if(state["Fist"] && handPreviousFrame[i])
        {
            cout << "Open hand -> Fist detected"<< endl;

            for(int i = 0; i < FRAMESTOBACKTRACK; i++)
            {
                handPreviousFrame[i] = false;
            }
            break;
        }
    }

    //prepoznavanje pokreta otvaranja ruke (saka -> otvorena ruka)
    for(int i = 0; i < FRAMESTOBACKTRACK; i++)
    {
        if(state["Open Hand"] && fistPreviousFrame[i])
        {
            cout << "Fist -> Open hand detected"<< endl;

            for(int i = 0; i < FRAMESTOBACKTRACK; i++)
            {
                fistPreviousFrame[i] = false;
            }
            break;
        }
    }

    //prepoznavanje pokreta prst -> saka
    for(int i = 0; i < FRAMESTOBACKTRACK; i++)
    {
        if(state["Fist"] && fingerPreviousFrame[i])
        {
            cout << "Finger -> Fist detected" <<endl;

            //MouseRightBtnDown();

            delay = 5;
            gestureDetected = true;

            for(int i = 0; i < FRAMESTOBACKTRACK; i++)
            {
                fingerPreviousFrame[i] = false;
            }
            break;
        }
    }

    //prepoznavanje pokreta saka -> prst
    for(int i = 0; i < FRAMESTOBACKTRACK; i++)
    {
        if(state["Finger Out"] && fistPreviousFrame[i])
        {
            cout << "Fist -> Finger detected" <<endl;

            //MouseRightBtnUp();

            delay = 5;
            gestureDetected = true;

            for(int i = 0; i < FRAMESTOBACKTRACK; i++)
            {
                fistPreviousFrame[i] = false;
            }
            break;
        }
    }

    //prepoznavanje pokreta prst -> otvorena ruka
    for(int i = 0; i < FRAMESTOBACKTRACK; i++)
    {
        if(state["Open Hand"] && fingerPreviousFrame[i])
        {
            cout <<"Finger -> Open hand detected" <<endl;

            MouseLeftBtnUp();

            delay = 5;
            gestureDetected = true;

            for(int i = 0; i < FRAMESTOBACKTRACK; i++)
            {
                fingerPreviousFrame[i] = false;
            }
            break;
        }
    }

    //prepoznavanje pokreta otvorena ruka -> prst
    for(int i = 0; i < FRAMESTOBACKTRACK; i++)
    {
        if(state["Finger Out"] && handPreviousFrame[i])
        {
            cout <<"Open hand -> Finger detected" <<endl;

            MouseLeftBtnDown();

            delay = 5;
            gestureDetected = true;

            for(int i = 0; i < FRAMESTOBACKTRACK; i++)
            {
                handPreviousFrame[i] = false;
            }
            break;
        }
    }

    //osvjezavanje niza proslih frame-ova s novim frame-om (otvorena ruka)
    handPreviousFrame[0] = state["Open Hand"];
    for(int i = FRAMESTOBACKTRACK - 1; i > 0; i--)
    {
        handPreviousFrame[i] = handPreviousFrame[i-1];
    }

    //osvjezavanje niza proslih frame-ova s novim frame-om (saka)
    fistPreviousFrame[0] = state["Fist"];
    for(int i = FRAMESTOBACKTRACK - 1; i > 0; i--)
    {
        fistPreviousFrame[i] = fistPreviousFrame[i-1];
    }

    //osvjezavanje niza proslih frame-ova s novim frame-om (prsti)
    fingerPreviousFrame[0] = state["Finger Out"];
    for(int i = FRAMESTOBACKTRACK - 1; i > 0; i--)
    {
        fingerPreviousFrame[i] = fingerPreviousFrame[i-1];
    }


    //osvjezavanje niza proslih x pozicija s novom
    xPreviousFrame[0] = x;
    for(int i = FRAMESTOBACKTRACK - 1; i > 0; i--)
    {
        xPreviousFrame[i] = xPreviousFrame[i-1];
    }

    //osvjezavanje niza proslih y pozicija s novom
    yPreviousFrame[0] = y;
    for(int i = FRAMESTOBACKTRACK - 1; i > 0; i--)
    {
        yPreviousFrame[i] = yPreviousFrame[i-1];
    }

    for(int i = FRAMESTOBACKTRACK -1; i > 0; i--)
    {
        xSum += xPreviousFrame[i];
    }
    xAverage = (int) xSum / FRAMESTOBACKTRACK;

    for(int i = FRAMESTOBACKTRACK -1; i > 0; i--)
    {
        ySum += yPreviousFrame[i];
    }
    yAverage = (int) ySum / FRAMESTOBACKTRACK;

    if(gestureDetected == false)
    {
        MouseMove(xAverage,yAverage);
    }

    xSum = 0;
    ySum = 0;
    xAverageLast = xAverage;
    yAverageLast = yAverage;
    xAverage = 0;
    yAverage = 0;


    if(delay > 0)
		delay--;
		else
		gestureDetected = false;
}
