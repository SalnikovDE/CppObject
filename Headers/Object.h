//
// Created by danil on 03.11.2021.
//


#ifndef OBJECT_OBJECT_H
#define OBJECT_OBJECT_H

#define CPPOBJECT_LOGGING

#ifdef CPPOBJECT_LOGGING

#include <iostream>

#endif

#include <string>
#include <unordered_map>
#include <set>
#include <vector>
#include <exception>
#include <ostream>
#include <functional>

namespace CppObject
{

    class Exception : std::exception
    {
        virtual std::string what() = 0;
    };

    class OutOfRange : Exception
    {
    public:
        explicit OutOfRange(const std::string &s)
        {
            info = s;
#ifdef CPPOBJECT_LOGGING
            std::cout << s << std::endl;
#endif
        }

        virtual std::string what() override
        {
            return info;
        }

    private:
        std::string info;
    };

    class TypeError : Exception
    {
    public:
        explicit TypeError(const std::string &s)
        {
            info = s;
#ifdef CPPOBJECT_LOGGING
            std::cout << s << std::endl;
#endif
        }

        virtual std::string what() override
        {
            return info;
        }

    private:
        std::string info;
    };

    class Object;

    typedef std::vector<Object> List;
    typedef std::unordered_map<std::string, Object> MapType;
    typedef std::function<Object(const Object &, Object *)> Callable;

    class Object
    {
    public:
        Object();

        Object(int);

        Object(double);

        Object(const char *s) : Object(std::string(s))
        {}

        Object(const std::string &);

        explicit Object(const List &);

        explicit Object(const MapType &);

        explicit Object(const Callable &f);

        Object(const Object &);

        static void *allocateObject(const Object &);

        ~Object();


        explicit operator int();

        explicit operator double();

        explicit operator std::string();

        Object &operator[](const std::string &);

        Object &operator[](const char s[])
        {
            return operator[](std::string(s));
        }

        const Object &operator[](const std::string &) const;

        const Object &operator[](const char s[]) const
        {
            return operator[](std::string(s));
        }

        Object &operator[](int);

        const Object &operator[](int) const;

        Object &operator=(const Object &a);

        Object &operator=(const char s[]);

        Object &operator+=(const Object &a);

        Object &operator-=(const Object &a);

        Object &operator*=(const Object &a);

        Object &operator/=(const Object &a);

        friend std::ostream &operator<<(std::ostream &os, const Object &obj);

        // arithmetic

        friend Object operator+(const Object &a, const Object &b);

        friend Object operator-(const Object &a, const Object &b);

        friend Object operator/(const Object &a, const Object &b);

        friend Object operator*(const Object &a, const Object &b);

        // comp operators

        friend bool operator!=(const Object &a, const Object &b);

        friend bool operator==(const Object &a, const Object &b);

        friend bool operator<(const Object &a, const Object &b);

        friend bool operator>(const Object &a, const Object &b);

        friend bool operator<=(const Object &a, const Object &b);

        friend bool operator>=(const Object &a, const Object &b);


        Object &operator++();

        Object &operator--();

        Object operator++(int);

        Object operator--(int);

        Object operator()(const Object &obj = Object{}, Object *self = nullptr);

        static bool isNone(const Object &obj);

        bool has(const std::string &property) const;

        static Object jsonParser(const std::string &json);

        constexpr static const char CallerField[] = "__calley";

        size_t size() const;

    private:

        static Object jsonParser(const char *begin, const char *end);

        constexpr static const double Epsilon = 1e-12; // set to negative if u dont wanna == double comparation;

        enum ContainedType : char
        {
            None,
            Int,
            String,
            Double,
            ObjectType,
            ListType,
            CallableType
        };
        char type;
        void *container;
    };
}


#endif //OBJECT_OBJECT_H
