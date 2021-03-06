#include "chronotext/cinder/CinderSketch.h"

#include <map>

@class GLKView;
@class GLViewController;

enum
{
    REASON_VIEW_WILL_APPEAR,
    REASON_VIEW_WILL_DISAPPEAR,
    REASON_APPLICATION_DID_BECOME_ACTIVE,
    REASON_APPLICATION_WILL_RESIGN_ACTIVE
};

@interface CinderDelegate : NSObject <UIAccelerometerDelegate>
{
    GLKView *view;
    GLViewController *viewController;
    CinderSketch *sketch;
    
    std::map<UITouch*, uint32_t> touchIdMap;

    float accelFilterFactor;
    ci::Vec3f lastAccel, lastRawAccel;
    
    int width;
    int height;
    float contentScale;
    
    ci::Timer timer;
    uint32_t frameCount;
    
    BOOL initialized;
    BOOL active;
}

@property (nonatomic, assign) GLKView *view;
@property (nonatomic, assign) GLViewController *viewController;
@property (nonatomic, assign) CinderSketch *sketch;
@property (nonatomic, assign) float accelFilterFactor;
@property (nonatomic, readonly) int width;
@property (nonatomic, readonly) int height;
@property (nonatomic, readonly) float contentScale;
@property (nonatomic, readonly) double elapsedSeconds;
@property (nonatomic, readonly) uint32_t elapsedFrames;
@property (nonatomic, readonly) BOOL initialized;
@property (nonatomic, readonly) BOOL active;

- (void) startWithReason:(int)reason;
- (void) stopWithReason:(int)reason;

- (void) setup;
- (void) update;
- (void) draw;

- (void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
- (void) touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (void) touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event;

- (uint32_t) addTouchToMap:(UITouch*)touch;
- (void) removeTouchFromMap:(UITouch*)touch;
- (uint32_t) findTouchInMap:(UITouch*)touch;
- (void) updateActiveTouches;

- (NSDictionary*) parseJSON:(NSString*)string;
- (void) sendMessageToSketch:(int)what;
- (void) sendMessageToSketch:(int)what body:(NSString*)body;
- (void) sendMessageToSketch:(int)what json:(NSDictionary*)json;
- (void) receiveMessageFromSketch:(int)what body:(NSString*)body;

@end
