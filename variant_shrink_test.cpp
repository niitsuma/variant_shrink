#include "variant_shrink.hpp"
int main()
{
  typedef make_variant_shrink_over<boost::mpl::vector<double,float,int,bool,char> >::type r1type;
  BOOST_MPL_ASSERT((boost::mpl::equal<r1type ,boost::variant<double,bool,char> > ));
  //BOOST_MPL_ASSERT((boost::is_same<r1type ,boost::variant<double,bool,char> > ));


  typedef make_variant_shrink_over<boost::mpl::vector<double,float,int> >::type r2type;
  BOOST_MPL_ASSERT((boost::mpl::equal<r2type ,double > ));
  //BOOST_MPL_ASSERT((boost::is_same<r2type ,double > ));
  r2type d1=1.1,d2=2.2;
  d2=d1+d2;
  std::cout << d2 << std::endl;
    
  
  typedef make_variant_shrink_over<boost::mpl::vector<bool,char,std::string> >::type r3type;
  BOOST_MPL_ASSERT((boost::mpl::equal<r3type ,boost::variant<bool,char,std::string> > )); 
  //BOOST_MPL_ASSERT((boost::is_same<r3type ,boost::variant<bool,charstd::string> > )); 
  r3type v3('a');
  v3="v3";
  //std::cout << v3<std::string > ;
  std::cout << v3 << std::endl;
  v3=false;
  std::cout << v3 << std::endl;

  typedef make_variant_shrink_over<boost::mpl::vector<int,double,double,bool,char,char,std::string> >::type r4type;
  BOOST_MPL_ASSERT((boost::mpl::equal<r4type ,boost::variant<double,bool,char,std::string> > )); 
  
  r4type v4("v4");
  std::cout << v4 << std::endl;
  v4=false;
  std::cout << v4 << std::endl;
  v4=1.11;
  std::cout << v4 << std::endl;
  //v4=v4+v4;


}
