#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include <iostream>
#include <vector>
#include "MainComponent.h"

struct Coordinate{
    int x, y;
    
    Coordinate(){
        x = 0;
        y = 0;
    }
};

using namespace std;
class TrackPadComponent   : public Component,
                               public MouseListener
{
public:
    TrackPadComponent(MainComponent *parent);
    ~TrackPadComponent();
    
    
    void clearBoard();
    void paint (Graphics&);
    void mouseDrag(const MouseEvent &event);
    void mouseUp(const MouseEvent &event);
    void mouseDown(const MouseEvent &event);
    const vector<int>& getAiInput();


private:
    vector<vector<Point<float>>> strokes;
    vector<int> aiInput;
    MainComponent *screen;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrackPadComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
