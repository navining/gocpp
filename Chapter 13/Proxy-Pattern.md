# Proxy Pattern

The proxy pattern provides a proxy for other objects which controls the access permission of objects. Let's look at this example, where we have a abstract class *Movie* and a derived class *MovieSite* which provides free movies and VIP movies. Free movies are for general users, while VIP movies are for members.

```cpp
class Movie {
public:
    virtual void freeMovie() = 0;
    virtual void vipMovie() = 0;
};

class MovieSite : public Movie {
public:
    virtual void freeMovie() {
        cout << "Free Movie" << endl;
    }
    virtual void vipMovie() {
        cout << "VIP Movie" << endl;
    }
};
```

However, if we write the class like this, its objects can access both *freeMovie()* and *vipMovie()*, which means we have to judge the authority of users in the service layer. It is apparently not a good OOP design.

```cpp
int main() {
    MovieSite *p = new MovieSite();
    p->freeMovie();	// Free Movie
    p->vipMovie();	// VIP Movie
    delete p;
    return 0;
}
```

A better approach is to provide a proxy class which controls the access permission of users. Here we have a *FreeMovieProxy* which acts as a proxy of free movies. The class combines a *MovieSite* object as its member. In this way, the *freeMovie()* method of the delegate class *MovieSite* is called through the *freeMovie()* method of its proxy class. Moreover, since general users can not watch VIP movies, the *vipMovie()* method of *MovieSite* can not be called through the proxy.

```cpp
class FreeMovieProxy : public Movie {
public:
    FreeMovieProxy() {
        pMovie = new MovieSite();
    }
    ~FreeMovieProxy() {
        delete pMovie;
    }
    virtual void freeMovie() {
        pMovie->freeMovie();
    }
    virtual void vipMovie() {
        cout << "Permission denied!" << endl;
    }
private:
    MovieSite *pMovie;
};
```

Similarly, we have a *VipMovieProxy* class which acts as a proxy of VIP movies. In this class, users have the full permissions to *freeMovie()* and *vipMovie()* of *MovieSite*.

```cpp
class VipMovieProxy : public Movie {
public:
    VipMovieProxy() {
        pMovie = new MovieSite();
    }
    ~VipMovieProxy() {
        delete pMovie;
    }
    virtual void freeMovie() {
        pMovie->freeMovie();
    }
    virtual void vipMovie() {
        pMovie->vipMovie();
    }
private:
    MovieSite *pMovie;
};
```

Then in the service module, the client accesses the proxy object instead of the original object, where the permissions of users can be managed.

```cpp
int main() {
    MovieSite *p = new FreeMovieProxy();
    p->freeMovie();	// Free Movie
    p->vipMovie();	// Permission denied!
    delete p;
    return 0;
}
```

