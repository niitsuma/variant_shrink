#include "variant_shrink.hpp"
int main()
{
  typedef make_variant_shrink_over<boost::mpl::vector<double,float,int,bool,char> >::type r1type;
  BOOST_MPL_ASSERT((boost::mpl::equal<r1type ,boost::variant<double,bool,char> > ));
  //BOOST_MPL_ASSERT((boost::is_same<r1type ,boost::variant<double,bool,char> > ));
  r1type val1(1.1);
  std::cout << val1 << std::endl;
  val1='a';
  std::cout << val1 << std::endl;



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

  typedef make_variant_shrink_over<boost::mpl::vector<int,double,double,bool,char,char,std::string> >::type r4type;
  BOOST_MPL_ASSERT((boost::mpl::equal<r4type ,boost::variant<double,bool,char,std::string> > )); 
  
  r4type v4("v4");
  std::cout << v4 << std::endl;
  v4=false;
  std::cout << v4 << std::endl;
  v4=1.11;
  std::cout << v4 << std::endl;
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
  v7=7.7777;
  boost::get<double>(v7);
  boost::get<int>(v7);
  //std::cout << v7<double> << std::endl;




  /////////////////////////////////////util test//////////////////////
    BOOST_MPL_ASSERT((is_less_type_over<int,double,default_type_order>));
  //BOOST_MPL_ASSERT((is_less_type_over<double,int,default_type_order>));
    BOOST_MPL_ASSERT((boost::is_same<greater_type_over::apply<int,double,default_type_order>::type,double> ));
    BOOST_MPL_ASSERT((boost::is_same<greater_type_over::apply<double,int,default_type_order>::type,double> ));
    BOOST_MPL_ASSERT((boost::is_same<greater_type_over::apply<float,short,default_type_order>::type,float> ));
    BOOST_MPL_ASSERT((boost::is_same<max_type_over<boost::mpl::vector<double,float,int>::type,default_type_order   >::type , double>  ));


  typedef mpl_vector_contains_filter<  
    boost::mpl::vector<double,float,int>
    ,boost::mpl::vector<double,float,char>
    >::type ct1;
  //BOOST_MPL_ASSERT((boost::is_same<ct1,boost::mpl::vector<double,float> >));
  BOOST_MPL_ASSERT((boost::mpl::equal< ct1 , boost::mpl::vector<double,float> >));

  typedef mpl_vector_not_contains_filter<  
    boost::mpl::vector<double,float,int,char>
    ,boost::mpl::vector<double,float>
    >::type cnt1;
  BOOST_MPL_ASSERT((boost::mpl::equal< cnt1 , boost::mpl::vector<int,char> >));


  boost::variant<int,double> vari;
  boost::get<int>(vari);
  boost::get<bool>(vari);


}
