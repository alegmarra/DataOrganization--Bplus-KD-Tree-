#ifndef KDTREE_KEY_INFINITY_H
#define KDTREE_KEY_INFINITY_H

#include "KDTree/Key.h"


class KeyInfinity: public Key
{

private:
    bool is_positive;

public:
    KeyInfinity(): Key("Inf") { KeyInfinity(false); };
    KeyInfinity(bool positive): Key("Inf") { is_positive = positive; };
    
    Comparator* getComparator();
    
private:

	class KeyInfinityComparator: public Comparator
	{

	private:
		bool is_positive;

	public:
		KeyInfinityComparator(bool is_positive): Comparator(&is_positive) {};
		virtual int compareTo(void * target);


	};

    
};

#endif
