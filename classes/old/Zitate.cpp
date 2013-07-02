
#include "Zitate.h"


Zitate::Zitate() {

}


void Zitate::load(string file) {
	json.openLocal(file);
	
	cout << json.getRawString(true) << endl;
}
