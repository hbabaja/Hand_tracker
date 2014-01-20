/**********************************************************
 * Datoteka: mouseactions.h                               *
 * Autor: Hrvoje Babaja                                   *
 **********************************************************/

//varijable od X11 za kontrolu miša
Display *dpy = XOpenDisplay(0);
Window root_window = XRootWindow(dpy,0);

void MouseMove(int x, int y)
{
    //int dx = 2200 - x*10;
    //int dy = 1500 - y*8;
    int dx = 1900 - x*9;
    int dy = 1300 - y*7;

    XSelectInput(dpy, root_window, KeyReleaseMask);

    XWarpPointer(dpy, None, root_window, 0, 0, 0, 0, dx, dy);

    XFlush(dpy);
}

void MouseLeftBtnDown()
{
    XTestFakeButtonEvent(dpy, LEFTMOUSEBTN, true, CurrentTime);
    XFlush(dpy);
}

void MouseLeftBtnUp()
{
    XTestFakeButtonEvent(dpy, LEFTMOUSEBTN, false, CurrentTime);
    XFlush(dpy);
}

void MouseRightBtnDown()
{
    XTestFakeButtonEvent(dpy, RIGHTMOUSEBTN, true, CurrentTime);
    XFlush(dpy);
}

void MouseRightBtnUp()
{
    XTestFakeButtonEvent(dpy, RIGHTMOUSEBTN, false, CurrentTime);
    XFlush(dpy);
}
