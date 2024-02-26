#include "bcg729/decoder.h"
#include <stdio.h>

#define BYTES_PER_FRAME 10
#define SAMPLES_PER_FRAME 80

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("usage: ./decoder encoded.bin output.raw\n");
		printf("input should be 8000 bit/s encoded audio\n");
		printf("output is signed 16-bit, mono, 8khz. (raw audio)");
		return -1;
	}

	int i = 0;

	short outbuf[SAMPLES_PER_FRAME];
	unsigned char inbuf[BYTES_PER_FRAME];

	FILE *fin = fopen(argv[1], "rb");
	FILE *fout = fopen(argv[2], "wb");

	bcg729DecoderChannelContextStruct *codec = initBcg729DecoderChannel();

	printf("TINYBCG729\n");
	printf("8000 bit/s G729 decoder\n\n");

	while(fread(inbuf, BYTES_PER_FRAME, 1, fin) == 1) {
		printf("frames decoded: %d\r", i);
		fflush(stdout);
		bcg729Decoder(codec, inbuf, outbuf);
		fwrite(outbuf, 2, SAMPLES_PER_FRAME, fout);
		i++;
	}
	return 0;
}
