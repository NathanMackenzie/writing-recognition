#ifndef __JUCE_HEADER_A0D30F872B3B5E9A__
#define __JUCE_HEADER_A0D30F872B3B5E9A__

#include "../JuceLibraryCode/JuceHeader.h"
#include "Network.h"

using namespace std;
class MainComponent  : public Component,
                         public ButtonListener,
                         public MouseListener
{
public:
    MainComponent ();
    ~MainComponent();
    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void calculate(vector<int>& aiInput);
    void addToTrainingSet(int value);
    void startTrainingCycle(int itterations);
    Boolean clearBoard();


private:
    Boolean clear = false;
    void updateLabel();
    ScopedPointer<Component> component;
    ScopedPointer<TextButton> clearButton;
    ScopedPointer<TextButton> incorrectButton;
    ScopedPointer<TextButton> trainingButton;
    ScopedPointer<Label> label;
    Network network;
    vector<pair<int, vector<int>>> training_set;
    vector<int> *current_screen;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

#endif
