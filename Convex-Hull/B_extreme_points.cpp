#include <iostream>

struct Point {
	int x;
	int y;
	bool extreme;
};

long long cross(Point p, Point q) {
	return p.x * q.y - p.y * q.x;
}

long long area2(Point p, Point q, Point s) {
	return cross(p, q) + cross(q, s) + cross(s, p);
}

bool toLeft(Point p, Point q, Point s) {
	return area2(p, q, s) > 0;
}

bool inTriangle(Point p, Point q, Point r, Point s) {
	bool pqLeft = toLeft(p, q, s);
	bool qrLeft = toLeft(q, r, s);
	bool rpLeft = toLeft(r, p, s);
	return (pqLeft == qrLeft) && (qrLeft == rpLeft);
}

void extremePoint(Point S[], int n) {
	for (int s = 0; s < n; ++s) {
		S[s].extreme = true;
	}
	for (int p = 0; p < n; ++p)
		for (int q = p + 1; q < n; ++q)
			for (int r = q + 1; r < n; ++r)
				for (int s = 0; s < n; ++s) {
					if (s == p || s == q || s == r || !S[s].extreme) {
						continue;
					}
					if (inTriangle(S[p], S[q], S[r], S[s])) {
						S[s].extreme = false;
					}
				}
}

int main() {
	
	return 0;
}
