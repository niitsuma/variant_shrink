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



  typedef boost::mpl::vector<int,boost::rational<int>,float,double,std::complex<double>  >::type default_type_order;


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



   template<typename T1,typename T2,typename TypeOrder>
   struct is_less_type_over :
     boost::is_same <
     typename boost::mpl::find<      
      typename  boost::mpl::iterator_range<
	typename boost::mpl::find<TypeOrder,T2>::type , 
	typename boost::mpl::end<TypeOrder>::type
	>::type , 
      T1 >::type, 
    typename boost::mpl::end<TypeOrder>::type >
  {};
  


  template<typename TypeVec,typename Order>
  struct max_type_over : public 
  boost::mpl::fold<
    TypeVec,
    typename boost::mpl::front<TypeVec>::type
    , boost::mpl::if_<is_less_type_over< boost::mpl::_1 , boost::mpl::_2 , Order> , boost::mpl::_2, boost::mpl::_1>
    >
  {};


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
      typename mpl_vector_not_contains_filter<TypeVec,TypeOrder>::type
      >//::type
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
