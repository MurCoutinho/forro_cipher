#define __test
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include "src/forro/x86-simd/forro.h"
#include "src/xote/x86-simd/xote.h"

int run_test_vectors(uint8_t key[32], uint8_t iv[8], uint8_t expected[128], uint32_t number_of_bytes)
{
    stream_ctx input;

    uint8_t *output_forro = (uint8_t *)malloc(number_of_bytes);
    uint8_t *output_xote = (uint8_t *)malloc(number_of_bytes);

    forro_keysetup(&input, key, 256, 64);
    forro_ivsetup(&input, iv);
    forro_keystream_bytes(&input, output_forro, number_of_bytes);

    xote_keysetup(&input, key, 256, 64);
    xote_ivsetup(&input, iv);
    xote_keystream_bytes(&input, output_xote, number_of_bytes);

    // Display the result to the screen

    printf("KEY:\n");
    for (int i = 0; i < 32; i++)
    {
        printf("%02x", key[i]);
        if (i % 16 == 15)
            printf("\n");
    }
    printf("\nNONCE:\n");
    for (int i = 0; i < 8; i++)
    {
        printf("%02x", iv[i]);
        if (i % 8 == 7)
            printf("\n");
    }
    printf("\nSTREAM:\n");
    printf("--------------------------------\t--------------------------------\t--------------------------------\n");
    printf("|             FORRO            |\t|             XOTE             |\t|           EXPECTED           |\n");
    printf("--------------------------------\t--------------------------------\t--------------------------------\n");
    for (int i = 0; i < 8; i++)
    {
        for (int k = 0; k < 16; k++)
            printf("%02x", output_forro[16 * i + k]);
        printf("\t");
        for (int k = 0; k < 16; k++)
            printf("%02x", output_xote[16 * i + k]);
        printf("\t");
        for (int k = 0; k < 16; k++)
            printf("%02x", expected[16 * i + k]);
        printf("\n");
    }

    printf("\n\n\n");

    if (memcmp(output_forro, expected, number_of_bytes))
    {
        printf("FORRO FAILED!\n");
        return 1;
    }

    if (memcmp(output_xote, expected, number_of_bytes))
    {
        printf("XOTE FAILED!\n");
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int rv;
    uint64_t number_of_bytes = 128;
    // printf("Teste: minha vida e andar.\n");
    // printf("---------------------------\n");

    uint8_t key[32] = "minha vida e andar por este pais";

    uint8_t iv[8] = "mostro a";
    // uint8_t count[8] = " alegria"; // UNUSED IN THIS VERSION
    uint8_t expected[128] = {
        0xc5, 0xa9, 0x6c, 0x62, 0xf2, 0x93, 0x52, 0xaf, 0xf2, 0x62, 0x95, 0xb5, 0x8d, 0xa0, 0x59, 0x5c,
        0x62, 0x10, 0x82, 0x25, 0xf1, 0x4e, 0x33, 0x11, 0x16, 0xad, 0x3f, 0x7b, 0x4e, 0xa0, 0x00, 0xfe,
        0xc0, 0xf0, 0x36, 0x8e, 0x42, 0x11, 0x49, 0xb2, 0x6b, 0x0b, 0x43, 0x98, 0xdb, 0x7b, 0x3b, 0xbb,
        0x99, 0xe3, 0xf5, 0xd7, 0xa9, 0x1b, 0xf0, 0x28, 0x99, 0x6a, 0x8c, 0x46, 0x51, 0x70, 0x7e, 0xf1,
        0xdc, 0xbe, 0xe0, 0xc1, 0x27, 0x1a, 0x0c, 0xf7, 0xe0, 0x0e, 0xb1, 0xbc, 0x1e, 0x6f, 0xf8, 0x6e,
        0xf2, 0x3c, 0xac, 0xa9, 0x86, 0xa0, 0x03, 0x7e, 0x02, 0x92, 0x2b, 0xa5, 0xaa, 0x6a, 0x1d, 0x6d,
        0xf0, 0x9f, 0x5b, 0xd1, 0xc5, 0x40, 0xb0, 0xd9, 0xd1, 0xcc, 0x8b, 0x3e, 0xc3, 0x90, 0x66, 0x0a,
        0xe6, 0x8a, 0x88, 0x49, 0xfb, 0x57, 0xea, 0x3a, 0x71, 0xd8, 0x44, 0xe7, 0x20, 0xb4, 0x84, 0x70};
    rv = run_test_vectors(key, iv, expected, number_of_bytes);

    if (rv)
        return 1;

    // printf("Teste: como se danca o baiao.\n");
    // printf("---------------------------\n");

    uint8_t key1[32] = "eu vou mostrar pra voces como se";

    uint8_t iv1[8] = "danca o ";
    // uint8_t count1[8] = "baiao!!!"; // UNUSED IN THIS VERSION
    uint8_t expected1[128] = {
        0x4b, 0x76, 0x8c, 0x5c, 0x17, 0x4b, 0xc9, 0xc1, 0xce, 0x1b, 0x8c, 0x2b, 0x1f, 0xac, 0xe8, 0xe4,
        0x5a, 0x63, 0xf9, 0x2e, 0x21, 0xd9, 0x7b, 0x81, 0xc8, 0x9d, 0x61, 0x90, 0x08, 0x82, 0xd9, 0x27,
        0x73, 0xc5, 0xf7, 0xe6, 0x2a, 0x1f, 0x29, 0x7c, 0xee, 0x9b, 0xae, 0x88, 0xbb, 0x6c, 0x70, 0x47,
        0x7b, 0x80, 0x3a, 0xca, 0xe3, 0x17, 0xc0, 0x18, 0x46, 0x74, 0xee, 0xfa, 0x43, 0x46, 0x99, 0xb8,
        0x50, 0xb6, 0xa4, 0x5e, 0xd9, 0x7b, 0x34, 0x79, 0x85, 0x2a, 0x76, 0xa6, 0x69, 0x6a, 0x23, 0x76,
        0x9a, 0xaa, 0xc2, 0xd7, 0x35, 0xff, 0x73, 0xf2, 0x8b, 0x9d, 0xfa, 0x8b, 0x22, 0x42, 0xb2, 0x0b,
        0x7c, 0x4e, 0x68, 0xc0, 0x3d, 0x16, 0x22, 0x6e, 0xe9, 0x06, 0x69, 0x33, 0x59, 0x84, 0x43, 0xda,
        0xf3, 0xbf, 0x43, 0x7b, 0xbc, 0xbc, 0x9f, 0x04, 0xc7, 0xec, 0xef, 0xa6, 0xa2, 0x4f, 0xad, 0x3d};
    rv = run_test_vectors(key1, iv1, expected1, number_of_bytes);

    if (rv)
        return 1;

    printf("TEST VECTORS CHECK!\n");

    return 0;
}
