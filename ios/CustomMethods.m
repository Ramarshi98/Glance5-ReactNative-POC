//
//  CustomMethods.m
//  AwesomeTestProject
//
//  Created by Raahil on 5/1/23.
//

#import <Foundation/Foundation.h>
#import "React/RCTBridgeModule.h"

@interface RCT_EXTERN_MODULE(CustomMethods, NSObject)
  RCT_EXTERN_METHOD(simpleMethod)
  RCT_EXTERN_METHOD(startVisitorSession:
    (RCTResponseSenderBlock) callback
  )
  RCT_EXTERN_METHOD(startPresence:
    (NSString *) groupId
    callback: (RCTResponseSenderBlock)callback
  )
  RCT_EXTERN_METHOD(endSession:
    (RCTResponseSenderBlock) callback
  )
  RCT_EXTERN_METHOD(
    resolvePromise: (RCTPromiseResolveBlock) resolve
    rejecter: (RCTPromiseRejectBlock) reject
  )
  RCT_EXTERN_METHOD(rejectPromise:
    (RCTPromiseResolveBlock) resolve
    rejecter: (RCTPromiseRejectBlock) reject
  )
@end
