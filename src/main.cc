/*
 * main.cc
 *
 *  Created on: 22 mar 2015
 *      Author: mac
 */

#include <exception>
#include <iostream>
#include <cassert>
#include "resources_fs.h"
#include "assets/strings.h"
#include "varchar.h"

int main(int argc, char *kargv[]) {
	assert(tie::unit::test_varchar());
	tie::lfd::Storage storage;
	storage.LoadTieDirectory("/Users/mac/Desktop/tie/resources");
	storage.GetAssetByName<tie::assets::TagStrings>("resource/battle1.lfd/battle1");
	return 0;
}

