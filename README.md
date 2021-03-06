`boost::variant` should reduce

`variant<int,int> `  
=> `int`

`variant<int,double> `  
=> `double `


`variant<int,boost::rational<int> > `  
=> `boost::rational<int> `  

`variant<int,double,std::string> `  
=> `variant<double,std::string>`

`variant_shrink` is such extension

# Usage:

just ` #include "variant_shrink.hpp" `  then

`make_variant_shrink_over<boost::mpl::vector<int,int> >::type`  
=> `int` 

`make_variant_shrink_over<boost::mpl::vector<int,boost::rational<int> >::type `  
=> `boost::rational <int>`

`make_variant_shrink_over<boost::mpl::vector<int,double >  >::type `  
=> `double `

`make_variant_shrink_over<boost::mpl::vector<double,std::string> >::type `  
=> `boost::variant<double,std::string>`

`make_variant_shrink_over<boost::mpl::vector<double,int,std::string> >::type `  
=> `boost::variant<double,std::string>`


# Example:

    template<typename X,typename Y> 
    typename make_variant_shrink_over<boost::mpl::vector<X,Y> >::type // same to decltype(x+y)
    adder(X x, Y y) {return x + y;} 
    
    
    double r1= adder(1,1.1); 
    
    
    boost::rational<int> x(2,3); 
    boost::rational<int> r2 = adder(1,x); 



# Advanced:
You can use your prefer type order.
For example, order:

    bool < int < long < boost::rational<int>  <  boost::rational<long>

can be used 

    typedef make_variant_shrink_over<
      boost::mpl::vector<float,bool,boost::rational<long> >       
      ,generate_mpl_lambda_is_generalizable_to_from_type_order_sequence<      
        boost::mpl::vector<
         bool , int , long , boost::rational<int>  ,  boost::rational<long>
          >  //your prefer order
        >::type
      >::type r8type;
    BOOST_MPL_ASSERT((boost::mpl::equal<r8type ,boost::variant<boost::rational<long> ,float> > ));


    typedef make_variant_shrink_over<
      boost::mpl::vector< int , boost::rational<int> >
      ,generate_mpl_lambda_is_generalizable_to_from_type_order_sequence<      
        boost::mpl::vector<
         bool , int , long , boost::rational<int>  ,  boost::rational<long>  
          >  //your prefer order
        >::type
      >::type r9type;
    BOOST_MPL_ASSERT((boost::is_same<r9type ,boost::rational<int> > ));

## define `is_generalizable_to ` :

More complicate type order can use by defining `is_generalizable_to<TypeFrom,TypeTo> ` .
For example:

float order:

    float < double < long double

int order:

    bool < char < short < int <  long  

And no relation between float and int orders.
Such relation can be used by defining following `is_generalizable_to ` function object:



    template<typename T,typename TBase>
    struct is_generalizable_to_custom : public
    boost::mpl::if_<
      boost::is_floating_point<T>
      , typename boost::mpl::if_< 
         boost::is_floating_point<TBase>
    	 ,is_less_in_orderd_mpl_sequence<
              T,TBase,boost::mpl::vector<float,double,long double > >  //float order
    	 ,boost::mpl::false_                      //no relation between float and int
    	 >::type
	 ,typename boost::mpl::if_<
	     boost::is_integral<T>
    	     ,typename boost::mpl::if_<
	           boost::is_integral<TBase>
      		   ,is_less_in_orderd_mpl_sequence<
               T,TBase,boost::mpl::vector<bool,char,short,int,long> > //int order
      		   ,boost::mpl::false_
              >::type
    	     ,boost::mpl::false_  //no change other types
         >::type 
      >::type
    {};
    
    typedef boost::mpl::lambda<is_generalizable_to_custom<
        boost::mpl::_1 , boost::mpl::_2 > >::type 
           is_generalizable_to_custom_mpl_lambda;

    typedef make_variant_shrink_over<
      boost::mpl::vector<double,float,bool,char> 
      ,is_generalizable_to_custom_mpl_lambda //input your custum order inforamtion as 2nd arg
    >::type r10type;

    BOOST_MPL_ASSERT((boost::mpl::equal<r10type 
       ,boost::variant<double,char> >));

### meaning `is_generalizable_to `:

`is_generalizable_to<float,double> ` => `mpl::true_ ` : `float ` can generailize to `double `

`is_generalizable_to<double,float> ` => `mpl::false_ ` : `double ` can not generailize to `float `

`is_generalizable_to<std::string,float> ` => `mpl::false_ ` : `std::string ` can not compare `float ` or `std::string ` can not generailize to `float `




# License

Boost license


© Copyright Hirotaka Niitsuma 2013;
