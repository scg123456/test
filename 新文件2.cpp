#include <stdio.h>
#include <math.h>

int main() {
	int a, b, xxl = 0, xxll = 0;
	double c ;
	char z[10];
	scanf("%d %d %lf", &a, &b, &c);
	int u = floor(c);
	double d = c - (int)c;
	for (int i = 0; i < 10; i++) {
		u = u / 10;
		if (u != 0) {
			xxl++;
			continue;
		} else
			break;
	}
	xxl++;
	for (int i = 0; i < 10; i++) {
		d = d * 10;
		if (d % 10 != 0) {
			xxll++;
			continue;
		} else
			break;
	}
	sprintf(z, "%f", c);
	int k = xxl - 1, o = 0, oi = 0;
	for (int i = 0; i < xxl; i++) {
		if (z[i] == 46) {
			continue;
		}
		o += (z[i] - '0') * pow(a, k);
		k--;
	}
	for (int i = xxl + 1; i <= xxll + xxl; i++) {
		if (z[i] == 46) {
			continue;
		}
		oi += (z[i] - '0') * pow(a, k);
		k--;
	}
	int iu = o, ui = oi;
	int d[10];
	int id = 0;
	for (int i = 0; i < 100; i++) {

		d[i] = iu % b;
		iu = iu / b;
		if (iu == 0) {
			id = i;
			break;
		}
	}



	for (int j = id; j >= 0; j--) {

		d[j] = d[j] + 48;
		if (d[j] == 58)
			d[j] = 'a';
		else if (d[j] == 59)
			d[j] = 'b';
		else if (d[j] == 60)
			d[j] = 'c';
		else if (d[j] == 61)
			d[j] = 'd';
		else if (d[j] == 62)
			d[j] = 'e';
		else if (d[j] == 63)
			d[j] = 'f';


	}
	return 0;
}