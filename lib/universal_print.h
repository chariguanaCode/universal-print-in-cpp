/* ==============================================================================
 *
 *  Contributors:
 *      Name:       Adam Jeliński
 *      Nickname:   charodziej
 *
 *      Name:       Kajetan Lewandowski
 *      Nickname:   LegwanXDL
 *
 *  Description:    A library implementing a uniform method of printing variables in C++.
 *                  Mainly intended for competetive programming, to greatly speedup debugging.
 *
 *  Created:        08.04.2019
 *  Last updated:   23.09.2019
 *
 *  Version: 1.1.3
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
        std::string to_string(size_t n) {
            std::ostringstream s;
            s << n;
            return s.str();
        }
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
}

/** =============================================================================
  *                                 Declarations
  * ============================================================================= **/
#define EXTENDED_ASCII 1
#define UNICODE 2
#define LEGACY 3
#define array_extent_push(x, i) if (i<cupl::array_rank) cupl::array_sizes.push(std::extent<decltype(x), i>::value);
#define watch(x, ...) \
    cupl::array_rank = std::rank<decltype(x)>::value;\
    array_extent_push(x, 0);\
    array_extent_push(x, 1);\
    array_extent_push(x, 2);\
    array_extent_push(x, 3);\
    array_extent_push(x, 4);\
    array_extent_push(x, 5);\
    cupl::print_main(x, __LINE__, #x, ##__VA_ARGS__);
#define debug if (1)


namespace cupl {

    std::vector<int> array_colours = {COLOUR_ARRAY};

    void checkEncodingCompatibility();

    namespace init { int _int = 0; }

    template <typename T> using is_iterable = decltype(detail::is_iterable_impl<T>(0)); //determines if a variable is iterable

    bool SHOW_TYPE_NAME = 1;    //to hide or show type names next to the variable name
    void showTypes(bool val);   //false - hide, true - show

    template <class T> std::string type_name(); //determines variable type name

    template <typename T, typename std::enable_if< (std::is_arithmetic<T>::value), T>::type* =nullptr> void print_process(T &x); //for arithmetic variables
    template <typename T, typename std::enable_if< (std::is_class     <T>::value) && \
                                                  !(     is_iterable  <T>::value), T>::type* =nullptr> void print_process(T &x); //for structs and classes
    template <typename T, typename std::enable_if< (std::is_pointer   <T>::value), T>::type* =nullptr> void print_process(T &x); //for pointers
    template <typename T, typename std::enable_if< (     is_iterable  <T>::value), T>::type* =nullptr> void print_process(T &x); //for iterable structures

    std::queue<int> array_sizes;
    unsigned   int  array_rank;
    template <typename T, typename std::enable_if<!(     is_iterable  <T>::value), T>::type* =nullptr> void array_process(T &x, std::queue<int> sizes); //for going thru dimensions
    template <typename T, typename std::enable_if< (     is_iterable  <T>::value), T>::type* =nullptr> void array_process(T &x, std::queue<int> sizes); //for the last dimension

                                                                                                      void print_process(std::string            &x);   //string
    template <size_t   T                                                                            > void print_process(std::bitset<T>         &x);   //bitset
    template <typename T, typename U                                                                > void print_process(std::pair<T, U>        &x);   //pair
    template <typename T                                                                            > void print_process(std::stack<T>          &x);   //stack
    template <typename T                                                                            > void print_process(std::queue<T>          &x);   //queue
    template <typename T                                                                            > void print_process(std::priority_queue<T> &x);   //priority_queue

    int indentation_level = 0;
    std::string indentation = "";
    void indent();
    void unindent();

    std::string colour(int val); //sets foreground ANSI colour
    std::string backgr(int val); //sets background ANSI colour
    std::string bold();          //makes text bold
    std::string clr();           //removes all text effects

    template <typename T, typename Targ1 = int, typename Targ2 = int, typename Targ3 = int, typename Targ4 = int, typename Targ5 = int>
        void print_main(T x, int line, std::string name, int mode = 0, Targ1 arg1 = init::_int, Targ2 &arg2 = init::_int, Targ3 &arg3 = init::_int, Targ4 &arg4 = init::_int, Targ5 &arg5 = init::_int);
    template <typename T, typename std::enable_if< (std::is_pointer   <T>::value), T>::type* =nullptr> void print_array(T &x, std::queue<int> sizes);
    template <typename T, typename std::enable_if<!(std::is_pointer   <T>::value), T>::type* =nullptr> void print_array(T &x, std::queue<int> sizes);

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
     *  Method of determining variables type ( may not be used in the final version )
     *  thx to Howard Hinnant
     *  https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c
     * ------------------------------------------------------------------------------ */
    template <class T> std::string type_name() {
        typedef typename std::remove_reference<T>::type TR;
        std::unique_ptr<char, void(*)(void*)> own
        (
#ifndef _MSC_VER
            abi::__cxa_demangle(typeid(TR).name(), nullptr,
                                nullptr, nullptr),
#else
            nullptr,
#endif
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
     *  The main function doing all the magic
     * ------------------------------------------------------------------------------ */
    template <typename T, typename Targ1, typename Targ2, typename Targ3, typename Targ4, typename Targ5>
    void print_main(T x, int line, std::string name, int mode, Targ1 arg1, Targ2 &arg2, Targ3 &arg3, Targ4 &arg4, Targ5 &arg5) {
        std::string name_type = type_name<T>();
        if (!array_sizes.empty()) {
            size_t pos = name_type.rfind(" (*) ");
            if (pos != std::string::npos) {
                name_type.replace(pos, 5, " [" + std::to_string(array_sizes.front()) + "] ");
            } else {
                pos = name_type.rfind("*");
                if (pos != std::string::npos) name_type.replace(pos, 2, " [" + std::to_string(array_sizes.front()) + "]");
            }
        }
        if (mode == 1) {
            while (!array_sizes.empty()) array_sizes.pop();
        }


        if (mode == 1 || mode == 0 ) {
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
        }
        if (mode == 0) {
            if (array_sizes.empty()) {
                print_process(x);
            } else {
                print_array(x, array_sizes);
                while (!array_sizes.empty()) array_sizes.pop();
            }
            std::cout << std::endl << clr();
        } else if (mode == 1) {
            std::cout << std::endl << clr();
            binaryTree_process(arg1, arg2, arg3, arg4, arg5);
        } else if (mode == 2) {
            if (array_sizes.empty()) {
                print_process(x);
            } else {
                print_array(x, array_sizes);
                while (!array_sizes.empty()) array_sizes.pop();
            }
        }
    }

    /* ------------------------------------------------------------------------------
     *  Helper function required to fix the arrays
     * ------------------------------------------------------------------------------ */
    template <typename T, typename std::enable_if< (std::is_pointer   <T>::value), T>::type* =nullptr>
    void print_array(T &x, std::queue<int> sizes) {
        if (sizes.empty()) { print_process(x); return; }
        int n = sizes.front();
        sizes.pop();

        std::cout << colour(array_colours[indentation_level]) << "{ " << clr();
        indent();

        if (sizes.size() > 0 || (is_iterable<decltype(x[0])>::value && n > 0))
            std::cout << '\n' << indentation;

        for (int i = 0; i < n; ++i) {
            array_process(x[i], sizes);

            if (sizes.size() > 0 || (is_iterable<decltype(x[0])>::value && n > 0)) {
                std::cout << '\n' << indentation;
            } else {
                std::cout << ' ';
            }
        }

        if ((sizes.size() > 0 || (is_iterable<decltype(x[0])>::value && n > 0)) && ANSIsupport)
            std::cout << "\033[4D";

        unindent();
        std::cout << colour(array_colours[indentation_level]) << "}" << clr();
    }

    template <typename T, typename std::enable_if<!(std::is_pointer   <T>::value), T>::type* =nullptr>
    void print_array(T &x, std::queue<int> sizes) {
        ;
    }

    /* ------------------------------------------------------------------------------
     *  Printing numeric variables
     * ------------------------------------------------------------------------------ */
    template <typename T, typename std::enable_if< (std::is_arithmetic<T>::value), T>::type* =nullptr>
    void print_process(T &x) {
        std::cout << colour(COLOUR_NUMBER) << bold() << x << clr();
    }

    /* ------------------------------------------------------------------------------
     *  Printing bitsets ( compatible with std::cout but aren't arithmetic )
     * ------------------------------------------------------------------------------ */
    template <size_t T>
    void print_process(std::bitset<T> &x) {
        std::cout << colour(COLOUR_BITSET) << bold() << x << clr();
    }

    /* ------------------------------------------------------------------------------
     *  Handling structs and classes
     * ------------------------------------------------------------------------------ */
    template <typename T, typename std::enable_if< (std::is_class<T>::value) && !(is_iterable<T>::value), T>::type* =nullptr>
    void print_process(T &x) {
        x.print_process();
    }

    /* ------------------------------------------------------------------------------
     *  Handling pointers
     * ------------------------------------------------------------------------------ */
    template <typename T, typename std::enable_if< (std::is_pointer   <T>::value), T>::type* =nullptr>
    void print_process(T &x) {
        std::cout << colour(COLOUR_POINTER) << bold() << '*' << clr();
        if (x != nullptr)
            print_process(*x);
        else
            std::cout << backgr(COLOUR_BACKGR_NULLPOINTER) << colour(COLOUR_NULLPOINTER) << bold() << "NULL" << clr();
    }

    /* ------------------------------------------------------------------------------
     *  Handling strings ( they are iterable, but shouldn't be shown like arrays )
     * ------------------------------------------------------------------------------ */
    void print_process(std::string &x) {
        std::cout << colour(COLOUR_STRING) << bold() << "\"" << x << "\"" << clr();
    }

    /* ------------------------------------------------------------------------------
     *  Handling pairs
     * ------------------------------------------------------------------------------ */
    template <typename T, typename U>
    void print_process(std::pair<T, U> &x) {
        std::cout << colour(array_colours[indentation_level]) << "(" << clr();
        ++indentation_level;
        print_process(x.first);
        std::cout << ", ";
        print_process(x.second);
        --indentation_level;
        std::cout << colour(array_colours[indentation_level]) << ")" << clr();
    }

    /* ------------------------------------------------------------------------------
     *  Handling stacks
     * ------------------------------------------------------------------------------ */
    template <typename T>
    void print_process(std::stack<T> &x) {
        std::stack<T>  tmp = x;
        std::vector<T> result;

        while (!tmp.empty()) {
            result.push_back(tmp.top());
            tmp.pop();
        }

        print_process(result);
    }

    /* ------------------------------------------------------------------------------
     *  Handling queues
     * ------------------------------------------------------------------------------ */
    template <typename T>
    void print_process(std::queue<T> &x) {
        std::queue<T>  tmp = x;
        std::vector<T> result;

        while (!tmp.empty()) {
            result.push_back(tmp.front());
            tmp.pop();
        }

        print_process(result);
    }

    /* ------------------------------------------------------------------------------
     *  Handling priority queues
     * ------------------------------------------------------------------------------ */
    template <typename T>
    void print_process(std::priority_queue<T> &x) {
        std::priority_queue<T> tmp = x;
        std::vector<T> result;

        while (!tmp.empty()) {
            result.push_back(tmp.top());
            tmp.pop();
        }

        print_process(result);
    }

    /* ------------------------------------------------------------------------------
     *  Iterating over iterable objects
     *  std::rank returns the number of dimensions of a standard array,
     *  allowing us to process multi dimensional arrays
     * ------------------------------------------------------------------------------ */
    template <typename T, typename std::enable_if< (       is_iterable<T>::value), T>::type* =nullptr>
    void print_process(T &x) {
        if (!std::rank<T>::value) {
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
    }

    /* ------------------------------------------------------------------------------
     *  Recursively go through all dimensions of an array
     * ------------------------------------------------------------------------------ */
    template <typename T, typename std::enable_if< (       is_iterable<T>::value), T>::type* =nullptr>
    void array_process(T &x, std::queue<int> sizes) {
        if (sizes.empty()) { print_process(x); return; }
        int n = sizes.front();
        sizes.pop();

        std::cout << colour(array_colours[indentation_level]) << "{ " << clr();
        indent();

        if (sizes.size() > 0 || (is_iterable<decltype(x[0])>::value && n > 0))
            std::cout << '\n' << indentation;

        for (int i = 0; i < n; ++i) {
            array_process(x[i], sizes);

            if (sizes.size() > 0 || (is_iterable<decltype(x[0])>::value && n > 0)) {
                std::cout << '\n' << indentation;
            } else {
                std::cout << ' ';
            }
        }

        if ((sizes.size() > 0 || (is_iterable<decltype(x[0])>::value && n > 0)) && ANSIsupport)
            std::cout << "\033[4D";

        unindent();
        std::cout << colour(array_colours[indentation_level]) << "}" << clr();
    }

    /* ------------------------------------------------------------------------------
     *  When reached the last dimension of an array, print its contents using previously defined methods
     * ------------------------------------------------------------------------------ */
    template <typename T, typename std::enable_if<!(       is_iterable<T>::value), T>::type* =nullptr>
    void array_process(T &x, std::queue<int> sizes) {
        print_process(x);
    }

     /* ------------------------------------------------------------------------------
     *  Binary trees <3
     * ------------------------------------------------------------------------------ */
    template <typename Tv,
              typename TdoesExist,   typename std::enable_if< (std::is_function<TdoesExist  >::value), TdoesExist  >::type* =nullptr,
              typename TgetValue,    typename std::enable_if< (std::is_function<TgetValue   >::value), TgetValue   >::type* =nullptr,
              typename TgetLeftSon,  typename std::enable_if< (std::is_function<TgetLeftSon >::value), TgetLeftSon >::type* =nullptr,
              typename TgetRightSon, typename std::enable_if< (std::is_function<TgetRightSon>::value), TgetRightSon>::type* =nullptr>
    void print_BinaryTree (std::string middle, std::string upper, Tv v, TdoesExist &doesExist, TgetValue &getValue, TgetLeftSon &getLeftSon, TgetRightSon &getRightSon)
    {
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
            watch(x, 2);
            std::cout<< '\n';

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
