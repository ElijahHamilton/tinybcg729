#include "bcg729/encoder.h"
#include <stdio.h>

#define BYTES_PER_FRAME 10
#define SAMPLES_PER_FRAME 80

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("usage: ./encoder input.raw encoded.bin\n");
		printf("input should be signed 16-bit, mono, 8khz. (raw audio)\n");
		printf("output is 8000 bit/s encoded audio");
		return -1;
	}

	int i = 0;

	short inbuf[SAMPLES_PER_FRAME];
	unsigned char encbuf[BYTES_PER_FRAME];

	FILE *fin = fopen(argv[1], "rb");
	FILE *fout = fopen(argv[2], "wb");

	bcg729EncoderChannelContextStruct *codec = initBcg729EncoderChannel();

	printf("TINYBCG729\n");
	printf("8000 bit/s G729 encoder\n\n");

	while(fread(inbuf, 2, SAMPLES_PER_FRAME, fin) == SAMPLES_PER_FRAME) {
		printf("frames encoded: %d\r", i);
		fflush(stdout);
		bcg729Encoder(codec, inbuf, encbuf);
		fwrite(encbuf, BYTES_PER_FRAME, 1, fout);
		i++;
	}
	return 0;
}
