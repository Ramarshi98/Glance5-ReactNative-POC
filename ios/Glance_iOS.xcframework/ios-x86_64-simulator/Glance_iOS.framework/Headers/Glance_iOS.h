//  Copyright (c) 2014-2017 Glance Networks, Inc. All rights reserved.
//
//  Glance iOS Framework - Glance_iOS.h
//
//

#import <UIKit/UIKit.h>

#import "GlanceVoice.h"
#import "GlanceVoiceDelegate.h"

//! Project version number for Glance_iOS.
FOUNDATION_EXPORT double Glance_iOSVersionNumber;

//! Project version string for Glance_iOS.
FOUNDATION_EXPORT const unsigned char Glance_iOSVersionString[];

// Events -----------------------------------------------------------------------------------------

typedef enum EventCode : NSUInteger
{
    EventNone
    ,EventInvalidParameter      ///< An invalid input parameter was passed into an API method
    ,EventInvalidState          ///< There was an attempt to invoke an Action that was not valid in current state
    ,EventLoginSucceeded        ///< User login succeeded
    ,EventLoginFailed           ///< User login failed
    ,EventPrivilegeViolation    ///< There was an attempt to do something that is not permitted by the User's privileges
    ,EventInvalidWebserver      ///< Attempt to direct the client to connect to a webserver that the client has not been configured to allow
    ,EventUpgradeAvailable      ///< An upgrade to the client library is available
    ,EventUpgradeRequired       ///< An upgrade to the client library is required
    ,EventCompositionDisabled   ///< Desktop composition was disabled (Windows Vista only)
    ,EventConnectedToSession    ///< Client successfully connected to a session, or reconnected after changing roles (display to viewer or vice versa)
    ,EventSwitchingToView       ///< A viewer participant in the session has started showing his screen, so the display is switching to view
    ,EventStartSessionFailed    ///< An attempt to start a new session was unsuccessful
    ,EventJoinFailed            ///< An attempt to join a session was unsuccessful
    ,EventSessionEnded          ///< Session endded
    ,EventFirstGuestSession     ///< A guest's first-ever session just ended, prompt user to uninstall
    ,EventTunneling             ///< Connection is tunneling
    ,EventRestartRequired       ///< To complete the driver install, a machine restart is required
    ,EventConnectionWarning     ///< Connectivity has been lost
    ,EventClearWarning          ///< Connectivity has been restored
    ,EventGuestCountChange      ///< The guest count changed
    ,EventViewerClose           ///< User clicked the viewer window close button
    ,EventActionsChange         ///< The set of allowed actions changed (NOT IMPLEMENTED)
    ,EventDriverInstallError    ///< There was an error installing Glance SpeedBoost.
    ,EventRCDisabled            ///< Remote control has been disabled.
    ,EventDeviceDisconnected    ///< Captured (video) device disconnected.  Can be reconnected and session continued.
    ,EventDeviceReconnected     ///< Captured (video) device reconnected.
    ,EventGesture               ///< A gesture was received.
    ,EventException             ///< Unexpected exception
    ,EventScreenshareInvitation ///< A screenshare session invitation received from another session participant
    ,EventMessageReceived       ///< A user message was received from another session participant
    ,EventChildSessionStarted   ///< A child session started.
    ,EventChildSessionEnded     ///< A child session ended.
    ,EventJoinChildSessionFailed///< An invitation was received to join a child session was received but the session could not be found
    ,EventVisitorInitialized    ///< Visitor API successfully initialized
    ,EventPresenceConnected     ///< Visitor connected to presence service
    ,EventPresenceConnectFail   ///< Visitor failed to connect to presence service
    ,EventPresenceShowTerms     ///< The agent signaled the visitor to show terms and conditions
    ,EventPresenceStartSession  ///< The agent signaled the visitor to start a session
    ,EventPresenceSignal        ///< The agent signaled the visitor
    ,EventPresenceBlur          ///< Another application connected to presence with the same visitor id
    ,EventPresenceSendFail      ///< Failed to send a message on the presence connection due to connection drop
    ,EventPresenceNotConfigured ///< Presence is not configured or not enabled for the group
    , EventPresenceDisconnected ///< The application has disconnected from the presence service
    , EventPresenceStartVideo    ///< The agent signaled the visitor to start a video session
} EventCode;

typedef enum EventType : NSUInteger
{
    EventTypeNone,
    EventInfo,
    EventWarning,
    EventError,
    EventAssertFail
} EventType;

@interface GlanceEvent: NSObject
{
    EventCode           code;
    EventType           type;
    NSString        *   message;
    NSDictionary    *   properties;
}
@property (readonly) EventCode           code;
@property (readonly) EventType           type;
@property (readonly, retain) NSString        *   message;
@property (readonly, retain) NSDictionary    *   properties;

- (id)initWithCode:(EventCode)c type:(EventType)t message:(NSString *)msg properties:(NSDictionary *)props;
- (NSString *)getProperty:(NSString *)key;
@end


@interface GlanceBase : NSObject
{
    id      evtTarget;
    SEL     evtSelector;
}

- (void)onEventNotifyTarget:(id)target selector:(SEL)selector;

@end


// User Settings and Privileges -------------------------------------------------------------------

@interface GlanceSettings : GlanceBase
{
    void * gs;
}
- (id)init;
- (void)dealloc;

- (void)set:(NSString *)name value:(NSString *)value;
- (NSString *)get:(NSString *)name;

@end

// Settings
extern NSString * const kGlanceSettingGlanceServer;
extern NSString * const kGlanceSettingGlanceAddress;
extern NSString * const kGlanceSettingPassword;
extern NSString * const kGlanceSettingSessionKey;
extern NSString * const kGlanceSettingForceAJAX;
extern NSString * const kGlanceSettingEncrypt;
extern NSString * const kGlanceSettingEnableShowback;
extern NSString * const kGlanceSettingGIFlags;
extern NSString * const kGlanceSettingGlanceGroup;
extern NSString * const kGlanceSettingEnableAgentVideo;

// User and Group level privileges
extern NSString * const kGlancePrivRCAllowed;
extern NSString * const kGlancePrivReverseAllowed;
extern NSString * const kGlancePrivShowbackAllowed;
extern NSString * const kGlancePrivSetGIFlagsAllowed;
extern NSString * const kGlancePrivKeylessAllowed;
extern NSString * const kGlancePrivVideoAllowed;
extern NSString * const kGlancePrivForceEncryption;
extern NSString * const kGlancePrivNumGuestsAllowed;
extern NSString * const kGlancePrivShowAllowed;

// User Subscription attributes
extern NSString * const kGlanceSubIsTrial;
extern NSString * const kGlanceSubPlanTitle;
extern NSString * const kGlanceSubPlanTimeout;


// User  ------------------------------------------------------------------------------------------

@interface GlanceCredentials : NSObject
{
@public
    NSString *  username;
    int         partnerId;
    NSString *  partnerUserId;
    NSString *  loginkey;
    NSString *  gssnid;
}
@property (retain) NSString * username;
@property int partnerId;
@property (retain) NSString * partnerUserId;
@property (retain) NSString * loginkey;
@property (retain) NSString * gssnid;

- (id)  init;
- (void)dealloc;

@end

@interface GlanceUser : GlanceBase
{
    void * user;
}

- (id)  init;
- (void)dealloc;

- (void)            authenticate;
- (void)            authenticateWithUsername:(NSString *)username password:(NSString *)password;
- (void)            authenticateWithUsername:(NSString *)username key:(NSString *)loginkey;
- (void)            authenticateWithPartnerId:(int)partnerId userId:(NSString *)partnerUserId key:(NSString* )loginkey;
- (bool)            authenticated;
- (NSString *)      getAccountSetting:(NSString *)name;
- (void)            logout;
- (GlanceCredentials *)getCredentialsValidForSeconds:(int)requiredTime error:(NSString **)err;

@end

// Session Parameters and Info --------------------------------------------------------------------

@interface GlanceDisplayParams : NSObject
{
@public
    NSString *              displayName; // Either a number, or the name of a video input device
    float                   scale;
    int                     captureWidth;
    int                     captureHeight;
    bool                    video;
}
@property (retain) NSString * displayName;
@property float scale;
@property int captureWidth;
@property int captureHeight;

- (id)init;
- (void)dealloc;
@end


typedef enum GuestInfoFlags : UInt32
{
    GuestNameRequired  = 0x0200,
    GuestEmailRequired = 0x0400,
    GuestPhoneRequired = 0x0800,
    GuestNameHidden    = 0x1000,
    GuestEmailHidden   = 0x2000,
    GuestPhoneHidden   = 0x4000
} GuestInfoFlags;


@interface GlanceStartParams : NSObject
{
@public
    unsigned long           mainCallId;
    short                   maxGuests;
    bool                    show;
    unsigned long           guestInfoFlags;
    bool                    encrypt;
    NSString *              key;
    GlanceDisplayParams *   displayParams;
    bool                    requestRC;
    bool                    instantJoin;
    bool                    forceTunnel;
    bool                    viewerCloseable;
}
@property (retain) NSString * key;
@property (retain) GlanceDisplayParams *   displayParams;

- (id)init;
- (void)dealloc;
@end


@interface GlanceJoinParams : NSObject
{
@public
    unsigned long           guestID;
    bool                    decline;        // join only for the purpose of notifying host of decline
    NSString *              guestName;
    NSString *              guestPhone;
    NSString *              guestEmail;
    bool                    forceTunnel;
    bool                    viewerCloseable;
}
@property          unsigned long    guestID;
@property          bool             decline;
@property          bool             forceTunnel;
@property          bool             viewerCloseable;
@property (retain) NSString *       guestName;
@property (retain) NSString *       guestPhone;
@property (retain) NSString *       guestEmail;

- (id)init;
- (void)dealloc;
@end


@interface GlanceSessionInfo : NSObject
{
@public
    unsigned long   callId;
    int             nGuests;
    NSString *      glanceAddress;
    NSString *      key;
    NSString *      hostName;
    bool            isGuest;
    bool            isReverse;
    bool            rcEnabled;
    bool            sbEnabled;
    bool            isPaused;
    bool            isConnected;
    bool            isShowing;
    bool            isViewing;
    NSString *      displayName;
    NSString *      offerURL;
}
@property (readonly) unsigned long   callId;
@property (readonly) int             nGuests;
@property (readonly) NSString *      glanceAddress;
@property (readonly) NSString *      key;
@property (readonly) NSString *      hostName;
@property (readonly) bool            isGuest;
@property (readonly) bool            isReverse;
@property (readonly) bool            rcEnabled;
@property (readonly) bool            sbEnabled;
@property (readonly) bool            isPaused;
@property (readonly) bool            isConnected;
@property (readonly) bool            isShowing;
@property (readonly) bool            isViewing;
@property (readonly) NSString *      displayName;
@property (readonly) NSString *      offerURL;
@end


typedef enum GlanceAction : NSUInteger
{
    ActionNone
    ,ActionStartShow                ///< Start a session to show screen
    ,ActionStartView                ///< Start a session to view screen
    ,ActionShowDisplay              ///< Show a different screen or device
    ,ActionPause                    ///< Pause a session which is currently showing.
    ,ActionUnpause                  ///< Unpause a session
    ,ActionEnableRemoteControl      ///< Enable remote control, allowing other side to control screen
    ,ActionDisableRemoteControl     ///< Disable remote control
    ,ActionEnableShowback           ///< Enable showback for the session, allowing guests to show their screens
    ,ActionDisableShowback          ///< Disable showback
    ,ActionEnableGestures           ///< Enable gesturing for the session, allowing guests to draw on the display side screen
    ,ActionDisableGestures          ///< Disable gesturing
    ,ActionEnd                      ///< End the session
} GlanceAction;

typedef enum GlanceDisplayType :NSUInteger { Monitor, Device } GlanceDisplayType;

// Sessions ---------------------------------------------------------------------------------------

/**
 * A delegate to manage the agent viewer video experience.
 */
@protocol GlanceCustomViewerDelegate

/**
 * Called when the agent viewer starts with a supplied UIView and size.
 *
 * @param glanceView    UIView displaying agent video.  Add this view to your interface.
 * @param size          Preferred size of the UIView
 */
-(void) glanceViewerDidStart:(UIView*)glanceView size:(CGSize)size;

/**
 * Called when the agent viewer has stopped
 *
 * @param glanceView    UIView displaying agent video.  Remove this view from your interface.
 */
-(void) glanceViewerDidStop:(UIView*)glanceView;
@end

@interface GlanceSession : GlanceBase
{
}

- (id)      init;
- (void)    dealloc;

// Display information
+ (int)                 getDisplayCount;         // total number of currently connected monitors and devices
+ (int)                 getMainMonitor;
+ (void)                identifyMonitors;       // draws a number on each monitor (@@@efh not implemented on Mac)
+ (GlanceDisplayType)   getTypeOfDisplay:(int)n;
+ (NSString *)          getNameOfDisplay:(int)n;

- (bool)                canInvokeAction:(GlanceAction)action;
- (void)                invokeAction:(GlanceAction)action;
- (GlanceSessionInfo *) getSessionInfo;
- (void)                end;

- (void)                showDisplay:(GlanceDisplayParams *)dParams;
@end


@interface GlanceHostSession : GlanceSession
{
    void * hs;
}

- (id)  initWithUser:(GlanceUser *)u;
- (void)dealloc;

- (void)                show:(GlanceStartParams *)sp;
- (void)                view:(GlanceStartParams *)sp;

- (void)                setMaskedViews:(NSSet *)masked;
- (void)                addMaskedViews:(NSSet *)masked;
- (void)                addMaskedView:(UIView *)v;
- (void)                removeMaskedView:(UIView *)v;
- (void)                maskKeyboard:(BOOL)maskKeyboard;

@end

@interface GlanceGuestSession : GlanceSession
{
    void * gs;
}

@property CGSize maxWindowSize;
@property UIViewContentMode contentMode;

- (void)dealloc;
- (void)setCustomViewerDelegate:(id<GlanceCustomViewerDelegate>)delegate;
- (GlanceSessionInfo *)lookup:(NSString*)address key:(NSString*)key;
- (void)join:(NSString*)address key:(NSString*)key joinParams:(GlanceJoinParams*)joinParams;
@end


#define GLANCE_WINDOW_TAG 1167

typedef NS_ENUM(NSInteger, GlanceDefaultUIColors) {
    CancelButtonColor,
    CircleViewColor,
    SessionLabelTextColor,
    SessionKeyBackgroundColor,
    SessionKeyLabelColor,
    CloseButtonBackgroundColor,
    DialogTitleBackgroundColor,
    DialogTitleColor,
    DialogLinkColor,
    DialogConfirmButtonBackgroundColor,
    DialogConfirmButtonTitleColor,
    DialogCancelButtonBackgroundColor,
    DialogCancelButtonTitleColor,
    DialogTextColor,
    DialogMainIconColor,
    DialogIconColor,
    BorderColor
};

@protocol GlanceVideoDefaultUIDelegate <NSObject>

@optional
-(void)glanceVideoDefaultUIDidError:(NSError*)error;

-(void)glanceDefaultUIVoiceAuthenticationRequired;
-(void)glanceDefaultUIVoiceAuthenticationFailed;

@end

@protocol GlanceDefaultUIDelegate <NSObject>

@optional
-(void)glanceDefaultUIVoiceDidAuthenticate:(NSDictionary*)dict;

-(void)glanceDefaultUIVoiceAuthenticationRequired;
-(void)glanceDefaultUIVoiceAuthenticationFailed;

@end

/**
 * GlanceVisitorDelegate
 *
 * A delegate for the GlanceVisitor interface to recieve events like session start, session ended and failures.
 */
@protocol GlanceVisitorDelegate
-(void)glanceVisitorEvent:(GlanceEvent*)event;
@end

/**
 * GlanceVisitorInitParams
 *
 * Parameters to the GlanceVisitor init method
 */
@interface GlanceVisitorInitParams : NSObject
{
@public
    int         groupid;    // Glance provided group ID integer associated with your account.
    NSString *  site;       // "staging" or "production"
    NSString *  token;      // Glance provided token string. _optional_
    NSString *  visitorid;
    NSString *  name;       // Name _optional_ Maximum length is 63 characters
    NSString *  email;      // Email address _optional_ Maximum length is 127 characters
    NSString *  phone;      // Phone number _optional_ Maximum length is 31 characters
    bool        screenshare;// Set to true if application is capable of starting screenshare via presence
    bool        video;      // Set to true if application is capable of starting video via presence
    NSString *  cameras;    // List of allowed cameras for starting video session via presence
}
@property int                   groupid;
@property (retain) NSString *   site;
@property (retain) NSString *   token;
@property (retain) NSString *   visitorid;
@property (retain) NSString *   name;
@property (retain) NSString *   email;
@property (retain) NSString *   phone;
@property bool                  screenshare;
@property bool                  video;
@property (retain) NSString *   cameras;

- (id)init:(int)groupid;
- (void)dealloc;
@end

/**
 * GlanceVisitor
 *
 * A utility class to interact with the Glance Visitor SDK.
 * There can only be one Visitor session at a time with this SDK.
 */
@interface GlanceVisitor : NSObject

/**
 * Call this once to initialize the SDK. You must pass your groupID obtained from Glance.  The token parameter is reserved for future use, pass an empty string now.  You may optionally pass the visitor’s name, email or phone or any strings useful to you.  These will be saved in the Glance database and you may obtain these session attributes via reports or API calls. The visitorid param is only required if subsequently connecting to presence
 *
 * **Init may be called again to supply or change a visitorid, but the gropuId may not be changed
 *
 * @param groupId   Glance provided group ID integer associated with your account. _required_
 * @param token     Glance provided token string. _optional_
 * @param name      Name _optional_ Maximum length is 63 characters
 * @param email     Email address _optional_ Maximum length is 127 characters
 * @param phone     Phone number _optional_ Maximum length is 31 characters
 * @param visitorid Visitor id _optional_ Maximum length is 62 characters. Required for presence, optional otherwise
 */
+(void)init:(int)groupId token:(NSString*)token name:(NSString*)name email:(NSString*)email phone:(NSString*)phone;
+(void)init:(int)groupId token:(NSString*)token name:(NSString*)name email:(NSString*)email phone:(NSString*)phone visitorid:(NSString*)visitorid;
+(void)init:(GlanceVisitorInitParams *)visitorInitParams;

/**
 * The method initVistor is the same as init, it can be used from Swift 5 where "init" is reserved.
 Call initVisitor once to initialize the SDK. You must pass your groupID obtained from Glance.  The token parameter is reserved for future use, pass an empty string now.  You may optionally pass the visitor’s name, email or phone or any strings useful to you.  These will be saved in the Glance database and you may obtain these session attributes via reports or API calls. The visitorid param is only required if subsequently connecting to presence
 *
 * **Init may be called again to supply or change a visitorid, but the gropuId may not be changed
 *
 * @param groupId   Glance provided group ID integer associated with your account. _required_
 * @param token     Glance provided token string. _optional_
 * @param name      Name _optional_ Maximum length is 63 characters
 * @param email     Email address _optional_ Maximum length is 127 characters
 * @param phone     Phone number _optional_ Maximum length is 31 characters
 * @param visitorid Visitor id _optional_ Maximum length is 62 characters. Required for presence, optional otherwise
 */
+(void)initVisitor:(int)groupId token:(NSString*)token name:(NSString*)name email:(NSString*)email phone:(NSString*)phone;
+(void)initVisitor:(int)groupId token:(NSString*)token name:(NSString*)name email:(NSString*)email phone:(NSString*)phone visitorid:(NSString*)visitorid;
+(void)initVisitor:(GlanceVisitorInitParams *)visitorInitParams;
/**
 * **Finish using the SDK and release any resources.  Your application should not call this method it is automatically called on UIApplicationWillTerminateNotification.  It is only needed for unit tests or other scenarios that where this notification is not sent.
 */
+(void)releaseVisitor;

/**
 * Start a screensharing session with a random numeric key.  Note that for Visitor sessions, the key identifies the session but is not sufficient to join the session.  Agents joining sessions must be logged-in or otherwise authenticated to Glance and must be members of the group specified in the call to init.  After calling startSession, the delegate will receive either EventSessionStarted or EventStartSessionFailed.
 *
 * **init: must be called first.**
 */
+(void)startSession;

/**
 * Start a screensharing session with a key you provide.  The key may only contain characters from the Base64 URL set.  Maximum length is 63.
 *
 * **init: should be called first.**
 *
 * @param sessionKey     Session key (4 digit string), pass @"GLANCE_KEYTYPE_RANDOM" to generate a random numeric key _required_
 */
+(void)startSession:(NSString*)sessionKey;

/**
  *
 */
+(void)startVideoCall:(NSString*)sessionkey camera:(NSString*)camera;

/**
 * Pause an active screensharing session
 *
 * @param pause     Pause session if true or unpause if false _required_
 */
+(void)pause:(BOOL)pause;

/**
 * End the screensharing session.  Calling endSession initiates the process of ending the session. The session is not actually ended until the EventSessionEnded event is fired.
 */
+(void)endSession;

/**
 * Adds a delegate for the Glance visitor session to receive events.
 *
 * @param delegate     GlanceVisitorDelegate instance _required_
 */
+(void)addDelegate:(id<GlanceVisitorDelegate>) delegate;

/**
 * Removes a delegate for the Glance visitor session to receive events.
 *
 * @param delegate     GlanceVisitorDelegate instance _required_
 */
+(void)removeDelegate:(id<GlanceVisitorDelegate>) delegate;

/**
 * Sets the custom viewer delegate to provide a custom implementation of the agent video viewer.
 *
 * @param customViewerDelegate     GlanceCustomViewerDelegate instance _required_
 */
+(void)setCustomViewerDelegate:(id<GlanceCustomViewerDelegate>) customViewerDelegate;


/**
 * Gets the custom viewer delegate to provide a custom implementation of the agent video viewer.
 */
+(id<GlanceCustomViewerDelegate>)customViewerDelegate;

/**
 * Sets the video content mode for the agent video viewer.
 *
 * @param contentMode              UIViewContentMode contentMode _required_
 */
+(void)setContentMode:(UIViewContentMode)contentMode;

/**
 * Adds a UIView to mask during the Glance visitor session.
 *
 * @param view  UIView instance to mask _required_
 */
+(void)addMaskedView:(UIView*)view;

/**
 * Adds a UIVIew to mask during the Glance visitor session with a label on top of the mask to identify it
 *
 * @param view UIView instance to mask _required_
 * @param label NSString to add on top of the mask _required_
 */
+(void)addMaskedView:(UIView*)view withLabel:(NSString*)label;

/**
 * Remove a UIView from being masked during a Glance visitor session.
 *
 * @param view  UIView instance to mask _required_
 */
+(void)removeMaskedView:(UIView*)view;

/**
 * Masks the keyboard from being shown
 *
 * @param maskKeyboard YES or NO to mask keyboard
 */
+(void)maskKeyboard:(BOOL)maskKeyboard;

/**
 * Sets the label that will be used on top of the keyboard mask to identify it
 * NOTE: This will only be visible if maskKeyboard method is set to YES
 * @param label NSString to add on top of the mask _required_
 */
+(void)setMaskedKeyboardLabel:(NSString*)label;

/**
 * Get Glance tag for UIWindows
 *
 * @return NSInteger of the tag used on Glance UIWindows
 */
+(NSInteger)glanceWindowTag;

/**
 * Set the tag to be used for Glance UIWindows.
 * This should be set before using GlanceVisitor or starting a session.
 *
 * @param tag - NSInteger of the tag to be used on Glance UIWindows
 */
+(void)setGlanceWindowTag:(NSInteger)tag;

/**
 * Is ReplayKit enabled
 *
 * @return BOOL true if ReplayKit is enabled
 */
+(BOOL)isReplayKitEnabled;

/**
 * Is ReplayKit enabled and available
 *
 * @return BOOL true if ReplayKit is enabled and available
 */
+(BOOL)isReplayKitEnabledAndAvailable;

/**
 * Set ReplayKit enabled
 * Setting this value to YES will try to use ReplayKit on iOS11+
 *
 * @param enabled - BOOL boolean to enable ro disable ReplayKit
 */
+(void)setReplayKitEnabled:(BOOL)enabled;

/**
 * Is ReplayKit enabled, available and currently running
 *
 * @return BOOL true if ReplayKit is enabled, available and running
 */
+(BOOL)isReplayKitRunning;

/**
 * Enable or disable default UI (enabled by default)
 *
 * @param enabled YES or NO to enable default UI
 */
+(void)defaultUI:(BOOL)enabled;

/**
 * Enable or disable default UI (enabled by default)
 *
 * @param enabled YES or NO to enable default UI
 * @param termsUrl - Terms and Conditions URL to display when starting a session
 */
+(void)defaultUI:(BOOL)enabled delegate:(id<GlanceDefaultUIDelegate>)delegate termsUrl:(NSString*)termsUrl;

/**
 * Enable or disable default UI with Voice Authentication (enabled by default)
 *
 * @param enabled YES or NO to enable default UI
 * @param delegate GlanceDefaultUIDelegate
 * @param termsUrl if this url string is passed in, defaultUI will show a link which will open the termsUrl in a browser
 * @param muted YES or NO to start off muted
 */
+(void)defaultUI:(BOOL)enabled delegate:(id<GlanceDefaultUIDelegate>)delegate  termsUrl:(NSString*)termsUrl muted:(BOOL)isMuted;

/**
 * Enable or disable default UI with voice (enabled by default)
 *
 * @param enabled YES or NO to enable default UI
 * @param delegate GlanceDefaultUIDelegate
 * @param termsUrl - Terms and Conditions URL to display when starting a session
 * @param voiceGroupId Voice Group ID
 * @param voiceApiKey API Key
 * @param voiceParameters Voice Parameters
 * @param muted YES or NO to start off muted
 */
+(void)defaultUI:(BOOL)enabled delegate:(id<GlanceDefaultUIDelegate>)delegate termsUrl:(NSString*)termsUrl voiceGroupId:(int)voiceGroupId voiceApiKey:(NSString*)voiceApiKey voiceParameters:(NSDictionary*)voiceParameters muted:(BOOL)isMuted;

/**
 * Start voice call within defaultUI and start session.
 * This should be called when the authentication token has been acquired
 * as a result of call to GlanceDefaultUIDelegate glanceDefaultUIVoiceAuthenticationRequired.
 *
 * @param json JSON string containing JWT and other params for voice authentication
 */
+(void)defaultUIVoiceStartCall:(NSString*)json;

/**
 * Start Glance 2-Way Video Call
 *
 * @param sessionkey
 * @param delegate
 * @param camera - "front" or "back"
 * @param termsUrl - Terms of Service URL to send users to
 */
+(void)startVideoCall:(NSString*)sessionkey delegate:(id<GlanceVideoDefaultUIDelegate>)delegate camera:(NSString*)camera termsUrl:(NSString *)termsUrl;

/**
 * Start Glance 2-Way Video Call (w/ option to toggle dialog off)
 *
 * @param sessionkey
 * @param delegate
 * @param camera - "front" or "back"
 * @param termsUrl - Terms of Service URL to send users to (can be nil or empty if showDialog is set to NO)
 * @param showDialog - if set to NO, skips default dialog that shows up before starting a video session. Video session will start automatically if this is set to NO
 */
+(void)startVideoCall:(NSString*)sessionkey delegate:(id<GlanceVideoDefaultUIDelegate>)delegate camera:(NSString*)camera termsUrl:(NSString *)termsUrl showDialog:(BOOL)showDialog;

/**
 * Start Glance 2-Way Video Call with customizable video parameters
 *
 * @param sessionkey
 * @param delegate
 * @param camera - "front" or "back"
 * @param preferredSize - default is CGSizeMake(0, 0)
 * @param framerate - default is 0
 * @param timeout - default is 0
 * @param termsUrl - Terms of Service URL to send users to
*/
+(void)startVideoCall:(NSString *)sessionKey delegate:(id<GlanceVideoDefaultUIDelegate>)delegate camera:(NSString *)camera preferredSize:(CGSize)preferredSize framerate:(int)framerate timeout:(int)timeout termsUrl:(NSString *)termsUrl;

/**
 * Start Glance 2-Way Video Call with customizable video parameters (& w/ option to toggle dialog off)
 *
 * @param sessionkey
 * @param delegate
 * @param camera - "front" or "back"
 * @param preferredSize - default is CGSizeMake(0, 0)
 * @param framerate - default is 0
 * @param timeout - default is 0
 * @param termsUrl - Terms of Service URL to send users to
 * @param showDialog - if set to NO, skips default dialog that shows up before starting a video session. Video session will start automatically if this is set to NO
*/
+(void)startVideoCall:(NSString *)sessionKey delegate:(id<GlanceVideoDefaultUIDelegate>)delegate camera:(NSString *)camera preferredSize:(CGSize)preferredSize framerate:(int)framerate timeout:(int)timeout termsUrl:(NSString *)termsUrl showDialog:(BOOL)showDialog;

/**
 * Start Glance 2-Way Video Call with Voice Authentication
 *
 * @param sessionkey
 * @param delegate
 * @param camera - "front" or "back"
 * @param preferredSize - default is CGSizeMake(0, 0)
 * @param framerate - default is 0
 * @param timeout - default is 0
 * @param termsUrl - Terms of Service URL to send users to
 * @param muted YES or NO to start Voice Call off muted
*/
+(void)startVideoCall:(NSString*)sessionKey delegate:(id<GlanceVideoDefaultUIDelegate>)delegate camera:(NSString*)camera preferredSize:(CGSize)preferredSize framerate:(int)framerate timeout:(int)timeout termsUrl:(NSString*)termsUrl muted:(BOOL)isMuted;

/**
 * Start Glance 2-Way Video Call with Voice Authentication (& w/ option to toggle dialog off)
 *
 * @param sessionkey
 * @param delegate
 * @param camera - "front" or "back"
 * @param preferredSize - default is CGSizeMake(0, 0)
 * @param framerate - default is 0
 * @param timeout - default is 0
 * @param termsUrl - Terms of Service URL to send users to
 * @param muted YES or NO to start Voice Call off muted
 * @param showDialog - if set to NO, skips default dialog that shows up before starting a video session. Video session will start automatically if this is set to NO
*/
+(void)startVideoCall:(NSString*)sessionKey delegate:(id<GlanceVideoDefaultUIDelegate>)delegate camera:(NSString*)camera preferredSize:(CGSize)preferredSize framerate:(int)framerate timeout:(int)timeout termsUrl:(NSString*)termsUrl muted:(BOOL)isMuted showDialog:(BOOL)showDialog;

/**
 * Start Glance 2-Way Video Call with Legacy Voice
 *
 * @param sessionkey
 * @param delegate
 * @param camera - "front" or "back"
 * @param preferredSize - default is CGSizeMake(0, 0)
 * @param framerate - default is 0
 * @param timeout - default is 0
 * @param termsUrl - Terms of Service URL to send users to
 * @param voiceGroupId Voice Group ID
 * @param voiceApiKey API Key
 * @param voiceParameters Voice Parameters
 * @param muted YES or NO to start Voice Call off muted
*/
+(void)startVideoCall:(NSString*)sessionKey delegate:(id<GlanceVideoDefaultUIDelegate>)delegate camera:(NSString*)camera preferredSize:(CGSize)preferredSize framerate:(int)framerate timeout:(int)timeout termsUrl:(NSString*)termsUrl voiceGroupId:(int)voiceGroupId voiceApiKey:(NSString*)voiceApiKey voiceParameters:(NSDictionary*)voiceParameters muted:(BOOL)isMuted;

/**
 * Start Glance 2-Way Video Call with Legacy Voice (& w/ option to toggle dialog off)
 *
 * @param sessionkey
 * @param delegate
 * @param camera - "front" or "back"
 * @param preferredSize - default is CGSizeMake(0, 0)
 * @param framerate - default is 0
 * @param timeout - default is 0
 * @param termsUrl - Terms of Service URL to send users to
 * @param voiceGroupId Voice Group ID
 * @param voiceApiKey API Key
 * @param voiceParameters Voice Parameters
 * @param muted YES or NO to start Voice Call off muted
 * @param showDialog - if set to NO, skips default dialog that shows up before starting a video session. Video session will start automatically if this is set to NO
*/
+(void)startVideoCall:(NSString*)sessionKey delegate:(id<GlanceVideoDefaultUIDelegate>)delegate camera:(NSString*)camera preferredSize:(CGSize)preferredSize framerate:(int)framerate timeout:(int)timeout termsUrl:(NSString*)termsUrl voiceGroupId:(int)voiceGroupId voiceApiKey:(NSString*)voiceApiKey voiceParameters:(NSDictionary*)voiceParameters muted:(BOOL)isMuted showDialog:(BOOL)showDialog;

/**
  End Glance Video Call
 * @param endVoiceCall end accompanying voice call along with video
 */
+(void)endVideoCall:(BOOL)endVoiceCall;

/**
 * Start voice call within video defaultUI and start session.
 * This should be called when the authentication token has been acquired
 * as a result of call to GlanceVideoDefaultUIDelegate glanceDefaultUIVoiceAuthenticationRequired.
 *
 * @param json JSON string containing JWT and other params for voice authentication
 */
+(void)videoDefaultUIVoiceStartCall:(NSString*)json;

/**
 * Set colors for particular areas of the default UI
 *
 * @param constant specifies which particular UI element's color to change
 * @param color the color to set to the specified area
 */
+(void)setDefaultUIColor:(GlanceDefaultUIColors)constant color:(UIColor*)color;

/**
 * Set colors for particular areas of the 2-Way video default UI
 *
 * @param constant specifies which particular UI element's color to change
 * @param color the color to set to the specified area
 */
+(void)setVideoDefaultUIColor:(GlanceDefaultUIColors)constant color:(UIColor*)color;
@end

// Presence ---------------------------------------------------------------------------------------

/**
 * GlancePresenceVisitor
 *
 * A utility class to interact with the Glance Presence SDK.
 * There can only be one Presence session at a time with this SDK.
 */
@interface GlancePresenceVisitor : NSObject

+(void)connect;

+(void)connect:(BOOL)registerForNotifications;

+(void)presence:(NSDictionary*)map;

+(void)signalVisibility:(BOOL)visible;

+(void)signalAgent:(NSString*)event map:(NSDictionary*)map;

+(void)disconnect;

+(void)setDefaultUI:(BOOL)defaultUI;

@end

