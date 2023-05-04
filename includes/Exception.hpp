/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-antony.jin
** File description:
** Exception
*/

#ifndef EXCEPTION_HPP
    #define EXCEPTION_HPP
    #include <exception>
    #include <iostream>

class Error : public std::exception {
    public:
        Error(std::string message) {
            _message = message;
        }
        ~Error() {}
        virtual const char* what() const noexcept {
            return _message.c_str();
        }
    private:
        std::string _message;
};

#endif
