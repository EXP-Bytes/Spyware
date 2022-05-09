#include "spy.h"

bool FileExists(LPCSTR fileName) {
	bool exists = false;
	FILE* FileExists;
	if (FileExists = fopen(fileName, "r")) {
		fclose(FileExists);
		exists = true;
	}
	return exists;
}