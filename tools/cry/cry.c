#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// NOTE: srand(seed) rand() will return different values on different OSs

int cry_file(const char* filei, const char* fileo, const int mode, const int shift) {
    FILE* fp1 = fopen(filei, "rb");
    if (fp1 == NULL) { return 0; }
	FILE* fp2 = fopen(fileo,"wb");
	if (fp2 == NULL) { return 0; }
	
	int c;
    while ((c = fgetc(fp1)) != EOF) {
		//printf("%02x", c);
		int g;
		switch (mode) {
			case 1: g = c + shift; break;
			case 2: g = c - shift; break;
			default: return 0; break;
		}
		fputc(g, fp2);
    }
	
    fclose(fp1);
	fclose(fp2);
	
	return 1;
}

int cry_file_r(const char* filei, const char* fileo, const int mode, const int rnd_seed) {
	
	srand(rnd_seed);
	
    FILE* fp1 = fopen(filei, "rb");
    if (fp1 == NULL) { return 0; }
	FILE* fp2 = fopen(fileo,"wb");
	if (fp2 == NULL) { return 0; }
	
	int c;
    while ((c = fgetc(fp1)) != EOF) {
		//printf("%02x", c);
		int g;
		switch (mode) {
			case 1: g = c + rand(); break;
			case 2: g = c - rand(); break;
			default: return 0; break;
		}
		fputc(g, fp2);
    }

    fclose(fp1);
	fclose(fp2);
	
	return 1;
}

int cry_str(const char* s1, char* s2, const int mode, const int shift) {
	for (int i = 0; i < strlen(s1); i++) {
		int c = s1[i];
		int g;
		switch (mode) {
			case 1: g = c + shift; break;
			case 2: g = c - shift; break;
			default: return 0; break;
		}
		s2[i] = g;
	}
	return 1;
}

int cry_str_r(const char* s1, char* s2, const int mode, const int rnd_seed) {
	
	srand(rnd_seed);
	
	for (int i = 0; i < strlen(s1); i++) {
		int c = s1[i];
		int g;
		switch (mode) {
			case 1: g = c + rand(); break;
			case 2: g = c - rand(); break;
			default: return 0; break;
		}
		s2[i] = g;
	}
	return 1;
}