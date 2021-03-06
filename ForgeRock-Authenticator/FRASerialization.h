/*
 * The contents of this file are subject to the terms of the Common Development and
 * Distribution License (the License). You may not use this file except in compliance with the
 * License.
 *
 * You can obtain a copy of the License at legal/CDDLv1.0.txt. See the License for the
 * specific language governing permission and limitations under the License.
 *
 * When distributing Covered Software, include this CDDL Header Notice in each file and include
 * the License file at legal/CDDLv1.0.txt. If applicable, add the following below the CDDL
 * Header, with the fields enclosed by brackets [] replaced by your own identifying
 * information: "Portions copyright [year] [name of copyright owner]".
 *
 * Copyright 2016 ForgeRock AS.
 */



/*!
 * Mechanism Secret Key
 */
extern NSString *const OATH_MECHANISM_SECRET;

/*!
 * Mechanism Hashing Algorithm
 */
extern NSString *const OATH_MECHANISM_ALGORITHM;

/*!
 * Mechanism Key length
 */
extern NSString *const OATH_MECHANISM_DIGITS;

/*!
 * Mechanism TOTP Period
 */
extern NSString *const OATH_MECHANISM_PERIOD;

/*!
 * Mechanism HOTP Counter
 */
extern NSString *const OATH_MECHANISM_COUNTER;

/*!
 * Storage key for Push Notification protocol version
 */
extern NSString *const PUSH_MECHANISM_VERSION;

/*!
 * Storage key for Push Notification secret key
 */
extern NSString *const PUSH_MECHANISM_SECRET;

/*!
 * Storage key for Push Notification authentication endpoint
 */
extern NSString *const PUSH_MECHANISM_AUTH_END_POINT;

/*!
 * Notification Message ID
 */
extern NSString *const NOTIFICATION_MESSAGE_ID;

/*!
 * Notification Push Challenge
 */
extern NSString *const NOTIFICATION_PUSH_CHALLENGE;

/*!
 * Notification Time To Live
 */
extern NSString *const NOTIFICATION_TIME_TO_LIVE;

/*!
 * Notification Load Balancer cookie
 */
extern NSString * const NOTIFICATION_LOAD_BALANCER_COOKIE;

/*!
 * A collection of useful data storage functions to simplify persistence
 * of data structures to JSON and back again.
 */
@interface FRASerialization : NSObject

/*!
 * Given a Dictionary of values, serialised them into JSON.
 *
 * @param dictionary Dictionary of values to map, maybe nil.
 * @param jsonString Output string to contain the JSON.
 * @param error If an error occurs, upon returns contains an NSError object that describes the problem. If you are not interested in possible errors, you may pass in NULL.
 *
 * @return NO if there was an error, otherwise YES to indicate no error occurred.
 */
+ (BOOL)serializeMap:(NSDictionary *)dictionary intoString:(NSString *__autoreleasing *)jsonString error:(NSError *__autoreleasing *)error;

/*!
 * Given a JSON string, deserialise it into a Dictionary.
 *
 * @param dictionaryJson String containing JSON to deserialise, maybe nil.
 * @param dictionary Output value to store Dictionary into.
 * @param error If an error occurs, upon returns contains an NSError object that describes the problem. If you are not interested in possible errors, you may pass in NULL.
 *
 * @return NO if there was an error, otherwise YES to indicate no error occurred.
 */
+ (BOOL)deserializeJSON:(NSString *)dictionaryJson intoDictionary:(NSDictionary *__autoreleasing *)dictionary error:(NSError *__autoreleasing *)error;

/*!
 * Given a byte array, serialise it to text using Base64.
 *
 * @param data Byte array of data to serialise, may be nil.
 * @return nil if the input was nil, otherwise non nil string containing the data.
 */
+ (NSString *)serializeBytes:(NSData *)data;

/*!
 * Given a Base64 encoded string, deserialise it to a byte array.
 *
 * @param data Encoded data to deserialise.
 * @return nil if the input was nil, otherwise non nil byte array.
 */
+ (NSData *)deserializeBytes:(NSString *)data;

/*!
 * Given an NSData object, serialise it to a hexadecimal string.
 *
 * @param data Encoded data to deserialise.
 * @return nil if the input was nil, otherwise non nil byte array.
 */
+ (NSString *)serializeSecret:(NSData *)data;

/*!
 * Given a hex encoded string, deserialise it to an NSData object.
 *
 * @param hexOfSecret hex encoded data to deserialise.
 * @return nil if the input was nil, otherwise non nil byte array.
 */
+ (NSData *)deserializeSecret:(NSString *)hexOfSecret;

/*!
 * Returns the number of seconds since 1970 for the given date.
 *
 * @param date The date to convert in seconds.
 * @return The number of seconds since 1970, or NSNULL if the date is nil.
 */
+ (id)nonNilDate:(NSDate *)date;

/*!
 * Returns the string if not nil, NSNull otherwise.
 *
 * @param string The string to check.
 * @return The string if not nil, otherwise NSNull.
 */
+ (id)nonNilString:(NSString *)string;

/*!
 * Returns the string if not nil, otherwise an empty string.
 *
 * @param string The string to check.
 * @return The string if not nil, otherwise an empty string.
 */
+ (NSString *)nullToEmpty:(NSString *)string;

@end