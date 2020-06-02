# Adapter Pattern

The adapter pattern is able to convert an interface into another, and let incompatible interfaces work together. It is also a structural pattern.

There are two popular interface in multimedia devices, HDMI and VGA. Suppose we have a *VGA* class, and a display device *TV1* which uses the interface.

```cpp
class VGA {
public:
    virtual void play() = 0;
};

class TV1 : public VGA {
public:
    void play() {
        cout << "TV1: VGA" << endl;
    }
};
```

What's more, we have a computer which supports VGA interface:

```cpp
class Computer {
public:
    void playVideo(VGA *pVGA) {
        pVGA->play();
    }
};
```

Since the interfaces of the computer and the screen are consistent, we can directly connect them together by passing a *VGA* pointer into the *playVideo()* method.

```cpp
int main() {
    Computer computer;
    computer.playVideo(new TV1());	// TV1: VGA
    return 0;
}
```

Now suppose we have another monitor which supports HDMI interface:

```cpp
class HDMI {
public:
    virtual void play() = 0;
};

class TV2 : public HDMI {
public:
    void play() {
        cout << "TV2: HDMI" << endl;
    }
};
```

Since our computer only takes a *VGA* pointer, we can not use this monitor directly. There are two ways to do so. We can simply change a computer which supports HDMI, which is equivalent to code refactoring. This method is once and for all, but would be a painful thing if there are a large amount of code. Or we can use an adapter which convert VGA into HDMI. 

Here we add an *Adapter* class which inherits from *VGA*. The class keeps a *HDMI* pointer as its member variable, and calls the *play()* method of *HDMI* from its own *play()* method.

```cpp
class Adapter : public VGA {
public:
    Adapter(HDMI *p) : pHDMI(p) {}
    void play() {
        pHDMI->play();
    }
private:
    HDMI *pHDMI;
};
```

Then we can use our adapter to connect the computer to *TV2*. The *playVideo()* method takes the *VGA* adapter, which is constructed by the *HDMI* object.

```cpp
int main() {
    Computer computer;
    computer.playVideo(new Adapter(new TV2()));	// TV2: HDMI
    return 0;
}
```

