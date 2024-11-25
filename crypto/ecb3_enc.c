/****************************************************************************
 * crypto/ecb3_enc.c
 *
 * SPDX-License-Identifier: SSLeay-standalone
 * SPDX-FileCopyrightText: Copyright (C) 1995 Eric Young (eay@mincom.oz.au)
 * SPDX-FileCopyrightText: Eric Young (eay@mincom.oz.au).
 *
 * This file is part of an SSL implementation written
 * by Eric Young (eay@mincom.oz.au).
 * The implementation was written so as to conform with Netscapes SSL
 * specification.  This library and applications are
 * FREE FOR COMMERCIAL AND NON-COMMERCIAL USE
 * as long as the following conditions are adhered to.
 *
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.  If this code is used in a product,
 * Eric Young should be given attribution as the author of the parts used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed
 *    by Eric Young (eay@mincom.oz.au)
 *
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.
 * i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include "des_locl.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

void des_ecb3_encrypt(FAR des_cblock *input, FAR des_cblock *output,
                      caddr_t ks1, caddr_t ks2, caddr_t ks3, int encrypt)
{
  register uint32_t l0;
  register uint32_t l1;
  FAR register unsigned char *in;
  FAR register unsigned char *out;
  uint32_t ll[2];

  in = (FAR unsigned char *)input;
  out = (FAR unsigned char *)output;
  c2l(in, l0);
  c2l(in, l1);
  IP(l0, l1);
  ll[0] = l0;
  ll[1] = l1;
  des_encrypt2(ll, ks1, encrypt);
  des_encrypt2(ll, ks2, !encrypt);
  des_encrypt2(ll, ks3, encrypt);
  l0 = ll[0];
  l1 = ll[1];
  FP(l1, l0);
  l2c(l0, out);
  l2c(l1, out);
}
