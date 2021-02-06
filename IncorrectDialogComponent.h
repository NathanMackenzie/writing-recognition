#ifndef __JUCE_HEADER_F472A98A35B98128__
#define __JUCE_HEADER_F472A98A35B98128__

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainComponent.h"

class IncorrectDialogComponent  : public Component,
                                  public ButtonListener
{
public:
    IncorrectDialogComponent (MainComponent *parent);
    ~IncorrectDialogComponent();

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    MainComponent *parent;
    ScopedPointer<Slider> slider;
    ScopedPointer<Label> label;
    ScopedPointer<TextButton> addButton;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IncorrectDialogComponent)
};

#endif
