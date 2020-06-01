#include <iostream>
using namespace std;

class Movie {
 public:
  virtual void freeMovie() = 0;
  virtual void vipMovie() = 0;
};

class MovieSite : public Movie {
 public:
  virtual void freeMovie() { cout << "Free Movie" << endl; }
  virtual void vipMovie() { cout << "VIP Movie" << endl; }
};

class FreeMovieProxy : public Movie {
 public:
  FreeMovieProxy() { pMovie = new MovieSite(); }
  ~FreeMovieProxy() { delete pMovie; }
  virtual void freeMovie() { pMovie->freeMovie(); }
  virtual void vipMovie() { cout << "Permission denied!" << endl; }

 private:
  MovieSite *pMovie;
};

class VipMovieProxy : public Movie {
 public:
  VipMovieProxy() { pMovie = new MovieSite(); }
  ~VipMovieProxy() { delete pMovie; }
  virtual void freeMovie() { pMovie->freeMovie(); }
  virtual void vipMovie() { pMovie->vipMovie(); }

 private:
  MovieSite *pMovie;
};