#include "MainComponent.h"
#include "TrackPadComponent.h"
#include "TrainingDialogComponent.h"
#include "IncorrectDialogComponent.h"

/*
 * MainComponent defines the main user screen GUI components. Also initializes the
 * underlying neural network topology.
 */
MainComponent::MainComponent ()
{
    // Define network topology
    vector<unsigned> topology {400, 350, 300, 250, 200, 150, 100, 50, 25, 10};
    network = Network(topology);
    
    // Create new component and make visible
    addAndMakeVisible (component = new TrackPadComponent(this));
    component->setName ("new component");
    
    // Define and add all buttons
    addAndMakeVisible (clearButton = new TextButton ("new k"));
    clearButton->setButtonText (TRANS("Clear"));
    clearButton->addListener (this);

    addAndMakeVisible (incorrectButton = new TextButton ("new k"));
    incorrectButton->setButtonText (TRANS("Incorrect"));
    incorrectButton->addListener (this);

    addAndMakeVisible (trainingButton = new TextButton ("new k"));
    trainingButton->setButtonText (TRANS("Training"));
    trainingButton->addListener (this);

    // Define and add label
    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("")));
    label->setFont (Font (48.00f, Font::plain));
    label->setJustificationType (Justification::centred);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    setSize (400, 475);

}

// Deconstructor
MainComponent::~MainComponent()
{
    component = nullptr;
    clearButton = nullptr;
    incorrectButton = nullptr;
    trainingButton = nullptr;
    label = nullptr;
}

// Set background color grey
void MainComponent::paint (Graphics& g)
{
    g.fillAll (Colours::grey);
}

// Define button sizes
void MainComponent::resized()
{
    component->setBounds (0, 0, 400, 400);
    clearButton->setBounds (8, 408, 112, 24);
    incorrectButton->setBounds (128, 408, 112, 24);
    trainingButton->setBounds (8, 440, 232, 24);
    label->setBounds (256, 416, 120, 48);
}

/*
 * buttonClicked handles the all button events on the main screen component.
 *
 * @param pointer to button instance
 * @return void
 */
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

/*
 * calculate calculates the predicted output based off of what was drawn on the screen.
 * Updates label with prediction.
 *
 * @param refrence to vector containing information of what was drawn on the board
 * @return void
 */
void MainComponent::calculate(vector<int>& aiInput){
    current_screen = &aiInput;
    network.feedForward(aiInput);
    updateLabel();
}

/*
 * addTo TrainingSet will add a key, value pair to a stack for future training of the
 * network. The key is a vector of ints containing the information of the board
 * with a drawn figure. The value is the proper value of the predictions.
 *
 * @param int value containing the correct value for whats drawn on the board
 * @return void
 */
void MainComponent::addToTrainingSet(int value){
    pair<int,vector<int>> set(value, *current_screen);
    training_set.push_back(set);
}

/*
 * startTrainingCycle begins training the neural network using back propagation. Randomly
 * itterates a define set of times through the training set.
 *
 * @param int of the number of times perform back propagation training
 * @return void
 */
void  MainComponent::startTrainingCycle(int itterations){
    for(int i = 0; i < itterations; ++i){
        // Create random value to choose which key, value to train from
        int random = rand() % training_set.size();
        
        // Find current predicted value input
        network.feedForward(training_set[random].second);
        
        // Perform back propagation to adjust network for input value
        vector<double> ideals(10, 0);
        ideals[training_set[random].first] = 1;
        network.backPropagate(ideals, .5, .5);
    }
}

/*
 * updateLabel retrieves the predicted output from the neural network then updates the
 * label with said prediction.
 *
 * @param void
 * @return void
 */
void MainComponent::updateLabel(){
    
    // Retrieves network output
    vector<double> output = network.getOutput();
    double closest = 100;
    int ans = 0;
    
    // Finds outcom with the highest probability
    for(int i = 0; i < output.size(); ++i){
        cout << output[i] << endl;
        if(abs(1-output[i]) < closest){
            closest = abs(1-output[i]);
            ans = i;
        }
    }
    
    label->setText(juce::String(ans), dontSendNotification);
}

/*
 * clearBoard erases the board of previously draw number
 *
 * @param void
 * @return void
 */
Boolean MainComponent::clearBoard(){
    Boolean temp = clear;
    clear = false;
    return temp;
}

