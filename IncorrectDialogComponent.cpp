#include "IncorrectDialogComponent.h"

IncorrectDialogComponent::IncorrectDialogComponent (MainComponent *parent)
{
    this->parent = parent;
    
    addAndMakeVisible (slider = new Slider ("new slider"));
    slider->setRange (0, 9, 1);
    slider->setSliderStyle (Slider::LinearHorizontal);
    slider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    
    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Add to training set")));
    label->setFont (Font (24.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (addButton = new TextButton ("Add"));
    addButton->addListener (this);

    setSize (260, 25);setSize (260, 25);
}

IncorrectDialogComponent::~IncorrectDialogComponent()
{
    slider = nullptr;
    addButton = nullptr;
    label = nullptr;
}

void IncorrectDialogComponent::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void IncorrectDialogComponent::resized()
{
    slider->setBounds (16, 50, 150, 24);
    label->setBounds (16, 18, 208, 24);
    addButton->setBounds (170, 50, 64, 24);
}

void IncorrectDialogComponent::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == addButton)
    {
        parent->addToTrainingSet(slider->getValue());
        findParentComponentOfClass<DialogWindow>()->exitModalState(0);
    }
}

