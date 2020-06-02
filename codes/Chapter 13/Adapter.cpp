#include <iostream>
using namespace std;

class VGA {
 public:
  virtual void play() = 0;
};

class TV1 : public VGA {
 public:
  void play() { cout << "TV1: VGA" << endl; }
};

class HDMI {
 public:
  virtual void play() = 0;
};

class TV2 : public HDMI {
 public:
  void play() { cout << "TV2: HDMI" << endl; }
};

class Adapter : public VGA {
 public:
  Adapter(HDMI *p) : pHDMI(p) {}
  void play() { pHDMI->play(); }

 private:
  HDMI *pHDMI;
};

class Computer {
 public:
  void playVideo(VGA *pVGA) { pVGA->play(); }
};