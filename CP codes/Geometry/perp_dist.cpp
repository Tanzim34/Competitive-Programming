struct point{
	ld x;
	ld y;
};

ld find_val(point a)
{
	return sqrt(a.x*a.x+a.y*a.y);
}

ld dot(point a, point b)
{
	return a.x*b.x+a.y*b.y;
}

ld find_angle(point a, point b, point c)
{
	b.x = b.x-a.x;
	b.y = b.y-a.y;
	c.x = c.x-a.x;
	c.y = c.y-a.y;
	ld angle = dot(b,c);
	angle = angle/((1.0)*find_val(b)*find_val(c));
	angle = abs(acos(angle));
	return angle;
}

// Find the perpendicular distance from O to the segment AB

ld perp_dist(point A, point B, point o)
{
	ld d = sqrt((A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y));
	ld AO = sqrt((A.x-o.x)*((A.x-o.x)) + (A.y-o.y)*((A.y-o.y)));
	ld BO = sqrt((B.x-o.x)*((B.x-o.x)) + (B.y-o.y)*((B.y-o.y)));

	if(AO > (BO + 1e-8)) swap(AO,BO);
	ld an1 = find_angle(A,B,o);
	ld an2 = find_angle(B,o,A);

	// Return large number if the projection is not in the segment
	if(an1>pi/2.0 || an2 > pi/2.0) return 1e15;

	ld an = find_angle(o, A, B);

	ld area = AO * BO * sin(an);

	// For when A,B,o are collinear
	if(area<=1e-7) return (A.x-o.x)*((A.x-o.x)) + (A.y-o.y)*((A.y-o.y));
	ld h = (area)/d;

	return h*h;
}
