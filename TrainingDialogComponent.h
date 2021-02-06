#ifndef __JUCE_HEADER_41B68AFA9AA3AC5A__
#define __JUCE_HEADER_41B68AFA9AA3AC5A__

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"

class TrainingDialogComponent  : public Component,
                                 public ButtonListener

{
public:
    TrainingDialogComponent (MainComponent *parent);
    ~TrainingDialogComponent();

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;


private:

    MainComponent *parent;
    ScopedPointer<Label> label;
    ScopedPointer<Slider> slider;
    ScopedPointer<TextButton> startButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrainingDialogComponent)
};
#endif
