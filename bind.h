#ifndef MYBIND_BIND_H
#define MYBIND_BIND_H

#include <utility>
#include <tuple>

template<std::size_t N>
struct placeholder {};

template<typename F, typename... DefArgs>//obj keep + ()
struct bindedFun {
private:
    //<creation>
    template<typename friendF,typename... friendArgs>//only way to create
    friend bindedFun<friendF,friendArgs...>bind(friendF&& func, friendArgs&&... args);

    bindedFun(F &&func, DefArgs &&... args ) : function(std::forward<F>(func)), bf_args(std::forward<DefArgs>(args)...) {}
    F function;
    std::tuple<DefArgs...> bf_args;
    //</creation>

    //<the indices trick>
    template<std::size_t... Indices>
    struct indices {};

    template<std::size_t Num, std::size_t... Indices>
    struct build_indices {
        typedef typename build_indices<Num - 1, Num - 1, Indices...>::type type;
    };
    template<std::size_t... Indices>
    struct build_indices<0, Indices...> {
        typedef indices<Indices...> type;
    };
    //</the indices trick>

    //<merge>
    template<std::size_t Index, typename... AfterArgs>///inserting
    auto &&merge(placeholder<Index>, AfterArgs &&...args) const {
        return std::get<Index>(std::forward_as_tuple(args...));
    };

    template<typename REAL, typename... AfterArgs>///keeping
    auto &&merge(REAL &&value, AfterArgs &&...args) const{
        return value;
    };

    template<typename argF, typename ...argDefArgs, typename ...AfterArgs>//bindedF as arg
    auto merge(bindedFun<argF, argDefArgs...> &argBF, AfterArgs &&... args) const {
        return argBF(std::forward<AfterArgs>(args)...);
    };
    //</merge>

    template<size_t... Indices, typename... AfterArgs>
    auto callFunction(indices<Indices...> inds, AfterArgs &&... args){
        return function(merge(std::get<Indices>(bf_args), std::forward<AfterArgs>(args)...)...);
    };

public:
    template<typename... AfterArgs>
    auto operator()(AfterArgs &&... args) {
        return callFunction(typename build_indices<std::tuple_size<std::tuple<DefArgs...> >::value>::type(), std::forward<AfterArgs>(args)...);
    }
};

template<typename F, typename... Args>//creating
bindedFun<F, Args...> bind(F &&function, Args &&... args) {
    return bindedFun<F, Args...>(std::forward<F>(function), std::forward<Args>(args)...);
};

#endif //MYBIND_BIND_H
