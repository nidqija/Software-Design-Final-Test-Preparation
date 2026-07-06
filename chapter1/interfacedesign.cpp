#include <iostream>


using namespace std;




// =========================================================================== //

// PART 1 : INTERFACE DESIGN COMPONENT



// Steps of Interface Design in Software Design Phases:

// 1. we define how different modules , components, or classes will communicate with each other.

// 2. we start by defining the interface of a class or module , which specifies the methods and properties 
//    that are available for use by other classes or modules.

// 3. we then implement the interface in the class or module , 
//    which provides the actual functionality and methods for each classes 



// we define the interface of a class or module , which specifies the methods and properties
// in this case , we are declaring audiplayer as our interface class
// this will be inherited by our concrete classes like mp3player and wavplayer

class AudioPlayer {


    public:
       // define a virtual function that will be implemented by the concrete classes
       virtual void playAudio() = 0;



       // define a destructor for the interface class
       virtual ~AudioPlayer() {
            cout << "AudioPlayer destructor called" << endl;
       };
};


// we inherit the interface class in our concrete classes like mp3player and wavplayer
class MP3Player : public AudioPlayer {


    public:
      // we define the function that will be implemented by the concrete classes
       void playAudio() override {
          cout << "Playing MP3 audio..." << endl;
       }
};


// we inherit the interface class in our concrete classes like mp3player and wavplayer
class WAVPlayer : public AudioPlayer {

     public:

      // we define the function that will be implemented by the concrete classes
      void playAudio() override {
          cout << "Playing WAV audio..." << endl;
       }


    };



// FOR MAINTAINABILITY AND SCALABILITY //
// we can create a factory class that will be responsible 
// for creating the objects of the concrete classes
// the factory doesnt care which concrete class is being used , it just calls the playAudio function of the interface class
class Factory {
       public:
          // to access the player object , we need to put the pointer to the interface class as an argument in the function
          // this way , we can pass any concrete class that inherits the interface class as an argument to the function
          void runSoundboard(AudioPlayer* player) {
              player->playAudio();
          }
};



int main(){

    // we instantiate the concrete classes and call the playAudio function
    AudioPlayer* mp3Player = new MP3Player();
    AudioPlayer* wavPlayer = new WAVPlayer();


    Factory factory;

    // we call the runSoundboard function of the factory class 
    // and pass the concrete classes as arguments
    factory.runSoundboard(mp3Player);
    factory.runSoundboard(wavPlayer);



    // delete the objects to free up memory
    delete mp3Player;
    delete wavPlayer;


    return 0;
}