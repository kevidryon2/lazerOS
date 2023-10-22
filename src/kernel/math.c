int abs(int n) {
	return (n < 0) ? -n : n;
}

int positive(int n) {
	return (n < 0) ? 0 : n;
}

int negative(int n) {
	return (n < 0) ? n : 0;
}

int rand() {
	static int seed = 0xC36B673;
	seed = ((seed * 404642423) + 2091154497) % 1854401557;
}