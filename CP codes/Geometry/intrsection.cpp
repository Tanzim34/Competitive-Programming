bool on_right(point a, point b, point c)
{
    b.x-=a.x;
    b.y-=a.y;
    c.x-=a.x;
    c.y-=a.y;
    if(b.x*c.y-b.y*c.x < 0) return true;
    return false;
}

bool on_line(point a, point b, point c)
{
    b.x-=a.x;
    b.y-=a.y;
    c.x-=a.x;
    c.y-=a.y;
    if(b.x*c.y-b.y*c.x == 0 && c.x>=min(0ll,b.x) && c.x<=max(0ll,b.x)) return true;
    return false;
}

bool on_left(point a, point b, point c)
{
    b.x-=a.x;
    b.y-=a.y;
    c.x-=a.x;
    c.y-=a.y;
    if(b.x*c.y-b.y*c.x > 0) return true;
    return false;
}