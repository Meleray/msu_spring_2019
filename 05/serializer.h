#pragma once

enum class Error{
    NoError,
    CorruptedArchive
};

class Serializer{
    static constexpr char Separator = ' ';
    std::ostream& out_;
public:
    explicit Serializer(std::ostream& out)
        : out_(out)
    {}

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return process(std::forward<ArgsT>(args)...);
    }

private:
    Error process(uint64_t arg)
    {
        out_ << arg;
        return Error::NoError;
    }

    Error process(bool arg)
    {
        if (arg)
            out_ << "true";
        else
            out_ << "false";
        return Error::NoError;
    }

    template <class T, class... ArgsT>
    Error process(T&& arg, ArgsT&&... args)
    {
        if (std::forward<T>(arg) == Error::NoError)
        {
            out_ << Separator;
            return process(std::forward<ArgsT>(args)...);
        }
        else
            return Error::CorruptedArchive;
    }
};


class Deserializer{
    std::istream& in_;
public:
    explicit Deserializer(std::istream& in)
        : in_(in)
    {}

    template <class T>
    Error load(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return process(std::forward<ArgsT>(args)...);
    }

private:
    Error process(uint64_t& arg)
    {
        std::string num;
        in_ >> num;
        std::string::iterator it = num.begin();
        if (it != num.end())
        {
            bool digit = isdigit(*it);
            ++it;
            while(it != num.end() && digit)
            {
                digit = isdigit(*it);
                ++it;
            }
            if (digit)
            {
                int64_t ans = stoi(num);
                if (ans >= 0)
                    arg = ans;
                else
                    return Error::CorruptedArchive;
            }
            else
                return Error::CorruptedArchive;
        }
        else
            return Error::CorruptedArchive;
        return Error::NoError;
    }

    Error process(bool& arg)
    {
        std::string bool_;
        in_ >> bool_;
        if (bool_ == "true")
            arg = true;
        else
        {
            if (bool_ == "false")
                arg = false;
            else
                return Error::CorruptedArchive;
        }
        return Error::NoError;
    }

    template <class T, class... ArgsT>
    Error process(T&& arg, ArgsT&&... args)
    {
        if (process(std::forward<T>(arg)) != Error::NoError)
            return Error::CorruptedArchive;
        else
            return process(std::forward<ArgsT>(args)...);
    }
};
