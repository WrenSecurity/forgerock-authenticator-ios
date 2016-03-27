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
 *
 * Portions Copyright 2014 Nathaniel McCallum, Red Hat
 */

#include "FRAIdentity.h"
#include "FRAMechanism.h"
#include "FRAOathCode.h"

/*!
 * An OATH authentication mechanism capable of generating HMAC- and Time-based One-Time Passwords.
 */
@interface FRAOathMechanism : NSObject <FRAMechanism>

/*!
 * The storage ID of this OATH mechanism.
 */
@property (nonatomic) NSInteger uid;
/*!
 * The version number of this OATH mechanism.
 */
@property (nonatomic, readonly) NSInteger version;
/*!
 * The identity to which this OATH mechanism is registered.
 */
@property (nonatomic, readonly) FRAIdentity* owner;
/*!
 * The type of this OATH mechanism (totp or hotp).
 */
@property (nonatomic, readonly) NSString* type;
/*!
 * The length of the OATH code generated by this mechanism. Always 6 or 8; defaults to 6.
 */
@property (nonatomic, readonly) NSUInteger digits;
/*!
 * The current login code for this OATH mechanism.
 */
@property (nonatomic, readonly) FRAOathCode* code;

/*!
 * Initializer which parses an OATH URL to extract all configuration detail.
 *
 * Extracted parameters include:
 * - Token type (HOTP, TOTP)
 * - Issuer
 * - Account Name
 * - Secret Key
 * - Algorithm (SHA1, MD5 etc)
 * - Counter
 *
 * @param url is the entire URL to parse.
 * @return instantiated instance or nil if a problem occurred.
 */
- (instancetype)initWithURL:(NSURL*)url;
/*!
 * Initializer which parses an OATH URL String to extract all configuration detail.
 *
 * Extracted parameters include:
 * - Token type (HOTP, TOTP)
 * - Issuer
 * - Account Name
 * - Secret Key
 * - Algorithm (SHA1, MD5 etc)
 * - Counter
 *
 * @param url is the entire URL to parse.
 * @return instantiated instance or nil if a problem occurred.
 */
- (instancetype)initWithString:(NSString*)string;

@end
