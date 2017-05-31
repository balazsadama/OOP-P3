#pragma once

#include <ctime>
//#include "Rendezes.cpp"

template <class T>
class Rendezes {
protected:
	virtual bool kisebb(T a, T b) = 0;
	virtual void csere(T &a, T &b) = 0;
public:
	virtual void rendez(T *tomb, int n) = 0;
};

//class Stat {
//private:
//	unsigned int ido, nHasonlit, nCsere;
//	std::clock_t c;
//
//protected:
//	void kezd();
//	void vege();
//	void init();
//	void incHasonlit();
//	void incCsere();
//
//public:
//	Stat();
//	unsigned int getIdo();
//	unsigned int getHasonlit();
//	unsigned int getCsere();
//};

template <class T>
class BuborekosRendezes : public Rendezes<T> {
protected:
	bool kisebb(T a, T b);
	void csere(T &a, T &b);

public:
	void rendez(T *tomb, int n);
};

//template <class T>
//class BuborekosRendezesT : public BuborekosRendezes<T>, public Stat {
//protected:
//	bool kisebb(T a, T b);
//	void csere(T &a, T &b);
//
//public:
//	void rendez(T *tomb, int n);
//};
//
//template <class T>
//class QuickSort : public Rendezes<T> {
//private:
//	void qsort(T* a, int bal, int jobb);
//	int particional(T *a, int bal, int jobb);
//
//protected:
//	bool kisebb(T a, T b);
//	void csere(T &a, T &b);
//
//public:
//	void rendez(T *tomb, int n);
//
//};
//
//template <class T>
//class QuickSortT : public QuickSort<T>, public Stat {
//
//protected:
//	bool kisebb(T a, T b);
//	void csere(T &a, T &b);
//
//public:
//	void rendez(T *tomb, int n);
//
//};

/***************************************************************************/
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