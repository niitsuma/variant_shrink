`boost::variant` should be

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
    typename make_variant_shrink_over<boost::mpl::vector<X,Y> >::type 
    adder(X x, Y y) {return x + y;} 
    
    
    double r1= adder(1,1.1); 
    
    
    boost::rational<int> x(2,3); 
    boost::rational<int> r2 = adder(1,x); 



# Advanced:

You can use your prefer type oder  

    typedef make_variant_shrink_over<
     boost::mpl::vector<double,float,bool,char> 
     ,boost::mpl::vector<bool,char,std::string>  //your prefer order
     >::type r5type;
    BOOST_MPL_ASSERT((boost::mpl::equal<r5type ,boost::variant<char,double,float> > ));

   typedef make_variant_shrink_over<
     boost::mpl::vector<char,int>::type
     ,boost::mpl::vector<bool,char,int>::type  //your prefer order
     >::type r6type;
   BOOST_MPL_ASSERT((boost::is_same<r6type ,int > ));



# license

Boost license


© Copyright Hirotaka Niitsuma 2012-2013;
