/*
 * main.cc
 *
 *  Created on: 22 mar 2015
 *      Author: mac
 */

#include <cassert>
#include "resources_fs.h"
#include "varchar.h"

int main(int argc, char *kargv[]) {
	assert(tie::unit::test_varchar());
	tie::lfd::Storage storage;
	storage.LoadTieDirectory("/Users/mac/Desktop/tie/resources");
	return 0;
}

