/* ====================================================================
 * Copyright (c) 2016 The OpenSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit. (http://www.OpenSSL.org/)"
 *
 * 4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    licensing@OpenSSL.org.
 *
 * 5. Products derived from this software may not be called "OpenSSL"
 *    nor may "OpenSSL" appear in their names without prior written
 *    permission of the OpenSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit (http://www.OpenSSL.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE OpenSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef HEADER_INTERNAL_THREADS_H
# define HEADER_INTERNAL_THREADS_H

#include "e_os.h"

/* 
 * The Linux 2.8 release provides Pthreads limited support.
 * We need to uncomment the definitions below to avoid
 * conflicts with those in the SGX SDK pthread.h header file
 * in include/tlibc.
 */

// definitions taken from pthreadtypes.h:

/* Keys for thread-specific data */
//typedef unsigned int pthread_key_t;

/* Once-only execution */
//typedef int pthread_once_t;

/* Thread identifiers.  The structure of the attribute type is not
   exposed on purpose.  */
//typedef unsigned long int pthread_t;

/* Single execution handling.  */
//#define PTHREAD_ONCE_INIT 0

////////////////////////////////////////

//typedef pthread_once_t CRYPTO_ONCE;
//typedef pthread_key_t CRYPTO_THREAD_LOCAL;
//typedef pthread_t CRYPTO_THREAD_ID;

//#define CRYPTO_ONCE_STATIC_INIT PTHREAD_ONCE_INIT

//int CRYPTO_THREAD_run_once(CRYPTO_ONCE *once, void (*init)(void));

//int CRYPTO_THREAD_init_local(CRYPTO_THREAD_LOCAL *key, void (*cleanup)(void *));
//void *CRYPTO_THREAD_get_local(CRYPTO_THREAD_LOCAL *key);
//int CRYPTO_THREAD_set_local(CRYPTO_THREAD_LOCAL *key, void *val);
//int CRYPTO_THREAD_cleanup_local(CRYPTO_THREAD_LOCAL *key);

//CRYPTO_THREAD_ID CRYPTO_THREAD_get_current_id(void);
//int CRYPTO_THREAD_compare_id(CRYPTO_THREAD_ID a, CRYPTO_THREAD_ID b);

#endif
