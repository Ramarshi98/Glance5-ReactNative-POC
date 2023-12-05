//  RCTCalendarModule.h
#import <React/RCTBridgeModule.h>
#import "RCTCalendarModule.m"
#import <React/RCTLog.h>

@interface RCTCalendarModule : NSObject <RCTBridgeModule>

RCT_EXPORT_METHOD(createCalendarEvent:(NSString *)name location:(NSString *)location);

@end
