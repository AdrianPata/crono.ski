char CRC8 (char* pointer, char len) {
    char CRC = 0x00;
    unsigned int tmp;

    while(len > 0) {
        tmp = CRC << 1;
        tmp += *pointer;
        CRC = (tmp & 0xFF) + (tmp >> 8);
        pointer++;
        --len;
    }

    return CRC;
}
