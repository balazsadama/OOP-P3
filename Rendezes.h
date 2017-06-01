#pragma once
#include <ctime>

template <class T>
class Rendezes {
protected:
	virtual bool kisebb(T a, T b) = 0;
	virtual void csere(T &a, T &b) = 0;
public:
	virtual void rendez(T *tomb, int n) = 0;
};

class Stat {
private:
	unsigned int ido, nHasonlit, nCsere;
	std::clock_t c;

protected:
	void kezd();
	void vege();
	void init();
	void incHasonlit();
	void incCsere();

public:
	Stat();
	unsigned int getIdo();
	unsigned int getHasonlit();
	unsigned int getCsere();
};

Stat::Stat() { init(); }

void Stat::init() { ido = 0; nHasonlit = 0;	nCsere = 0; }

void Stat::kezd() {
	c = clock();
}

void Stat::vege() {
	ido = clock() - c;
}

unsigned int Stat::getIdo() {
	return ido;
}

unsigned int Stat::getHasonlit() {
	return nHasonlit;
}

unsigned int Stat::getCsere() {
	return nCsere;
}

void Stat::incHasonlit() {
	nHasonlit++;
}

void Stat::incCsere() {
	nCsere++;
}


template <class T>
class BuborekosRendezes : public Rendezes<T> {
protected:
	bool kisebb(T a, T b);
	void csere(T &a, T &b);

public:
	void rendez(T *tomb, int n);
};

template <class T>
bool BuborekosRendezes<T>::kisebb(T a, T b) {
	return (a < b) ? true : false;
}

template <class T>
void BuborekosRendezes<T>::csere(T &a, T &b) {
	T temp;
	temp = a;
	a = b;
	b = temp;
}

template <class T>
void BuborekosRendezes<T>::rendez(T *tomb, int n) {
	int regibal, regijobb, jobb;
	bool ok;

	regibal = 0;
	regijobb = n - 1;
	do {
		ok = true;
		jobb = 0;
		for (int i = regibal; i < regijobb; i++) {
			if (kisebb(tomb[i + 1], tomb[i])) {
				ok = false;
				csere(tomb[i + 1], tomb[i]);
				if (i > jobb)
					jobb = i;
			}
		}
		regijobb = jobb;
	} while (!ok);
}


template <class T>
class BuborekosRendezesT : public BuborekosRendezes<T>, public Stat {
protected:
	bool kisebb(T a, T b);
	void csere(T &a, T &b);

public:
	void rendez(T *tomb, int n);
};

template <class T>
bool BuborekosRendezesT<T>::kisebb(T a, T b) {
	incHasonlit();
	return BuborekosRendezes<T>::kisebb(a, b);
}

template <class T>
void BuborekosRendezesT<T>::csere(T &a, T &b) {
	incCsere();
	BuborekosRendezes<T>::csere(a, b);
}

template <class T>
void BuborekosRendezesT<T>::rendez(T *tomb, int n) {
	kezd();
	BuborekosRendezes<T>::rendez(tomb, n);
	vege();
}

template <class T>
class QuickSort : public Rendezes<T> {
private:
	void qsort(T* a, int bal, int jobb);
	int particional(T *a, int bal, int jobb);

protected:
	bool kisebb(T a, T b);
	void csere(T &a, T &b);

public:
	void rendez(T *tomb, int n);

};

template <class T>
bool QuickSort<T>::kisebb(T a, T b) {
	return (a < b) ? true : false;
}

template <class T>
void QuickSort<T>::csere(T &a, T &b) {
	T temp;
	temp = a;
	a = b;
	b = temp;
}

template <class T>
int QuickSort<T>::particional(T *a, int bal, int jobb) {
	int pInd = bal;
	T pivot = a[jobb];

	for (int i = bal; i < jobb; i++) {
		if (kisebb(a[i], pivot)) {
			csere(a[i], a[pInd]);
			pInd++;
		}
	}

	csere(a[pInd], a[jobb]);
	return pInd;
}

template <class T>
void QuickSort<T>::qsort(T* a, int bal, int jobb) {
	int pInd;

	if (bal < jobb) {
		pInd = particional(a, bal, jobb);
		qsort(a, bal, pInd - 1);
		qsort(a, pInd + 1, jobb);
	}
}

template <class T>
void QuickSort<T>::rendez(T *tomb, int n) {
	qsort(tomb, 0, n - 1);
}


template <class T>
class QuickSortT : public QuickSort<T>, public Stat {

protected:
	bool kisebb(T a, T b);
	void csere(T &a, T &b);

public:
	void rendez(T *tomb, int n);
};

template <class T>
bool QuickSortT<T>::kisebb(T a, T b) {
	incHasonlit();
	return QuickSort<T>::kisebb(a, b);
}

template <class T>
void QuickSortT<T>::csere(T &a, T &b) {
	incCsere();
	QuickSort<T>::csere(a, b);
}

template <class T>
void QuickSortT<T>::rendez(T *tomb, int n) {
	kezd();
	QuickSort<T>::rendez(tomb, n);
	vege();
}