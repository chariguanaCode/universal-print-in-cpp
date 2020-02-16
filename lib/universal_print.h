/* ==============================================================================
 *
 *  Contributors:
 *      Name:       Kajetan Lewandowski
 *      Nickname:   LegwanXDL
 *
 *      Name:       Adam Jeliñski
 *      Nickname:   charodziej
 *
 *  Description:    A library implementing a uniform method of printing variables in C++.
 *                  Mainly intended for competetive programming, to greatly speedup debugging.
 *
 *  Created:        08.04.2019
 *  Last updated:   16.02.2020
 *
 *  Version: 2.0.0
 *
 *  universal-print-in-cpp
 *  Universal print in C++
 *  the Competetive Universal Print Library
 *
 *  g++ -std=c++11 -o template.o template.cpp
 *  ./template.o
 *
 * ============================================================================== */

#ifndef _universal_print_h_
#define _universal_print_h_

/** =============================================================================
  * User setup (colours' and character encoding definitions, std::cout precision)
  * ============================================================================= **/

/* ------------------------------------------------------------------------------
 *  Here you can change colors using numbers from the ANSI 8-bit colour table
 *  https://i.stack.imgur.com/KTSQa.png
 * ------------------------------------------------------------------------------ */

#define COLOUR_DEBUG_MODE_BANNER    250
#define COLOUR_LINE                 220
#define COLOUR_TYPE_NAME            250
#define COLOUR_NAME                  40

#define COLOUR_NUMBER                44
#define COLOUR_POINTER              213
#define COLOUR_BACKGR_NULLPOINTER   196
#define COLOUR_NULLPOINTER           15
#define COLOUR_STRING                28
#define COLOUR_BITSET                48
#define COLOUR_BINARY_TREE          214

#define COLOUR_ARRAY 31,208,87,93,160,31

/* ------------------------------------------------------------------------------
 *  Here you can change the character encoding: EXTENDED_ASCII/UNICODE/LEGACY
 *  Check your terminal encoding by calling cupl::checkEncodingCompatibility()
 *  (you need to uncomment the following #define for your changes to be considered)
 * ------------------------------------------------------------------------------ */

//#define CHARACTER_ENCODING LEGACY

//if you don't uncomment the define above, the default one for your system will be used

#ifndef CHARACTER_ENCODING
#   if defined _WIN32 || defined _WIN64
#       define CHARACTER_ENCODING EXTENDED_ASCII
#   else
#       define CHARACTER_ENCODING UNICODE
#   endif
#endif

/* ------------------------------------------------------------------------------
 *  Here you can set the std::cout precision (5 by default)
 * ------------------------------------------------------------------------------ */

#define STD_COUT_PRECISION 5

/** =============================================================================
  *                         Libraries and initialization
  * ============================================================================= **/

#define TODO /**/
#include <iostream>
#include <queue>
#include <stack>
#include <bitset>
#include <memory>
#include <sstream>

//for visual studio users <3
#ifndef _MSC_VER
#   include <cxxabi.h>
#endif
#ifdef _MSC_VER
#   pragma message("We have detected that you are using Visual Studio. Please make the world a better place and stop this activity.")
#endif

    /* ------------------------------------------------------------------------------
     *                             Fixing std::to_string
     * ------------------------------------------------------------------------------ */
 namespace std {
    //in GCC 4.8.1 to_string bug is fixed
    #if __GNUC__ < 4 || \
            (__GNUC__ == 4 && (__GNUC_MINOR__ < 8 || \
                                (__GNUC_MINOR__ == 8 && \
                                __GNUC_PATCHLEVEL__ < 1)))
        std::string to_string(size_t n) {
            std::ostringstream s;
            s << n;
            return s.str();
        }
    #endif
}

namespace cupl {

    /* ------------------------------------------------------------------------------
     *                   Enabling ANSI escape sequences on Windows
     * ------------------------------------------------------------------------------ */
#if defined _WIN32 || defined _WIN64
#   include <windows.h>
    bool ANSIsupport = [] {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut == INVALID_HANDLE_VALUE) {
            return 0;
        }
        DWORD dwMode = 0;
        if (!GetConsoleMode(hOut, &dwMode)) {
            return 0;
        }
        dwMode |= 0x0004;
        if (!SetConsoleMode(hOut, dwMode)) {
            return 0;
        }
        return 1;
    }();
#else
    bool ANSIsupport = true;
#endif

    /* ------------------------------------------------------------------------------
     *  Method of determining if a variable is iterable
     *  thx to Jarod42
     *  https://stackoverflow.com/questions/13830158/check-if-a-variable-is-iterable
     * ------------------------------------------------------------------------------ */
    namespace detail {
        using std::begin;
        using std::end;

        template <typename T>
        auto is_iterable_impl(int)
        -> decltype (
            begin(std::declval<T&>()) != end(std::declval<T&>()),   // begin/end and operator !=
            void(),                                                 // Handle evil operator ,
            ++std::declval<decltype(begin(std::declval<T&>()))&>(), // operator ++
            void(*begin(std::declval<T&>())),                       // operator*
            std::true_type {});

        template <typename T>
        std::false_type is_iterable_impl(...);
    }
     /* ------------------------------------------------------------------------------
     *  Method of determining variables type ( may not be used in the final version )
     *  thx to Howard Hinnant
     *  https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c
     * ------------------------------------------------------------------------------ */
    template <class T> std::string type_name() {
        typedef typename std::remove_reference<T>::type TR;
        std::unique_ptr<char, void(*)(void*)> own
        (
            abi::__cxa_demangle(typeid(TR).name(), nullptr, nullptr, nullptr),
            std::free
        );
        std::string r = own != nullptr ? own.get() : typeid(TR).name();
        if (std::is_const<TR>::value)
            r += " const";
        if (std::is_volatile<TR>::value)
            r += " volatile";
        if (std::is_lvalue_reference<T>::value)
            r += "&";
        else if (std::is_rvalue_reference<T>::value)
            r += "&&";
        return r;
    }
}

/** =============================================================================
  *                              Support for structs
  * ============================================================================= **/

#define _GET_NTH_ARG(_1, _2, _3, _4, _5, N, ...) N

#define _fe_0(_call, ...)
#define _fe_1(_call, member)      _call(member)
#define _fe_2(_call, member, ...) _call(member) _fe_1(_call, __VA_ARGS__)
#define _fe_3(_call, member, ...) _call(member) _fe_2(_call, __VA_ARGS__)
#define _fe_4(_call, member, ...) _call(member) _fe_3(_call, __VA_ARGS__)

#define _CALL_MACRO_FOR_EACH(func, ...) \
    _GET_NTH_ARG("ignored", ##__VA_ARGS__, \
    _fe_4, _fe_3, _fe_2, _fe_1, _fe_0)(func, ##__VA_ARGS__)

#define _PRINT_STRUCT_MEMBER(_member) \
    cupl::print_struct_member(this->_member, #_member);

#define declare_struct(...) \
    void print_process() { \
        _CALL_MACRO_FOR_EACH(_PRINT_STRUCT_MEMBER, ##__VA_ARGS__); \
    }

/** =============================================================================
  *                                 Declarations
  * ============================================================================= **/
#define EXTENDED_ASCII 1
#define UNICODE 2
#define LEGACY 3

#define _CUPL_GET_NUMBER_OF_WATCH_ARGS_(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, N, ...) N

#define _CUPL_watch_1(line, var, ...) cupl::print_main(var, line, #var);
#define _CUPL_watch_2(line, var, ...) cupl::print_main(var, line, #var); _CUPL_watch_1(line,__VA_ARGS__)
#define _CUPL_watch_3(line, var, ...) cupl::print_main(var, line, #var); _CUPL_watch_2(line,__VA_ARGS__)
#define _CUPL_watch_4(line, var, ...) cupl::print_main(var, line, #var); _CUPL_watch_3(line,__VA_ARGS__)
#define _CUPL_watch_5(line, var, ...) cupl::print_main(var, line, #var); _CUPL_watch_4(line,__VA_ARGS__)
#define _CUPL_watch_6(line, var, ...) cupl::print_main(var, line, #var); _CUPL_watch_5(line,__VA_ARGS__)
#define _CUPL_watch_7(line, var, ...) cupl::print_main(var, line, #var); _CUPL_watch_6(line,__VA_ARGS__)
#define _CUPL_watch_8(line, var, ...) cupl::print_main(var, line, #var); _CUPL_watch_7(line,__VA_ARGS__)
#define _CUPL_watch_9(line, var, ...) cupl::print_main(var, line, #var); _CUPL_watch_8(line,__VA_ARGS__)
#define _CUPL_watch_10(line, var, ...) cupl::print_main(var, line, #var); _CUPL_watch_9(line,__VA_ARGS__)
#define _CUPL_watch_11(line, var, ...) cupl::print_main(var, line, #var); _CUPL_watch_10(line,__VA_ARGS__)
#define _CUPL_watch_12(line, var, ...) cupl::print_main(var, line, #var); _CUPL_watch_11(line,__VA_ARGS__)
#define _CUPL_watch_13(line, var, ...) cupl::print_main(var, line, #var); _CUPL_watch_12(line,__VA_ARGS__)
#define _CUPL_watch_14(line, var, ...) cupl::print_main(var, line, #var); _CUPL_watch_13(line,__VA_ARGS__)
#define _CUPL_watch_15(line, var, ...) cupl::print_main(var, line, #var); _CUPL_watch_14(line,__VA_ARGS__)
#define _CUPL_watch_16(line, var, ...) cupl::print_main(var, line, #var); _CUPL_watch_15(line,__VA_ARGS__)

#define watch(...) \
    _CUPL_GET_NUMBER_OF_WATCH_ARGS_(ignore, ##__VA_ARGS__, \
    _CUPL_watch_16, _CUPL_watch_15,_CUPL_watch_14,_CUPL_watch_13,_CUPL_watch_12,_CUPL_watch_11, \
    _CUPL_watch_10,_CUPL_watch_9 ,_CUPL_watch_8 ,_CUPL_watch_7 ,_CUPL_watch_6 ,_CUPL_watch_5,  \
    _CUPL_watch_4 ,_CUPL_watch_3 ,_CUPL_watch_2 ,_CUPL_watch_1, _CUPL_watch_0)(__LINE__,__VA_ARGS__);

#define watchb(var, ...) \
    cupl::print_main_B(var, __LINE__, #var, __VA_ARGS__, cupl::watchb_placeholder, cupl::watchb_placeholder);

#define watchc(var) \
    cupl::print_main(var, __LINE__, #var, false);

namespace cupl {

    const bool watchb_placeholder = false;

    std::vector<int> array_colours = {COLOUR_ARRAY};

    void checkEncodingCompatibility();

    namespace init { int _int = 0; }

    template <typename T> using is_iterable = decltype(detail::is_iterable_impl<T>(0)); //determines if a variable is iterable

    bool SHOW_TYPE_NAME = 0;    //to hide or show type names next to the variable name
    void showTypes(bool val);   //false - hide, true - show

    template <class T> std::string type_name(); //determines variable type name

    template <typename T> using is_iterable = decltype(cupl::detail::is_iterable_impl<T>(0));

    template <typename T           >  void print_main       (T x      , int line, std::string name, bool print_data = true);
    template <typename T, size_t N >  void print_main       (T (&x)[N], int line, std::string name, bool print_data = true);
    template <typename T           >  void print_main_handle(T &x, std::string name, int line, bool print_data);
    //template <typename T1, typename T2, typename T3, typename T4 = bool, typename T5 = bool>
      //  void print_main_B(T1 x, int line, std::string name, T2 &x2, T3 &x3, T4 &x4, T5 &x5);

    template <typename T> void print_process(T &x);
    template <size_t   S> void print_process(std::bitset<S> &x);
    template <typename U, typename H> void print_process(std::pair<U, H> &x);
    template <typename T> void print_process(std::stack<T> &x);
    template <typename T> void print_process(std::queue<T> &x);
    template <typename T> void print_process(std::priority_queue<T> &x);


    template <typename T, size_t   N > void print_array         (T                    (&x)[N]);
    template <typename T             > void print_iterable      (T                         &x);
    template <typename T             > void print_arithmetic    (T                         &x);
    template <typename T             > void print_class_struct  (T                         &x);
    template <typename T             > void print_pointer       (T                         &x);
    template <typename U, typename H > void print_pair          (std::pair          <U, H> &x);
    template <typename T             > void print_stack         (std::stack         <T   > &x);
    template <typename T             > void print_queue         (std::queue         <T   > &x);
    template <typename T, typename C, typename D> void print_priority_queue(std::priority_queue<T, C, D> &x);
    template <size_t   T             > void print_bitset        (std::bitset        <T   > &x);
                                       void print_string        (std::string               &x);

    int indentation_level = 0;
    std::string indentation = "";
    void indent();
    void unindent();

    std::string colour(int val); //sets foreground ANSI colour
    std::string backgr(int val); //sets background ANSI colour
    std::string bold();          //makes text bold
    std::string clr();           //removes all text effects

    namespace pbt {

        #if CHARACTER_ENCODING == 1
        std::string crv_r = {(char)218, (char)196};
        std::string crv_l = {(char)192, (char)196};
        std::string   str = {(char)179, ' '      };
        #elif CHARACTER_ENCODING == 2
        std::string crv_r = "\u250C\u2500";
        std::string crv_l = "\u2514\u2500";
        std::string   str = "\u2502 ";
        #elif CHARACTER_ENCODING == 3
        std::string crv_r = {'.', '-'            };
        std::string crv_l = {'L', '-'            };
        std::string   str = {'|', ' '            };
        #else
        #warning Incorrect character encoding
        std::string crv_r = {'.', '-'            };
        std::string crv_l = {'L', '-'            };
        std::string   str = {'|', ' '            };
        #endif
        namespace pbt_default {
            int getLeftSon1 (int val) {return val * 2;    }
            int getRightSon1(int val) {return val * 2 + 1;}
        }

    }

    template <typename Tv,
              typename TdoesExist,   typename std::enable_if< (std::is_function<TdoesExist  >::value), TdoesExist  >::type* =nullptr,
              typename TgetValue,    typename std::enable_if< (std::is_function<TgetValue   >::value), TgetValue   >::type* =nullptr,
              typename TgetLeftSon,  typename std::enable_if< (std::is_function<TgetLeftSon >::value), TgetLeftSon >::type* =nullptr,
              typename TgetRightSon, typename std::enable_if< (std::is_function<TgetRightSon>::value), TgetRightSon>::type* =nullptr>
        void print_BinaryTree (std::string middle, std::string upper, Tv v, TdoesExist &doesExist, TgetValue &getValue, TgetLeftSon &getLeftSon, TgetRightSon &getRightSon);

    template <typename Tv,
              typename TdoesExist,   typename std::enable_if< (std::is_function<TdoesExist  >::value), TdoesExist  >::type* =nullptr,
              typename TgetValue,    typename std::enable_if< (std::is_function<TgetValue   >::value), TgetValue   >::type* =nullptr,
              typename TgetLeftSon,  typename std::enable_if< (std::is_function<TgetLeftSon >::value), TgetLeftSon >::type* =nullptr,
              typename TgetRightSon, typename std::enable_if< (std::is_function<TgetRightSon>::value), TgetRightSon>::type* =nullptr>
        void binaryTree_process (Tv v, TdoesExist &doesExist, TgetValue &getValue, TgetLeftSon &getLeftSon, TgetRightSon &getRightSon);
    template <typename Tv,
              typename TdoesExist,   typename std::enable_if< (std::is_function<TdoesExist  >::value), TdoesExist  >::type* =nullptr,
              typename TgetValue,    typename std::enable_if< (std::is_function<TgetValue   >::value), TgetValue   >::type* =nullptr,
              typename TgetLeftSon,  typename std::enable_if<!(std::is_function<TgetLeftSon >::value), TgetLeftSon >::type* =nullptr,
              typename TgetRightSon, typename std::enable_if<!(std::is_function<TgetRightSon>::value), TgetRightSon>::type* =nullptr>
        void binaryTree_process (Tv v, TdoesExist &doesExist, TgetValue &getValue, TgetLeftSon &getLeftSon, TgetRightSon &getRightSon);
    template <typename Tv,
              typename TdoesExist,   typename std::enable_if< (std::is_function<TdoesExist  >::value), TdoesExist  >::type* =nullptr,
              typename TgetValue,    typename std::enable_if< (std::is_function<TgetValue   >::value), TgetValue   >::type* =nullptr,
              typename TgetLeftSon,  typename std::enable_if< (std::is_function<TgetLeftSon >::value), TgetLeftSon >::type* =nullptr,
              typename TgetRightSon, typename std::enable_if<!(std::is_function<TgetRightSon>::value), TgetRightSon>::type* =nullptr>
        void binaryTree_process (Tv v, TdoesExist &doesExist, TgetValue &getValue, TgetLeftSon &getLeftSon, TgetRightSon &getRightSon);
    template <typename Tv,
              typename TdoesExist,   typename std::enable_if<!(std::is_function<TdoesExist  >::value), TdoesExist  >::type* =nullptr,
              typename TgetValue,    typename std::enable_if<!(std::is_function<TgetValue   >::value), TgetValue   >::type* =nullptr,
              typename TgetLeftSon,  typename std::enable_if<!(std::is_function<TgetLeftSon >::value), TgetLeftSon >::type* =nullptr,
              typename TgetRightSon, typename std::enable_if<!(std::is_function<TgetRightSon>::value), TgetRightSon>::type* =nullptr>
        void binaryTree_process(Tv v, TdoesExist &doesExist, TgetValue &getValue, TgetLeftSon &getLeftSon, TgetRightSon &getRightSon);
}

/** =============================================================================
  *                                  Definitions
  * ============================================================================= **/

namespace cupl {

    using namespace std;

    /* ------------------------------------------------------------------------------
     *  Management of showing types of variables
     * ------------------------------------------------------------------------------ */
    void showTypes(bool val) {
        SHOW_TYPE_NAME = val;
    }

    /* ------------------------------------------------------------------------------
     *  Checking character coding compatibility
     * ------------------------------------------------------------------------------ */
    void checkEncodingCompatibility() {
        std::cout << "\nBelow you can see characters encoded using different systems supported by this library. Pick the most similar to the one shown in /screenshots/character_encoding.png\n" << std::endl;

        std::cout << "EXTENDED_ASCII: " << (char)218 << (char)196 << "    " << \
        (char)192 << (char)196 << "    " << (char)179 << "\n\n";

        std::cout << "UNICODE:        \u250C\u2500    \u2514\u2500    \u2502\n\n";

        std::cout << "LEGACY:         .-    L-    |\n";
    }

    /* ------------------------------------------------------------------------------
     *  Indentation management
     * ------------------------------------------------------------------------------ */
    void indent() {
        for (int i = 0; i < 4; ++i)
            indentation.push_back(' ');
        ++indentation_level;
        indentation_level = (indentation_level + array_colours.size()) % array_colours.size();
    }

    void unindent() {
        for (int i = 0; i < 4; ++i)
            indentation.pop_back();
        --indentation_level;
        indentation_level = (indentation_level + array_colours.size()) % array_colours.size();
    }

    /* ------------------------------------------------------------------------------
     *  Colours!
     * ------------------------------------------------------------------------------ */
    std::string colour(int val) { if (ANSIsupport) return "\033[38;5;" + std::to_string(val) + "m"; return ""; }
    std::string backgr(int val) { if (ANSIsupport) return "\033[48;5;" + std::to_string(val) + "m"; return ""; }
    std::string bold  (       ) { if (ANSIsupport) return "\033[1m";                                return ""; }
    std::string clr   (       ) { if (ANSIsupport) return "\033[0m";                                return ""; }

    /* ------------------------------------------------------------------------------
     *  The main function
     * ------------------------------------------------------------------------------ */

     template <typename T1, typename T2, typename T3, typename T4, typename T5>
    void print_main_B(T1 x, int line, std::string name, T2 &x2, T3 &x3, T4 &x4, T5 &x5, ...) {
        std::string name_type = type_name<T1>();
        if (SHOW_TYPE_NAME) {
            std::cout << colour(COLOUR_LINE) << line << colour(15) << ": "\
                      << colour(COLOUR_TYPE_NAME) << name_type << " "\
                      << colour(COLOUR_NAME) << bold() << name << clr()\
                      << colour( 15) << " = ";
        } else {
            std::cout << colour(COLOUR_LINE) << line << colour(15) << ": "\
                      << colour(COLOUR_NAME) << bold() << name << clr()\
                      << colour( 15) << " = ";
        }
        std::cout << endl;
        binaryTree_process(x,x2,x3,x4,x5);
        std::cout << std::endl << clr();
    }

     template <typename T>
    void print_main(T x, int line, std::string name, bool print_data) {
        print_main_handle(x,name,line,print_data);
    }

    template <typename T, size_t N>
    void print_main(T (&x)[N], int line, std::string name, bool print_data) {
        print_main_handle(x,name,line,print_data);
    }

    template <typename T>
    void print_main_handle(T &x, std::string name, int line, bool print_data) {
        std::string name_type = type_name<T>();
        if (SHOW_TYPE_NAME) {
            std::cout << colour(COLOUR_LINE) << line << colour(15) << ": "\
                      << colour(COLOUR_TYPE_NAME) << name_type << " "\
                      << colour(COLOUR_NAME) << bold() << name << clr()\
                      << colour( 15) << " = ";
        } else if(print_data) {
            std::cout << colour(COLOUR_LINE) << line << colour(15) << ": "\
                      << colour(COLOUR_NAME) << bold() << name << clr()\
                      << colour( 15) << " = ";
        }
        print_process(x);
        std::cout << std::endl << clr();
    }


    template <typename T>
    void print_process(T &x){
             if constexpr(is_arithmetic_v <T                     >       ) print_arithmetic    (x);
        else if constexpr(is_array_v      <T                     >       ) print_array         (x);
        else if constexpr(is_pointer_v    <T                     >       ) print_pointer       (x);
        else if constexpr(is_same         <T,string              >::value) print_string        (x);
       /* else if constexpr(is_same         <T,bitset        <S  > >::value) print_bitset        (x);
        else if constexpr(is_same         <T,pair          <U,H> >::value) print_pair          (x);
        else if constexpr(is_same         <T,stack         <U  > >::value) print_stack         (x);
        else if constexpr(is_same         <T,queue         <U  > >::value) print_queue         (x);
        else if constexpr(is_same         <T,priority_queue<U> >::value) print_priority_queue(x);*/
        else if constexpr(is_iterable     <T                     >::value) print_iterable      (x);
        else if constexpr(is_class_v      <T> && !(is_iterable<T>::value)) print_class_struct  (x);
    }

    //temporary solution
     template <size_t S>
    void print_process(bitset<S> &x) {
        print_bitset(x);
    }

    template <typename U, typename H>
    void print_process(pair<U, H> &x) {
        print_pair(x);
    }

    template <typename T>
    void print_process(stack<T> &x) {
        print_stack(x);
    }

    template <typename T>
    void print_process(queue<T> &x) {
        print_queue(x);
    }

    template <typename T>
    void print_process(priority_queue<T> &x) {
       print_priority_queue(x);
    }


    template <typename T, size_t N>
    void print_array(T (&a)[N]){

        bool is_not_last_dimention = is_iterable<decltype(a[0])>::value && int(N) > 0;

        std::cout << colour(array_colours[indentation_level]) << "{ " << clr();
        indent();

         if (is_not_last_dimention)
            std::cout << '\n' << indentation;

        for (int i = 0; i < int(N); ++i) {
            print_process(a[i]);
            if (is_not_last_dimention) {
                std::cout << '\n' << indentation;
            } else {
                std::cout << ' ';
            }
        }

        if (ANSIsupport && is_not_last_dimention)
            std::cout << "\033[4D";

        unindent();
        std::cout << colour(array_colours[indentation_level]) << "}" << clr();
    }

    template <typename T>
    void print_iterable(T &x) {
        std::cout << colour(array_colours[indentation_level]) << "{ " << clr();
        indent();

        if (is_iterable<decltype(*std::begin(x))>::value && std::begin(x) != std::end(x))
            std::cout << '\n' << indentation;

        for (auto e : x) {
            print_process(e);

            if (is_iterable<decltype(*std::begin(x))>::value && std::begin(x) != std::end(x)) {
                std::cout << '\n' << indentation;
            } else {
                std::cout << ' ';
            }
        }

        if (is_iterable<decltype(*std::begin(x))>::value && std::begin(x) != std::end(x) && ANSIsupport)
            std::cout << "\033[4D";

        unindent();
        std::cout << colour(array_colours[indentation_level]) << "}" << clr();
    }

    template <typename T>
    void print_arithmetic(T &x) {
        std::cout << colour(COLOUR_NUMBER) << bold() << x << clr();
    }

    template <size_t T>
    void print_bitset(std::bitset<T> &x) {
        std::cout << colour(COLOUR_BITSET) << bold() << x << clr();
    }

    template <typename T>
    void print_class_struct(T &x) {
        x.print_process();
    }

    template <typename T>
    void print_struct_member(T &x, std::string member_name) {
        print_string(member_name);
        print_process(x);
    }

    template <typename T>
    void print_pointer(T &x) {
        if (x != nullptr)
            print_process(*x);
        else
            std::cout << backgr(COLOUR_BACKGR_NULLPOINTER) << colour(COLOUR_NULLPOINTER) << bold() << "NULL" << clr();
    }

    void print_string(std::string &x) {
        std::cout << colour(COLOUR_STRING) << bold() << "\"" << x << "\"" << clr();
    }

    template <typename U, typename H>
    void print_pair(std::pair<U, H> &x) {
        std::cout << colour(array_colours[indentation_level]) << "(" << clr();
        ++indentation_level;
        print_process(x.first);
        std::cout << ", ";
        print_process(x.second);
        --indentation_level;
        std::cout << colour(array_colours[indentation_level]) << ")" << clr();
    }

    template <typename T>
    void print_stack(std::stack<T> &x) {
        std::stack<T> tmp = x;
        std::vector<T>   result;

        while (!tmp.empty()) {
            result.push_back(tmp.top());
            tmp.pop();
        }

        print_process(result);
    }

    template <typename T>
    void print_queue(std::queue<T> &x) {
        std::queue<T> tmp = x;
        std::vector<T>   result;
        while (!tmp.empty()) {
            result.push_back(tmp.front());
            tmp.pop();
        }
        print_process(result);
    }

    template <typename T, typename C, typename D>
    void print_priority_queue(std::priority_queue<T, C, D> &x) {
        std::priority_queue<T, C, D> tmp = x;
        std::vector<T> result;
        while (!tmp.empty()) {
            result.push_back(tmp.top());
            tmp.pop();
        }
        print_process(result);
    }

     /* ------------------------------------------------------------------------------
     *  Binary trees <3
     * ------------------------------------------------------------------------------ */
    template <typename Tv,
              typename TdoesExist,   typename std::enable_if< (std::is_function<TdoesExist  >::value), TdoesExist  >::type* =nullptr,
              typename TgetValue,    typename std::enable_if< (std::is_function<TgetValue   >::value), TgetValue   >::type* =nullptr,
              typename TgetLeftSon,  typename std::enable_if< (std::is_function<TgetLeftSon >::value), TgetLeftSon >::type* =nullptr,
              typename TgetRightSon, typename std::enable_if< (std::is_function<TgetRightSon>::value), TgetRightSon>::type* =nullptr>
    void print_BinaryTree (std::string middle, std::string upper, Tv v, TdoesExist &doesExist, TgetValue &getValue, TgetLeftSon &getLeftSon, TgetRightSon &getRightSon) {
        std::string s;

        if (doesExist(v)) {
            //Right child
            s = middle;
            if (upper == pbt::crv_r) s = s.replace(s.size() - pbt::str.size(), pbt::str.size(), "  ");
            print_BinaryTree(s + pbt::str, pbt::crv_r, getRightSon(v), doesExist, getValue, getLeftSon, getRightSon);

            //Printing
            s = s.substr(0, middle.size() - pbt::str.size());
            std::cout << colour(COLOUR_BINARY_TREE) << s << upper << clr();
                 if (upper == pbt::crv_l &&  doesExist(getLeftSon(v))) indentation = s + "  " + pbt::str + ' ';
            else if (upper == pbt::crv_l && !doesExist(getLeftSon(v))) indentation = s + "  ";
            else if (upper == pbt::crv_r &&  doesExist(getLeftSon(v))) indentation = s + pbt::str + pbt::str + ' ';
            else if (upper == pbt::crv_r && !doesExist(getLeftSon(v))) indentation = s + pbt::str + ' ';
            else indentation = s;
            indentation = colour(COLOUR_BINARY_TREE) + indentation + clr();
            auto x = getValue(v);
            watchc(x);
            //std::cout<< '\n';

            //Left child
            s = middle;
            if (upper == pbt::crv_l) s = s.replace(s.size() - pbt::str.size(), pbt::str.size(), "  ");
            print_BinaryTree(s + pbt::str, pbt::crv_l, getLeftSon(v), doesExist, getValue, getLeftSon, getRightSon);
        }
        return;
    }

    template <typename Tv,
              typename TdoesExist,   typename std::enable_if< (std::is_function<TdoesExist  >::value), TdoesExist  >::type* =nullptr,
              typename TgetValue,    typename std::enable_if< (std::is_function<TgetValue   >::value), TgetValue   >::type* =nullptr,
              typename TgetLeftSon,  typename std::enable_if< (std::is_function<TgetLeftSon >::value), TgetLeftSon >::type* =nullptr,
              typename TgetRightSon, typename std::enable_if< (std::is_function<TgetRightSon>::value), TgetRightSon>::type* =nullptr>
    void binaryTree_process (Tv v, TdoesExist &doesExist, TgetValue &getValue, TgetLeftSon &getLeftSon, TgetRightSon &getRightSon) {
        print_BinaryTree("", "", v, doesExist, getValue, getLeftSon, getRightSon);
    }

    template <typename Tv,
              typename TdoesExist,   typename std::enable_if< (std::is_function<TdoesExist  >::value), TdoesExist  >::type* =nullptr,
              typename TgetValue,    typename std::enable_if< (std::is_function<TgetValue   >::value), TgetValue   >::type* =nullptr,
              typename TgetLeftSon,  typename std::enable_if< (std::is_function<TgetLeftSon >::value), TgetLeftSon >::type* =nullptr,
              typename TgetRightSon, typename std::enable_if<!(std::is_function<TgetRightSon>::value), TgetRightSon>::type* =nullptr>
    void binaryTree_process (Tv v, TdoesExist &doesExist, TgetValue &getValue, TgetLeftSon &getLeftSon, TgetRightSon &getRightSon) {
        print_BinaryTree("", "", v, doesExist, getValue, getLeftSon, pbt::pbt_default::getRightSon1);
    }
    template <typename Tv,
              typename TdoesExist,   typename std::enable_if< (std::is_function<TdoesExist  >::value), TdoesExist  >::type* =nullptr,
              typename TgetValue,    typename std::enable_if< (std::is_function<TgetValue   >::value), TgetValue   >::type* =nullptr,
              typename TgetLeftSon,  typename std::enable_if<!(std::is_function<TgetLeftSon >::value), TgetLeftSon >::type* =nullptr,
              typename TgetRightSon, typename std::enable_if<!(std::is_function<TgetRightSon>::value), TgetRightSon>::type* =nullptr>
    void binaryTree_process (Tv v, TdoesExist &doesExist, TgetValue &getValue, TgetLeftSon &getLeftSon, TgetRightSon &getRightSon) {
        print_BinaryTree("", "", v, doesExist, getValue, pbt::pbt_default::getLeftSon1, pbt::pbt_default::getRightSon1);
    }
    template <typename Tv,
              typename TdoesExist,   typename std::enable_if<!(std::is_function<TdoesExist  >::value), TdoesExist  >::type* =nullptr,
              typename TgetValue,    typename std::enable_if<!(std::is_function<TgetValue   >::value), TgetValue   >::type* =nullptr,
              typename TgetLeftSon,  typename std::enable_if<!(std::is_function<TgetLeftSon >::value), TgetLeftSon >::type* =nullptr,
              typename TgetRightSon, typename std::enable_if<!(std::is_function<TgetRightSon>::value), TgetRightSon>::type* =nullptr>
    void binaryTree_process(Tv v, TdoesExist &doesExist, TgetValue &getValue, TgetLeftSon &getLeftSon, TgetRightSon &getRightSon) {std::cout << "TOO FEW ARGUMENTS :'(" << std::endl;}
}

/** =============================================================================
  *                                     Start
  * ============================================================================= **/

namespace cupl {

    bool setCoutPrecision = [] {std::cout.precision(STD_COUT_PRECISION); return 0;}();

    /* ------------------------------------------------------------------------------
     *  Informing the user that debug mode is enabled
     * ------------------------------------------------------------------------------ */
    bool print_debug_mode = [] {
#ifdef _MSC_VER
        std::cout << colour(9)\
                  << "/* ------------------------------------------------------------------------------"    << '\n'\
                  << " *                          COMPILED WITH VISUAL STUDIO                          "    << '\n'\
                  << " *    THIS LIBRARY WORKS BADLY WITH THIS IDE AND YOU SHOULD SWITCH IMMEDIATELY   "    << '\n'\
                  << " * ------------------------------------------------------------------------------ */" << '\n' << '\n' << clr();
#endif
        std::cout << colour(COLOUR_DEBUG_MODE_BANNER)\
                  << "/* ------------------------------------------------------------------------------"    << '\n'\
                  << " *                                 DEBUG MODE                                    "    << '\n'\
                  << " * ------------------------------------------------------------------------------ */" << '\n' << clr();
        return 0;
    }();
}
#endif
