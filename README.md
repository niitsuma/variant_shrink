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
    typename make_variant_shrink_over<boost::mpl::vector<X,Y> >::type // == decltype(x+y)
    adder(X x, Y y) {return x + y;} 
    
    
    double r1= adder(1,1.1); 
    
    
    boost::rational<int> x(2,3); 
    boost::rational<int> r2 = adder(1,x); 



# Advanced:

You can use your prefer generalize type order.
For example, order:

    bool < int < long < boost::rational<int>  <  boost::rational<long>

can be used 

    typedef make_variant_shrink_over<
     boost::mpl::vector<float,bool,boost::rational<long> >
     ,boost::mpl::vector<
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


# License

Boost license


© Copyright Hirotaka Niitsuma 2013;
