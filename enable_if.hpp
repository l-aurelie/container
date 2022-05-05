#pragma once

namespace ft
{
    /* If B is true, std::enable_if has a public member typedef type, equal to T;
    otherwise, there is no member typedef.
    This metafunction is a convenient way to leverage SFINAE, in particular for
    conditionally removing functions from the candidate set based on type traits,
    allowing separate function overloads or specializations based on those different
    type traits.  */
    template<bool Cond, class T = void>
    struct  enable_if {};

    template<class T>
    struct  enable_if<true, T>
    {
        typedef T   type;
    };

    /*===/ IS INTEGRAL /===*/
    /* Inherit from integral_constant */
    template<class T, T v>
    struct  integral_constant
    {
        typedef T                           value_type;
        typedef integral_constant<T, v>     type;
        static const T value = v;

        operator value_type(void) const { return value; }
    };

    /* Checks whether T is an integral type. Provides the member constant
    value which is equal to true, if T is one of the type following */
    typedef integral_constant<bool, true>   true_type;
    typedef integral_constant<bool, false>  false_type;

    template<class T>
    struct  is_integral : public false_type {};

    template<>
    struct  is_integral<bool> : public true_type {};

    template<>
    struct  is_integral<char> : public true_type {};

    template<>
    struct  is_integral<wchar_t> : public true_type {};

    template<>
    struct  is_integral<signed char> : public true_type {};

    template<>
    struct  is_integral<short int> : public true_type {};

    template<>
    struct  is_integral<int> : public true_type {};

    template<>
    struct  is_integral<long int> : public true_type {};

    template<>
    struct  is_integral<unsigned char> : public true_type {};

    template<>
    struct  is_integral<unsigned int> : public true_type {};

    template<>
    struct  is_integral<unsigned long int> : public true_type {};

    template<>
    struct  is_integral<unsigned short int> : public true_type {};


    template<>
    struct  is_integral<const bool> : public true_type {};

    template<>
    struct  is_integral<const char> : public true_type {};

    template<>
    struct  is_integral<const wchar_t> : public true_type {};

    template<>
    struct  is_integral<const signed char> : public true_type {};

    template<>
    struct  is_integral<const short int> : public true_type {};

    template<>
    struct  is_integral<const int> : public true_type {};

    template<>
    struct  is_integral<const long int> : public true_type {};

    template<>
    struct  is_integral<const unsigned char> : public true_type {};

    template<>
    struct  is_integral<const unsigned int> : public true_type {};

    template<>
    struct  is_integral<const unsigned long int> : public true_type {};

    template<>
    struct  is_integral<const unsigned short int> : public true_type {};
}