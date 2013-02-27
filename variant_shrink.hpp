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


  typedef boost::mpl::vector<int,boost::rational<int>,float,double,long double,std::complex<double>,std::complex<long double>  >::type ordered_number_types;




  typedef boost::mpl::lambda<boost::mpl::contains<ordered_number_types,boost::mpl::_1>  >::type  is_number_type_mpl_lambda;
  typedef boost::mpl::lambda<boost::mpl::not_<boost::mpl::contains<ordered_number_types,boost::mpl::_1>  > >::type  is_not_number_type_mpl_lambda;
 

  typedef boost::mpl::lambda<boost::mpl::filter_view<boost::mpl::_1 , is_number_type_mpl_lambda> >::type number_type_filter_mpl_lambda;
  typedef boost::mpl::lambda<boost::mpl::filter_view<boost::mpl::_1 , is_not_number_type_mpl_lambda> >::type not_number_type_filter_mpl_lambda;



  template<typename T1,typename T2>
  struct is_less_number_type
    :
     boost::is_same <
     typename boost::mpl::find<      
      typename  boost::mpl::iterator_range<
	typename boost::mpl::find<ordered_number_types,T2>::type , 
	typename boost::mpl::end< ordered_number_types >::type
	>::type , 
      T1 >::type, 
    typename boost::mpl::end<ordered_number_types >::type >
  {};
  
  typedef boost::mpl::lambda<boost::mpl::if_<is_less_number_type< boost::mpl::_1 , boost::mpl::_2> , boost::mpl::_2, boost::mpl::_1> >::type  greater_number_type;
  

  template<typename TypeVec>
  struct max_number_type
    :  
    public boost::mpl::fold<
    TypeVec,
    typename boost::mpl::front<TypeVec>::type
    //boost::mpl::front<TypeVec>::type
    //int
    , greater_number_type
    >
  {};

  template<typename TypeVec>
  struct variant_shrink_after_unique_concatenate_and_max_vector : public 
  boost::mpl::copy<
    typename not_number_type_filter_mpl_lambda::apply<TypeVec>::type
    ,typename boost::mpl::back_inserter< 
       typename boost::mpl::vector<
	 typename max_number_type<
	   typename number_type_filter_mpl_lambda::apply<TypeVec>::type
	   >::type
         >::type
       >
    >::type
  {};

  template<typename TypeVec>
  struct variant_shrink_after_unique_not_empty_number : public 
  boost::mpl::if_<  
    boost::mpl::empty<
      typename not_number_type_filter_mpl_lambda::apply<TypeVec>::type 
      >//::type
    ,typename max_number_type<TypeVec>::type
    ,typename boost::make_variant_over<
       typename variant_shrink_after_unique_concatenate_and_max_vector<TypeVec>::type
       >::type
    >
  {};


  template<typename TypeVec>
  struct variant_shrink_after_unique : public 
  boost::mpl::if_<
    boost::mpl::empty<
      typename number_type_filter_mpl_lambda::apply<TypeVec>::type 
      > //::type
    ,typename boost::make_variant_over<TypeVec>
    ,variant_shrink_after_unique_not_empty_number<TypeVec>
    >
  {};

  template<typename TypeVec>
  struct 
  //variant_shrink 
  make_variant_shrink_over
    : public 
  variant_shrink_after_unique<
    typename boost::mpl::unique<
      TypeVec
      ,boost::is_same<boost::mpl::_1,boost::mpl::_2>
      >::type
    >::type
  {};


#endif
