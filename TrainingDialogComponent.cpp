#include "TrainingDialogComponent.h"
#include <cstdlib>

TrainingDialogComponent::TrainingDialogComponent (MainComponent *parent)
{
    this->parent = parent;

    addAndMakeVisible (label = new Label ("label",
                                          TRANS("Training Cylce")));
    label->setFont (Font (24.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (startButton = new TextButton ("Start"));
    startButton->addListener (this);

    addAndMakeVisible (slider = new Slider ("slider"));
    slider->setRange (0, 10000, 1);
    slider->setSliderStyle (Slider::LinearHorizontal);
    slider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);

    setSize (260, 25);
}

TrainingDialogComponent::~TrainingDialogComponent()
{

    label = nullptr;
    startButton = nullptr;
    slider = nullptr;
}

void TrainingDialogComponent::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void TrainingDialogComponent::resized()
{
    slider->setBounds (16, 50, 150, 24);
    label->setBounds (16, 18, 208, 24);
    startButton->setBounds (170, 50, 64, 24);
}

void TrainingDialogComponent::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == startButton)
    {
        parent->startTrainingCycle(slider->getValue());
        findParentComponentOfClass<DialogWindow>()->exitModalState(0);
    }
}
