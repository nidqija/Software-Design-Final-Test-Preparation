#include <iostream>
#include <string>

using namespace std;


// =========================================================================== //



// PART 2 : ARCHITECTURAL DESIGN COMPONENT
// in this part , we will discuss the architectural design component of software design phases
// we are establishing the overall structure of the system by identifying high level components and how they are organized , connected and communicate with each other




// in this use case , we are doing a simple MVC architecture design for a simple audio player application




// MODEL LAYER 
// the model layer is responsible for managing the data and business logic of the application
// it fetches the data from the database and sends it to the controller layer for processing
class ModelLayer {
    

    public:
       // define a function that will be implemented by the concrete classes
       void findSongfromDB() {
          cout << "Done! The song is found in DB ( Model Layer )"  << endl;
       }
};



// VIEW LAYER
// the view layer is responsible for presenting the data to the user and receiving user input
// it sends the user input to the controller layer for processing
class ViewLayer {
    
    public:
       // define a function that will be implemented by the concrete classes
       string displayAudioData(string audioFile) {
          cout << "Receive audio file: " << audioFile << " (View Layer)" << endl;
          return audioFile;
       }


       
};


// CONTROLLER LAYER
// the controller layer is responsible for handling user input and coordinating the flow of data between the model and view layers
// it receives the user input from the view layer and sends it to the model layer for processing
class ControllerLayer {
    
    public:
       // define a function that will be implemented by the concrete classes
       void controlAudioData(string audioFile) {
          cout << "Received the request from the view layer : " + audioFile << " (Controller Layer)" << endl;
          cout << "Sending the request to the model layer..." << endl;
       }
};


int main(){


    string audioFile = "song.mp3";


    // create an object of the model layer
    ControllerLayer controller;
    ModelLayer model;
    ViewLayer view;


    cout << "MVC Architecture Design for Audio Player Application" << endl;

    view.displayAudioData(audioFile);

    controller.controlAudioData(audioFile);

    model.findSongfromDB();

    return 0;
}


    


