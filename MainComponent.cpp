#include "MainComponent.h"
#include "TrackPadComponent.h"
#include "TrainingDialogComponent.h"
#include "IncorrectDialogComponent.h"

MainComponent::MainComponent ()
{
    vector<unsigned> topology {400, 350, 300, 250, 200, 150, 100, 50, 25, 10};
    network = Network(topology);
    addAndMakeVisible (component = new TrackPadComponent(this));
    component->setName ("new component");
    
    addAndMakeVisible (clearButton = new TextButton ("new k"));
    clearButton->setButtonText (TRANS("Clear"));
    clearButton->addListener (this);

    addAndMakeVisible (incorrectButton = new TextButton ("new k"));
    incorrectButton->setButtonText (TRANS("Incorrect"));
    incorrectButton->addListener (this);

    addAndMakeVisible (trainingButton = new TextButton ("new k"));
    trainingButton->setButtonText (TRANS("Training"));
    trainingButton->addListener (this);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("")));
    label->setFont (Font (48.00f, Font::plain));
    label->setJustificationType (Justification::centred);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    setSize (400, 475);

}

MainComponent::~MainComponent()
{
    component = nullptr;
    clearButton = nullptr;
    incorrectButton = nullptr;
    trainingButton = nullptr;
    label = nullptr;
}

void MainComponent::paint (Graphics& g)
{
    g.fillAll (Colours::grey);
}

void MainComponent::resized()
{
    component->setBounds (0, 0, 400, 400);
    clearButton->setBounds (8, 408, 112, 24);
    incorrectButton->setBounds (128, 408, 112, 24);
    trainingButton->setBounds (8, 440, 232, 24);
    label->setBounds (256, 416, 120, 48);
}

void MainComponent::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == clearButton)
    {
        clear = true;
        component->repaint();
    }
    else if (buttonThatWasClicked == incorrectButton)
    {
        IncorrectDialogComponent comp(this);
        DialogWindow::showModalDialog ("Training", &comp, nullptr, Colours::white, true, false, false);
    }
    else if (buttonThatWasClicked == trainingButton)
    {
        TrainingDialogComponent comp(this);
        DialogWindow::showModalDialog ("Training", &comp, nullptr, Colours::white, true, false, false);
    }
}

void MainComponent::calculate(vector<int>& aiInput){
    current_screen = &aiInput;
    network.feedForward(aiInput);
    updateLabel();
}


void MainComponent::addToTrainingSet(int value){
    pair<int,vector<int>> set(value, *current_screen);
    training_set.push_back(set);
}

void  MainComponent::startTrainingCycle(int itterations){
    for(int i = 0; i < itterations; ++i){
        int random = rand() % training_set.size();
        
        network.feedForward(training_set[random].second);
        
        vector<double> ideals(10, 0);
        ideals[training_set[random].first] = 1;
        network.backPropagate(ideals, .5, .5);
    }
}

void MainComponent::updateLabel(){
    vector<double> output = network.getOutput();
    double closest = 100;
    int ans = 0;
    
    for(int i = 0; i < output.size(); ++i){
        cout << output[i] << endl;
        if(abs(1-output[i]) < closest){
            closest = abs(1-output[i]);
            ans = i;
        }
    }
    
    label->setText(juce::String(ans), dontSendNotification);
}

Boolean MainComponent::clearBoard(){
    Boolean temp = clear;
    clear = false;
    return temp;
}

