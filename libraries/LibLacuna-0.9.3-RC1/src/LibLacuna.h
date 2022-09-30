/*
 *  _                                   ____                       
 * | |    __ _  ___ _   _ _ __   __ _  / ___| _ __   __ _  ___ ___ 
 * | |   / _` |/ __| | | | '_ \ / _` | \___ \| '_ \ / _` |/ __/ _ \
 * | |__| (_| | (__| |_| | | | | (_| |  ___) | |_) | (_| | (_|  __/
 * |_____\__,_|\___|\__,_|_| |_|\__,_| |____/| .__/ \__,_|\___\___|
 *                                           |_|                   
 * Copyright (C) 2021 Lacuna Space Ltd.
 *
 * Description:
 * 
 * License: Revised BSD License, see LICENSE-LACUNA.TXT file included in the project
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

 /*!
 * This library implements sending of Lora and LR-FHSS packets
 * on Semtech SX1262 and SX1276 devices. Packets can be sent
 * either as raw data, or as LoraWAN.
 *
 * Usage is as follows:
 * 1) Initialize the device, by either calling `lsInitSX1276` or `lsInitSX126x`, 
 *    depending on the device-type.
 * 2) Send a message. This is done by one of the following functions:
 *    - `lsSendLora`, to send a raw Lora packet
 *    - `lsSendLoraWAN`, to send a LoraWAN packet over Lora
 * 3) Repeat step 2) as often as desired.
 */

#ifndef _LACUNA_H_
#define _LACUNA_H_

#define LIBLACUNA_VERSION "0.9.3"

#define R_EU868 (0x01) 
#define R_US915 (0x02)
#define R_AS923 (0x03)
#define R_IN865 (0x04)
#define R_AU915 (0x05)

#ifndef REGION
#define REGION R_EU868
#endif

#ifndef BOARD_VERSION
#define BOARD_VERSION 0
#endif

#include <Arduino.h>

#define LS_LORA_SYNCWORD_PRIVATE	(0x1424)
#define LS_LORA_SYNCWORD_PUBLIC	(0x3444)

#define RX2_FREQ_EU863_870	869525000
#define RX2_FREQ_US902_928	923300000
#define RX2_FREQ_AS923		923200000
#define RX2_FREQ_AU915_928	923300000
#define RX2_FREQ_IN865_867	866550000

#define RX2_SF_EU863_870	lsLoraSpreadingFactor_9
#define	RX2_SF_US902_928	lsLoraSpreadingFactor_12
#define	RX2_SF_AU915_928	lsLoraSpreadingFactor_12
#define	RX2_SF_AS923		lsLoraSpreadingFactor_10
#define	RX2_SF_IN865_867	lsLoraSpreadingFactor_10

typedef enum {
	 EU863_870 = 1,
	 US902_928 = 2,
	 AS923 = 3,
	 AU915_928 = 4,
	 IN865_867 = 5
} lsLoraChannelPlan;

typedef enum {
	 lsLoraCodingRate_4_5 = 1,
	 lsLoraCodingRate_4_6 = 2,
	 lsLoraCodingRate_4_7 = 3,
	 lsLoraCodingRate_4_8 = 4
} lsLoraCodingRate;

typedef enum {
	lsLoraSpreadingFactor_5 = 5,
	lsLoraSpreadingFactor_6 = 6,
	lsLoraSpreadingFactor_7 = 7,
	lsLoraSpreadingFactor_8 = 8,
	lsLoraSpreadingFactor_9 = 9,
	lsLoraSpreadingFactor_10 = 10,
	lsLoraSpreadingFactor_11 = 11,
	lsLoraSpreadingFactor_12 = 12
} lsLoraSpreadingFactor;

typedef enum {
	 lsLoraBandwidth_7_81_khz = 0,
	 lsLoraBandwidth_10_41_khz = 1,
	 lsLoraBandwidth_15_62_khz = 2,
	 lsLoraBandwidth_20_83_khz = 3,
	 lsLoraBandwidth_31_25_khz = 4,
	 lsLoraBandwidth_41_66_khz = 5,
	 lsLoraBandwidth_62_50_khz = 6,
	 lsLoraBandwidth_125_khz = 7,
	 lsLoraBandwidth_250_khz = 8,
	 lsLoraBandwidth_500_khz = 9
} lsLoraBandwidth;

/*! Datastructure used in initialisation of an SX1276 device */
typedef struct {
    byte nssPin;            /*!< Arduino pin-number to which the SX1276 `NSS` pin is connected . Example: `10` */
    byte resetPin;          /*!< Arduino pin-number to which the SX1276 `NRESET` pin is connected. Example: `A0` */
    byte antennaSwitchPin;  /*!< Arduino pin-number to which the SX1276 `RXTX` pin is connected. Example: `A4` */
    bool paBoost;        /*!< Indicates if PA_BOOST is to be used. */
} lsSX1276Config;

/*! Enum indicating the type of oscillator used by the SX126x */
typedef enum {
	lsSX126xOscXtal,        /*!< Indicates a crystal oscillator */
	lsSX126xOscTCXO         /*!< Indicates a temperature compensated oscillator */
} lsSX126xOsc;

/*! Enum indicating the type of SX126x device */
typedef enum {
	lsSX126xTypeSX1261,     /*!< Indicates an SX1261 */
	lsSX126xTypeSX1262      /*!< Indicated an SX1262 */
} lsSX126xType;

/*! Datastructure used in initialisation of an SX126x device */
typedef struct {
	byte nssPin;                    /*!< Arduino pin-number to which the SX126x `NSS` pin is connected. Example: `7` */
	byte resetPin;                  /*!< Arduino pin-number to which the SX126x `NRESET` pin is connected. Example: `A0` */
	byte antennaSwitchPin;          /*!< Arduino pin-number to which the SX126x `RXEN` pin is connected. Example: `8` */
	byte busyPin;                   /*!< Arduino pin-number to which the SX126x `BUSY` pin is connected. Example: `2` */
	byte dio1Pin;					/*!< Arduino pin-number to which the SX126x `DIO1` pin is connected. Example: `5` */
	lsSX126xOsc osc;                /*!< Oscillator type used */
	lsSX126xType type;              /*!< Device type used */
} lsSX126xConfig;

/*! Datastructure containing parameters used when sending a Lora packet */
typedef struct {
    int8_t power;                           /*!< Transmission power in dBm */
    lsLoraSpreadingFactor spreadingFactor;  /*!< Spreading factor */
    lsLoraCodingRate codingRate;            /*!< Coding rate */
    bool invertIq;                       	/*!< Set to `true` to invert I/Q signals */
    uint32_t frequency;                     /*!< Transmission frequency, in Hz */
    lsLoraBandwidth bandwidth;              /*!< Bandwidth */
    lsLoraChannelPlan channelplan;			/*!< LoRaWAN channel plan */
    int8_t snr;								/*!< SNR of last received packet */
	int16_t rssi;							/*!< RSSI in dBm of last received packet */
	int16_t signalrssi;						/*!< Signal strength in dBm of last received packet */
	int32_t frequency_error;				/*!< Frequency error of received message in Hz */
    unsigned int syncWord;                  /*!< Syncword to use, use one of `LS_LORA_SYNCWORD_PRIVATE`
                                                                          or `LS_LORA_SYNCWORD_PUBLIC` */
    unsigned int preambleLength;            /*!< Length of the preamble. Use 8 if you have no special requirements. */
    bool preambleRelay;						/*!< Enable long preamble for relay */
    bool ldro;								/*!< Set true to set lowDataRateOptimization regardless of BW/SF */
    uint32_t rxTimeout;						/*!< Timeout in milliseconds for receive */
} lsLoraTxParams;

/*! Enum to specify the LoraWAN framecounter size */
typedef enum {
	lsLoraWANFramecounterSize16 = 16,
	lsLoraWANFramecounterSize32 = 32
} lsLoraWANFramecounterSize;

/*! Enum to specify the LoraWAN minor version */
typedef enum {
	lsLoraWANMinorVersion0 = 0,
} lsLoraWANMinorVersion;

/*! Datastructure containing parameters to send a LoraWAN packet */
typedef struct {
	byte networkKey[16];                            /*!< The LoraWAN network session key */
	byte applicationKey[16];                        /*!< The LoraWAN application key */
	byte deviceAddress[4];                          /*!< The LoraWAN device address (MSB first) */
	byte mc_networkKey[16];                         /*!< The LoraWAN multicast network session key */
	byte mc_applicationKey[16];                     /*!< The LoraWAN multicast application key */
	byte mc_deviceAddress[4];                       /*!< The LoraWAN multicast device address (MSB first) */
	lsLoraWANFramecounterSize framecounterSize;     /*!< Specifies whether to use 16- or 32-bits framecounter */
	unsigned int framecounter;                      /*!< The framecounter value */
	unsigned int framecounter_down; 				/*!< The framecounter value for downlink */
	unsigned int framecounter_mc;					/*!< The framecounter value for multicast downlink */
	lsLoraWANMinorVersion minorVersion;             /*!< The LoraWAN minor version */
	uint8_t txPort;         					    /*!< The LoraWAN port number to use to transmit */
	uint8_t rxPort;									/*!< The LoraWAN port number of the last received message */
	uint8_t	rxMc;									/*!< Last received message was multicast */
	uint8_t rxEnable;								/*!< Listen for incoming messages in RX1 and RX2 windows */
	uint8_t rxpayloadLength;						/*!< Length of the last received message, 0 if nothing received */
} lsLoraWANParams;

#define LS_OK                       		(0)
#define LS_ERR_NULL_POINTER         		(-1)
#define LS_ERR_INVALID_PIN          		(-2)
#define LS_ERR_INVALID_OSC				(-3)
#define LS_ERR_INVALID_TYPE				(-4)
#define LS_ERR_INVALID_SYNCWORD			(-5)
#define LS_ERR_INVALID_BANDWIDTH	   		(-50)
#define LS_ERR_INVALID_CODINGRATE   		(-51)
#define LS_ERR_INVALID_DATARATE     		(-52)
#define LS_ERR_INVALID_SPREADINGFACTOR	(-53)
#define LS_ERR_INVALID_GRID				(-54)
#define LS_ERR_INVALID_NBSYNC			(-55)
#define LS_ERR_INVALID_CHANNELPLAN		(-56)
#define LS_ERR_INVALID_PREAMBLE_LENGTH      (-57)
#define LS_ERR_HARDWARE             		(-100)
#define LS_ERR_ALREADY_INITIALIZED  		(-200)
#define LS_ERR_NOT_INITIALIZED      		(-201)
#define LS_ERR_PAYLOAD_TOO_LONG       	(-300)
#define LS_ERR_INVALID_FRAMECOUNTER_SIZE	(-400)
#define LS_ERR_INVALID_MINOR_VERSION		(-401)
#define LS_ERR_NOT_IMPLEMENTED			(-500)
#define LS_ERR_NO_DETECT				(-600)
#define LS_ERR_CRC						(-601)
#define LS_ERR_TIMEOUT					(-602)

/*!
 * Populates the given `lsSX1276Config` struct with default configuration.
 * Using this function is optional - alternatively, you can populate the
 * struct yourself, or first use this function to generate a default
 * configuration and then override specific fields with custom values.
 *
 * The settings used by this function are applicable for an SX1276MB1xAS Mbed board or
 * compatible:
 * - `nssPin` is set to `10`
 * - `resetPin` is set to `A0`
 * - `antennaSwitchPin` is set to `A4`
 * - `paBoost` is set to `false`
 * 
 * \param cfg Pointer to an `lsSX1276Config` struct allocated by the caller.
 */
void lsCreateDefaultSX1276Config(lsSX1276Config *cfg);

/*!
 * Populates the given `lsSX126xConfig` struct with default configuration.
 * Using this function is optional - alternatively, you can populate the
 * struct yourself, or first use this function to generate a default
 * configuration and then override specific fields with custom values.
 *
 * The settings used by this function are applicable for an SX126xMB2xAS Mbed board, or
 * compatible such as the Lacuna LS101/102 boards:
 * - `nssPin` is set to `7`
 * - `resetPin` is set to `A0`
 * - `antennaSwitchPin` is set to `8`
 * - `busyPin` is set to `2`
 * - `osc` is set to `lsSX126xOscTCXO`
 * - `type` is set to `lsSX126xTypeSX1262`
 * 
 * \param cfg Pointer to an `lsSX126xConfig` struct allocated by the caller.
 */
void lsCreateDefaultSX126xConfig(lsSX126xConfig *cfg, uint8_t board_version);

/*!
 * Populates the given `lsLoraTxParams` struct with a default configuration.
 * Using this function is optional - alternatively, you can populate the
 * struct yourself, or first use this function to generate a default
 * configuration and then override specific fields with custom values.
 *
 * The settings used by this function are:
 * - `power` is set to `14`
 * - `spreadingfactor` is set to `lsLoraSpreadingFactor_7`
 * - `codingRate` is set to `lsLoraCodingRate_4_5`
 * - `invertIq` is set to `false`
 * - `frequency` is set to `868100000`
 * - `bandwidth` is set to `lsLoraBandwidth_125_khz`
 * - `syncword` is set to `LS_LORA_SYNCWORD_PUBLIC`
 * - `preambleLength` is set to `8`
 * This is suitable for use with TheThingsNetwork in the EU. If you
 * are in a different geographic location, or you use a different network,
 * you may have to change parameters.
 * 
 * \param params Pointer to an `lsLoraTxParams` struct allocated by the caller.
 */
void lsCreateDefaultLoraTxParams(lsLoraTxParams *params, uint8_t region);

/*!
 * Populates the given `lsLoraWANParams` struct with a default confguration, using the
 * `networkKey`  `applicationKey` and `deviceAddress` supplied.
 * Using this function is optional - alternatively, you can populate the
 * struct yourself, or first use this function to generate a default
 * configuration and then override specific fields with custom values.
 * 
 * The settings used by this function are:
 * - `framecounter` is set to `0`
 * - `framecounterSize` is set to `lsLoraWANFramecounterSize32`
 * - `minorVersion` is set to `lsLoraWANMinorVersion0`
 * Additionally, the given `networkKey`, `applicationKey` and `deviceAddress` are
 * copied into the `lsLoraWANParams` struct. 
 * The settings used are suitable for use with TheThingsNetwork and/or Lacuna Space.
 *
 * \param params pointer to `lsLoraWANParams` struct allocated by the caller
 * \param networkKey pointer to an array of 16 bytes containing the LoraWAN network key. The network
 *                   key will be copied by this function, and can be safely deallocated after this function
 *                   returns.
 * \param applicationKey pointer to an array of 16 bytes containing the LoraWAN applicaton key. The 
 *                       key will be copied by this function, and can be safely deallocated after this function
 *                       returns.
 * \param deviceAddress pointer to an array ot 4 bytes containing the LoraWAN device address, MSB first. The
 *                      device address will be copied by this function, and can be safelt deallocated after this
 *                      function returns.
 * \return `LS_OK` if initialisation was successfull, or one of the `LS_ERR_*` constants when an error occurs.
*/
int lsCreateDefaultLoraWANParams(lsLoraWANParams *params, byte *networkKey, byte *applicationKey, byte *deviceAddress);

/*!
 * Initialises the library for use with an `SX1276` device. 
 *
 * \param cfg Pointer to an `lsSX1276Config` struct. The struct is copied by the `lsInitSX1276`
 *            function, and can safely be discarded after this function returns.
 *
 * \return `LS_OK` if initialisation was successful, or an other value if there was an error. Use
 *                  `lsErrorToString` to obtain a human-readable error-message. 
 */
int lsInitSX1276(lsSX1276Config *cfg);

/*!
 * Initialises the library for use with an `SX126x` device. 
 *
 * \param cfg Pointer to an `lsSX126xConfig` struct. The struct is copied by the `lsInitSX126x`
 *            function, and can safely be discarded after this function returns.
 *
 * \return `LS_OK` if initialisation was successful, or an other value if there was an error. Use
 *                  `lsErrorToString` to obtain a human-readable error-message. 
 */
int lsInitSX126x(lsSX126xConfig *cfg, uint8_t region);

/*!
 * Sends a raw Lora packet.
 *
 * This is a blocking function -- it doesn't return until either the packet has been transmitted,
 * or an error has occurred.
 * The library must have been initialised before this function can be used.
 *
 * \param lsLoraTxParams Pointer to an `lsLoraTxParams` struct containing Lora-related parameters.
 * \param payload Pointer to an array of bytes containing the payload to be sent.
 * \param payloadSize Number of bytes in `payload`. Maximum allowed payload length is 255 bytes.
 *
 * \return `LS_OK` if transmission was successful, or an other value if there was an error. Use
 *                  `lsErrorToString` to obtain a human-readable error-message.
 */
int lsSendLora(lsLoraTxParams *params, byte *payload, byte payloadSize, byte rxenable);

/*!
 * Sends a LoraWAN packet over Lora.
 *
 * This is a blocking function -- it doesn't return until either the packet has been transmitted,
 * or an error has occurred.
 * The library must have been initialised before this function can be used.
 * 
 * \param loraWanParams Pointer to an `lsLoraWanParams` struct containing LoraWAN-related parameters.
 * \param loraParams Pointer to an `lsLoraTxParams` struct containing Lora-related parameters.
 * \param payload Pointer to an array of bytes containing the payload to be sent.
 * \param payloadSize Number of bytes in `payload`. If the payload is too long for the parameters
 *                  that are used, `LS_ERR_PAYLOAD_TOO_LONG` will be returned.
 *
 * \return `LS_OK` if transmission was successful, or an other value if there was an error. Use
 *                  `lsErrorToString` to obtain a human-readable error-message.
 */
int lsSendLoraWAN(lsLoraWANParams *loraWanParams, lsLoraTxParams *loraParams, byte *payload, byte payloadSize);

/* Receive */
int lsReceiveLora(lsLoraTxParams *params, byte *payload);

/*!
 * Converts an error-code to a human-readable string.
 *
 * \param error error-code returned by one of the `ls*` functions
 *
 * \return a human-readable error message. Returned strings are statically allocated, and must not
 *         be de-allocated by the caller.
 */
char const *lsErrorToString(int error);

#endif
