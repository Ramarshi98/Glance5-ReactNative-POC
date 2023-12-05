//  Copyright © 2017 Glance Networks, Inc. - All rights reserved.
//
//  GlanceVoice.h
//  GlanceVoice
//
//

#import <UIKit/UIKit.h>

//! Project version number for GlanceVoice.
FOUNDATION_EXPORT double GlanceVoiceVersionNumber;

//! Project version string for GlanceVoice.
FOUNDATION_EXPORT const unsigned char GlanceVoiceVersionString[];

FOUNDATION_EXPORT NSString *const GlanceVoiceErrorDomain;

#import "GlanceVoiceDelegate.h"

@interface GlanceVoice : NSObject

+(void)setDelegate:(id<GlanceVoiceDelegate>)delegate;

+(void)authenticate:(NSUInteger)groupId apiKey:(NSString*)apiKey;

+(void)startCall:(NSString*)json;
+(void)startCall:(NSString*)accessToken number:(NSString*)number pin:(NSString*)pin name:(NSString*)name;
+(void)endCall;
+(BOOL)inCall;
+(void)setMuted:(BOOL)muted;
+(BOOL)isMuted;

+(void)setSpeakerphoneEnabled:(BOOL)enabled;

+(void)setGlanceServer:(NSString*)server;

+(BOOL)isAvailable;

@end
