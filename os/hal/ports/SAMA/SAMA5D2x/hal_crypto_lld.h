/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    hal_cry_lld.h
 * @brief   PLATFORM cryptographic subsystem low level driver header.
 *
 * @addtogroup CRYPTO
 * @{
 */

#ifndef HAL_CRYPTO_LLD_H
#define HAL_CRYPTO_LLD_H

#if HAL_USE_CRY || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    Driver capability switches
 * @{
 */
#define CRY_LLD_SUPPORTS_AES                TRUE
#define CRY_LLD_SUPPORTS_AES_ECB            TRUE
#define CRY_LLD_SUPPORTS_AES_CBC            TRUE
#define CRY_LLD_SUPPORTS_AES_CFB            TRUE
#define CRY_LLD_SUPPORTS_AES_CTR            TRUE
#define CRY_LLD_SUPPORTS_AES_GCM            TRUE
#define CRY_LLD_SUPPORTS_DES                TRUE
#define CRY_LLD_SUPPORTS_DES_ECB            TRUE
#define CRY_LLD_SUPPORTS_DES_CBC            TRUE
/** @{ */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    PLATFORM configuration options
 * @{
 */
/**
 * @brief   CRY1 driver enable switch.
 * @details If set to @p TRUE the support for CRY1 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(PLATFORM_CRY_USE_CRY1) || defined(__DOXYGEN__)
#define PLATFORM_CRY_USE_CRY1                  FALSE
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

typedef struct
{
	uint32_t encrypt;
	uint32_t block_size;
	uint32_t mode;
	const uint8_t *iv;
}aesparams;

typedef enum  {
	TRANSFER_DMA = 0,
	TRANSFER_POLLING,
}crytransfermode_t;

typedef enum  {
	AES_CFBS_128 = 0,
	AES_CFBS_64,
	AES_CFBS_32,
	AES_CFBS_16,
	AES_CFBS_8
}aesciphersize_t;


/**
 * @brief   CRY key identifier type.
 */
typedef uint32_t crykey_t;

/**
 * @brief   Type of a structure representing an CRY driver.
 */
typedef struct CRYDriver CRYDriver;

/**
 * @brief   Driver configuration structure.
 * @note    It could be empty on some architectures.
 */


typedef enum  {
	TDES_ALGO_SINGLE = 0,
	TDES_ALGO_TRIPLE,
	TDES_ALGO_XTEA
}tdes_algo_t;

typedef struct {

	crytransfermode_t				transfer_mode;
	uint32_t                 		cfbs;
	tdes_algo_t						tdes_algo;

} CRYConfig;

#define CRY_DRIVER_EXT_FIELDS	thread_reference_t        thread;		\
								sama_dma_channel_t       *dmarx;		\
								sama_dma_channel_t       *dmatx;		\
								uint32_t                 rxdmamode;		\
								uint32_t                 txdmamode;		\
								uint8_t						dmawith;		\
								uint8_t				 dmachunksize;	\
								uint8_t enabledPer;
/**
 * @brief   Structure representing an CRY driver.
 */
struct CRYDriver {
  /**
   * @brief   Driver state.
   */
  crystate_t                state;
  /**
   * @brief   Current configuration data.
   */
  const CRYConfig           *config;
  /**
   * @brief   Algorithm type of transient key.
   */
  cryalgorithm_t            key0_type;
  /**
   * @brief   Size of transient key.
   */
  size_t                    key0_size;
#if (HAL_CRY_USE_FALLBACK == TRUE) || defined(__DOXYGEN__)
  /**
   * @brief   Key buffer for the fall-back implementation.
   */
  uint8_t                   key0_buffer[HAL_CRY_MAX_KEY_SIZE];
#endif
#if defined(CRY_DRIVER_EXT_FIELDS)
  CRY_DRIVER_EXT_FIELDS
#endif
  /* End of the mandatory fields.*/
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if (PLATFORM_CRY_USE_CRY1 == TRUE) && !defined(__DOXYGEN__)
extern CRYDriver CRYD1;
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void cry_lld_init(void);
  void cry_lld_start(CRYDriver *cryp);
  void cry_lld_stop(CRYDriver *cryp);
  cryerror_t cry_lld_loadkey(CRYDriver *cryp,
                             cryalgorithm_t algorithm,
                             size_t size,
                             const uint8_t *keyp);
  cryerror_t cry_lld_encrypt_AES(CRYDriver *cryp,
                                 crykey_t key_id,
                                 const uint8_t *in,
                                 uint8_t *out);
  cryerror_t cry_lld_decrypt_AES(CRYDriver *cryp,
                                 crykey_t key_id,
                                 const uint8_t *in,
                                 uint8_t *out);
  cryerror_t cry_lld_encrypt_AES_ECB(CRYDriver *cryp,
                                     crykey_t key_id,
                                     size_t size,
                                     const uint8_t *in,
                                     uint8_t *out);
  cryerror_t cry_lld_decrypt_AES_ECB(CRYDriver *cryp,
                                     crykey_t key_id,
                                     size_t size,
                                     const uint8_t *in,
                                     uint8_t *out);
  cryerror_t cry_lld_encrypt_AES_CBC(CRYDriver *cryp,
                                     crykey_t key_id,
                                     size_t size,
                                     const uint8_t *in,
                                     uint8_t *out,
                                     const uint8_t *iv);
  cryerror_t cry_lld_decrypt_AES_CBC(CRYDriver *cryp,
                                     crykey_t key_id,
                                     size_t size,
                                     const uint8_t *in,
                                     uint8_t *out,
                                     const uint8_t *iv);
  cryerror_t cry_lld_encrypt_AES_CFB(CRYDriver *cryp,
                                     crykey_t key_id,
                                     size_t size,
                                     const uint8_t *in,
                                     uint8_t *out,
                                     const uint8_t *iv);
  cryerror_t cry_lld_decrypt_AES_CFB(CRYDriver *cryp,
                                     crykey_t key_id,
                                     size_t size,
                                     const uint8_t *in,
                                     uint8_t *out,
                                     const uint8_t *iv);
  cryerror_t cry_lld_encrypt_AES_CTR(CRYDriver *cryp,
                                     crykey_t key_id,
                                     size_t size,
                                     const uint8_t *in,
                                     uint8_t *out,
                                     const uint8_t *iv);
  cryerror_t cry_lld_decrypt_AES_CTR(CRYDriver *cryp,
                                     crykey_t key_id,
                                     size_t size,
                                     const uint8_t *in,
                                     uint8_t *out,
                                     const uint8_t *iv);
  cryerror_t cry_lld_encrypt_AES_GCM(CRYDriver *cryp,
                                     crykey_t key_id,
                                     size_t size,
                                     const uint8_t *in,
                                     uint8_t *out,
                                     const uint8_t *iv,
                                     size_t aadsize,
                                     const uint8_t *aad,
                                     uint8_t *authtag);
  cryerror_t cry_lld_decrypt_AES_GCM(CRYDriver *cryp,
                                     crykey_t key_id,
                                     size_t size,
                                     const uint8_t *in,
                                     uint8_t *out,
                                     const uint8_t *iv,
                                     size_t aadsize,
                                     const uint8_t *aad,
                                     uint8_t *authtag);
  cryerror_t cry_lld_encrypt_DES(CRYDriver *cryp,
                                 crykey_t key_id,
                                 const uint8_t *in,
                                 uint8_t *out);
  cryerror_t cry_lld_decrypt_DES(CRYDriver *cryp,
                                 crykey_t key_id,
                                 const uint8_t *in,
                                 uint8_t *out);
  cryerror_t cry_lld_encrypt_DES_ECB(CRYDriver *cryp,
                                    crykey_t key_id,
                                    size_t size,
                                    const uint8_t *in,
                                    uint8_t *out);
  cryerror_t cry_lld_decrypt_DES_ECB(CRYDriver *cryp,
                                     crykey_t key_id,
                                     size_t size,
                                     const uint8_t *in,
                                     uint8_t *out);
  cryerror_t cry_lld_encrypt_DES_CBC(CRYDriver *cryp,
                                     crykey_t key_id,
                                     size_t size,
                                     const uint8_t *in,
                                     uint8_t *out,
                                     const uint8_t *iv);
  cryerror_t cry_lld_decrypt_DES_CBC(CRYDriver *cryp,
                                     crykey_t key_id,
                                     size_t size,
                                     const uint8_t *in,
                                     uint8_t *out,
                                     const uint8_t *iv);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_CRY */

#endif /* HAL_CRYPTO_LLD_H */

/** @} */
