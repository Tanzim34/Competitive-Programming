double find_val(pt a)
{
    return sqrt(a.x*a.x+a.y*a.y);
}

double dot(pt a, pt b)
{
    return a.x*b.x+a.y*b.y;
}

double find_angle(pt a, pt b, pt c)
{
    b.x = b.x-a.x;
    b.y = b.y-a.y;
    c.x = c.x-a.x;
    c.y = c.y-a.y;
    double angle = dot(b,c);
    angle = angle/((1.0)*find_val(b)*find_val(c));
    angle = abs(acos(angle));
    return angle;
}

double find_min(vector<pt> &a){
    double ans = pi;
    for(int i=0; i<a.size(); i++)
    {
        ld angle;
        if(i==0){
            angle = find_angle(a[0],a[a.size()-1],a[1]);
        }
        else if(i==a.size()-1) angle = find_angle(a[i],a[0],a[i-1]);
        else angle = find_angle(a[i],a[i-1],a[i+1]);

        if(ans > angle+eps) ans = angle;
    }
    return ans;
}