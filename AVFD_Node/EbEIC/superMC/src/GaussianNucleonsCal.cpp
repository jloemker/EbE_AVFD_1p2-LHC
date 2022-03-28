// Ver 0.1
#include <iostream>
#include <cmath>
#include <ctime>
#include "stdlib.h"

#include "Nucleus.h"
#include "arsenal.h"

#include "GaussianNucleonsCal.h"
#include "Particle.h"
#include "Box2D.h"

#define EulerGamma 0.5772156649

using namespace std;

//----------------------------------------------------------------------
double Gamma0Integrand(double t)
{
  return 1./t*exp(-t);
}

GaussianNucleonsCal::GaussianNucleonsCal(ParameterReader* paraRdr_in)
// Note: sigmaNN_in is in the unit of mb!
{
  paraRdr = paraRdr_in;
  lambda = paraRdr->getVal("gaussian_lambda");
  entropy_gaussian_width = paraRdr->getVal("glb_entropy_width");
  int shape_of_nucleons = paraRdr->getVal("shape_of_nucleons");
  double gauss_nucl_width = paraRdr->getVal("gauss_nucl_width");
  double sigmaNN_in = paraRdr->getVal("siginNN");
  
  if(shape_of_nucleons == 1)
  {
    width = sqrt(0.1*sigmaNN_in/(M_PI))/2.0;
    sigma_gg = getSigEff(sigmaNN_in, width);
  }
  if (shape_of_nucleons==3) // see documents
  {
    double sigmaNN_in_sigam_gg_ratio = (EulerGamma + qiu_simpsons(Gamma0Integrand, lambda, lambda+100., 1e-10) + log(lambda))/lambda; // lambda+100 is used as "inf" in the fast decaying integral
    width = sqrt(sigmaNN_in*0.1/(4*M_PI*lambda*sigmaNN_in_sigam_gg_ratio));
    sigma_gg = sigmaNN_in*0.1/sigmaNN_in_sigam_gg_ratio;
  }
  else if (shape_of_nucleons==2) // "classical" gaussian nucleons
  {
    width = sqrt(0.1*sigmaNN_in/M_PI)/sqrt(8); // rms-radius of a gaussian = rms-radius of a disc with radius R, where 2*PI*(2R)^2=sigmaNN
    sigma_gg = getSigEff(sigmaNN_in, width);
  }
  else if (shape_of_nucleons==4) // manually fix nucleon width
  {
    width = gauss_nucl_width; 
    sigma_gg = getSigEff(sigmaNN_in, width);
  }
}


//----------------------------------------------------------------------
bool GaussianNucleonsCal::testSmoothCollision(double b)
// Simulate if there is a collision at impact parameter b. The size of
// nucleons are read from those public variables.
{
  if (drand48() < 1.-exp( -sigma_gg*exp(-b*b/(4.*width*width))/(4.*M_PI*width*width) ))
    return true;
  else
    return false;
}

/* Add up the overlap of the quarks to get the total overlap. */
bool GaussianNucleonsCal::testFluctuatedCollision(Particle* me, Particle* you)
{
    double dxy = 0.02;
    double overlap = 0;
    vector<Quark> myQuarks = me->getQuarks();
    vector<Quark> yourQuarks = you->getQuarks();
    double gaussianWidthSqr = Quark::width*Quark::width;
    double cutoffDistance = 5*Quark::width;
    
    for(int i = 0; i < myQuarks.size(); i++)
    {
        Quark mine = myQuarks[i];
        Box2D myBox = mine.getBoundingBox();
        for(int j = 0; j < yourQuarks.size(); j++)
        {
            Quark yours = yourQuarks[j];
            double d = (mine.getX()-yours.getX())*(mine.getX()-yours.getX()) +
                       (mine.getY()-yours.getY())*(mine.getY()-yours.getY());

            overlap += (1/(4*M_PI*gaussianWidthSqr)) * exp(-d/(4*gaussianWidthSqr))/9;
        }
    }
    cout << overlap << endl;
    if(drand48() < 1.-exp(-sigma_gg*overlap))
        return true;
    else
        return false;
}

bool GaussianNucleonsCal::testCollisionFromDensity(Particle* me, Particle* you)
{
    double dxy = 0.02;
    double overlap = 0;

    Box2D intersection = me->getBoundingBox().intersection(you->getBoundingBox());
    for(double x = intersection.getXL(); x < intersection.getXR(); x+=dxy)
    {
      for(double y = intersection.getYL(); y < intersection.getYR(); y+=dxy)
      {
        overlap += dxy*dxy*me->getSmoothTn(x,y)*you->getSmoothTn(x,y);
        //cout << me->getSmoothDensity(x,y) << " " << you->getSmoothDensity(x,y) << endl;
      }
    }
    if(drand48() < 1.-exp(-sigma_gg*overlap))
        return true;
    else
        return false;
}

//-----------------------------------------------------------------------
double GaussianNucleonsCal::get2DHeightFromWidth(double w)
// Return the peak height for a normalized 2d-Gaussian with width=w
{
  return 1/(2*M_PI*w*w);
}

//-----------------------------------------------------------------------
// (YN): compute sigeff(s) from the formula
//        sigmaNN_in(s) = int d^2b [1-exp(-sigeff(s)*Tpp(b))]
//        Reads sigmaNN, returns guassian width
double GaussianNucleonsCal::getSigEff(double siginNN, double width)
{
  int N2=38;  // # of integration points
  double *xg = new double [N2];
  double *wg = new double [N2];
  Nucleus::Gauss38(0.0,1.0,xg,wg);
  double sigin=siginNN*0.1;   // sigma_in(s) [mb --> fm^2]
  
  int ib;
  double sum, dN, Bmax, b, db, Tpp;
  Bmax=5.0*width;

  double sigeff=10.0;  // starting point of iteration
  double sigeff0;     // holds value from previous iteration step
  do {                                       // iterate ...
    sigeff0 = sigeff;
    sum=0.0;
    dN=0.0;
    for(ib=0; ib<N2; ib++) {  // integral d^2b from 0 to Bmax
      b = *(xg+ib)*Bmax;
      db = *(wg+ib)*Bmax;
      Tpp = exp(-b*b/(4.*width*width))/(M_PI*(4.*width*width));
      sum += 2*M_PI*b*db*(1.0 - exp(-sigeff*Tpp));
      dN += 2*M_PI*b*db*Tpp*exp(-sigeff*Tpp);
    }
    sigeff -= (sum-sigin)/dN;
    //cout << "# sigeff=" << sigeff << " siginNN=" << sum << endl;
  } while(abs(sigeff-sigeff0) > 1e-4);       // ... until sigeff has converged

  delete [] xg;
  delete [] wg;

  return sigeff;
}
