#include "variant_shrink.hpp"


template<typename T,typename TBase>
struct is_generalizable_to_custom : public
boost::mpl::if_<
  boost::is_floating_point<T>
  , 
  typename
  boost::mpl::if_< 
    boost::is_floating_point<TBase>
    ,is_less_in_orderd_mpl_sequence<T,TBase,boost::mpl::vector<float,double,long double > >
    ,boost::mpl::false_
    >::type
  //,mpl::false_
  , 
  typename
  boost::mpl::if_<
    boost::is_integral<T>
    ,
    typename
    boost::mpl::if_<
      boost::is_integral<TBase>
      , is_less_in_orderd_mpl_sequence<T,TBase,boost::mpl::vector<bool,char,short,int,long> >
      ,boost::mpl::false_
      >::type
    ,boost::mpl::false_
    >::type
  >::type
{};



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

#if 1

  typedef make_variant_shrink_over<
    boost::mpl::vector<double,float,bool,char> 
    ,generate_mpl_lambda_is_generalizable_to_from_type_order_sequence<      
      boost::mpl::vector<bool,char,std::string>  //your prefer order
      >::type 
    >::type r5type;
   BOOST_MPL_ASSERT((boost::mpl::equal<r5type ,boost::variant<char,double,float> > ));
   //BOOST_MPL_ASSERT((boost::is_same<r5type ,boost::variant<char,double,float> > ));

#endif

#if 1
  typedef make_variant_shrink_over<
    boost::mpl::vector<char,int>//::type
    ,generate_mpl_lambda_is_generalizable_to_from_type_order_sequence<      
      boost::mpl::vector<bool,char,int> //::type  //your prefer order
      >::type
    >::type r6type;
   BOOST_MPL_ASSERT((boost::mpl::equal<r6type ,int > ));
   BOOST_MPL_ASSERT((boost::is_same<r6type ,int > ));
  r6type i1=1,i2=2;
  i2=i1+i2;
#endif
    
#if 1 
  typedef make_variant_shrink_over<
    boost::mpl::vector<char,std::string,double,int>
    ,generate_mpl_lambda_is_generalizable_to_from_type_order_sequence<      
      boost::mpl::vector<bool,char,int,std::string>  //your prefer order
      >::type
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
#endif

#if 1
    typedef make_variant_shrink_over<
      boost::mpl::vector<float,bool,boost::rational<long> >       
      ,generate_mpl_lambda_is_generalizable_to_from_type_order_sequence<      
	boost::mpl::vector<
         bool , int , long , boost::rational<int>  ,  boost::rational<long>
	 >  //your prefer order
	>::type
     >::type r8type;
    BOOST_MPL_ASSERT((boost::mpl::equal<r8type ,boost::variant<boost::rational<long> ,float> > ));
#endif

#if 1
    typedef make_variant_shrink_over<
      boost::mpl::vector< int , boost::rational<int> >
      ,generate_mpl_lambda_is_generalizable_to_from_type_order_sequence<      
	boost::mpl::vector<
         bool , int , long , boost::rational<int>  ,  boost::rational<long>  
	 >  //your prefer order
	>::type
     >::type r9type;
    BOOST_MPL_ASSERT((boost::is_same<r9type ,boost::rational<int> > ));
#endif


    typedef boost::mpl::lambda<is_generalizable_to_custom<boost::mpl::_1 , boost::mpl::_2 > >::type is_generalizable_to_custom_mpl_lambda;

    typedef make_variant_shrink_over<
    boost::mpl::vector<double,float,bool,char> 
    ,is_generalizable_to_custom_mpl_lambda
    >::type r10type;

    BOOST_MPL_ASSERT((boost::mpl::equal<r10type ,boost::variant<double,char> >));

    r10type v10(10.1);
    std::cout << v10 << std::endl;
    std::cout << v10.which() << std::endl;
    boost::get<double>(v10);
    //v10=10;
    v10='a';
    std::cout << v10 << std::endl;
    std::cout << v10.which() << std::endl;
    boost::get<char>(v10);

    typedef make_variant_shrink_over<
    boost::mpl::vector<double,float> 
    ,is_generalizable_to_custom_mpl_lambda
    >::type r11type;
    BOOST_MPL_ASSERT((boost::is_same<r11type ,double > ));



}
