#include "variant_shrink.hpp"

template<typename X,typename Y>
typename make_variant_shrink_over<boost::mpl::vector<X,Y> >::type
adder(X x, Y y) {return x + y;}


int main()
{
  double r1= adder(1,1.1);

  boost::rational<int> x(2,3);
  boost::rational<int> r2 = adder(1,x);
  

}
