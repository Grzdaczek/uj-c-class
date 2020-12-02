int getb(void *word, unsigned int bit) { 
	return *(char*)(word+(bit>>3)) >> (bit%8) & 1;
}

void setb(void *word, unsigned int bit) {
	*(char*)(word+(bit>>3)) |= 1 << (bit%8);
}

void clrb(void *word, unsigned int bit) {
	*(char*)(word+(bit>>3)) &= ~(1 << (bit%8));
}

void notb(void *word, unsigned int bit) {
	*(char*)(word+(bit>>3)) ^= 1 << (bit%8);
}
