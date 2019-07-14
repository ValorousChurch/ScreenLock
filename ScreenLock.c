// Complile using the following command line:
// gcc -Wall -o ScreenLock ScreenLock.c -framework ApplicationServices

#include <ApplicationServices/ApplicationServices.h>

static CGRect screenBounds;

// This callback will be invoked every time the mouse moves.
CGEventRef myCGEventCallback( CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon )
{
  // Do some sanity check.
  if ( type != kCGEventMouseMoved )
  {
    return event;
  }

  // The incoming mouse position.
  CGPoint location = CGEventGetLocation( event );
  //printf( "(%f, %f)\n", location.x, location.y);

  if( location.y < 0 )
  {
    CGPoint newLocation = { .x = CGRectGetWidth( screenBounds ) - 20, .y = 20 };
    CGDisplayMoveCursorToPoint( CGMainDisplayID(), newLocation );
    printf( "Off screen (%f, %f). Moving back to (%f, %f).\n", location.x, location.y, newLocation.x, newLocation.y);
  }

  // We must return the event for it to be useful.
  return event;
}

int main( void )
{
  CFMachPortRef      eventTap;
  CGEventMask        eventMask;
  CFRunLoopSourceRef runLoopSource;

  // The screen size of the primary display.
  screenBounds = CGDisplayBounds( CGMainDisplayID() );
  //printf( "The main screen is %dx%d\n", (int)screenBounds.size.width, (int)screenBounds.size.height );

  // Create an event tap. We are interested in mouse movements.
  eventMask = ( 1 << kCGEventMouseMoved );
  eventTap = CGEventTapCreate( kCGSessionEventTap, kCGHeadInsertEventTap, 0, eventMask, myCGEventCallback, NULL );
  if ( !eventTap ) {
    fprintf( stderr, "failed to create event tap\n" );
    exit( 1 );
  }

  // Create a run loop source.
  runLoopSource = CFMachPortCreateRunLoopSource( kCFAllocatorDefault, eventTap, 0 );

  // Add to the current run loop.
  CFRunLoopAddSource( CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes );

  // Enable the event tap.
  CGEventTapEnable( eventTap, true );

  // Set it all running.
  CFRunLoopRun();

  exit(0);
}