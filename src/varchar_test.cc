/*
 * varchar_test.cc
 *
 *  Created on: 22 mar 2015
 *      Author: mac
 */

#include "varchar.h"

namespace tie {
namespace unit {

bool test_varchar() {
	Varchar<8> string0;
	if (string0.size() != 8) return false;
	if (string0.length() != 0) return false;

	Varchar<16> string1;
	if (string1 != string0) return false;

	string0 = "Ph'nglui mglw'nafh Cthulhu R'lyeh wgah'nagl fhtagn";
	if (string0.length() != string0.size()) return false;

	string1 = "Ph’nglui mglw’nafh Cthulhu R’lyeh wgah’nagl fhtagn";
	if (string0.length() > string1.length()) return false;

	return true;
}

};
};
