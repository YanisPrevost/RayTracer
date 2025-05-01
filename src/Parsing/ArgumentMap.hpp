/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ArgumentMap
*/

#ifndef ARGUMENTMAP_HPP_
#define ARGUMENTMAP_HPP_
#include <unordered_map>
#include <any>
#include <iostream>
namespace RayTracer {
    class ArgumentMap {
        public:
            ArgumentMap();
            ~ArgumentMap();
            class Assigner {
                public:
                    template <typename T>
                    T &as() {
                        return (std::any_cast<T&> (_val));
                    }

                    Assigner(std::any &val) : _val(val) {}
                    template<typename T>
                    ArgumentMap::Assigner &operator=(T val)
                    {
                        _val = val;
                        return *this;
                    }
                private:
                    std::any &_val;
            };
            Assigner operator[](std::string key);
        protected:
        private:
        std::unordered_map<std::string, std::any> _map;

    };
}
#endif /* !ARGUMENTMAP_HPP_ */
