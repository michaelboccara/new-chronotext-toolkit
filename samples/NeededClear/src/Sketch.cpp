#include "Sketch.h"

using namespace ci;
using namespace ci::app;
using namespace std;

void Sketch::draw()
{
	gl::clear( Color( 0.1f, 0.1f, 0.15f ) );

	gl::color( 1.0f, 0.5f, 0.25f );	
	gl::begin( GL_LINE_STRIP );
	for( auto pointIter = mPoints.begin(); pointIter != mPoints.end(); ++pointIter ) {
		gl::vertex( *pointIter );
	}
	gl::end();
}

void Sketch::updateTouch(int index, float x, float y)
{
	mPoints.push_back( Vec2f(x, y) );
	mApp->requestDraw();
}
