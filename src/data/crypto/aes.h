// SPDX-FileCopyrightText: TinyAES Striped to support only AES for ff7tk by Chris Rizzitello <sithlord48@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************/
//    TinyAES Striped for our specific needs                                //
//    Origin: https://github.com/kokke/tiny-AES-c                           //
/****************************************************************************/

#ifndef _AES_H_
#define _AES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define AES_BLOCKLEN 16 //Block length in bytes AES is 128b block only
#define AES_KEYLEN 16   // Key length in bytes
#define AES_keyExpSize 176

struct AES_ctx
{
  uint8_t RoundKey[AES_keyExpSize];
  uint8_t Iv[AES_BLOCKLEN];
};

void AES_init_ctx_iv(struct AES_ctx* ctx, const uint8_t* key, const uint8_t* iv);
void XorWithIv(uint8_t* buf, const uint8_t* Iv);
void XorWithByte(uint8_t* buf, uint8_t byte, int length);

// buffer size is exactly AES_BLOCKLEN bytes; 
// you need only AES_init_ctx as IV is not used in ECB 
// NB: ECB is considered insecure for most uses
void AES_ECB_encrypt(const struct AES_ctx* ctx, uint8_t* buf);
void AES_ECB_decrypt(const struct AES_ctx* ctx, uint8_t* buf);

#ifdef __cplusplus
}
#endif
#endif //_AES_H_
