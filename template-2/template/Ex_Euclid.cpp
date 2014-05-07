ll Ex_Euclid(ll a,ll b,ll & x,ll & y) {
	if (a == 0) {
		x = 0, y = 1;
		return b;
	}
	ll res = Ex_Euclid(b%a,a,x,y),t = y;
	y = x,x = t-x*(b/a);
	return res;
}