#include "TrackPadComponent.h"

TrackPadComponent::TrackPadComponent(MainComponent *parent)
{
    setSize (400, 400);
    aiInput.assign(400, 0);
    screen = parent;
}

TrackPadComponent::~TrackPadComponent()
{
    screen = nullptr;
}

void TrackPadComponent::paint (Graphics& g)
{
    g.fillAll (Colours::white);
    
    if(screen->clearBoard()){
        clearBoard();
    }
    
    g.setColour (Colours::black);
    for(int i = 0; i < strokes.size(); i++){
        Path p;
        p.startNewSubPath(strokes[i][0].x, strokes[i][0].y);
        for(int c = 1; c < strokes[i].size(); ++c){
            p.lineTo(strokes[i][c].x, strokes[i][c].y);
        }
        g.strokePath (p, PathStrokeType (5.0f),AffineTransform::identity);
    }
}

void TrackPadComponent::mouseDrag(const MouseEvent &event){
    Point<float> point;
    point.setXY(event.getMouseDownX() + event.getDistanceFromDragStartX(), event.getMouseDownY() + event.getDistanceFromDragStartY());
    
    strokes[strokes.size()-1].push_back(point);
    repaint();
    
    aiInput[((point.y/20)*20)+(point.x/20)] = 1;
}

void TrackPadComponent::mouseUp(const MouseEvent &event){
    screen->calculate(aiInput);
}

void TrackPadComponent::mouseDown(const juce::MouseEvent &event){
    vector<Point<float>> stroke;
    strokes.push_back(stroke);
}

 const vector<int>& TrackPadComponent::getAiInput(){
    return aiInput;
}

void TrackPadComponent::clearBoard(){
    //Reset aiInput
    for(int i = 0; i < aiInput.size(); ++i){
        aiInput[i] = 0;
    }
    strokes.clear();
}


