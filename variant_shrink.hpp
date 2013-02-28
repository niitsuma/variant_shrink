#ifndef VARIANT_SHRINK
#define VARIANT_SHRINK


#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/unique.hpp>
#include <boost/mpl/copy.hpp>

#include <boost/rational.hpp>
#include <boost/math/complex.hpp>

#include <boost/variant.hpp>


//typedef boost::mpl::vector<unsigned,short,int,boost::rational<int>,float,double,long double,std::complex<double>,std::complex<long double>  >::type ordered_number_types;
//typedef ordered_number_types 

typedef boost::mpl::vector<int,boost::rational<int>,float,double,std::complex<double>  >::type default_type_order;




//typedef boost::mpl::lambda<boost::mpl::contains<ordered_number_types,boost::mpl::_1>  >::type  is_number_type_mpl_lambda;
//typedef boost::mpl::lambda<boost::mpl::not_<boost::mpl::contains<ordered_number_types,boost::mpl::_1>  > >::type  is_not_number_type_mpl_lambda;
 

//typedef boost::mpl::lambda<boost::mpl::filter_view<boost::mpl::_1 , is_number_type_mpl_lambda> >::type number_type_filter_mpl_lambda;
//typedef boost::mpl::lambda<boost::mpl::filter_view<boost::mpl::_1 , is_not_number_type_mpl_lambda> >::type not_number_type_filter_mpl_lambda;


  template<typename TypeVec,typename TypeOrder=default_type_order>
  struct mpl_vector_contains_filter : boost::mpl::filter_view<
    TypeVec
    ,boost::mpl::contains<TypeOrder,boost::mpl::_1>
    >
  {};


  template<typename TypeVec,typename TypeOrder=default_type_order>
  struct mpl_vector_not_contains_filter : boost::mpl::filter_view<
    TypeVec
    ,boost::mpl::not_<boost::mpl::contains<TypeOrder,boost::mpl::_1> >
    >
  {};


  // template<typename T1,typename T2>
  // struct is_less_number_type
  //   :
  //    boost::is_same <
  //    typename boost::mpl::find<      
  //     typename  boost::mpl::iterator_range<
  // 	typename boost::mpl::find<ordered_number_types,T2>::type , 
  // 	typename boost::mpl::end< ordered_number_types >::type
  // 	>::type , 
  //     T1 >::type, 
  //   typename boost::mpl::end<ordered_number_types >::type >
  // {};


   template<typename T1,typename T2,typename TypeOrder>
   struct is_less_type_over
    :
     boost::is_same <
     typename boost::mpl::find<      
      typename  boost::mpl::iterator_range<
	typename boost::mpl::find<TypeOrder,T2>::type , 
	typename boost::mpl::end<TypeOrder>::type
	>::type , 
      T1 >::type, 
    typename boost::mpl::end<TypeOrder>::type >
  {};
  
//typedef boost::mpl::lambda<boost::mpl::if_<is_less_number_type< boost::mpl::_1 , boost::mpl::_2> , boost::mpl::_2, boost::mpl::_1> >::type  greater_number_type;

//typedef boost::mpl::lambda<boost::mpl::if_<is_less_type_over< boost::mpl::_1 , boost::mpl::_2 , boost::mpl::_3> , boost::mpl::_2, boost::mpl::_1> >::type  greater_type_over;


  

  // template<typename TypeVec>
  // struct max_number_type
  //   :  
  //   public boost::mpl::fold<
  //   TypeVec,
  //   typename boost::mpl::front<TypeVec>::type
  //   //boost::mpl::front<TypeVec>::type
  //   //int
  //   , greater_number_type
  //   >
  // {};


  template<typename TypeVec,typename Order>
  struct max_type_over
    :  
    public boost::mpl::fold<
    TypeVec,
    typename boost::mpl::front<TypeVec>::type
    //boost::mpl::front<TypeVec>::type
    //int
    , boost::mpl::if_<is_less_type_over< boost::mpl::_1 , boost::mpl::_2 , Order> , boost::mpl::_2, boost::mpl::_1>
    //greater_type_over
    >
  {};

  // template<typename TypeVec,typename TypeOrder=default_type_order>
  // struct make_variant_concatenate_and_max_vector_over : public 
  // boost::mpl::copy<
  //   typename not_number_type_filter_mpl_lambda::apply<TypeVec>::type
  //   ,typename boost::mpl::back_inserter< 
  //      typename boost::mpl::vector<
  // 	 typename max_number_type<
  // 	   typename number_type_filter_mpl_lambda::apply<TypeVec>::type
  // 	   >::type
  //        >::type
  //      >
  //   >::type
  // {};

  template<typename TypeVec,typename TypeOrder=default_type_order>
  struct make_variant_concatenate_and_max_vector_over : public 
  boost::mpl::copy<
    typename mpl_vector_not_contains_filter<TypeVec,TypeOrder>::type ,
    typename boost::mpl::back_inserter< 
      typename boost::mpl::vector<
	 typename max_type_over<
	   typename mpl_vector_contains_filter<TypeVec,TypeOrder>::type
	   ,TypeOrder
	   >::type
         >::type
     >
    >::type
  {};


  template<typename TypeVec,typename TypeOrder=default_type_order>
  struct make_variant_shrink_without_unique_over_not_empty_number : public 
  boost::mpl::if_<  
    boost::mpl::empty<
      //typename not_number_type_filter_mpl_lambda::apply<TypeVec>::type 
      typename mpl_vector_not_contains_filter<TypeVec,TypeOrder>::type
      >//::type
    //,typename max_number_type<TypeVec>::type
    ,typename max_type_over<TypeVec,TypeOrder>::type
    ,typename boost::make_variant_over<
       typename make_variant_concatenate_and_max_vector_over<TypeVec,TypeOrder>::type
       >::type
    >
  {};


  template<typename TypeVec,typename TypeOrder=default_type_order>
  struct make_variant_shrink_without_unique_over : public 
  boost::mpl::if_<
    boost::mpl::empty<
      //typename number_type_filter_mpl_lambda::apply<TypeVec>::type 
      typename mpl_vector_contains_filter<TypeVec,TypeOrder>::type
      > //::type
    ,typename boost::make_variant_over<TypeVec>
    ,make_variant_shrink_without_unique_over_not_empty_number<TypeVec,TypeOrder>
    >
  {};

  template<typename TypeVec,typename TypeOrder=default_type_order>
  struct make_variant_shrink_over : make_variant_shrink_without_unique_over<
    typename boost::mpl::unique<
      TypeVec
      ,boost::is_same<boost::mpl::_1,boost::mpl::_2>
      >::type
    ,TypeOrder
    >::type
  {};





#endif //VARIANT_SHRINK
