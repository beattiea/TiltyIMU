int checkMemory(int test_writes) {
	
	int memory[test_writes];
	
	flash.eraseChip();
	
	for (int i = 0; i < sizeof(memory) / sizeof(int); i++) {
		memory[i] = random(0, 65535);
		flash.bufferData(memory[i]);
	}
	
	int wrong_count = 0;
	
	for (int i = 0; i < sizeof(memory) / sizeof(int); i++) {
		if (flash.readInt(i * sizeof(int)) != memory[i]) {	wrong_count++;}
	}
	return wrong_count;
}