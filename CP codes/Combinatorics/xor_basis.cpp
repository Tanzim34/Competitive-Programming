const ll N = 1e5 + 10, LOG_A = 52;

ll basis[LOG_A], sz = 0;

void insertVector(ll mask) {
	for (ll i = LOG_A - 1; i >= 0; i--) {
		if ((mask & (1ll << i)) == 0) continue;

		if (!basis[i]) {
			basis[i] = mask;
			sz++;
			return;
		}

		mask ^= basis[i];
	}
}