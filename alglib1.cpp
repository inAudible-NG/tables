/*
 * http://www.tobtu.com/rtcalc.php#params
 *
 * keyspace is 256^4 (length is always 4)
 * 99.999999% (Total success rate)
 *
 * ./rtgen audible byte 4 4 0 10000 10008356 0
 * ./rtgen audible byte 4 4 1 10000 10008356 0
 * ./rtgen audible byte 4 4 2 10000 10008356 0
 * ./rtgen audible byte 4 4 3 10000 10008356 0
 * ./rtgen audible byte 4 4 4 10000 10008356 0
 * ./rtgen audible byte 4 4 5 10000 10008356 0
 * ./rtgen audible byte 4 4 6 10000 10008356 0
 * ./rtgen audible byte 4 4 7 10000 10008356 0
 * ./rtgen audible byte 4 4 8 10000 10008356 0
 * ./rtgen audible byte 4 4 9 10000 10008356 0
 *
 * ./rtsort *.rt
 * ./rt2rtc *.rt 21 24 -m 18 -p
 * ./rt2rtc *.rt 25 25 -m 512 -p
 */

// #include <openssl/sha.h>
#include <stdio.h>
#include "sha1.h"
#ifdef _WIN32
#pragma comment(lib, "libeay32.lib")
#endif

#define MIN_HASH_LEN    8
#define MAX_HASH_LEN    32

void
#ifdef _WIN32
__stdcall
#endif
Audible(
    unsigned char *pData,               // [in] plaintext to be hashed
    unsigned int  uLen,                 // [in] length of the plaintext
    unsigned char Hash[MAX_HASH_LEN])   // [out] the result hash, size of the buffer is MAX_HASH_LEN bytes
{
    unsigned char fixed_key[] = { 0x77, 0x21, 0x4d, 0x4b, 0x19, 0x6a, 0x87,
        0xcd, 0x52, 0x00, 0x45, 0xfd, 0x20, 0xa5, 0x1d, 0x67 };

    unsigned char intermediate_key[20] = {0};
    unsigned char intermediate_iv[20] = {0};
    SHA_CTX ctx;

    SHA1_Init(&ctx);
    SHA1_Update(&ctx, fixed_key, 16);
    SHA1_Update(&ctx, pData, uLen);
    SHA1_Final(intermediate_key, &ctx);

    SHA1_Init(&ctx);
    SHA1_Update(&ctx, fixed_key, 16);
    SHA1_Update(&ctx, intermediate_key, 20);
    SHA1_Update(&ctx, pData, uLen);
    SHA1_Final(intermediate_iv, &ctx);

    SHA1_Init(&ctx);
    SHA1_Update(&ctx, intermediate_key, 16);
    SHA1_Update(&ctx, intermediate_iv, 16);
    SHA1_Final(Hash, &ctx);
}

struct HashAlgorithmEntry
{
    const char  *szName;            // name of the hash algorithm
    void        *pHashAlgorithm;    // function pointer to the hash algorithm's implementation
    unsigned int    uHashLen;       // output length of the hash algorithm, MIN_HASH_LEN <= uHashLen <= MAX_HASH_LEN

    // input plaintext length range supported by the hash algorithm's implementation
    unsigned int    uPlaintextLenMin;
    unsigned int    uPlaintextLenMax;
};

struct HashAlgorithmEntry HashAlgorithms[] = {  // this symbol will be exported
    {"audible", (void *)Audible, 20, 4, 4},     // always 4 bytes
    {0, 0, 0, 0, 0},                            // terminated by an entry of all zeroes
};
