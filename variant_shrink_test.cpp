#include "variant_shrink.hpp"


int main()
{

  typedef make_variant_shrink_over<
    boost::mpl::vector<double,float,int,bool,char> 
    >::type r1type;
  BOOST_MPL_ASSERT((boost::mpl::equal<r1type ,boost::variant<double,bool,char> > ));
  //BOOST_MPL_ASSERT((boost::is_same<r1type ,boost::variant<double,bool,char> > ));
  r1type val1(1.1);
  std::cout << val1 << std::endl;
  std::cout << val1.which() << std::endl;

  val1='a';
  std::cout << val1 << std::endl;
  std::cout << val1.which() << std::endl;

  val1=false;
  std::cout << val1 << std::endl;
  std::cout << val1.which() << std::endl;




  typedef make_variant_shrink_over<boost::mpl::vector<double,float,int> >::type r2type;
  BOOST_MPL_ASSERT((boost::mpl::equal<r2type ,double > ));
  BOOST_MPL_ASSERT((boost::is_same<r2type ,double > ));
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


  typedef make_variant_shrink_over<boost::mpl::vector<int,double,double,char,char,std::string> >::type r4type;
  BOOST_MPL_ASSERT((boost::mpl::equal<r4type ,boost::variant<double,char,std::string> > )); 
  
  r4type v4("v4");
  std::cout << v4 << std::endl;
  std::cout << v4.which() << std::endl;

  //v4=false;
  //std::cout << v4 << std::endl;
  //std::cout << v4.which() << std::endl;

  v4='4';
  std::cout << v4 << std::endl;
  std::cout << v4.which() << std::endl;

  v4=4.44;
  std::cout << v4 << std::endl;
  std::cout << v4.which() << std::endl;

  // v4=4;
  // std::cout << v4 << std::endl;
  // std::cout << v4.which() << std::endl;

  //v4=v4+v4;





  typedef make_variant_shrink_over<
    boost::mpl::vector<double,float,bool,char> 
    ,boost::mpl::vector<bool,char,std::string>  //your prefer order
    >::type r5type;
   BOOST_MPL_ASSERT((boost::mpl::equal<r5type ,boost::variant<char,double,float> > ));
   //BOOST_MPL_ASSERT((boost::is_same<r5type ,boost::variant<char,double,float> > ));


  typedef make_variant_shrink_over<
    boost::mpl::vector<char,int>::type
    ,boost::mpl::vector<bool,char,int>::type  //your prefer order
    >::type r6type;
   BOOST_MPL_ASSERT((boost::mpl::equal<r6type ,int > ));
   BOOST_MPL_ASSERT((boost::is_same<r6type ,int > ));
  r6type i1=1,i2=2;
  i2=i1+i2;
    
  
  typedef make_variant_shrink_over<
    boost::mpl::vector<char,std::string,double,int>
    ,boost::mpl::vector<bool,char,int,std::string>  //your prefer order
    >::type r7type;
   BOOST_MPL_ASSERT((boost::mpl::equal<r7type ,boost::variant<std::string,double> > )); 
  
  r7type v7("v777");
  std::cout << v7 << std::endl;
  std::cout << v7.which() << std::endl;

  //assert( v7.which() == 0 );  
  //v7=7.7777;
  //boost::get<double>(v7);
  //boost::get<int>(v7);
  //std::cout << v7<double> << std::endl;

    typedef make_variant_shrink_over<
     boost::mpl::vector<float,bool,boost::rational<long> > 
     ,
     boost::mpl::vector<
         bool , int , long , boost::rational<int>  ,  boost::rational<long>
	 >  //your prefer order

     >::type r8type;
    BOOST_MPL_ASSERT((boost::mpl::equal<r8type ,boost::variant<boost::rational<long> ,float> > ));


    typedef make_variant_shrink_over<
     boost::mpl::vector< int , boost::rational<int> >
     ,boost::mpl::vector<
         bool , int , long , boost::rational<int>  ,  boost::rational<long>  
	 >  //your prefer order
     >::type r9type;
    BOOST_MPL_ASSERT((boost::is_same<r9type ,boost::rational<int> > ));

}
