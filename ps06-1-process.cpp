template<typename T>
typename T::value_type process(const T &v)
{
    typename T::value_type sum = typename T::value_type();
    auto it = v.rbegin();
    for (int i = 3; i-- && it != v.rend(); ++it)
        sum += *it;
    return sum;
}
