int abs(int n) {
	return (n < 0) ? -n : n;
}

int rand() {
	static int seed = 0xC36B673;
	seed = ((seed * 404642423) + 2091154497) % 1854401557;
}