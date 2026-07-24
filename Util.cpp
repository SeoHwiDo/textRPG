#include "Util.h"
int Util::validSetValue(int _set, int _min,int _max ) {
	if (_set < _min) {
		return _min;
	}
	else if (_stat > _max) {
		return _max;
	}
	else {
		return _stat;
	}
}
