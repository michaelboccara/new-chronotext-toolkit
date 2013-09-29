/*
 * A SIMPLE SKETCH FEATURING:
 * - RESOLUTION-INDEPENDENT 2D SCALE
 * - BASIC SINGLE-FINGER DRAG
 */

#pragma once

#include "chronotext/cinder/CinderApp.h"
#include "chronotext/cinder/CinderSketch.h"

using namespace std;
using namespace ci;

class Sketch : public CinderSketch
{
	// This will maintain a list of points which we will draw line segments between
	CinderApp* mApp;
	list<Vec2f>		mPoints;

public:
    Sketch(CinderApp *context, void *delegate = NULL) : CinderSketch(context, delegate), mApp(context) {}

    void draw();
    
    void updateTouch(int index, float x, float y);
};
