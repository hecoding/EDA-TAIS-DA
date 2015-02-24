#include <iostream>
using namespace std;

void mostrar (int v[], int N, int c) {
	for (int i = 0; i < N; i++) {
		cout << v[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < c; i++)
		cout << "  ";
	cout << "|";

	cout << endl << endl;
}

void cambiar (int v[], int a1, int a2, int k) {
	int i = 0;
	int temp;
	cout << "a1 = " << a1 << ", a2 = " << a2 << endl;
	while (i < k) {
		temp = v[a2 + i];
		v[a2 + i] = v[a1 + i];
		v[a1 + i] = temp;
		mostrar (v, 7, i);
		i = i + 1;
	}
}

void transponer (int v[], int N, int k, int c) {
	if (k == N - k) cambiar (v, 0, k + 1, k);
	else if (k <= c) {
		cout << "antes de cambiar" << endl;
		mostrar (v, 7, c);
		cambiar (v, 0, c - k + 1, k);
		cout << "despues de cambiar" << endl;
		mostrar (v, 7, c);
		transponer (v, N, k, c - k);
	}
}

void transponer (int v[], int N, int k) {
	transponer (v, N, k, N - 1);
}

int main () {
	int v[] = {1,2,3,4,5,6,7};
	int N = 7;
	int k;

	//cout << "k = ";
	//cin >> k;
	k = 2;
	transponer (v, N, k);
	mostrar (v, N, 0);

	return 0;
}