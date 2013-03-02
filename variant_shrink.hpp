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

#include <boost/mpl/partition.hpp>


#include <boost/rational.hpp>
#include <boost/math/complex.hpp>

#include <boost/variant.hpp>


typedef boost::mpl::vector<int,boost::rational<int>,float,double,std::complex<double>  >::type default_type_order;


////////////mpl general util begin

template<typename TypeVec>
struct is_mpl_sequence_single : 
  boost::is_same<
  typename boost::mpl::size<TypeVec>::type
  ,typename boost::mpl::long_<1> >
 {};

template<typename TypeVec>
struct mpl_sequence_if_single_then_element_else_variant : public
  boost::mpl::if_<
  typename is_mpl_sequence_single<TypeVec>::type
  ,
  typename 
  boost::mpl::front<TypeVec>//::type
  //,typename TypeVec::type
  //,TypeVec
  ,typename boost::make_variant_over<TypeVec>
  >::type
{};

  template<typename TypeVec,typename IsLess>
  struct max_in_mpl_sequence_given_is_less_lambda : public 
  boost::mpl::fold<
    TypeVec
    ,typename boost::mpl::front<TypeVec>::type
    ,boost::mpl::if_<
       boost::mpl::bind2<IsLess,boost::mpl::_1 , boost::mpl::_2 >
       //typename boost::mpl::apply<IsLess,boost::mpl::_1 , boost::mpl::_2 >//::type
       //typename IsLess::apply< boost::mpl::_1 , boost::mpl::_2 >
       //boost::mpl::true_
       ,boost::mpl::_2 , boost::mpl::_1 >
    >
  {};


  template<typename TypeVec,typename TypeOrder>
  struct mpl_vector_contains_filter : boost::mpl::filter_view<
    TypeVec
    ,boost::mpl::contains<TypeOrder,boost::mpl::_1>
    >
  {};

  template<typename TypeVec,typename TypeOrder>
  struct mpl_vector_not_contains_filter : boost::mpl::filter_view<
    TypeVec
    ,boost::mpl::not_<boost::mpl::contains<TypeOrder,boost::mpl::_1> >
    >
  {};



////////////mpl general util end



   template<typename T1,typename T2,typename TypeOrder>
   struct is_less_in_orderd_mpl_sequence :
     boost::is_same <
     typename boost::mpl::find<      
      typename  boost::mpl::iterator_range<
	typename boost::mpl::find<TypeOrder,T2>::type , 
	typename boost::mpl::end<TypeOrder>::type
	>::type , 
      T1 >::type, 
    typename boost::mpl::end<TypeOrder>::type >
  {};

  typedef boost::mpl::lambda<is_less_in_orderd_mpl_sequence<boost::mpl::_1 , boost::mpl::_2 , default_type_order> >::type is_less_over_default_type_order_mpl_lambda;


  //shrinkable
 //generalizable
   template<typename T1,typename TBase,typename TypeOrder>
   struct is_generalizable_to_using_generaize_order_sequence :
     boost::mpl::if_<
     typename 
     boost::mpl::contains<TypeOrder,T1>::type
     ,
     typename
     boost::mpl::if_<
	typename 
	boost::mpl::contains<TypeOrder,TBase>::type
	,
	//typename 
	is_less_in_orderd_mpl_sequence<T1,TBase,TypeOrder> //::type
	,
	//typename 
	boost::mpl::false_ //::type 
	>::type
     ,
     //typename 
     boost::mpl::false_ //::type 
     > ::type
  {};

template<typename TypeOrder>
struct generate_mpl_lambda_is_generalizable_to_from_type_order_sequence
{ typedef typename boost::mpl::lambda<is_generalizable_to_using_generaize_order_sequence<boost::mpl::_1 , boost::mpl::_2 , TypeOrder> >::type type;
};

//typedef boost::mpl::lambda<is_generalizable_to_using_generaize_order_sequence<boost::mpl::_1 , boost::mpl::_2 , default_type_order> >::type is_generalizable_using_default_type_order_mpl_lambda;

typedef generate_mpl_lambda_is_generalizable_to_from_type_order_sequence<default_type_order>::type is_generalizable_using_default_type_order_mpl_lambda;


//template<typename TypeVec,typename Greater>
template<typename TypeVec,typename TypeBase,typename IsGeneralizable>
  struct generalize_type_sequence_to_base : 
  boost::mpl::transform<
    TypeVec
    ,boost::mpl::if_<
       boost::mpl::bind2<IsGeneralizable,boost::mpl::_1 , TypeBase >
       ,TypeBase
       ,boost::mpl::_1>
   >
  {};


template<typename TypeVec,typename IsGeneralizable>
struct generaize_type_sequence_using_is_generalizable_to : 
  boost::mpl::fold<
  TypeVec
  ,TypeVec
  ,
  //typename 
  generalize_type_sequence_to_base<boost::mpl::_1,boost::mpl::_2,IsGeneralizable > //::type
  >::type
{};

  
template<typename TypeVec,typename IsGeneralizable=is_generalizable_using_default_type_order_mpl_lambda >
struct make_variant_shrink_over : public
//mpl_sequence_if_single_to_element
mpl_sequence_if_single_then_element_else_variant<
  typename 
  boost::mpl::unique<
    typename 
    generaize_type_sequence_using_is_generalizable_to<TypeVec,IsGeneralizable>::type
    ,boost::is_same<boost::mpl::_1,boost::mpl::_2>
    >::type
  >//::type
  {};




#endif //VARIANT_SHRINK
