//  Copyright © 2017 Glance Networks, Inc. - All rights reserved.
//
//  GlanceVoiceDelegate.h
//  GlanceVoice
//
//

#import <Foundation/Foundation.h>

@protocol GlanceVoiceDelegate <NSObject>

@optional

- (void) glanceVoiceAuthenticateDidSucceed:(NSString *)value;
- (void) glanceVoiceAuthenticateDidFail:(NSError*) error;

- (void) glanceVoiceStartDidSucceed;
- (void) glanceVoiceStartDidFail:(NSError*)error;
- (void) glanceVoiceDidDisconnectWithError:(NSError*)error;
- (void) glanceVoiceReconnecting;
- (void) glanceVoiceDidReconnect;
- (void) glanceVoiceReconnectDidTimeout;

@end
